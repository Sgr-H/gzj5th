#ifndef MYSERIALPORT_H
#define MYSERIALPORT_H

#include <QObject>
#include <QSerialPort>      //串口类
#include <QSerialPortInfo>  //串口信息类
#include "APISgrH/APISgrH.h"

class MySerialPort : public QObject
{
    Q_OBJECT
public:
    explicit MySerialPort(QObject *parent = NULL);
    ~MySerialPort();
    SeriSettings *settings() const;
    void setSettings(const QString &str_portN ,const int &i_parity ,const int &i_baud ,const int &i_dateB ,const int &i_stopB ,const int &i_flowC);
public slots:
    void open_port();  //初始化串口
    void bufferData();    //3.5字节数
    void handle_data();  //处理接收到的数据
    void write_data();     //发送数据
    void SlotStartThread();
signals:
    //测试用信号
    void test();
    //修改seriSettings
    void signSetSetting(const QString &str_portN ,const int &i_parity ,const int &i_baud ,const int &i_dateB ,const int &i_stopB ,const int &i_flowC);
    //接收数据
    void SignStartThread();
    void receive_data(const QByteArray &tmp,const QByteArray &tmp1);

private:
    QTimer *readTimer=nullptr;
    QByteArray buffArray;
    QThread *my_thread;
    QSerialPort *port;
    SeriSettings *m_settings=nullptr;
    int i;
};

#endif // MYSERIALPORT_H
