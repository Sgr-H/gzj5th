#include "tcpclientmodel.h"
#include "tcpclientmanager.h"
#include "APISgrH/APISgrH.h"
#include "gzjsqlite.h"

rapidjson::Value str_value_rj(rapidjson::kStringType);
TcpClientModel::TcpClientModel(QObject *parent) : QObject(parent)
{

}

void TcpClientModel::countSlot()
{
    qDebug()<<"tcpCM work: "<<QThread::currentThreadId();
    emit Singleton<TcpClientManager>::getInstance().finishedCountSignal();
}

void TcpClientModel::msgParse(const QString &_rev_msg)
{
    //当前进程
    QThread::currentThread()->setObjectName("tcp线程");
    Document dom;
    if(!dom.Parse(_rev_msg.toStdString().c_str()).HasParseError()){
        if(domIsGZJprotocol){
            //A2 00 2 网关主动请求（操作码00）
            if(dom[gzj_FunctionC].GetString()==tr(FN_gzjDeviceTI)&&dom[gzj_OperationC].GetString()==tr(OP_gzjNone)&&dom[gzj_AnswerF].GetInt()==AF_gjzAnswerData){
                A2_00_2(dom);
            }
            //A2 03 0 上位机读请求（操作码03）
            if(dom[gzj_FunctionC].GetString()==tr(FN_gzjDeviceTI)&&dom[gzj_OperationC].GetString()==tr(OP_gzjRead)&&dom[gzj_AnswerF].GetInt()==AF_gzjNoAnswer){
                A2_03_0(dom);
            }
            //A2 06 0 上位机写网关（操作码06）
            if(dom[gzj_FunctionC].GetString()==tr(FN_gzjDeviceTI)&&dom[gzj_OperationC].GetString()==tr(OP_gzjWrite)&&dom[gzj_AnswerF].GetInt()==AF_gzjNoAnswer){
                A2_06_0(dom);
            }
            //A3 00 2 网关主动请求（操作码00）
            if(dom[gzj_FunctionC].GetString()==tr(FN_gzjTargetTI)&&dom[gzj_OperationC].GetString()==tr(OP_gzjNone)&&dom[gzj_AnswerF].GetInt()==AF_gjzAnswerData){
                A3_00_2(dom);
            }
            //A3 03 0 上位机读请求（操作码03）
            if(dom[gzj_FunctionC].GetString()==tr(FN_gzjTargetTI)&&dom[gzj_OperationC].GetString()==tr(OP_gzjRead)&&dom[gzj_AnswerF].GetInt()==AF_gzjNoAnswer){
                A3_03_0(dom);
            }
            //A3 06 0 上位机写请求（操作码06）
            if(dom[gzj_FunctionC].GetString()==tr(FN_gzjTargetTI)&&dom[gzj_OperationC].GetString()==tr(OP_gzjWrite)&&dom[gzj_AnswerF].GetInt()==AF_gzjNoAnswer){
                A3_06_0(dom);
            }
            //A4 00 2 网关主动请求（操作码00）
            if(dom[gzj_FunctionC].GetString()==tr(FN_gzjDeviceMI)&&dom[gzj_OperationC].GetString()==tr(OP_gzjNone)&&dom[gzj_AnswerF].GetInt()==AF_gjzAnswerData){

                A4_00_2(dom);
            }
            //A4 03 0 上位机读请求（操作码03）
            if(dom[gzj_FunctionC].GetString()==tr(FN_gzjDeviceMI)&&dom[gzj_OperationC].GetString()==tr(OP_gzjRead)&&dom[gzj_AnswerF].GetInt()==AF_gzjNoAnswer){
                A4_03_0(dom);
            }
            //A4 06 0 上位机写请求（操作码06）
            if(dom[gzj_FunctionC].GetString()==tr(FN_gzjDeviceMI)&&dom[gzj_OperationC].GetString()==tr(OP_gzjWrite)&&dom[gzj_AnswerF].GetInt()==AF_gzjNoAnswer){
                A4_06_0(dom);
            }
            //A5 00 2 网关主动请求（操作码00）
            if(dom[gzj_FunctionC].GetString()==tr(FN_gzjCircCT)&&dom[gzj_OperationC].GetString()==tr(OP_gzjNone)&&dom[gzj_AnswerF].GetInt()==AF_gjzAnswerData){
                A5_00_2(dom);
            }
            //A5 03 0 上位机读请求（操作码03）
            if(dom[gzj_FunctionC].GetString()==tr(FN_gzjCircCT)&&dom[gzj_OperationC].GetString()==tr(OP_gzjRead)&&dom[gzj_AnswerF].GetInt()==AF_gzjNoAnswer){
                A5_03_0(dom);
            }
            //A5 06 0 上位机写请求（操作码06）
            if(dom[gzj_FunctionC].GetString()==tr(FN_gzjCircCT)&&dom[gzj_OperationC].GetString()==tr(OP_gzjWrite)&&dom[gzj_AnswerF].GetInt()==AF_gzjNoAnswer){
                A5_06_0(dom);
            }
            //B1 03 0 固件版本读取指令B1
            if(dom[gzj_FunctionC].GetString()==tr(FN_gzjFireware)&&dom[gzj_OperationC].GetString()==tr(OP_gzjRead)&&dom[gzj_AnswerF].GetInt()==AF_gzjNoAnswer){
                B1_03_0(dom);
            }
            //B2 03 0 硬件版本读取指令B2
            if(dom[gzj_FunctionC].GetString()==tr(FN_gzjHadrware)&&dom[gzj_OperationC].GetString()==tr(OP_gzjRead)&&dom[gzj_AnswerF].GetInt()==AF_gzjNoAnswer){
                B2_03_0(dom);
            }
            //B3 03 0 电池电压状态读取指令B3
            if(dom[gzj_FunctionC].GetString()==tr(FN_gzjBatteryVS)&&dom[gzj_OperationC].GetString()==tr(OP_gzjRead)&&dom[gzj_AnswerF].GetInt()==AF_gzjNoAnswer){
                B3_03_0(dom);
            }
            //B4 03 0 电源供电状态读取指令B4
            if(dom[gzj_FunctionC].GetString()==tr(FN_gzjPowerCS)&&dom[gzj_OperationC].GetString()==tr(OP_gzjRead)&&dom[gzj_AnswerF].GetInt()==AF_gzjNoAnswer){
                B4_03_0(dom);
            }
            //C1 03 0 时间同步（操作码03）
            if(dom[gzj_FunctionC].GetString()==tr(FN_gzjTimeSync)&&dom[gzj_OperationC].GetString()==tr(OP_gzjRead)&&dom[gzj_AnswerF].GetInt()==AF_gzjNoAnswer){
                C1_03_0(dom);
            }
            //C1 06 0 时间同步（操作码06）
            if(dom[gzj_FunctionC].GetString()==tr(FN_gzjTimeSync)&&dom[gzj_OperationC].GetString()==tr(OP_gzjWrite)&&dom[gzj_AnswerF].GetInt()==AF_gzjNoAnswer){
                C1_06_0(dom);
            }
            //C1 03 0 读串口配置（操作码03）
            if(dom[gzj_FunctionC].GetString()==tr(FN_gzjSeriS)&&dom[gzj_OperationC].GetString()==tr(OP_gzjRead)&&dom[gzj_AnswerF].GetInt()==AF_gzjNoAnswer){
                C2_03_0(_rev_msg);
            }
            //C1 06 0 写串口配置（操作码06）
            if(dom[gzj_FunctionC].GetString()==tr(FN_gzjSeriS)&&dom[gzj_OperationC].GetString()==tr(OP_gzjWrite)&&dom[gzj_AnswerF].GetInt()==AF_gzjNoAnswer){
                C2_06_0(dom);
            }

            //sqlTEST测试用命令
            if(dom[gzj_FunctionC].GetString()==tr("TEST")){
                Singleton<GzjSqlite>::getInstance().sqlTest(tr(dom[gzj_OperationC].GetString()));
            }
        }
    }
}
//A2 00 2 网关主动请求（操作码00）
void TcpClientModel::A2_00_2(Document &dom)
{
    if (dom.HasMember("Data"))
    {
        Value Data;
        Data = dom["Data"];
        struct_deviceTI structDTI;
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
                        structDTI.VL_TN<<tr(tempData["TN"].GetString());
                        structDTI.VL_PN<<tr(tempData["PN"].GetString());
                        structDTI.VL_Name<<tr(tempData["Name"].GetString());
                        structDTI.VL_EnName<<tr(tempData["EnName"].GetString());

                        qDebug()<<tr(tempData["Name"].GetString());
                    }
                }
            }
        }
        Singleton<GzjSqlite>::getInstance().insertDeviceTI(structDTI);
    }
}
//A2 06 0 上位机写网关（操作码06）
void TcpClientModel::A2_06_0(Document &dom)
{
    Document send_dom;
    Document::AllocatorType& allocator=send_dom.GetAllocator();
    str_value_rj.SetString(dom[gzj_RequestC].GetString(),allocator);
    send_dom.SetObject();
    send_dom.AddMember(gzj_RequestC, str_value_rj, allocator);
    send_dom.AddMember(gzj_ProtocolV, Ver_gzjVersion, allocator);
    send_dom.AddMember(gzj_FunctionC, FN_gzjDeviceTI, allocator);
    send_dom.AddMember(gzj_OperationC, OP_gzjWrite, allocator);
    send_dom.AddMember(gzj_FunctionC, AF_gzjAnswerNoData, allocator);
    send_dom.AddMember(gzj_Result, Result_gzjSuccess, allocator);
    send_dom.AddMember(gzj_ErrorC, EC_gzjNoEC, allocator);

    if (dom.HasMember("Data"))
    {
        Value Data;
        Data = dom["Data"];
        struct_deviceTI structDTI;
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
                        structDTI.VL_TN<<tr(tempData["TN"].GetString());
                        structDTI.VL_PN<<tr(tempData["PN"].GetString());
                        structDTI.VL_Name<<tr(tempData["Name"].GetString());
                        structDTI.VL_EnName<<tr(tempData["EnName"].GetString());

                        qDebug()<<tr(tempData["Name"].GetString());
                    }
                }
            }
        }
        Singleton<GzjSqlite>::getInstance().insertDeviceTI(structDTI);
    }
    StringBuffer buf;
    Writer<rapidjson::StringBuffer> writer(buf);
    send_dom.Accept(writer);
    QByteArray ba_data(buf.GetString());
    emit Singleton<TcpClientManager>::getInstance().modelSend(ba_data);
}
//A2 03 0 上位机读网关（操作码03）
void TcpClientModel::A2_03_0(Document &dom)
{
    Document send_dom;
    Document::AllocatorType& allocator=send_dom.GetAllocator();
    str_value_rj.SetString(dom[gzj_RequestC].GetString(),allocator);
    send_dom.SetObject();
    send_dom.AddMember(gzj_RequestC, str_value_rj, allocator);
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
            str_value_rj.SetString(sql_query.value(0).toString().toStdString().c_str(), allocator);
            Data.AddMember("TN", str_value_rj, allocator);
            str_value_rj.SetString(sql_query.value(1).toString().toStdString().c_str(), allocator);
            Data.AddMember("PN", str_value_rj, allocator);
            str_value_rj.SetString(sql_query.value(2).toString().toStdString().c_str(), allocator);
            Data.AddMember("Name", str_value_rj, allocator);
            str_value_rj.SetString(sql_query.value(3).toString().toStdString().c_str(), allocator);
            Data.AddMember("EnName", str_value_rj, allocator);
            DataArray.PushBack(Data, allocator);
        }
        send_dom.AddMember("Data", DataArray, allocator);
    }
    StringBuffer buf;
    Writer<rapidjson::StringBuffer> writer(buf);
    send_dom.Accept(writer);
    QByteArray ba_data(buf.GetString());
    emit Singleton<TcpClientManager>::getInstance().modelSend(ba_data);
}

