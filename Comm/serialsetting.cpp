#include "serialsetting.h"
#include "ui_serialsetting.h"
#include "Comm/serialsettingmanager.h"
#include "gzjsqlite.h"

rapidjson::Value str_value_rj_seri(rapidjson::kStringType);
SerialSetting::SerialSetting(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SerialSetting)
{
    ui->setupUi(this);
//    initSeri();
//    uiConnect();

    msp1 = new MySerialPort();
    emit msp1->SignStartThread();
    emit msp1->signSetSetting(QString("/dev/ttymxc2"),QSerialPort::NoParity,QSerialPort::Baud9600,QSerialPort::Data8,QSerialPort::OneStop,QSerialPort::NoFlowControl);
//    msp2 = new MySerialPort();
//    emit msp2->SignStartThread();
//    emit msp2->signSetSetting(QString("/dev/ttymxc0"),QSerialPort::NoParity,QSerialPort::Baud9600,QSerialPort::Data8,QSerialPort::OneStop,QSerialPort::NoFlowControl);

    connect(ui->pushButton_3,&QPushButton::clicked,msp1,&MySerialPort::write_data);
    connect(msp1,&MySerialPort::receive_data,&Singleton<SerialSettingManager>::getInstance(),&SerialSettingManager::msgParse);

//    Worker *worker = new Worker;
//    worker->moveToThread(&workerThread);
//    connect(&workerThread, &QThread::finished, worker, &QObject::deleteLater);
//    connect(this, &SerialSetting::operate, worker, &Worker::doWork);
//    workerThread.start();
//    emit operate("hjj");

}

SerialSetting::~SerialSetting()
{
    delete ui;
    workerThread.quit();
    workerThread.wait();
}

SerialSetting::SeriSettings *SerialSetting::settings() const
{
    return m_settings;
}

void SerialSetting::changeComboBox()
{
    for (int var = 0; var < 4; ++var) {

        switch (m_settings[var].parity) {
        case 0:
            parityCombo[var]->setCurrentIndex(0);
            break;
        case 2:
            parityCombo[var]->setCurrentIndex(1);
            break;
        case 3:
            parityCombo[var]->setCurrentIndex(2);
            break;
        case 4:
            parityCombo[var]->setCurrentIndex(3);
            break;
        case 5:
            parityCombo[var]->setCurrentIndex(4);
            break;
        default:
            break;
        }

        switch (m_settings[var].baud) {
        case 1200:
            baudCombo[var]->setCurrentIndex(0);
            break;
        case 2400:
            baudCombo[var]->setCurrentIndex(1);
            break;
        case 4800:
            baudCombo[var]->setCurrentIndex(2);
            break;
        case 9600:
            baudCombo[var]->setCurrentIndex(3);
            break;
        case 19200:
            baudCombo[var]->setCurrentIndex(4);
            break;
        case 38400:
            baudCombo[var]->setCurrentIndex(5);
            break;
        case 57600:
            baudCombo[var]->setCurrentIndex(6);
            break;
        case 115200:
            baudCombo[var]->setCurrentIndex(7);
            break;
        default:
            break;
        }

        switch (m_settings[var].dataBits) {
        case 5:
            dataBitsCombo[var]->setCurrentIndex(0);
            break;
        case 6:
            dataBitsCombo[var]->setCurrentIndex(1);
            break;
        case 7:
            dataBitsCombo[var]->setCurrentIndex(2);
            break;
        case 8:
            dataBitsCombo[var]->setCurrentIndex(3);
            break;

        default:
            break;
        }

        switch (m_settings[var].stopBits) {
        case 1:
            stopBitsCombo[var]->setCurrentIndex(0);
            break;
        case 2:
            stopBitsCombo[var]->setCurrentIndex(1);
            break;
        case 3:
            stopBitsCombo[var]->setCurrentIndex(2);
            break;

        default:
            break;
        }

    }
}

