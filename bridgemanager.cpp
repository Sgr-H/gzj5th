#include "bridgemanager.h"

BridgeManager::BridgeManager()
{
    init();
    UIconnect();
}
BridgeManager::~BridgeManager()
{

}

void BridgeManager::test()
{
    qDebug()<<"BM test!";
}

//返回独立电实例
IndepElect *BridgeManager::IndepElectINS() const
{
    return m_indepElect;
}
//返回登录实例
LogInWidget *BridgeManager::LogInWidgetIns() const
{
    return m_logInWidget;
}

logPrintWidget *BridgeManager::logPrintWidgetINS() const
{
    return m_logPrintWidget;
}

date1View *BridgeManager::date1ViewINS() const
{
    return m_date1View;
}

date2View *BridgeManager::date2ViewINS() const
{
    return m_date2View;
}

date3Elect *BridgeManager::date3ElectINS() const
{
    return m_date3Elect;
}

date3Water *BridgeManager::date3WaterINS() const
{
    return m_date3Water;
}

date3lift *BridgeManager::date3liftINS() const
{
    return m_date3lift;
}

date3Airc *BridgeManager::date3AircINS() const
{
    return m_date3Airc;
}

date3Shaft *BridgeManager::date3ShaftINS() const
{
    return m_date3Shaft;
}

//初始化
void BridgeManager::init()
{
    //初始化变量
    m_indepElect=new IndepElect();
    m_logInWidget=new LogInWidget();
    m_logPrintWidget=new logPrintWidget();
    m_date1View=new date1View();
    m_date2View=new date2View();
    m_date3Elect=new date3Elect();
    m_date3Water=new date3Water();
    m_date3lift=new date3lift();
    m_date3Airc=new date3Airc();
    m_date3Shaft=new date3Shaft();
}
//关于UI的信号槽
void BridgeManager::UIconnect()
{
    connect(this,&BridgeManager::SignPriEquip,m_indepElect,&IndepElect::SlotPriEquip);
}