//A3 00 2 网关主动请求（操作码00）
void TcpClientModel::A3_00_2(Document &dom)
{
    if (dom.HasMember("Data"))
    {
        Value Data;
        Data = dom["Data"];
        struct_targetTI structTTI;
        //先取Array
        if (Data.IsArray() && !Data.Empty())
        {
            rapidjson::Value tempData;
            for (rapidjson::SizeType i = 0; i < Data.Size(); i++)
            {
                tempData = Data[i];
                if (tempData.IsObject())
                {

                    if (tempData.HasMember("TN") && tempData.HasMember("Type")&& tempData.HasMember("Name")&&
                            tempData.HasMember("EnName")&& tempData.HasMember("Unit"))
                    {
                        structTTI.VL_TN<<tr(tempData["TN"].GetString());
                        structTTI.VL_Type<<tempData["Type"].GetInt();
                        structTTI.VL_Name<<tr(tempData["Name"].GetString());
                        structTTI.VL_EnName<<tr(tempData["EnName"].GetString());
                        structTTI.VL_Unit<<tr(tempData["Unit"].GetString());

                        qDebug()<<tr(tempData["Name"].GetString());
                    }
                }
            }
        }
        Singleton<GzjSqlite>::getInstance().insertTargetTI(structTTI);
    }
}
//A3 03 0 上位机读网关（操作码03）
void TcpClientModel::A3_03_0(Document &dom)
{
    Document send_dom;
    Document::AllocatorType& allocator=send_dom.GetAllocator();
    str_value_rj.SetString(dom[gzj_RequestC].GetString(),allocator);
    send_dom.SetObject();
    send_dom.AddMember(gzj_RequestC, str_value_rj, allocator);
    send_dom.AddMember(gzj_ProtocolV, Ver_gzjVersion, allocator);
    send_dom.AddMember(gzj_FunctionC, FN_gzjTargetTI, allocator);
    send_dom.AddMember(gzj_OperationC, OP_gzjRead, allocator);
    send_dom.AddMember(gzj_FunctionC, AF_gjzAnswerData, allocator);

    QSqlQuery sql_query(Singleton<GzjSqlite>::getInstance().sqlDatabase);
    QString select_sql = "select TN ,Type ,Name ,EnName ,Unit from targetTI";

    if(!sql_query.exec(select_sql)){
        Singleton<Log>::getInstance().debug("exec fail: "+sql_query.lastError().text());
    }
    else
    {
        Value DataArray(rapidjson::kArrayType);
        while(sql_query.next())
        {
            Value Data(rapidjson::kObjectType);
            str_value_rj.SetString(sql_query.value(0).toString().toStdString().c_str(), allocator);
            Data.AddMember("TN", str_value_rj, allocator);
            str_value_rj.SetInt(sql_query.value(1).toInt());
            Data.AddMember("Type", str_value_rj, allocator);
            str_value_rj.SetString(sql_query.value(2).toString().toStdString().c_str(), allocator);
            Data.AddMember("Name", str_value_rj, allocator);
            str_value_rj.SetString(sql_query.value(3).toString().toStdString().c_str(), allocator);
            Data.AddMember("EnName", str_value_rj, allocator);
            str_value_rj.SetString(sql_query.value(4).toString().toStdString().c_str(), allocator);
            Data.AddMember("Unit", str_value_rj, allocator);
            DataArray.PushBack(Data, allocator);
        }
        send_dom.AddMember("Data", DataArray, allocator);
    }
    StringBuffer buf;
    Writer<rapidjson::StringBuffer> writer(buf);
    send_dom.Accept(writer);
    QByteArray ba_data(buf.GetString());
    emit Singleton<TcpClientManager>::getInstance().modelSend(ba_data);
}
//A3 06 0 上位机写网关（操作码06）
void TcpClientModel::A3_06_0(Document &dom)
{
    Document send_dom;
    Document::AllocatorType& allocator=send_dom.GetAllocator();
    str_value_rj.SetString(dom[gzj_RequestC].GetString(),allocator);
    send_dom.SetObject();
    send_dom.AddMember(gzj_RequestC, str_value_rj, allocator);
    send_dom.AddMember(gzj_ProtocolV, Ver_gzjVersion, allocator);
    send_dom.AddMember(gzj_FunctionC, FN_gzjTargetTI, allocator);
    send_dom.AddMember(gzj_OperationC, OP_gzjWrite, allocator);
    send_dom.AddMember(gzj_FunctionC, AF_gzjAnswerNoData, allocator);
    send_dom.AddMember(gzj_Result, Result_gzjSuccess, allocator);
    send_dom.AddMember(gzj_ErrorC, EC_gzjNoEC, allocator);
    if (dom.HasMember("Data"))
    {
        Value Data;
        Data = dom["Data"];
        struct_targetTI structTTI;
        //先取Array
        if (Data.IsArray() && !Data.Empty())
        {
            rapidjson::Value tempData;
            for (rapidjson::SizeType i = 0; i < Data.Size(); i++)
            {
                tempData = Data[i];
                if (tempData.IsObject())
                {

                    if (tempData.HasMember("TN") && tempData.HasMember("Type")&& tempData.HasMember("Name")&&
                            tempData.HasMember("EnName")&& tempData.HasMember("Unit"))
                    {
                        structTTI.VL_TN<<tr(tempData["TN"].GetString());
                        structTTI.VL_Type<<tempData["Type"].GetInt();
                        structTTI.VL_Name<<tr(tempData["Name"].GetString());
                        structTTI.VL_EnName<<tr(tempData["EnName"].GetString());
                        structTTI.VL_Unit<<tr(tempData["Unit"].GetString());

                        qDebug()<<tr(tempData["Name"].GetString());
                    }
                }
            }
        }
        Singleton<GzjSqlite>::getInstance().insertTargetTI(structTTI);
    }
    StringBuffer buf;
    Writer<rapidjson::StringBuffer> writer(buf);
    send_dom.Accept(writer);
    QByteArray ba_data(buf.GetString());
    emit Singleton<TcpClientManager>::getInstance().modelSend(ba_data);

}