void SerialSetting::bufferData()
{
    //定时50ms
    readTimer->start(quint32(38.5/m_settings[0].baud*1000+1));
    buffArray.append(VectorSerialPort.at(0)->readAll());
}

void SerialSetting::bufferData1()
{
    qDebug()<<"seri1 tId:" <<QThread::currentThreadId();

    //定时50ms
    readTimer1->start(quint32(38.5/m_settings[1].baud*1000+1));
    buffArray1.append(VectorSerialPort.at(1)->readAll());
}

void SerialSetting::readData()
{
    readTimer->stop();
    ui->textBrowser->append("服务端："+buffArray.toHex());
    emit Singleton<SerialSettingManager>::getInstance().msgParse(/*VectorClcCmd.at(0)*/" ",buffArray);
    buffArray.clear();
}

void SerialSetting::readData1()
{
    readTimer1->stop();
    ui->textBrowser->append("服务端："+buffArray1.toHex());
    emit Singleton<SerialSettingManager>::getInstance().msgParse(/*VectorClcCmd.at(0)*/" ",buffArray1);
    buffArray1.clear();
}

//向上位机发送串口配置信号
void SerialSetting::readSeriSetting(QString _strDom)
{
    Document dom;
    if(!dom.Parse(_strDom.toStdString().c_str()).HasParseError()){
        Document send_dom;
        Document::AllocatorType& allocator=send_dom.GetAllocator();
        str_value_rj_seri.SetString(dom[gzj_RequestC].GetString(),allocator);
        send_dom.SetObject();
        send_dom.AddMember(gzj_RequestC, str_value_rj_seri, allocator);
        send_dom.AddMember(gzj_ProtocolV, Ver_gzjVersion, allocator);
        send_dom.AddMember(gzj_FunctionC, FN_gzjSeriS, allocator);
        send_dom.AddMember(gzj_OperationC, OP_gzjRead, allocator);
        send_dom.AddMember(gzj_FunctionC, AF_gjzAnswerData, allocator);
        if (dom.HasMember("Data"))
        {
            Value Data;
            Data=dom["Data"];
            Value DataArray(rapidjson::kArrayType);
            for (rapidjson::SizeType i = 0; i < Data.Size(); i++)
            {
                Value DataObj(rapidjson::kObjectType);
                if(!QString(Data[i].GetString()).compare("485-1")){
                    DataObj.AddMember("SP","485-1", allocator);
                    str_value_rj_seri.SetInt(m_settings[0].baud);
                    DataObj.AddMember("Baud",str_value_rj_seri,allocator);
                    switch (m_settings[0].parity) {
                    case 0:
                        DataObj.AddMember("CB","None",allocator);
                        break;
                    case 2:
                        DataObj.AddMember("CB","Even",allocator);
                        break;
                    case 3:
                        DataObj.AddMember("CB","Odd",allocator);
                        break;
                    case 4:
                        DataObj.AddMember("CB","Space",allocator);
                        break;
                    case 5:
                        DataObj.AddMember("CB","Mark",allocator);
                        break;
                    default:
                        break;
                    }
                    str_value_rj_seri.SetInt(m_settings[0].dataBits);
                    DataObj.AddMember("DB",str_value_rj_seri,allocator);
                    switch (m_settings[0].stopBits) {
                    case 1:
                        DataObj.AddMember("SB",1.0,allocator);
                        break;
                    case 2:
                        DataObj.AddMember("SB",2.0,allocator);
                        break;
                    case 3:
                        DataObj.AddMember("SB",1.5,allocator);
                        break;
                    default:
                        break;
                    }
                    DataArray.PushBack(DataObj,allocator);
                }
                if(!QString(Data[i].GetString()).compare("485-2")){
                    DataObj.AddMember("SP","485-2", allocator);
                    str_value_rj_seri.SetInt(m_settings[1].baud);
                    DataObj.AddMember("Baud",str_value_rj_seri,allocator);
                    switch (m_settings[1].parity) {
                    case 0:
                        DataObj.AddMember("CB","None",allocator);
                        break;
                    case 2:
                        DataObj.AddMember("CB","Even",allocator);
                        break;
                    case 3:
                        DataObj.AddMember("CB","Odd",allocator);
                        break;
                    case 4:
                        DataObj.AddMember("CB","Space",allocator);
                        break;
                    case 5:
                        DataObj.AddMember("CB","Mark",allocator);
                        break;
                    default:
                        break;
                    }
                    str_value_rj_seri.SetInt(m_settings[1].dataBits);
                    DataObj.AddMember("DB",str_value_rj_seri,allocator);
                    switch (m_settings[1].stopBits) {
                    case 1:
                        DataObj.AddMember("SB",1.0,allocator);
                        break;
                    case 2:
                        DataObj.AddMember("SB",2.0,allocator);
                        break;
                    case 3:
                        DataObj.AddMember("SB",1.5,allocator);
                        break;
                    default:
                        break;
                    }
                    DataArray.PushBack(DataObj,allocator);
                }
                if(!QString(Data[i].GetString()).compare("485-3")){
                    DataObj.AddMember("SP","485-3", allocator);
                    str_value_rj_seri.SetInt(m_settings[2].baud);
                    DataObj.AddMember("Baud",str_value_rj_seri,allocator);
                    switch (m_settings[2].parity) {
                    case 0:
                        DataObj.AddMember("CB","None",allocator);
                        break;
                    case 2:
                        DataObj.AddMember("CB","Even",allocator);
                        break;
                    case 3:
                        DataObj.AddMember("CB","Odd",allocator);
                        break;
                    case 4:
                        DataObj.AddMember("CB","Space",allocator);
                        break;
                    case 5:
                        DataObj.AddMember("CB","Mark",allocator);
                        break;
                    default:
                        break;
                    }
                    str_value_rj_seri.SetInt(m_settings[2].dataBits);
                    DataObj.AddMember("DB",str_value_rj_seri,allocator);
                    switch (m_settings[2].stopBits) {
                    case 1:
                        DataObj.AddMember("SB",1.0,allocator);
                        break;
                    case 2:
                        DataObj.AddMember("SB",2.0,allocator);
                        break;
                    case 3:
                        DataObj.AddMember("SB",1.5,allocator);
                        break;
                    default:
                        break;
                    }
                    DataArray.PushBack(DataObj,allocator);
                }
                if(!QString(Data[i].GetString()).compare("485-4")){
                    DataObj.AddMember("SP","485-4", allocator);
                    str_value_rj_seri.SetInt(m_settings[3].baud);
                    DataObj.AddMember("Baud",str_value_rj_seri,allocator);
                    switch (m_settings[3].parity) {
                    case 0:
                        DataObj.AddMember("CB","None",allocator);
                        break;
                    case 2:
                        DataObj.AddMember("CB","Even",allocator);
                        break;
                    case 3:
                        DataObj.AddMember("CB","Odd",allocator);
                        break;
                    case 4:
                        DataObj.AddMember("CB","Space",allocator);
                        break;
                    case 5:
                        DataObj.AddMember("CB","Mark",allocator);
                        break;
                    default:
                        break;
                    }
                    str_value_rj_seri.SetInt(m_settings[3].dataBits);
                    DataObj.AddMember("DB",str_value_rj_seri,allocator);
                    switch (m_settings[3].stopBits) {
                    case 1:
                        DataObj.AddMember("SB",1.0,allocator);
                        break;
                    case 2:
                        DataObj.AddMember("SB",2.0,allocator);
                        break;
                    case 3:
                        DataObj.AddMember("SB",1.5,allocator);
                        break;
                    default:
                        break;
                    }
                    DataArray.PushBack(DataObj,allocator);
                }
            }
            send_dom.AddMember("Data", DataArray, allocator);
        }
        StringBuffer buf;
        Writer<rapidjson::StringBuffer> writer(buf);
        send_dom.Accept(writer);
        QByteArray ba_data(buf.GetString());
        emit signToTcpSend(ba_data);
    }
}
//由上位机信息配置串口
void SerialSetting::writeSeriSetting(const QVariantList &VL_SP, const QVariantList &VL_Baud, const QVariantList &VL_CB, const QVariantList &VL_DB, const QVariantList &VL_SB)
{
    for (int var = 0; var < VectorPortName.count(); ++var) {
        //查看串口是否连接
        if(VectorSerialPort.at(var)->isOpen())
            VectorSerialPort.at(var)->close();
    }
    for (int var = 0; var < VL_SP.size(); ++var) {
        modifySetting(VL_SP.at(var).toString(),VL_Baud.at(var).toInt(),VL_CB.at(var).toString(),VL_DB.at(var).toInt(),VL_SB.at(var).toDouble());
    }
    changeComboBox();
    for (int var = 0; var < VectorPortName.count(); ++var) {
        serialControl(var,VectorPortName.at(var),0);
    }

}

