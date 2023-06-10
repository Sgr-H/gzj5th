#ifndef GZJSQLITE_H
#define GZJSQLITE_H

#include <QObject>
#include "APISgrH/APISgrH.h"

class GzjSqlite : public QObject
{
    SINGLETON(GzjSqlite)
    Q_OBJECT
    public:

    QSqlDatabase sqlDatabase;
    QSqlQuery sql_query;
    void insertDeviceTI(const struct_deviceTI &_struct_DTI);
    void insertTargetTI(const struct_targetTI &_struct_TTI);
    void insertDeviceMI(const struct_deviceMI &_struct_DMI);
    void insertCircCT(const struct_circCT &_struct_CCT);
    void sqlTest(const QString &sql_str);
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