//A4 00 2 网关主动请求（操作码00)
void TcpClientModel::A4_00_2(Document &dom)
{
    Document copyDom;
    //深拷贝
    copyDom.CopyFrom(dom,copyDom.GetAllocator());
    Value DataFile;
    DataFile=copyDom["Data"];
    if (dom.HasMember("Data"))
    {
        Value Data;
        Data = dom["Data"];
        struct_deviceMIF structDMIF;
        struct_analyticP structAP;
        //先取Array
        if (Data.IsArray() && !Data.Empty())
        {
            rapidjson::Value tempData;
            for (rapidjson::SizeType i = 0; i < Data.Size(); i++)
            {
                tempData = Data[i];
                if (tempData.IsObject())
                {

                    if (tempData.HasMember("TN") && tempData.HasMember("IT")&& tempData.HasMember("PN")
                            && tempData.HasMember("CMD")&& tempData.HasMember("PS")&& tempData.HasMember("AP"))
                    {
                        structDMIF.VL_TN<<tempData["TN"].GetInt();
                        structDMIF.VL_IT<<tr(tempData["IT"].GetString());
                        structDMIF.VL_PN<<tempData["PN"].GetInt();
                        structDMIF.VL_CMD<<tr(tempData["CMD"].GetString());
                        structDMIF.VL_PS<<tempData["PS"].GetInt();

                        Value Data2;
                        Data2 = tempData["AP"];
                        if (Data2.IsArray() && !Data2.Empty())
                        {
                            Value tempData2;
                            for (rapidjson::SizeType i = 0; i < Data2.Size(); i++)
                            {
                                tempData2 = Data2[i];
                                if (tempData2.IsObject())
                                {
                                    if (tempData2.HasMember("TN") && tempData2.HasMember("IT")&& tempData2.HasMember("PN")
                                            && tempData2.HasMember("CMD")&& tempData2.HasMember("PS")&& tempData2.HasMember("AP"))
                                    {
                                        structAP.VL_RB=tempData2["RB"].GetInt();
                                        structAP.VL_PB=tempData2["PB"].GetInt();
                                        structAP.VL_TM=tempData2["TM"].GetInt();
                                        structAP.VL_SI=tr(tempData2["SI"].GetString());
                                        structAP.VL_DL=tempData2["DL"].GetInt();
                                        structAP.VL_DT=tr(tempData2["DT"].GetString());
                                        structAP.VL_Formula=tr(tempData2["Formula"].GetString());
                                        structAP.VL_UL=tempData2["UL"].GetDouble();
                                        structAP.VL_LL=tempData2["LL"].GetDouble();
                                    }
                                }
                            }
                        }
                        structDMIF.VL_AP<<structAP;

                        qDebug()<<tr(tempData["IT"].GetString());
                    }
                }
            }
        }
        APISgrH::set_deviceMIF(structDMIF);
        //文件操作
        Document jDDMI;
        Document::AllocatorType& allocator=jDDMI.GetAllocator();
        jDDMI.SetObject();
        jDDMI.AddMember("Data",DataFile,allocator);
        StringBuffer buf;
        PrettyWriter<rapidjson::StringBuffer> writer(buf);
        jDDMI.Accept(writer);
        QString fileDir = QCoreApplication::applicationDirPath() + "/etc/JsonDeviceMI.txt";
        QFile file(fileDir);
        //对文件进行写操作
        if(!file.open(QIODevice::WriteOnly)){
            qDebug()<<"文件打开失败";
        }
        //向文件中写入字符串
        file.write(buf.GetString());
        //关闭文件
        file.close();

    }




    /*数据库操作
    if (dom.HasMember("Data"))
    {
        Value Data;
        Data = dom["Data"];
        struct_deviceMI structDMI;
        //先取Array
        if (Data.IsArray() && !Data.Empty())
        {
            rapidjson::Value tempData;
            for (rapidjson::SizeType i = 0; i < Data.Size(); i++)
            {
                tempData = Data[i];
                if (tempData.IsObject())
                {

                    if (tempData.HasMember("TN") && tempData.HasMember("IT")&& tempData.HasMember("PN")
                            && tempData.HasMember("CMD")&& tempData.HasMember("PS")&& tempData.HasMember("RB")
                            && tempData.HasMember("PB")&& tempData.HasMember("TM")&& tempData.HasMember("SI")
                            && tempData.HasMember("DL")&& tempData.HasMember("DT")&& tempData.HasMember("Formula")
                            && tempData.HasMember("UL")&& tempData.HasMember("LL"))
                    {
                        structDMI.VL_TN<<tempData["TN"].GetInt();
                        structDMI.VL_IT<<tr(tempData["IT"].GetString());
                        structDMI.VL_PN<<tempData["PN"].GetInt();
                        structDMI.VL_CMD<<tr(tempData["CMD"].GetString());
                        structDMI.VL_PS<<tempData["PS"].GetInt();
                        structDMI.VL_RB<<tempData["RB"].GetInt();
                        structDMI.VL_PB<<tempData["PB"].GetInt();
                        structDMI.VL_TM<<tempData["TM"].GetInt();
                        structDMI.VL_SI<<tr(tempData["SI"].GetString());
                        structDMI.VL_DL<<tempData["DL"].GetInt();
                        structDMI.VL_DT<<tr(tempData["DT"].GetString());
                        structDMI.VL_Formula<<tr(tempData["Formula"].GetString());
                        structDMI.VL_UL<<tempData["UL"].GetDouble();
                        structDMI.VL_LL<<tempData["LL"].GetDouble();

                        qDebug()<<tr(tempData["IT"].GetString());
                    }
                }
            }
        }
        Singleton<GzjSqlite>::getInstance().insertDeviceMI(structDMI);
    }
*/
}
//A4 03 0 上位机读网关（操作码03）
void TcpClientModel::A4_03_0(Document &dom)
{
    //文件操作
    Document send_dom;
    Document::AllocatorType& allocator=send_dom.GetAllocator();
    str_value_rj.SetString(dom[gzj_RequestC].GetString(),allocator);
    send_dom.SetObject();
    send_dom.AddMember(gzj_RequestC, str_value_rj, allocator);
    send_dom.AddMember(gzj_ProtocolV, Ver_gzjVersion, allocator);
    send_dom.AddMember(gzj_FunctionC, FN_gzjDeviceMI, allocator);
    send_dom.AddMember(gzj_OperationC, OP_gzjRead, allocator);
    send_dom.AddMember(gzj_FunctionC, AF_gjzAnswerData, allocator);

    QString fileDir = QCoreApplication::applicationDirPath() + "/etc/JsonDeviceMI.txt";
    QFile file(fileDir);
    //对文件进行写操作
    if(!file.open(QIODevice::ReadOnly)){
        qDebug()<<"文件打开失败";
    }
    //文件中读json字符串
    QByteArray dataDMIF;
    dataDMIF=file.readAll();
    Document DDMIF;
    if(!DDMIF.Parse(dataDMIF.toStdString().c_str()).HasParseError()){
        if(DDMIF.HasMember("Data")){
            Value DataArray(rapidjson::kArrayType);
            DataArray=DDMIF["Data"];
            send_dom.AddMember("Data", DataArray, allocator);
        }
    }
    //关闭文件
    file.close();


    StringBuffer buf;
    Writer<rapidjson::StringBuffer> writer(buf);
    send_dom.Accept(writer);
    QByteArray ba_data(buf.GetString());
    emit Singleton<TcpClientManager>::getInstance().modelSend(ba_data);
    /*
    Document send_dom;
    Document::AllocatorType& allocator=send_dom.GetAllocator();
    str_value_rj.SetString(dom[gzj_RequestC].GetString(),allocator);
    send_dom.SetObject();
    send_dom.AddMember(gzj_RequestC, str_value_rj, allocator);
    send_dom.AddMember(gzj_ProtocolV, Ver_gzjVersion, allocator);
    send_dom.AddMember(gzj_FunctionC, FN_gzjDeviceMI, allocator);
    send_dom.AddMember(gzj_OperationC, OP_gzjRead, allocator);
    send_dom.AddMember(gzj_FunctionC, AF_gjzAnswerData, allocator);

    QSqlQuery sql_query(Singleton<GzjSqlite>::getInstance().sqlDatabase);
    QString select_sql = "select TN ,IT ,PN ,CMD ,PS ,RB ,PB ,TM ,SI ,DL ,DT ,Formula ,UL ,LL from deviceMI";

    if(!sql_query.exec(select_sql)){
        Singleton<Log>::getInstance().debug("exec fail: "+sql_query.lastError().text());
    }
    else
    {
        Value DataArray(rapidjson::kArrayType);
        while(sql_query.next())
        {
            Value Data(rapidjson::kObjectType);
            str_value_rj.SetInt(sql_query.value(0).toInt());
            Data.AddMember("TN", str_value_rj, allocator);
            str_value_rj.SetString(sql_query.value(1).toString().toStdString().c_str(), allocator);
            Data.AddMember("IT", str_value_rj, allocator);
            str_value_rj.SetInt(sql_query.value(2).toInt());
            Data.AddMember("PN", str_value_rj, allocator);
            str_value_rj.SetString(sql_query.value(3).toString().toStdString().c_str(), allocator);
            Data.AddMember("CMD", str_value_rj, allocator);
            str_value_rj.SetInt(sql_query.value(4).toInt());
            Data.AddMember("PS", str_value_rj, allocator);
            str_value_rj.SetInt(sql_query.value(5).toInt());
            Data.AddMember("RB", str_value_rj, allocator);
            str_value_rj.SetInt(sql_query.value(6).toInt());
            Data.AddMember("PB", str_value_rj, allocator);
            str_value_rj.SetInt(sql_query.value(7).toInt());
            Data.AddMember("TM", str_value_rj, allocator);
            str_value_rj.SetString(sql_query.value(8).toString().toStdString().c_str(), allocator);
            Data.AddMember("SI", str_value_rj, allocator);
            str_value_rj.SetInt(sql_query.value(9).toInt());
            Data.AddMember("DL", str_value_rj, allocator);
            str_value_rj.SetString(sql_query.value(10).toString().toStdString().c_str(), allocator);
            Data.AddMember("DT", str_value_rj, allocator);
            str_value_rj.SetString(sql_query.value(11).toString().toStdString().c_str(), allocator);
            Data.AddMember("Formula", str_value_rj, allocator);
            str_value_rj.SetInt(sql_query.value(12).toDouble());
            Data.AddMember("UL", str_value_rj, allocator);
            str_value_rj.SetInt(sql_query.value(13).toDouble());
            Data.AddMember("LL", str_value_rj, allocator);

            DataArray.PushBack(Data, allocator);
        }
        send_dom.AddMember("Data", DataArray, allocator);
    }
    StringBuffer buf;
    Writer<rapidjson::StringBuffer> writer(buf);
    send_dom.Accept(writer);
    QByteArray ba_data(buf.GetString());
    emit Singleton<TcpClientManager>::getInstance().modelSend(ba_data);
    */
}
//A4 06 0 上位机写网关（操作码06）
void TcpClientModel::A4_06_0(Document &dom)
{
    //文件操作
    Document copyDom;
    copyDom.CopyFrom(dom,copyDom.GetAllocator());
    Value DataFile;
    DataFile=copyDom["Data"];
    Document send_dom;
    Document::AllocatorType& allocator=send_dom.GetAllocator();
    str_value_rj.SetString(dom[gzj_RequestC].GetString(),allocator);
    send_dom.SetObject();
    send_dom.AddMember(gzj_RequestC, str_value_rj, allocator);
    send_dom.AddMember(gzj_ProtocolV, Ver_gzjVersion, allocator);
    send_dom.AddMember(gzj_FunctionC, FN_gzjDeviceMI, allocator);
    send_dom.AddMember(gzj_OperationC, OP_gzjWrite, allocator);
    send_dom.AddMember(gzj_FunctionC, AF_gzjAnswerNoData, allocator);
    send_dom.AddMember(gzj_Result, Result_gzjSuccess, allocator);
    send_dom.AddMember(gzj_ErrorC, EC_gzjNoEC, allocator);

    if (dom.HasMember("Data"))
    {
        Value Data;
        Data = dom["Data"];
        struct_deviceMIF structDMIF;
        struct_analyticP structAP;
        //先取Array
        if (Data.IsArray() && !Data.Empty())
        {
            rapidjson::Value tempData;
            for (rapidjson::SizeType i = 0; i < Data.Size(); i++)
            {
                tempData = Data[i];
                if (tempData.IsObject())
                {

                    if (tempData.HasMember("TN") && tempData.HasMember("IT")&& tempData.HasMember("PN")
                            && tempData.HasMember("CMD")&& tempData.HasMember("PS")&& tempData.HasMember("AP"))
                    {
                        structDMIF.VL_TN<<tempData["TN"].GetInt();
                        structDMIF.VL_IT<<tr(tempData["IT"].GetString());
                        structDMIF.VL_PN<<tempData["PN"].GetInt();
                        structDMIF.VL_CMD<<tr(tempData["CMD"].GetString());
                        structDMIF.VL_PS<<tempData["PS"].GetInt();

                        Value Data2;
                        Data2 = tempData["AP"];
                        if (Data2.IsArray() && !Data2.Empty())
                        {
                            Value tempData2;
                            for (rapidjson::SizeType i = 0; i < Data2.Size(); i++)
                            {
                                tempData2 = Data2[i];
                                if (tempData2.IsObject())
                                {
                                    if (tempData2.HasMember("TN") && tempData2.HasMember("IT")&& tempData2.HasMember("PN")
                                            && tempData2.HasMember("CMD")&& tempData2.HasMember("PS")&& tempData2.HasMember("AP"))
                                    {
                                        structAP.VL_RB=tempData2["RB"].GetInt();
                                        structAP.VL_PB=tempData2["PB"].GetInt();
                                        structAP.VL_TM=tempData2["TM"].GetInt();
                                        structAP.VL_SI=tr(tempData2["SI"].GetString());
                                        structAP.VL_DL=tempData2["DL"].GetInt();
                                        structAP.VL_DT=tr(tempData2["DT"].GetString());
                                        structAP.VL_Formula=tr(tempData2["Formula"].GetString());
                                        structAP.VL_UL=tempData2["UL"].GetDouble();
                                        structAP.VL_LL=tempData2["LL"].GetDouble();
                                    }
                                }
                            }
                        }
                        structDMIF.VL_AP<<structAP;

                        qDebug()<<tr(tempData["IT"].GetString());
                    }
                }
            }
        }
        APISgrH::set_deviceMIF(structDMIF);
        //文件操作
        Document jDDMI;
        Document::AllocatorType& allocator=jDDMI.GetAllocator();
        jDDMI.SetObject();
        jDDMI.AddMember("Data",DataFile,allocator);
        StringBuffer buf;
        PrettyWriter<rapidjson::StringBuffer> writer(buf);
        jDDMI.Accept(writer);
        QString fileDir = QCoreApplication::applicationDirPath() + "/etc/JsonDeviceMI.txt";
        QFile file(fileDir);
        //对文件进行写操作
        if(!file.open(QIODevice::WriteOnly)){
            qDebug()<<"文件打开失败";
        }
        //向文件中写入字符串
        file.write(buf.GetString());
        //关闭文件
        file.close();

    }

    StringBuffer buf;
    Writer<rapidjson::StringBuffer> writer(buf);
    send_dom.Accept(writer);
    QByteArray ba_data(buf.GetString());
    emit Singleton<TcpClientManager>::getInstance().modelSend(ba_data);

    /*
    Document send_dom;
    Document::AllocatorType& allocator=send_dom.GetAllocator();
    str_value_rj.SetString(dom[gzj_RequestC].GetString(),allocator);
    send_dom.SetObject();
    send_dom.AddMember(gzj_RequestC, str_value_rj, allocator);
    send_dom.AddMember(gzj_ProtocolV, Ver_gzjVersion, allocator);
    send_dom.AddMember(gzj_FunctionC, FN_gzjDeviceMI, allocator);
    send_dom.AddMember(gzj_OperationC, OP_gzjWrite, allocator);
    send_dom.AddMember(gzj_FunctionC, AF_gzjAnswerNoData, allocator);
    send_dom.AddMember(gzj_Result, Result_gzjSuccess, allocator);
    send_dom.AddMember(gzj_ErrorC, EC_gzjNoEC, allocator);
    if (dom.HasMember("Data"))
    {
        Value Data;
        Data = dom["Data"];
        struct_deviceMI structDMI;
        //先取Array
        if (Data.IsArray() && !Data.Empty())
        {
            rapidjson::Value tempData;
            for (rapidjson::SizeType i = 0; i < Data.Size(); i++)
            {
                tempData = Data[i];
                if (tempData.IsObject())
                {

                    if (tempData.HasMember("TN") && tempData.HasMember("IT")&& tempData.HasMember("PN")
                            && tempData.HasMember("CMD")&& tempData.HasMember("PS")&& tempData.HasMember("RB")
                            && tempData.HasMember("PB")&& tempData.HasMember("TM")&& tempData.HasMember("SI")
                            && tempData.HasMember("DL")&& tempData.HasMember("DT")&& tempData.HasMember("Formula")
                            && tempData.HasMember("UL")&& tempData.HasMember("LL"))
                    {
                        structDMI.VL_TN<<tempData["TN"].GetInt();
                        structDMI.VL_IT<<tr(tempData["IT"].GetString());
                        structDMI.VL_PN<<tempData["PN"].GetInt();
                        structDMI.VL_CMD<<tr(tempData["CMD"].GetString());
                        structDMI.VL_PS<<tempData["PS"].GetInt();
                        structDMI.VL_RB<<tempData["RB"].GetInt();
                        structDMI.VL_PB<<tempData["PB"].GetInt();
                        structDMI.VL_TM<<tempData["TM"].GetInt();
                        structDMI.VL_SI<<tr(tempData["SI"].GetString());
                        structDMI.VL_DL<<tempData["DL"].GetInt();
                        structDMI.VL_DT<<tr(tempData["DT"].GetString());
                        structDMI.VL_Formula<<tr(tempData["Formula"].GetString());
                        structDMI.VL_UL<<tempData["UL"].GetDouble();
                        structDMI.VL_LL<<tempData["LL"].GetDouble();

                        qDebug()<<tr(tempData["IT"].GetString());
                    }
                }
            }
        }
        Singleton<GzjSqlite>::getInstance().insertDeviceMI(structDMI);
    }
    StringBuffer buf;
    Writer<rapidjson::StringBuffer> writer(buf);
    send_dom.Accept(writer);
    QByteArray ba_data(buf.GetString());
    emit Singleton<TcpClientManager>::getInstance().modelSend(ba_data);
*/
}

