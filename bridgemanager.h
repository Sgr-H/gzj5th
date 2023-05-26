#ifndef BRIDGEMANAGER_H
#define BRIDGEMANAGER_H

#include <QObject>

#include "View/indepelect.h"
#include "View/loginwidget.h"
#include "View/logprintwidget.h"
#include "View/date1view.h"
#include "View/date2view.h"
#include "View/date3elect.h"
#include "View/date3water.h"
#include "View/date3lift.h"
#include "View/date3airc.h"
#include "View/date3shaft.h"

class BridgeManager : public QObject
{
    SINGLETON(BridgeManager)
    Q_OBJECT
public:
    void test();
    IndepElect * IndepElectINS()const;//返回独立电实例
    LogInWidget * LogInWidgetIns()const;//返回登录实例
    logPrintWidget *logPrintWidgetINS()const;//返回日志实例
    date1View *date1ViewINS()const;//返回数据界面1实例
    date2View *date2ViewINS()const;//返回数据界面2实例
    date3Elect *date3ElectINS()const;//返回数据界面3电表实例
    date3Water *date3WaterINS()const;//返回数据界面3水表实例
    date3lift *date3liftINS()const;//返回数据界面3电梯实例
    date3Airc *date3AircINS()const;//返回数据界面3空调实例
    date3Shaft *date3ShaftINS()const;//返回数据界面3窨井实例

    //explicit BridgeManager(QObject *parent = nullptr);

signals:
    void SignPriEquip(const int &_var);
public slots:

private:
    //变量
        IndepElect *m_indepElect=nullptr;
        LogInWidget *m_logInWidget=nullptr;
        logPrintWidget *m_logPrintWidget=nullptr;
        date1View *m_date1View=nullptr;
        date2View *m_date2View=nullptr;
        date3Elect *m_date3Elect=nullptr;
        date3Water *m_date3Water=nullptr;
        date3lift *m_date3lift=nullptr;
        date3Airc *m_date3Airc=nullptr;
        date3Shaft *m_date3Shaft=nullptr;
    //函数
    void init();
    void UIconnect();
};

#endif // BRIDGEMANAGER_H
