#include "mynetport.h"
#include "APISgrH/APISgrH.h"
#include "tcpclientmanager.h"
MyNetPort::MyNetPort(QObject *parent) : QObject(parent)
{
    my_thread = new QThread();
    this->moveToThread(my_thread);
    my_thread->start();  //启动线程
    connect(this,&MyNetPort::SignStartThread,this,&MyNetPort::SlotStartThread);
}

MyNetPort::~MyNetPort()
{
    tcpSocket->close();
    tcpSocket->deleteLater();
    my_thread->quit();
    my_thread->wait();
    my_thread->deleteLater();
}

void MyNetPort::receiveMessages()
{
    qDebug()<<"tcp state:  "<<tcpSocket->state();
    QByteArray messageB=tcpSocket->readAll();
    emit Singleton<TcpClientManager>::getInstance().msgParse(QString(messageB));
}

void MyNetPort::socketStateChange(QAbstractSocket::SocketState)
{
    if(nullptr==tcpSocket)
        return;
    if(tcpSocket->state()==tcpSocket->ConnectedState){
        QString tmpMac=getHostMacAddress().remove(':');
        tcpSocket->write(tmpMac.toUtf8().data());
        if(!heartBeat->isActive()){
            heartBeat->start(30000);
        }
        if(reConnectTimer->isActive()){
            reConnectTimer->stop();
        }

    }
    else if(tcpSocket->state()==tcpSocket->UnconnectedState){
        if(heartBeat->isActive()){
            heartBeat->stop();
        }
        if(!reConnectTimer->isActive()){
            reConnectTimer->start(30000);
        }
        toConnect();
    }
}

void MyNetPort::SlotStartThread()
{
    QThread::currentThread()->setObjectName("tcp线程");
    //初始化变量
    tcpSocket = new QTcpSocket(this);
    heartBeat=new QTimer(this);
    reConnectTimer=new QTimer(this);
    initJson();
    reConnectTimer->start(30000);
    toConnect();
    //uiConnect

    connect(tcpSocket,SIGNAL(readyRead()),this,SLOT(receiveMessages()));
    connect(tcpSocket,SIGNAL(stateChanged(QAbstractSocket::SocketState)),
            this,SLOT(socketStateChange(QAbstractSocket::SocketState)));
    //心跳定时
    connect(heartBeat,&QTimer::timeout,this,&MyNetPort::heartBS);
    //业务层数据发送
    connect(&Singleton<TcpClientManager>::getInstance(),&TcpClientManager::modelSend,this,&MyNetPort::sendMessages);
    //重连定时
    connect(reConnectTimer,&QTimer::timeout,this,&MyNetPort::reConnectT);

}

void MyNetPort::sendMessages(const QByteArray &_data)
{
    if(nullptr==tcpSocket)
            return;
        if(tcpSocket->state()==tcpSocket->ConnectedState){
            tcpSocket->write(_data);
        }
}

void MyNetPort::toConnect()
{
    if(tcpSocket->state()!=tcpSocket->ConnectedState){
        tcpSocket->abort();
        tcpSocket->connectToHost("192.168.0.199",9999 ,QAbstractSocket::ReadWrite, QAbstractSocket::IPv4Protocol);

//        tcpSocket->connectToHost(ui->lineEdit->text()/*ui->comboBox_2->currentText()*//*IPlist[ui->comboBox_2->currentIndex()]*/,
//                                 quint16(ui->spinBox->value()));
    }
}

void MyNetPort::toDisConnect()
{
    tcpSocket->disconnectFromHost();
    tcpSocket->close();
}

void MyNetPort::heartBS()
{
    Value& v1 = jDHeartBeat[gzj_RequestC];
    v1.SetString(STRDATETIMEMSSP,QString(STRDATETIMEMSSP).size());
    StringBuffer buf;
    Writer<rapidjson::StringBuffer> writer(buf);
    jDHeartBeat.Accept(writer);
    tcpSocket->write(buf.GetString());
}

void MyNetPort::reConnectT()
{
    QMetaEnum metaEnum = QMetaEnum::fromType<QAbstractSocket::SocketState>();
    Singleton<Log>::getInstance().debug(metaEnum.valueToKey(tcpSocket->state()));
//    toConnect();
}

void MyNetPort::initJson()
{
    jDHeartBeat.SetObject();
    jDHeartBeat.AddMember(gzj_RequestC, gzj_noneStr, allocator);
    jDHeartBeat.AddMember(gzj_ProtocolV, Ver_gzjVersion, allocator);
    jDHeartBeat.AddMember(gzj_FunctionC, FN_gzjHeartBeat, allocator);
    jDHeartBeat.AddMember(gzj_OperationC, OP_gzjNone, allocator);
    jDHeartBeat.AddMember(gzj_AnswerF, AF_gzjAnswerNoData, allocator);
}

QString MyNetPort::getHostMacAddress()
{
    QList<QNetworkInterface> nets = QNetworkInterface::allInterfaces();// 获取所有网络接口列表
    int nCnt = nets.count();
    //    qDebug()<<nets;
    QString strMacAddr = "";
    for(int i = 0; i < nCnt; i ++)
    {
        // 如果此网络接口被激活并且正在运行并且不是回环地址，且该mac的ip地址不能是回环地址并且是ipv4地址，则就是我们需要找的Mac地址
        if(nets[i].flags().testFlag(QNetworkInterface::IsUp) &&
                nets[i].flags().testFlag(QNetworkInterface::IsRunning)
                && !nets[i].flags().testFlag(QNetworkInterface::IsLoopBack))
        {
            for (int j=0;j<nets[i].addressEntries().size() ;j++ ) {
                //该mac的ip地址不能为172.0.0.1，且需是ipv4地址
                if(nets[i].addressEntries().at(j).ip()!=QHostAddress::LocalHost&&nets[i].addressEntries().at(j).ip().protocol()== QAbstractSocket::IPv4Protocol
                        ){
                    strMacAddr = nets[i].hardwareAddress();
                }
            }
        }
    }
    Singleton<Log>::getInstance().debug("strMacAddr:  "+strMacAddr);
    return strMacAddr;
}
