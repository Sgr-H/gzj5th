#include "tcpclientmanager.h"

TcpClientManager::TcpClientManager()
{
    initController();
}

TcpClientManager::~TcpClientManager()
{
    threadCount->quit();
    threadCount->wait();
}

void TcpClientManager::quitCountThreadSlot()
{
    qDebug()<<"qct ok";
}

void TcpClientManager::initController()
{
//    if(threadCount){
//        return;
//    }
    threadCount=new QThread;
    tcpClientModel=new TcpClientModel();
    tcpClientModel->moveToThread(threadCount);
    connect(this,&TcpClientManager::startedCountSignal,tcpClientModel,&TcpClientModel::countSlot);
    connect(threadCount,&QThread::finished,threadCount,&QThread::deleteLater);
    connect(this,&TcpClientManager::finishedCountSignal,this,&TcpClientManager::quitCountThreadSlot);
    connect(this,&TcpClientManager::msgParse,tcpClientModel,&TcpClientModel::msgParse);
    threadCount->start();
}
