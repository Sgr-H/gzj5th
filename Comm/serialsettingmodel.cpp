#include "serialsettingmodel.h"
#include "gzjsqlite.h"

SerialSettingModel::SerialSettingModel(QObject *parent) : QObject(parent)
{

}

void SerialSettingModel::countSlot()
{

}

void SerialSettingModel::msgParse(const QByteArray &_collect_ba, const QByteArray &_byte_array)
{
//    if(A5isEmpty())
//        return;
    qDebug()<<QThread::currentThreadId()<< "  " <<_collect_ba<<_byte_array;
}

void SerialSettingModel::initCCI()
{
    if(A5isEmpty())
        return;
    if(A4isEmpty())
        return;
    QSqlQuery sql_query(Singleton<GzjSqlite>::getInstance().sqlDatabase);
    QString select_sql = "select TN ,Addr ,VA ,SP ,CMD ,CF ,UF from circCT";

    if(!sql_query.exec(select_sql)){
        Singleton<Log>::getInstance().debug("exec fail: "+sql_query.lastError().text());
    }
    else
    {

        while(sql_query.next())
        {
//            str_value_rj.SetString(sql_query.value(3).toString().toStdString().c_str(), allocator);
//            Data.AddMember("EnName", str_value_rj, allocator);
        }
    }
}

bool SerialSettingModel::A5isEmpty()
{
    QSqlQuery sql_query(Singleton<GzjSqlite>::getInstance().sqlDatabase);
    QString select_sql = "select TN ,Addr ,VA ,SP ,CMD ,CF ,UF from circCT";

    if(!sql_query.exec(select_sql)){
        Singleton<Log>::getInstance().debug("exec fail: "+sql_query.lastError().text());
        return true;
    }
    else{
        if(sql_query.next()){
            return false;
        }
        else{
            Document send_dom;
            Document::AllocatorType& allocator=send_dom.GetAllocator();
            send_dom.SetObject();
            send_dom.AddMember(gzj_RequestC, gzj_noneStr, allocator);
            Value& v1 = send_dom[gzj_RequestC];
            v1.SetString(STRDATETIMEMSSP,QString(STRDATETIMEMSSP).size());
            send_dom.AddMember(gzj_ProtocolV, Ver_gzjVersion, allocator);
            send_dom.AddMember(gzj_FunctionC, FN_gzjCircCT, allocator);
            send_dom.AddMember(gzj_OperationC, OP_gzjNone, allocator);
            send_dom.AddMember(gzj_FunctionC, AF_gzjNoAnswer, allocator);
            StringBuffer buf;
            Writer<rapidjson::StringBuffer> writer(buf);
            send_dom.Accept(writer);
            QByteArray ba_data(buf.GetString());
            emit SModelSignToTcpSend(ba_data);
            return true;
        }
    }
}

bool SerialSettingModel::A4isEmpty()
{
    QSqlQuery sql_query(Singleton<GzjSqlite>::getInstance().sqlDatabase);
    QString select_sql = "select TN ,IT ,PN ,CMD ,PS ,RB ,PB ,TM ,SI ,DL ,DT ,Formula ,UL ,LL from deviceMI";
    if(!sql_query.exec(select_sql)){
        Singleton<Log>::getInstance().debug("exec fail: "+sql_query.lastError().text());
        return true;
    }
    else{
        if(sql_query.next()){
            return false;
        }
        else{
            Document send_dom;
            Document::AllocatorType& allocator=send_dom.GetAllocator();
            send_dom.SetObject();
            send_dom.AddMember(gzj_RequestC, gzj_noneStr, allocator);
            Value& v1 = send_dom[gzj_RequestC];
            v1.SetString(STRDATETIMEMSSP,QString(STRDATETIMEMSSP).size());
            send_dom.AddMember(gzj_ProtocolV, Ver_gzjVersion, allocator);
            send_dom.AddMember(gzj_FunctionC, FN_gzjDeviceMI, allocator);
            send_dom.AddMember(gzj_OperationC, OP_gzjNone, allocator);
            send_dom.AddMember(gzj_FunctionC, AF_gzjNoAnswer, allocator);
            StringBuffer buf;
            Writer<rapidjson::StringBuffer> writer(buf);
            send_dom.Accept(writer);
            QByteArray ba_data(buf.GetString());
            emit SModelSignToTcpSend(ba_data);
            return true;
        }
    }
}

