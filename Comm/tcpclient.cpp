#include "tcpclient.h"
#include "ui_tcpclient.h"
#include "APISgrH/APISgrH.h"
#include "tcpclientmanager.h"
#include "log.h"

TcpClient::TcpClient(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TcpClient)
{
    ui->setupUi(this);
    initTcpC();
    initJson();
    uiConnect();
    toConnect();
}

TcpClient::~TcpClient()
{
    delete ui;
}

void TcpClient::connected()
{
    ui->textBrowser->append("已经连上服务端");
    ui->pushButton->setEnabled(false);
    ui->pushButton_2->setEnabled(true);
    ui->comboBox->setEnabled(false);
    ui->spinBox->setEnabled(false);
    ui->lineEdit->setEnabled(false);
}

void TcpClient::disconnected()
{
    ui->textBrowser->append("已经断开服务端");
    ui->pushButton->setEnabled(true);
    ui->pushButton_2->setEnabled(false);
    ui->comboBox->setEnabled(true);
    ui->spinBox->setEnabled(true);
    ui->lineEdit->setEnabled(true);
}

void TcpClient::receiveMessages()
{
    QByteArray messageB=tcpSocket->readAll();
    ui->textBrowser->append("服务端："+QString(messageB));
    qDebug()<<messageB;
    emit Singleton<TcpClientManager>::getInstance().msgParse(QString(messageB));
}

void TcpClient::socketStateChange(QAbstractSocket::SocketState)
{
    if(nullptr==tcpSocket)
        return;
    if(tcpSocket->state()==tcpSocket->ConnectedState){
        QString tmpMac=getHostMacAddress().remove(':');
        ui->textBrowser->append(tmpMac);
        tcpSocket->write(tmpMac.toUtf8().data());
        if(!heartBeat->isActive())
            heartBeat->start(30000);
    }
    else if(tcpSocket->state()==tcpSocket->UnconnectedState){
        if(heartBeat->isActive())
            heartBeat->stop();
    }

}

void TcpClient::getLocalHostIP()
{
    QList<QNetworkInterface> list
            = QNetworkInterface::allInterfaces();

    /* 遍历 list */
    foreach (QNetworkInterface interface, list) {
        /* QNetworkAddressEntry 类存储 IP 地址子网掩码和广播地址 */
        QList<QNetworkAddressEntry> entryList
                = interface.addressEntries();

        /* 遍历 entryList */
        foreach (QNetworkAddressEntry entry, entryList) {
            /* 过滤 IPv6 地址，只留下 IPv4 */
            if (entry.ip().protocol() ==
                    QAbstractSocket::IPv4Protocol) {
                ui->comboBox->addItem(entry.ip().toString());
                /* 添加到 IP 列表中 */
                IPlist<<entry.ip();
            }
        }
    }
}

QString TcpClient::getHostMacAddress()
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

void TcpClient::initTcpC()
{
    //隐藏
    ui->lineEdit_2->setVisible(false);
    ui->lineEdit_3->setVisible(false);
    ui->pushButton_4->setVisible(false);
    ui->pushButton_5->setVisible(false);

    this->setWindowTitle("客户端");
    //初始化变量
    Singleton<TcpClientManager>::getInstance();

    tcpSocket=new QTcpSocket(this);
    heartBeat=new QTimer(this);
    getLocalHostIP();
}

void TcpClient::uiConnect()
{
    connect(tcpSocket,SIGNAL(connected()),this,SLOT(connected()));
    connect(tcpSocket,SIGNAL(disconnected()),this,SLOT(disconnected()));
    connect(tcpSocket,SIGNAL(readyRead()),this,SLOT(receiveMessages()));
    connect(tcpSocket,SIGNAL(stateChanged(QAbstractSocket::SocketState)),
            this,SLOT(socketStateChange(QAbstractSocket::SocketState)));
    //心跳定时
    connect(heartBeat,&QTimer::timeout,this,&TcpClient::heartBS);

    //业务层数据发送
    connect(&Singleton<TcpClientManager>::getInstance(),&TcpClientManager::modelSend,this,&TcpClient::sendMessages);

    //发送处理操作信号到串口
    connect(&Singleton<TcpClientManager>::getInstance(),&TcpClientManager::readSeriSetting,this,&TcpClient::readSeriSetting);
    connect(&Singleton<TcpClientManager>::getInstance(),&TcpClientManager::writeSeriSetting,this,&TcpClient::writeSeriSetting);
    //按钮信号槽
    connect(ui->pushButton,&QPushButton::clicked,this,&TcpClient::toConnect);
    connect(ui->pushButton_2,&QPushButton::clicked,this,&TcpClient::toDisConnect);

    connect(ui->pushButton_6,&QPushButton::clicked,this,[]{
        emit Singleton<TcpClientManager>::getInstance().startedCountSignal();
    });
}

void TcpClient::initJson()
{
    jDHeartB.SetObject();
    jDHeartB.AddMember(gzj_RequestC, gzj_noneStr, allocator);
    jDHeartB.AddMember(gzj_ProtocolV, Ver_gzjVersion, allocator);
    jDHeartB.AddMember(gzj_FunctionC, FN_gzjHeartBeat, allocator);
    jDHeartB.AddMember(gzj_OperationC, OP_gzjNone, allocator);
    jDHeartB.AddMember(gzj_AnswerF, AF_gzjAnswerNoData, allocator);


    //    StringBuffer buf;
    //    Writer<rapidjson::StringBuffer> writer(buf);
    //    writer.StartObject();
    //    writer.Key(gzj_RequestC); writer.String(STRDATETIMEMSSP);
    //    writer.Key(gzj_ProtocolV); writer.String(Ver_gzjVersion);
    //    writer.Key(gzj_FunctionC); writer.String(FN_gzjHeartBeat);
    //    writer.Key(gzj_OperationC); writer.String(OP_gzjNone);
    //    writer.Key(gzj_FunctionC); writer.Int(AF_gzjAnswerData);
    //    writer.EndObject();
    //    const char* json_content = buf.GetString();

}

void TcpClient::toConnect()
{
    if(tcpSocket->state()!=tcpSocket->ConnectedState){
        tcpSocket->connectToHost(ui->lineEdit->text()/*ui->comboBox_2->currentText()*//*IPlist[ui->comboBox_2->currentIndex()]*/,
                                 quint16(ui->spinBox->value()));
    }
}

void TcpClient::toDisConnect()
{
    tcpSocket->disconnectFromHost();
    tcpSocket->close();
}

void TcpClient::heartBS()
{
    Value& v1 = jDHeartB[gzj_RequestC];
    v1.SetString(STRDATETIMEMSSP,QString(STRDATETIMEMSSP).size());
    StringBuffer buf;
    Writer<rapidjson::StringBuffer> writer(buf);
    jDHeartB.Accept(writer);

    tcpSocket->write(buf.GetString());
    ui->textBrowser->append("客户端："+QString(buf.GetString()));
}

void TcpClient::sendMessages(const QByteArray &_data)
{
    if(nullptr==tcpSocket)
            return;
        if(tcpSocket->state()==tcpSocket->ConnectedState){
            qDebug()<<_data.data();
            tcpSocket->write(_data);
            ui->textBrowser->append("客户端："+QString(_data));
        }
}