//A5 00 2 网关主动请求（操作码00)
void TcpClientModel::A5_00_2(Document &dom)
{
    if (dom.HasMember("Data"))
    {
        Value Data;
        Data = dom["Data"];
        struct_circCT structCCT;
        //先取Array
        if (Data.IsArray() && !Data.Empty())
        {
            rapidjson::Value tempData;
            for (rapidjson::SizeType i = 0; i < Data.Size(); i++)
            {
                tempData = Data[i];
                if (tempData.IsObject())
                {

                    if (tempData.HasMember("TN") && tempData.HasMember("Addr")&& tempData.HasMember("VA")
                            && tempData.HasMember("SP")&& tempData.HasMember("IT")&& tempData.HasMember("CF")
                            && tempData.HasMember("UF"))
                    {
                        structCCT.VL_TN<<tempData["TN"].GetInt();
                        structCCT.VL_Addr<<tr(tempData["Addr"].GetString());
                        structCCT.VL_VA<<tempData["VA"].GetInt();
                        structCCT.VL_SP<<tr(tempData["SP"].GetString());
                        structCCT.VL_IT<<tr(tempData["IT"].GetString());
                        structCCT.VL_CF<<tr(tempData["CF"].GetString());
                        structCCT.VL_UF<<tr(tempData["UF"].GetString());

                        qDebug()<<tr(tempData["Addr"].GetString());
                    }
                }
            }
        }
        Singleton<GzjSqlite>::getInstance().insertCircCT(structCCT);
    }
}
//A5 03 0 上位机读网关（操作码03）
void TcpClientModel::A5_03_0(Document &dom)
{
    Document send_dom;
    Document::AllocatorType& allocator=send_dom.GetAllocator();
    str_value_rj.SetString(dom[gzj_RequestC].GetString(),allocator);
    send_dom.SetObject();
    send_dom.AddMember(gzj_RequestC, str_value_rj, allocator);
    send_dom.AddMember(gzj_ProtocolV, Ver_gzjVersion, allocator);
    send_dom.AddMember(gzj_FunctionC, FN_gzjCircCT, allocator);
    send_dom.AddMember(gzj_OperationC, OP_gzjRead, allocator);
    send_dom.AddMember(gzj_FunctionC, AF_gjzAnswerData, allocator);

    QSqlQuery sql_query(Singleton<GzjSqlite>::getInstance().sqlDatabase);
    QString select_sql = "select TN ,Addr ,VA ,SP ,IT ,CF ,UF from circCT";

    if(!sql_query.exec(select_sql)){
        Singleton<Log>::getInstance().debug("exec fail: "+sql_query.lastError().text());
    }
    else
    {
        Value DataArray(rapidjson::kArrayType);
        while(sql_query.next())
        {
            Value Data(rapidjson::kObjectType);
            str_value_rj.SetInt(sql_query.value(0).toInt());
            Data.AddMember("TN", str_value_rj, allocator);
            str_value_rj.SetString(sql_query.value(1).toString().toStdString().c_str(), allocator);
            Data.AddMember("Addr", str_value_rj, allocator);
            str_value_rj.SetInt(sql_query.value(2).toInt());
            Data.AddMember("VA", str_value_rj, allocator);
            str_value_rj.SetString(sql_query.value(3).toString().toStdString().c_str(), allocator);
            Data.AddMember("SP", str_value_rj, allocator);
            str_value_rj.SetString(sql_query.value(4).toString().toStdString().c_str(), allocator);
            Data.AddMember("IT", str_value_rj, allocator);
            str_value_rj.SetString(sql_query.value(5).toString().toStdString().c_str(), allocator);
            Data.AddMember("CF", str_value_rj, allocator);
            str_value_rj.SetString(sql_query.value(6).toString().toStdString().c_str(), allocator);
            Data.AddMember("UF", str_value_rj, allocator);


            DataArray.PushBack(Data, allocator);
        }
        send_dom.AddMember("Data", DataArray, allocator);
    }
    StringBuffer buf;
    Writer<rapidjson::StringBuffer> writer(buf);
    send_dom.Accept(writer);
    QByteArray ba_data(buf.GetString());
    emit Singleton<TcpClientManager>::getInstance().modelSend(ba_data);
}
//A5 06 0 上位机写网关（操作码06）
void TcpClientModel::A5_06_0(Document &dom)
{
    Document send_dom;
    Document::AllocatorType& allocator=send_dom.GetAllocator();
    str_value_rj.SetString(dom[gzj_RequestC].GetString(),allocator);
    send_dom.SetObject();
    send_dom.AddMember(gzj_RequestC, str_value_rj, allocator);
    send_dom.AddMember(gzj_ProtocolV, Ver_gzjVersion, allocator);
    send_dom.AddMember(gzj_FunctionC, FN_gzjCircCT, allocator);
    send_dom.AddMember(gzj_OperationC, OP_gzjWrite, allocator);
    send_dom.AddMember(gzj_FunctionC, AF_gzjAnswerNoData, allocator);
    send_dom.AddMember(gzj_Result, Result_gzjSuccess, allocator);
    send_dom.AddMember(gzj_ErrorC, EC_gzjNoEC, allocator);
    if (dom.HasMember("Data"))
    {
        Value Data;
        Data = dom["Data"];
        struct_circCT structCCT;
        //先取Array
        if (Data.IsArray() && !Data.Empty())
        {
            rapidjson::Value tempData;
            for (rapidjson::SizeType i = 0; i < Data.Size(); i++)
            {
                tempData = Data[i];
                if (tempData.IsObject())
                {

                    if (tempData.HasMember("TN") && tempData.HasMember("Addr")&& tempData.HasMember("VA")
                            && tempData.HasMember("SP")&& tempData.HasMember("IT")&& tempData.HasMember("CF")
                            && tempData.HasMember("UF"))
                    {
                        structCCT.VL_TN<<tempData["TN"].GetInt();
                        structCCT.VL_Addr<<tr(tempData["Addr"].GetString());
                        structCCT.VL_VA<<tempData["VA"].GetInt();
                        structCCT.VL_SP<<tr(tempData["SP"].GetString());
                        structCCT.VL_IT<<tr(tempData["IT"].GetString());
                        structCCT.VL_CF<<tr(tempData["CF"].GetString());
                        structCCT.VL_UF<<tr(tempData["UF"].GetString());

                        qDebug()<<tr(tempData["Addr"].GetString());
                    }
                }
            }
        }
        Singleton<GzjSqlite>::getInstance().insertCircCT(structCCT);
    }
    StringBuffer buf;
    Writer<rapidjson::StringBuffer> writer(buf);
    send_dom.Accept(writer);
    QByteArray ba_data(buf.GetString());
    emit Singleton<TcpClientManager>::getInstance().modelSend(ba_data);

}

