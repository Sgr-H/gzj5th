#include "gzjsqlite.h"
GzjSqlite::GzjSqlite()
{
    initSql();
    initTable();
}

GzjSqlite::~GzjSqlite()
{
    sqlDatabase.close();
}

void GzjSqlite::insertDeviceTI(const struct_deviceTI &_struct_DTI)
{
    //表中是否有deviceTI
    if(tableNameList.contains("deviceTI")){
        //清表
        sql_query.exec("delete from deviceTI");
        sql_query.exec("update sqlite_sequence SET seq = 0 where name ='deviceTI'");
        //插入
        sqlDatabase.transaction();
        QString commit_Sql=QString("insert into %1 values(?,?,?,?)").arg("deviceTI");
        sql_query.prepare(commit_Sql);
        sql_query.addBindValue(_struct_DTI.VL_TN);
        sql_query.addBindValue(_struct_DTI.VL_PN);
        sql_query.addBindValue(_struct_DTI.VL_Name);
        sql_query.addBindValue(_struct_DTI.VL_EnName);
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
            APISgrH::set_deviceTI(_struct_DTI);
            qDebug() << "commit deviceTI Success" ;
        }
    }
}

void GzjSqlite::insertTargetTI(const struct_targetTI &_struct_TTI)
{

    //表中是否有targetTI
    if(tableNameList.contains("targetTI")){
        //清表
        sql_query.exec("delete from targetTI");
        sql_query.exec("update sqlite_sequence SET seq = 0 where name ='targetTI'");
        //插入
        sqlDatabase.transaction();
        QString commit_Sql=QString("insert into %1 values(?,?,?,?,?)").arg("targetTI");
        sql_query.prepare(commit_Sql);
        sql_query.addBindValue(_struct_TTI.VL_TN);
        sql_query.addBindValue(_struct_TTI.VL_Type);
        sql_query.addBindValue(_struct_TTI.VL_Name);
        sql_query.addBindValue(_struct_TTI.VL_EnName);
        sql_query.addBindValue(_struct_TTI.VL_Unit);
        if(!sql_query.execBatch()){
            qDebug() << "execBatch fail:" << sql_query.lastError().text();
            if(!sqlDatabase.rollback()){
                qDebug() << "rollback fail:" << sqlDatabase.lastError().text();
            }
        }
        if(!sqlDatabase.commit()){
            qDebug() << "commit targetTI fail:" << sqlDatabase.lastError().text();
        }
        else
        {
            APISgrH::set_targetTI(_struct_TTI);
            qDebug() << "commit targetTI Success" ;
        }
    }
}

void GzjSqlite::insertDeviceMI(const struct_deviceMI &_struct_DMI)
{
    //表中是否有targetTI
    if(tableNameList.contains("deviceMI")){
        //清表
        sql_query.exec("delete from deviceMI");
        sql_query.exec("update sqlite_sequence SET seq = 0 where name ='deviceMI'");
        //插入
        sqlDatabase.transaction();
        QString commit_Sql=QString("insert into %1 values(?,?,?,?,?,?,?,?,?,?,?,?,?,?)").arg("deviceMI");
        sql_query.prepare(commit_Sql);
        sql_query.addBindValue(_struct_DMI.VL_TN);
        sql_query.addBindValue(_struct_DMI.VL_IT);
        sql_query.addBindValue(_struct_DMI.VL_PN);
        sql_query.addBindValue(_struct_DMI.VL_CMD);
        sql_query.addBindValue(_struct_DMI.VL_PS);
        sql_query.addBindValue(_struct_DMI.VL_RB);
        sql_query.addBindValue(_struct_DMI.VL_PB);
        sql_query.addBindValue(_struct_DMI.VL_TM);
        sql_query.addBindValue(_struct_DMI.VL_SI);
        sql_query.addBindValue(_struct_DMI.VL_DL);
        sql_query.addBindValue(_struct_DMI.VL_DT);
        sql_query.addBindValue(_struct_DMI.VL_Formula);
        sql_query.addBindValue(_struct_DMI.VL_UL);
        sql_query.addBindValue(_struct_DMI.VL_LL);

        if(!sql_query.execBatch()){
            qDebug() << "execBatch fail:" << sql_query.lastError().text();
            if(!sqlDatabase.rollback()){
                qDebug() << "rollback fail:" << sqlDatabase.lastError().text();
            }
        }
        if(!sqlDatabase.commit()){
            qDebug() << "commitdeviceMI fail:" << sqlDatabase.lastError().text();
        }
        else
        {
            qDebug() << "commit deviceMI Success" ;
        }
    }
}

