#include "serialsettingmanager.h"

SerialSettingManager::SerialSettingManager()
{
    initController();
}
SerialSettingManager::~SerialSettingManager()
{
    threadCount->quit();
    threadCount->wait();
}
void SerialSettingManager::quitCountThreadSlot()
{
    qDebug()<<"ok";
}

void SerialSettingManager::initController()
{
    threadCount=new QThread;
    serialSettingModel=new SerialSettingModel();
    serialSettingModel->moveToThread(threadCount);
    connect(this,&SerialSettingManager::startedCountSignal,serialSettingModel,&SerialSettingModel::countSlot);
    connect(threadCount,&QThread::finished,threadCount,&QThread::deleteLater);
    connect(this,&SerialSettingManager::finishedCountSignal,this,&SerialSettingManager::quitCountThreadSlot);
    //协议解析工作启动
    connect(this,&SerialSettingManager::msgParse,serialSettingModel,&SerialSettingModel::msgParse);
    //通知网络发送数据
    connect(serialSettingModel,&SerialSettingModel::SModelSignToTcpSend,this,&SerialSettingManager::SManagerSignToTcpSend);
    threadCount->start();

}
