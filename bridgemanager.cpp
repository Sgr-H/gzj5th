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

//初始化
void BridgeManager::init()
{
    //初始化变量
    m_indepElect=new IndepElect();
}
//关于UI的信号槽
void BridgeManager::UIconnect()
{
    connect(this,&BridgeManager::SignPriEquip,m_indepElect,&IndepElect::SlotPriEquip);
}
