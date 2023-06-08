#include "gzjsqlite.h"
#include "log.h"
GzjSqlite::GzjSqlite()
{
    initSql();
    initTable();
}

GzjSqlite::~GzjSqlite()
{
    sqlDatabase.close();
}

void GzjSqlite::insertDeviceTI(const QVariantList &_TN, const QVariantList &_PN, const QVariantList &_Name, const QVariantList &_EnName)
{
    //表中是否有deviceTI，无则创建
    if(tableNameList.contains("deviceTI")){
        //清表
        sql_query.exec("delete from deviceTI");
        //插入
        sqlDatabase.transaction();
        QString commit_Sql=QString("insert into %1 values(?,?,?,?)").arg("deviceTI");
        sql_query.prepare(commit_Sql);
        sql_query.addBindValue(_TN);
        sql_query.addBindValue(_PN);
        sql_query.addBindValue(_Name);
        sql_query.addBindValue(_EnName);
        if(!sql_query.execBatch()){
            qDebug() << "execBatch fail:" << sql_query.lastError().text();
            if(!sqlDatabase.rollback()){
                qDebug() << "rollback fail:" << sqlDatabase.lastError().text();
            }
        }
        if(!sqlDatabase.commit()){
            qDebug() << "commitdeviceTI fail:" << sqlDatabase.lastError().text();
        }
        else
        {
            qDebug() << "commit Success" ;
        }
    }
}

void GzjSqlite::selectDeviceTI()
{

}

void GzjSqlite::sqlTest()
{
    QString clear_sql = "delete from deviceTI";
    sql_query.prepare(clear_sql);
    if(!sql_query.exec())
    {
        qDebug() << sql_query.lastError();
    }
    else
    {
        qDebug() << "table cleared";
    }
}

void GzjSqlite::initSql()
{
    //查看系统已存在数据库
    QStringList drivers = QSqlDatabase::drivers();
    foreach(QString driver, drivers) {
        Singleton<Log>::getInstance().debug(driver);
    }
    //检查数据库连接，若无则新建
    if (QSqlDatabase::contains("qt_sql_default_connection"))
    {
        sqlDatabase = QSqlDatabase::database("qt_sql_default_connection");
    }
    else
    {
        sqlDatabase = QSqlDatabase::addDatabase("QSQLITE");
        sqlDatabase.setDatabaseName("gzjsqlite.db");
        sqlDatabase.setUserName("sgrh");
        sqlDatabase.setPassword("123456");
    }
    //连接数据库
    if (!sqlDatabase.open())
        qDebug()<<"连接数据库错误"<<sqlDatabase.lastError()  <<endl;
    sql_query=QSqlQuery(sqlDatabase);
}

void GzjSqlite::initTable()
{
    //连接数据库
    if (!sqlDatabase.open())
        qDebug()<<"连接数据库错误"<<sqlDatabase.lastError()  <<endl;
    else{
        Singleton<Log>::getInstance().debug("连接数据库成功");
        //查询表个数
        tableNameList   = sqlDatabase.tables();
        Singleton<Log>::getInstance().debug("查询的表名的个数= "+QString::number(tableNameList.count()));

        for (int var = 0; var < tableNameList.count(); ++var) {
            Singleton<Log>::getInstance().debug(tableNameList.at(var));
        }

        //表中是否有deviceTI，无则创建
        if(!tableNameList.contains("deviceTI")){
            //            使用sql语句创建表并且初始化字段
            QString createTable_sql = "create table deviceTI (TN varchar(8),PN varchar(8),Name varchar(20),EnName varchar(20))";
            sql_query.prepare(createTable_sql);
            if(!sql_query.exec())
            {
                qDebug() << sql_query.lastError();
            }
            else
            {
                qDebug() << "create deviceTI table!";
            }
        }
    }
}
