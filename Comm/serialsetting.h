#ifndef SERIALSETTING_H
#define SERIALSETTING_H
#include <QSerialPort>      //串口类
#include <QSerialPortInfo>  //串口信息类
#include <QWidget>
#include "Comm/myserialport.h"

using namespace rapidjson;
namespace Ui {
class SerialSetting;
}

//class Worker : public QObject
//  {
//      Q_OBJECT

//  public slots:
//      void doWork(const QString &parameter) {
//          QString result;
//          result=parameter;
//          emit resultReady(result);
//      }
//  signals:
//      void resultReady(const QString &result);
//  };

class SerialSetting : public QWidget
{
    Q_OBJECT

public:
    explicit SerialSetting(QWidget *parent = nullptr);
    ~SerialSetting();
    struct SeriSettings {
        int parity = QSerialPort::NoParity;
        int baud = QSerialPort::Baud9600;
        int dataBits = QSerialPort::Data8;
        int stopBits = QSerialPort::OneStop;
    }struct_seriSetting;
    SeriSettings *settings() const;
    void changeComboBox();
signals:
    void operate(const QString &);

    void signToTcpSend(const QByteArray &_data);
public slots:

    void bufferData();
    void bufferData1();
    void readData();
    void readData1();
    void readSeriSetting(QString _strDom);
    void writeSeriSetting(const QVariantList &VL_SP,const QVariantList &VL_Baud,
                          const QVariantList &VL_CB,const QVariantList &VL_DB,const QVariantList &VL_SB);
private:
#if 1
    MySerialPort *msp1;
    MySerialPort *msp2;
    QThread workerThread;
    //以上测试用代码
#endif
    //变量
    QSerialPort * serialPort1=new QSerialPort();
    QSerialPort * serialPort2=new QSerialPort();
    QSerialPort * serialPort3=new QSerialPort();
    QSerialPort * serialPort4=new QSerialPort();
    QVector<QSerialPort*> VectorSerialPort;
    QVector<QPushButton*> VectorPushBotton;
    QVector<QString> VectorPortName;
    QVector<QByteArray> VectorClcCmd;

    QComboBox *parityCombo[4];
    QComboBox *baudCombo[4];
    QComboBox *dataBitsCombo[4];
    QComboBox *stopBitsCombo[4];
    QTimer *readTimer=nullptr;
    QTimer *readTimer1=nullptr;
    QByteArray buffArray;
    QByteArray buffArray1;
    SeriSettings *m_settings=nullptr;
    Ui::SerialSetting *ui;
    //函数
    void modifySetting(const QString &_SP,const int &_Baud,const QString &_CB,const int &_DB,const double &_SB);
    void serialControl(quint8 serialNum,QString portName,int flag);//打开串口
    void initSeri();
    void uiConnect();
};


#endif // SERIALSETTING_H