void SerialSetting::modifySetting(const QString &_SP, const int &_Baud, const QString &_CB, const int &_DB, const double &_SB)
{
    if(!_SP.compare("485-1")){
        m_settings[0].dataBits=_DB;
        m_settings[0].baud=_Baud;
        if(!_CB.compare("None")){
            m_settings[0].parity=0;
        }
        else if(!_CB.compare("Even")){
            m_settings[0].parity=2;
        }
        else if(!_CB.compare("Odd")){
            m_settings[0].parity=3;
        }
        else if(!_CB.compare("Space")){
            m_settings[0].parity=4;
        }
        else if(!_CB.compare("Mark")){
            m_settings[0].parity=5;
        }
        if(_SB==1.0){
            m_settings[0].stopBits=1;
        }
        else if(_SB==2.0){
            m_settings[0].stopBits=2;
        }
        else if(_SB==1.5){
            m_settings[0].stopBits=3;
        }
    }

    if(!_SP.compare("485-2")){
        m_settings[1].dataBits=_DB;
        m_settings[1].baud=_Baud;
        if(!_CB.compare("None")){
            m_settings[1].parity=0;
        }
        else if(!_CB.compare("Even")){
            m_settings[1].parity=2;
        }
        else if(!_CB.compare("Odd")){
            m_settings[1].parity=3;
        }
        else if(!_CB.compare("Space")){
            m_settings[1].parity=4;
        }
        else if(!_CB.compare("Mark")){
            m_settings[1].parity=5;
        }
        if(_SB==1.0){
            m_settings[1].stopBits=1;
        }
        else if(_SB==2.0){
            m_settings[1].stopBits=2;
        }
        else if(_SB==1.5){
            m_settings[1].stopBits=3;
        }
    }

    if(!_SP.compare("485-3")){
        m_settings[2].dataBits=_DB;
        m_settings[2].baud=_Baud;
        if(!_CB.compare("None")){
            m_settings[2].parity=0;
        }
        else if(!_CB.compare("Even")){
            m_settings[2].parity=2;
        }
        else if(!_CB.compare("Odd")){
            m_settings[2].parity=3;
        }
        else if(!_CB.compare("Space")){
            m_settings[2].parity=4;
        }
        else if(!_CB.compare("Mark")){
            m_settings[2].parity=5;
        }
        if(_SB==1.0){
            m_settings[2].stopBits=1;
        }
        else if(_SB==2.0){
            m_settings[2].stopBits=2;
        }
        else if(_SB==1.5){
            m_settings[2].stopBits=3;
        }
    }

    if(!_SP.compare("485-4")){
        m_settings[3].dataBits=_DB;
        m_settings[3].baud=_Baud;
        if(!_CB.compare("None")){
            m_settings[3].parity=0;
        }
        else if(!_CB.compare("Even")){
            m_settings[3].parity=2;
        }
        else if(!_CB.compare("Odd")){
            m_settings[3].parity=3;
        }
        else if(!_CB.compare("Space")){
            m_settings[3].parity=4;
        }
        else if(!_CB.compare("Mark")){
            m_settings[3].parity=5;
        }
        if(_SB==1.0){
            m_settings[3].stopBits=1;
        }
        else if(_SB==2.0){
            m_settings[3].stopBits=2;
        }
        else if(_SB==1.5){
            m_settings[3].stopBits=3;
        }
    }
}

