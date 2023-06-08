#include "tcpclientmodel.h"
#include "tcpclientmanager.h"
#include "log.h"
#include "APISgrH/APISgrH.h"
#include "gzjsqlite.h"

TcpClientModel::TcpClientModel(QObject *parent) : QObject(parent)
{

}

void TcpClientModel::countSlot()
{
    qDebug()<<"tcpCM work: "<<QThread::currentThreadId();
    emit Singleton<TcpClientManager>::getInstance().finishedCountSignal();
}

void TcpClientModel::msgParse(const QString _rev_msg)
{
    //当前进程
    QThread::currentThread()->setObjectName("tcp线程");
    Document dom;
    if(!dom.Parse(_rev_msg.toStdString().c_str()).HasParseError()){
        if(domIsGZJprotocol){
            //A2 03 0 网关主动请求（操作码00）
            if(dom[gzj_FunctionC].GetString()==tr(FN_gzjDeviceTI)&&dom[gzj_OperationC].GetString()==tr(OP_gzjRead)&&dom[gzj_AnswerF].GetInt()==AF_gzjNoAnswer){
                A2_03_0(dom);
            }
            //A2 06 0上位机写网关（操作码06）
            if(dom[gzj_FunctionC].GetString()==tr(FN_gzjDeviceTI)&&dom[gzj_OperationC].GetString()==tr(OP_gzjWrite)&&dom[gzj_AnswerF].GetInt()==AF_gzjNoAnswer){
                A2_06_0(dom);
            }

            //TEST测试用命令
            if(dom[gzj_FunctionC].GetString()==tr("TEST")){
                Singleton<GzjSqlite>::getInstance().sqlTest();
            }
        }
    }
}

void TcpClientModel::A2_06_0(Document &dom)
{
    if (dom.HasMember("Data"))
    {
        Value Data;
        Data = dom["Data"];
        QVariantList VL_TN;
        QVariantList VL_PN;
        QVariantList VL_Name;
        QVariantList VL_EnName;
        //先取Array
        if (Data.IsArray() && !Data.Empty())
        {
            rapidjson::Value tempData;
            for (rapidjson::SizeType i = 0; i < Data.Size(); i++)
            {
                tempData = Data[i];
                if (tempData.IsObject())
                {

                    if (tempData.HasMember("TN") && tempData.HasMember("PN")&& tempData.HasMember("Name")&& tempData.HasMember("EnName"))
                    {
                        VL_TN<<tr(tempData["TN"].GetString());
                        VL_PN<<tr(tempData["PN"].GetString());
                        VL_Name<<tr(tempData["Name"].GetString());
                        VL_EnName<<tr(tempData["EnName"].GetString());

                        qDebug()<<tr(tempData["Name"].GetString());
                    }
                }
            }
        }
        Singleton<GzjSqlite>::getInstance().insertDeviceTI(VL_TN,VL_PN,VL_Name,VL_EnName);
    }
}

void TcpClientModel::A2_03_0(Document &dom)
{
    dom.HasMember("RN");
    Document send_dom;
    Document::AllocatorType& allocator=send_dom.GetAllocator();
    rapidjson::Value str_value(rapidjson::kStringType);
    str_value.SetString(dom[gzj_RequestC].GetString(),allocator);
    send_dom.SetObject();
    send_dom.AddMember(gzj_RequestC, str_value, allocator);
    send_dom.AddMember(gzj_ProtocolV, Ver_gzjVersion, allocator);
    send_dom.AddMember(gzj_FunctionC, FN_gzjDeviceTI, allocator);
    send_dom.AddMember(gzj_OperationC, OP_gzjRead, allocator);
    send_dom.AddMember(gzj_FunctionC, AF_gjzAnswerData, allocator);

    QSqlQuery sql_query(Singleton<GzjSqlite>::getInstance().sqlDatabase);
    QString select_sql = "select TN ,PN ,Name ,EnName from deviceTI";

    if(!sql_query.exec(select_sql)){
        Singleton<Log>::getInstance().debug("exec fail: "+sql_query.lastError().text());
    }
    else
    {
        Value DataArray(rapidjson::kArrayType);
        while(sql_query.next())
        {
            Value Data(rapidjson::kObjectType);
            str_value.SetString(sql_query.value(0).toString().toStdString().c_str(), allocator);
            Data.AddMember("TN", str_value, allocator);
            str_value.SetString(sql_query.value(1).toString().toStdString().c_str(), allocator);
            Data.AddMember("PN", str_value, allocator);
            str_value.SetString(sql_query.value(2).toString().toStdString().c_str(), allocator);
            Data.AddMember("Name", str_value, allocator);
            str_value.SetString(sql_query.value(3).toString().toStdString().c_str(), allocator);
            Data.AddMember("EnName", str_value, allocator);
            DataArray.PushBack(Data, allocator);
        }
        send_dom.AddMember("Data", DataArray, allocator);
    }
    StringBuffer buf;
    Writer<rapidjson::StringBuffer> writer(buf);
    send_dom.Accept(writer);
    emit Singleton<TcpClientManager>::getInstance().modelSend(buf.GetString());
    qDebug()<<buf.GetString();
}
