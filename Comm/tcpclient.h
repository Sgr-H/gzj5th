#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include <QWidget>
using namespace rapidjson;
namespace Ui {
class TcpClient;
}

class TcpClient : public QWidget
{
    Q_OBJECT

public:
    explicit TcpClient(QWidget *parent = nullptr);
    ~TcpClient();
signals:
    void readSeriSetting(QString _strDom);
    void writeSeriSetting(const QVariantList &VL_SP,const QVariantList &VL_Baud,
                          const QVariantList &VL_CB,const QVariantList &VL_DB,const QVariantList &VL_SB);
public slots:
    void connected();
    void disconnected();
    void receiveMessages();
    void socketStateChange(QAbstractSocket::SocketState);
    void toConnect();
    void toDisConnect();
    //心跳包
    void heartBS();
    void sendMessages(const QByteArray &_data);
private:
    Ui::TcpClient *ui;
    //函数
    void getLocalHostIP();
    QString getHostMacAddress();
    void initTcpC();
    void uiConnect();
    void initJson();
    //变量
    QTimer *heartBeat=nullptr;
    QTcpSocket *tcpSocket=nullptr;
    QList<QHostAddress>IPlist;
    Document jDHeartB;
    Document::AllocatorType& allocator=jDHeartB.GetAllocator();

};

#endif // TCPCLIENT_H