//serialNum为串口编号，portName为串口名，flag为1则有开关串口功能，flag为0则只有打开串口功能
void SerialSetting::serialControl(quint8 serialNum, QString portName, int flag)
{
    //查看串口是否连接
    if(!VectorSerialPort.at(serialNum)->isOpen()){
        //实现串口连接
        VectorSerialPort.at(serialNum)->setPortName(portName);
        VectorSerialPort.at(serialNum)->setBaudRate(m_settings[serialNum].baud);
        VectorSerialPort.at(serialNum)->setStopBits(QSerialPort::StopBits(m_settings[serialNum].stopBits));
        VectorSerialPort.at(serialNum)->setDataBits(QSerialPort::DataBits(m_settings[serialNum].dataBits));
        VectorSerialPort.at(serialNum)->setParity(QSerialPort::Parity(m_settings[serialNum].parity));
        VectorSerialPort.at(serialNum)->setFlowControl(QSerialPort::NoFlowControl);
        if(!VectorSerialPort.at(serialNum)->open(QIODevice::ReadWrite)){
            QMessageBox::about(this,"erro",QString("serialPort%1 open fail").arg(serialNum+1));
            qDebug()<<"serial open fail!";
            return;
        }
        else{
            qDebug()<<"serial open!";
            if(flag)
                QMessageBox::about(this,"about","open");
            VectorPushBotton.at(serialNum)->setText(tr("关闭串口"));
            VectorPushBotton.at(serialNum)->setStyleSheet(tr("QPushButton{background-color: rgb(204, 0, 0);}"));
        }
    }
    else{
        if(flag){
            //断开连接
            VectorSerialPort.at(serialNum)->close();
            QMessageBox::about(this,"success","close");
            VectorPushBotton.at(serialNum)->setText(tr("打开串口"));
            VectorPushBotton.at(serialNum)->setStyleSheet(tr("QPushButton{background-color: rgb(115, 210, 22);}"));
        }
    }
}