//B1 03 0 固件版本读取（操作码03）
void TcpClientModel::B1_03_0(Document &dom)
{
    Document send_dom;
    Document::AllocatorType& allocator=send_dom.GetAllocator();
    str_value_rj.SetString(dom[gzj_RequestC].GetString(),allocator);
    send_dom.SetObject();
    send_dom.AddMember(gzj_RequestC, str_value_rj, allocator);
    send_dom.AddMember(gzj_ProtocolV, Ver_gzjVersion, allocator);
    send_dom.AddMember(gzj_FunctionC, FN_gzjFireware, allocator);
    send_dom.AddMember(gzj_OperationC, OP_gzjRead, allocator);
    send_dom.AddMember(gzj_FunctionC, AF_gjzAnswerData, allocator);
    send_dom.AddMember("Data", gzj_firmware, allocator);

    StringBuffer buf;
    Writer<rapidjson::StringBuffer> writer(buf);
    send_dom.Accept(writer);
    QByteArray ba_data(buf.GetString());
    emit Singleton<TcpClientManager>::getInstance().modelSend(ba_data);
}
//B2 03 0 硬件版本读取（操作码03）
void TcpClientModel::B2_03_0(Document &dom)
{
    Document send_dom;
    Document::AllocatorType& allocator=send_dom.GetAllocator();
    str_value_rj.SetString(dom[gzj_RequestC].GetString(),allocator);
    send_dom.SetObject();
    send_dom.AddMember(gzj_RequestC, str_value_rj, allocator);
    send_dom.AddMember(gzj_ProtocolV, Ver_gzjVersion, allocator);
    send_dom.AddMember(gzj_FunctionC, FN_gzjHadrware, allocator);
    send_dom.AddMember(gzj_OperationC, OP_gzjRead, allocator);
    send_dom.AddMember(gzj_FunctionC, AF_gjzAnswerData, allocator);
    send_dom.AddMember("Data", gzj_hardware, allocator);
    StringBuffer buf;
    Writer<rapidjson::StringBuffer> writer(buf);
    send_dom.Accept(writer);
    QByteArray ba_data(buf.GetString());
    emit Singleton<TcpClientManager>::getInstance().modelSend(ba_data);
}
//B3电池电压状态读取指令B3（操作码03）
void TcpClientModel::B3_03_0(Document &dom)
{
    Document send_dom;
    Document::AllocatorType& allocator=send_dom.GetAllocator();
    str_value_rj.SetString(dom[gzj_RequestC].GetString(),allocator);
    send_dom.SetObject();
    send_dom.AddMember(gzj_RequestC, str_value_rj, allocator);
    send_dom.AddMember(gzj_ProtocolV, Ver_gzjVersion, allocator);
    send_dom.AddMember(gzj_FunctionC, FN_gzjBatteryVS, allocator);
    send_dom.AddMember(gzj_OperationC, OP_gzjRead, allocator);
    send_dom.AddMember(gzj_FunctionC, AF_gjzAnswerData, allocator);
    send_dom.AddMember("Data", "1", allocator);
    StringBuffer buf;
    Writer<rapidjson::StringBuffer> writer(buf);
    send_dom.Accept(writer);
    QByteArray ba_data(buf.GetString());
    emit Singleton<TcpClientManager>::getInstance().modelSend(ba_data);
}
//B4电源供电状态读取指令B4（操作码03）
void TcpClientModel::B4_03_0(Document &dom)
{
    Document send_dom;
    Document::AllocatorType& allocator=send_dom.GetAllocator();
    str_value_rj.SetString(dom[gzj_RequestC].GetString(),allocator);
    send_dom.SetObject();
    send_dom.AddMember(gzj_RequestC, str_value_rj, allocator);
    send_dom.AddMember(gzj_ProtocolV, Ver_gzjVersion, allocator);
    send_dom.AddMember(gzj_FunctionC, FN_gzjPowerCS, allocator);
    send_dom.AddMember(gzj_OperationC, OP_gzjRead, allocator);
    send_dom.AddMember(gzj_FunctionC, AF_gjzAnswerData, allocator);
    send_dom.AddMember("Data", "1", allocator);
    StringBuffer buf;
    Writer<rapidjson::StringBuffer> writer(buf);
    send_dom.Accept(writer);
    QByteArray ba_data(buf.GetString());
    emit Singleton<TcpClientManager>::getInstance().modelSend(ba_data);
}
//C1 03 0 时间同步（操作码03）
void TcpClientModel::C1_03_0(Document &dom)
{
    Document send_dom;
    Document::AllocatorType& allocator=send_dom.GetAllocator();
    str_value_rj.SetString(dom[gzj_RequestC].GetString(),allocator);
    send_dom.SetObject();
    send_dom.AddMember(gzj_RequestC, str_value_rj, allocator);
    send_dom.AddMember(gzj_ProtocolV, Ver_gzjVersion, allocator);
    send_dom.AddMember(gzj_FunctionC, FN_gzjTimeSync, allocator);
    send_dom.AddMember(gzj_OperationC, OP_gzjRead, allocator);
    send_dom.AddMember(gzj_FunctionC, AF_gjzAnswerData, allocator);
    QDateTime time =QDateTime::currentDateTime();
    str_value_rj.SetString(time.toString("yyyyMMddhhmmss").toStdString().c_str(), allocator);
    send_dom.AddMember("Data", str_value_rj, allocator);

    StringBuffer buf;
    Writer<rapidjson::StringBuffer> writer(buf);
    send_dom.Accept(writer);
    QByteArray ba_data(buf.GetString());
    emit Singleton<TcpClientManager>::getInstance().modelSend(ba_data);
}
//C1 06 0 时间同步（操作码06）
void TcpClientModel::C1_06_0(Document &dom)
{

    Document send_dom;
    Document::AllocatorType& allocator=send_dom.GetAllocator();
    str_value_rj.SetString(dom[gzj_RequestC].GetString(),allocator);
    send_dom.SetObject();
    send_dom.AddMember(gzj_RequestC, str_value_rj, allocator);
    send_dom.AddMember(gzj_ProtocolV, Ver_gzjVersion, allocator);
    send_dom.AddMember(gzj_FunctionC, FN_gzjTimeSync, allocator);
    send_dom.AddMember(gzj_OperationC, OP_gzjWrite, allocator);
    send_dom.AddMember(gzj_FunctionC, AF_gzjAnswerNoData, allocator);
    send_dom.AddMember(gzj_Result, Result_gzjSuccess, allocator);
    send_dom.AddMember(gzj_ErrorC, EC_gzjNoEC, allocator);
    if (dom.HasMember("Data"))
    {
        QString strData(tr(dom["Data"].GetString()));
        QString strData1=strData.left(8);
        QString strData2=strData.right(6);
        strData2.insert(2,':');
        strData2.insert(5,':');
        QString qstrDateTime = QString("date -s %1").arg(strData1);
        QProcess::execute(qstrDateTime);
        qstrDateTime = QString("date -s %1").arg(strData2);
        QProcess::execute(qstrDateTime);
        qstrDateTime = QString("hwclock --systohc");
        QProcess::execute(qstrDateTime);
    }
    StringBuffer buf;
    Writer<rapidjson::StringBuffer> writer(buf);
    send_dom.Accept(writer);
    QByteArray ba_data(buf.GetString());
    emit Singleton<TcpClientManager>::getInstance().modelSend(ba_data);

}
//C2 03 0 读串口配置（操作码03）
void TcpClientModel::C2_03_0(const QString &dom)
{
    emit Singleton<TcpClientManager>::getInstance().readSeriSetting(dom);
}
//C2 06 0 写串口配置（操作码06）
void TcpClientModel::C2_06_0(Document &dom)
{
    Document send_dom;
    Document::AllocatorType& allocator=send_dom.GetAllocator();
    str_value_rj.SetString(dom[gzj_RequestC].GetString(),allocator);
    send_dom.SetObject();
    send_dom.AddMember(gzj_RequestC, str_value_rj, allocator);
    send_dom.AddMember(gzj_ProtocolV, Ver_gzjVersion, allocator);
    send_dom.AddMember(gzj_FunctionC, FN_gzjSeriS, allocator);
    send_dom.AddMember(gzj_OperationC, OP_gzjWrite, allocator);
    send_dom.AddMember(gzj_FunctionC, AF_gzjAnswerNoData, allocator);
    send_dom.AddMember(gzj_Result, Result_gzjSuccess, allocator);
    send_dom.AddMember(gzj_ErrorC, EC_gzjNoEC, allocator);
    if (dom.HasMember("Data"))
    {
        Value Data;
        Data = dom["Data"];
        //先取Array
        if (Data.IsArray() && !Data.Empty())
        {
            rapidjson::Value tempData;
            QVariantList VL_SP,VL_Baud,VL_None,VL_DB,VL_SB;
            for (rapidjson::SizeType i = 0; i < Data.Size(); i++)
            {
                tempData = Data[i];
                if (tempData.IsObject())
                {

                    if (tempData.HasMember("SP") && tempData.HasMember("Baud")&& tempData.HasMember("CB")&&
                            tempData.HasMember("DB")&& tempData.HasMember("SB"))
                    {
                        VL_SP<<tr(tempData["SP"].GetString());
                        VL_Baud<<tempData["Baud"].GetInt();
                        VL_None<<tr(tempData["CB"].GetString());
                        VL_DB<<tempData["DB"].GetInt();
                        VL_SB<<tempData["SB"].GetDouble();
                    }
                }
            }
            emit Singleton<TcpClientManager>::getInstance().writeSeriSetting(VL_SP,VL_Baud,VL_None,VL_DB,VL_SB);
        }
    }
    StringBuffer buf;
    Writer<rapidjson::StringBuffer> writer(buf);
    send_dom.Accept(writer);
    QByteArray ba_data(buf.GetString());
    emit Singleton<TcpClientManager>::getInstance().modelSend(ba_data);
}