void GzjSqlite::insertCircCT(const struct_circCT &_struct_CCT)
{
    //表中是否有targetTI
    if(tableNameList.contains("circCT")){
        //清表
        sql_query.exec("delete from circCT");
        sql_query.exec("update sqlite_sequence SET seq = 0 where name ='circCT'");
        //插入
        sqlDatabase.transaction();
        QString commit_Sql=QString("insert into %1 values(?,?,?,?,?,?,?)").arg("circCT");
        sql_query.prepare(commit_Sql);
        sql_query.addBindValue(_struct_CCT.VL_TN);
        sql_query.addBindValue(_struct_CCT.VL_Addr);
        sql_query.addBindValue(_struct_CCT.VL_VA);
        sql_query.addBindValue(_struct_CCT.VL_SP);
        sql_query.addBindValue(_struct_CCT.VL_CMD);
        sql_query.addBindValue(_struct_CCT.VL_CF);
        sql_query.addBindValue(_struct_CCT.VL_UF);

        if(!sql_query.execBatch()){
            qDebug() << "execBatch fail:" << sql_query.lastError().text();
            if(!sqlDatabase.rollback()){
                qDebug() << "rollback fail:" << sqlDatabase.lastError().text();
            }
        }
        if(!sqlDatabase.commit()){
            qDebug() << "commit circCT fail:" << sqlDatabase.lastError().text();
        }
        else
        {
            APISgrH::set_circCT(_struct_CCT);
            qDebug() << "commit circCT Success" ;
        }
    }
}

void GzjSqlite::sqlTest(const QString &sql_str)
{
    sql_query.prepare(sql_str);
    if(!sql_query.exec())
    {
        qDebug() << sql_query.lastError();
    }
    else
    {
        qDebug() << sql_str <<" success";
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
        //表中是否有targetTI，无则创建
        if(!tableNameList.contains("targetTI")){
            //            使用sql语句创建表并且初始化字段
            QString createTable_sql = "create table targetTI (TN varchar(8),Type int,Name varchar(20),EnName varchar(20),Unit varchar(20))";
            sql_query.prepare(createTable_sql);
            if(!sql_query.exec())
            {
                qDebug() << sql_query.lastError();
            }
            else
            {
                qDebug() << "create targetTI table!";
            }
        }
        //表中是否有deviceMI，无则创建
        if(!tableNameList.contains("deviceMI")){
            //            使用sql语句创建表并且初始化字段
            QString createTable_sql = "create table deviceMI (TN int,IT varchar(20),PN int,CMD varchar(20),PS int,RB int,PB int,TM int,"
                                      "SI varchar(8),DL int,DT varchar(20),Formula varchar(20),UL double,LL double)";
            sql_query.prepare(createTable_sql);
            if(!sql_query.exec())
            {
                qDebug() << sql_query.lastError();
            }
            else
            {
                qDebug() << "create deviceMI table!";
            }
        }
        //表中是否有circCT，无则创建
        if(!tableNameList.contains("circCT")){
            //            使用sql语句创建表并且初始化字段
            QString createTable_sql = "create table circCT (TN int,Addr varchar(20),VA int,SP varchar(20),"
                                      "CMD varchar(200),CF varchar(20),UF varchar(20))";
            sql_query.prepare(createTable_sql);
            if(!sql_query.exec())
            {
                qDebug() << sql_query.lastError();
            }
            else
            {
                qDebug() << "create circCT table!";
            }
        }
    }
}