void SerialSetting::initSeri()
{
    m_settings=new SeriSettings[4];
    VectorSerialPort.append(serialPort1);
    VectorSerialPort.append(serialPort2);
    VectorSerialPort.append(serialPort3);
    VectorSerialPort.append(serialPort4);

    VectorPushBotton.append(ui->serial1PushButton);
    VectorPushBotton.append(ui->serial2PushButton);
    VectorPushBotton.append(ui->serial3PushButton);
    VectorPushBotton.append(ui->serial4PushButton);

    parityCombo[0]=ui->parityCombo10;
    parityCombo[1]=ui->parityCombo11;
    parityCombo[2]=ui->parityCombo12;
    parityCombo[3]=ui->parityCombo13;

    baudCombo[0]=ui->baudCombo10;
    baudCombo[1]=ui->baudCombo11;
    baudCombo[2]=ui->baudCombo12;
    baudCombo[3]=ui->baudCombo13;

    dataBitsCombo[0]=ui->dataBitsCombo10;
    dataBitsCombo[1]=ui->dataBitsCombo11;
    dataBitsCombo[2]=ui->dataBitsCombo12;
    dataBitsCombo[3]=ui->dataBitsCombo13;

    stopBitsCombo[0]=ui->stopBitsCombo10;
    stopBitsCombo[1]=ui->stopBitsCombo11;
    stopBitsCombo[2]=ui->stopBitsCombo12;
    stopBitsCombo[3]=ui->stopBitsCombo13;
    readTimer=new QTimer(this);             //3.5个字符读取时间  控制每次读取时间
    readTimer1=new QTimer(this);
    //初始控件
    changeComboBox();

    //扫描本机的串口，并且添加到下拉框里
    foreach(const QSerialPortInfo &info, QSerialPortInfo::availablePorts()) {
        ui->serialComboBox->addItem(info.portName());
        VectorPortName.append(info.portName());
    }
    for (int var = 0; var < VectorPortName.count(); ++var) {
        serialControl(var,VectorPortName.at(var),0);
    }
}

