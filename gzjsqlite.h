#ifndef GZJSQLITE_H
#define GZJSQLITE_H

#include <QObject>

class GzjSqlite : public QObject
{
    SINGLETON(GzjSqlite)
    Q_OBJECT
    public:

    QSqlDatabase sqlDatabase;
    QSqlQuery sql_query;
    void insertDeviceTI(const QVariantList &_TN, const QVariantList &_PN,const QVariantList &_Name,const QVariantList &_EnName);
    void selectDeviceTI();
    void sqlTest();
signals:

public slots:

private:
    //函数
    void initSql();
    void initTable();
    //变量
    QStringList tableNameList;
};

#endif // GZJSQLITE_H
