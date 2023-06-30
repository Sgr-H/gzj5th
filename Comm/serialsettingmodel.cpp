#include "serialsettingmodel.h"
#include "gzjsqlite.h"
#include "log.h"
SerialSettingModel::SerialSettingModel(QObject *parent) : QObject(parent)
{

}

void SerialSettingModel::countSlot()
{

}

void SerialSettingModel::msgParse(const QByteArray &_collect_ba, const QByteArray &_byte_array)
{
    qDebug()<<_collect_ba<<_byte_array;
}

void SerialSettingModel::initCCI()
{
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