void SerialSetting::uiConnect()
{
    //信号槽
    connect(VectorSerialPort.at(0),SIGNAL(readyRead()),this,SLOT(bufferData()));
    connect(readTimer,&QTimer::timeout,this,&SerialSetting::readData);

    connect(VectorSerialPort.at(1),SIGNAL(readyRead()),this,SLOT(bufferData1()));
    connect(readTimer1,&QTimer::timeout,this,&SerialSetting::readData1);

    connect(&Singleton<SerialSettingManager>::getInstance(),&SerialSettingManager::SManagerSignToTcpSend,this,&SerialSetting::signToTcpSend);

    //关闭按钮
    connect(ui->closePushButton,&QPushButton::clicked,this,[=]{
        changeComboBox();
        this->hide();
    });
    //应用按钮
    connect(ui->applyButton_5,&QPushButton::clicked,this,[=]{
        for (int var = 0; var < 4; ++var) {
            m_settings[var].parity = parityCombo[var]->currentIndex();
            if (m_settings[var].parity > 0)
                m_settings[var].parity++;
            m_settings[var].baud = baudCombo[var]->currentText().toInt();
            m_settings[var].dataBits = dataBitsCombo[var]->currentText().toInt();
            m_settings[var].stopBits = stopBitsCombo[var]->currentText().toInt();
        }
    });
    //打开串口按钮
    connect(ui->serial1PushButton,&QPushButton::clicked,this,[=]{
        if (VectorPortName.count()>0)
            serialControl(0,VectorPortName.at(0),1);
        else
            QMessageBox::about(this,"erro","串口不存在或异常");
    });
    connect(ui->serial2PushButton,&QPushButton::clicked,this,[=]{
        if (VectorPortName.count()>1)
            serialControl(1,VectorPortName.at(1),1);
        else
            QMessageBox::about(this,"erro","串口不存在或异常");
    });
    connect(ui->serial3PushButton,&QPushButton::clicked,this,[=]{
        if (VectorPortName.count()>2)
            serialControl(2,VectorPortName.at(2),1);
        else
            QMessageBox::about(this,"erro","串口不存在或异常");
    });
    connect(ui->serial4PushButton,&QPushButton::clicked,this,[=]{
        if (VectorPortName.count()>3)
            serialControl(3,VectorPortName.at(3),1);
        else
            QMessageBox::about(this,"erro","串口不存在或异常");
    });
    //发送按钮
    connect(ui->pushButton_2,&QPushButton::clicked,this,[=]{
        if(nullptr==serialPort1&&nullptr==serialPort2&&nullptr==serialPort3&&nullptr==serialPort4)
            return;
        if(ui->serialComboBox->currentText()==VectorPortName.at(0)){
            if(serialPort1->isOpen()){
                ui->textBrowser->append("客户端："+ui->lineEdit->text());
                serialPort1->write(QByteArray::fromHex(ui->lineEdit->text().toLatin1()));
            }
        }
        else if(ui->serialComboBox->currentText()==VectorPortName.at(1)){
            if(serialPort2->isOpen()){
                ui->textBrowser->append("客户端："+ui->lineEdit->text());
                serialPort2->write(QByteArray::fromHex(ui->lineEdit->text().toLatin1()));
            }
        }
    });
    //清空发送区按钮
    connect(ui->pushButton_3,&QPushButton::clicked,this,[=]{
        ui->lineEdit->clear();
    });

}

