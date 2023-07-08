#include "myserialport.h"

MySerialPort::MySerialPort(QObject *parent) : QObject(parent)
{
    my_thread = new QThread();
    this->moveToThread(my_thread);
    my_thread->start();  //启动线程
    //uiconnect
    connect(this,&MySerialPort::SignStartThread,this,&MySerialPort::SlotStartThread);
    connect(this,&MySerialPort::signSetSetting,this,&MySerialPort::setSettings);
}

MySerialPort::~MySerialPort()
{
    port->close();
    port->deleteLater();
    my_thread->quit();
    my_thread->wait();
    my_thread->deleteLater();
}

SeriSettings *MySerialPort::settings() const
{
    return m_settings;
}

void MySerialPort::setSettings(const QString &str_portN ,const int &i_parity ,const int &i_baud ,
                               const int &i_dateB ,const int &i_stopB ,const int &i_flowC)
{
    if(port->isOpen()){
        port->close();
    }
    m_settings->setSeriSettings(str_portN,i_parity,i_baud,i_dateB,i_stopB,i_flowC);
    open_port();
}

void MySerialPort::open_port()
{
    //扫描本机的串口，并且添加到下拉框里
    //    foreach(const QSerialPortInfo &info, QSerialPortInfo::availablePorts()) {
    //        qDebug()<<info.portName();
    //    }
    if(!port->isOpen()){
        port->setPortName(m_settings->PortName);                   //串口名 windows下写作COM1
        port->setBaudRate(m_settings->baud);                           //波特率
        port->setDataBits(QSerialPort::DataBits(m_settings->dataBits));             //数据位
        port->setStopBits(QSerialPort::StopBits(m_settings->stopBits));           //停止位
        port->setParity(QSerialPort::Parity(m_settings->parity));            //奇偶校验
        port->setFlowControl(QSerialPort::FlowControl(m_settings->flowControl));  //流控制
        if (port->open(QIODevice::ReadWrite))
        {
            Singleton<Log>::getInstance().debug("Port have been opened");
        }
        else
        {
            Singleton<Log>::getInstance().debug("open it failed");
        }
    }
}

void MySerialPort::bufferData()
{
    //定时3.5个字符长度
    readTimer->start(quint32(38.5/m_settings->baud*1000+1));
    buffArray.append(port->readAll());
}

void MySerialPort::handle_data()
{
    readTimer->stop();
    qDebug() << QThread::currentThreadId() <<QStringLiteral("   data received(收到的数据):") << buffArray;
    emit receive_data("hjj",buffArray);
    //    write_data();
    buffArray.clear();
}

void MySerialPort::write_data()
{
    //      port->write("data", 4);   //发送“data”字符
    //        qDebug() << QThread::currentThreadId() <<" write tid";
    port->write(QByteArray::fromHex("2143"));

}

void MySerialPort::SlotStartThread()
{
    {
        QMutexLocker locker(&APISgrH::seriThreadNameSN_mutex);
        QThread::currentThread()->setObjectName(QString("%1%2%3").arg("seri").arg(APISgrH::seriThreadNameSN++).arg("线程"));
    }
    //初始化变量
    port = new QSerialPort();
    readTimer=new QTimer(this);
    m_settings=new SeriSettings();
    //uiConnect
    connect(port, SIGNAL(readyRead()), this, SLOT(bufferData()), Qt::QueuedConnection); //Qt::DirectConnection
    connect(readTimer,&QTimer::timeout,this,&MySerialPort::handle_data);
}
