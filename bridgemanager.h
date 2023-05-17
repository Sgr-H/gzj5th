#ifndef BRIDGEMANAGER_H
#define BRIDGEMANAGER_H

#include <QObject>

#include "View/indepelect.h"
#include "View/loginwidget.h"
#include "View/logprintwidget.h"

class BridgeManager : public QObject
{
    SINGLETON(BridgeManager)
    Q_OBJECT
public:
    void test();
    IndepElect * IndepElectINS()const;//返回独立电实例
    LogInWidget * LogInWidgetIns()const;//返回登录实例
    logPrintWidget *logPrintWidgetINS()const;//返回日志实例
    //explicit BridgeManager(QObject *parent = nullptr);

signals:
    void SignPriEquip(const int &_var);
public slots:

private:
    //变量
        IndepElect *m_indepElect=nullptr;
        LogInWidget *m_logInWidget=nullptr;
        logPrintWidget *m_logPrintWidget=nullptr;
    //函数
    void init();
    void UIconnect();
};

#endif // BRIDGEMANAGER_H
