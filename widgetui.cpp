#include "widgetui.h"
#include "ui_widgetui.h"
#include "bridgemanager.h"
Widgetui::Widgetui(QWidget *parent)
    : FramelessWidget(parent)
    , ui(new Ui::Widgetui)
{
    ui->setupUi(this);
    this->show();
    init();
}

Widgetui::~Widgetui()
{
    delete ui;
    delete m_uiSelect;
}

void Widgetui::init()
{
    m_uiSelect=new QSettings(QCoreApplication::applicationDirPath()+"/info.ini",QSettings::IniFormat);
    //通过读取配置文件选择显示界面
    if(m_uiSelect->value("uiselect/electOnly").toInt()){
        emit Singleton<BridgeManager>::getInstance().SignPriEquip(m_uiSelect->value("uiselect/electOnly").toInt());
        this->hide();
        Singleton<BridgeManager>::getInstance().IndepElectINS()->show();
    }
    Singleton<BridgeManager>::getInstance().test();
    //独立电发送显示主界面信号
    connect(Singleton<BridgeManager>::getInstance().IndepElectINS(),&IndepElect::showWidgetUI,this,&Widgetui::show);
    //按钮2控制写独立电配置
    connect(ui->pushButton_2,&QPushButton::clicked,this,[=]{
        qDebug()<<QCoreApplication::applicationDirPath();
        m_uiSelect->setValue("uiselect/electOnly",1);
        qDebug()<<m_uiSelect->value("uiselect/electOnly");
        emit Singleton<BridgeManager>::getInstance().SignPriEquip(m_uiSelect->value("uiselect/electOnly").toInt());
        emit ui->pushButton->clicked();
    });
    //按钮3控制水电合用
    connect(ui->pushButton_3,&QPushButton::clicked,this,[=]{
        m_uiSelect->setValue("uiselect/electOnly",2);
        qDebug()<<m_uiSelect->value("uiselect/electOnly");
        emit Singleton<BridgeManager>::getInstance().SignPriEquip(m_uiSelect->value("uiselect/electOnly").toInt());
        emit ui->pushButton->clicked();
    });
    //按钮1控制跳转
    connect(ui->pushButton,&QPushButton::clicked,this,[=]{
        this->hide();
        Singleton<BridgeManager>::getInstance().IndepElectINS()->show();
    });
    //收到清除配置信号
    connect(Singleton<BridgeManager>::getInstance().IndepElectINS(),&IndepElect::clearCfg,this,[=]{
        m_uiSelect->setValue("uiselect/electOnly",0);
        Singleton<BridgeManager>::getInstance().IndepElectINS()->hide();
        this->show();
    });


}

