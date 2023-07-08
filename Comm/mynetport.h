#ifndef MYNETPORT_H
#define MYNETPORT_H

#include <QObject>
using namespace rapidjson;
class MyNetPort : public QObject
{
    Q_OBJECT
public:
    explicit MyNetPort(QObject *parent = nullptr);
    ~MyNetPort();
signals:
    void SignStartThread();
public slots:
    void receiveMessages();
    void socketStateChange(QAbstractSocket::SocketState);
    void SlotStartThread();
    void sendMessages(const QByteArray &_data);
    void toConnect();
    void toDisConnect();
    //心跳包
    void heartBS();
    //重连网络
    void reConnectT();
private:
    //变量
    QTimer *heartBeat=nullptr;
    QTimer *reConnectTimer=nullptr;
    QThread *my_thread;
    QTcpSocket *tcpSocket=nullptr;
    Document jDHeartBeat;
    Document::AllocatorType& allocator=jDHeartBeat.GetAllocator();
    //函数
    void initJson();
    QString getHostMacAddress();

};

#endif // MYNETPORT_H
