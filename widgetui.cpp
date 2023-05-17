#include "widgetui.h"
#include "ui_widgetui.h"
#include "bridgemanager.h"
Widgetui::Widgetui(QWidget *parent)
    : FramelessWidget(parent)
    , ui(new Ui::Widgetui)
{
    ui->setupUi(this);
//    Singleton<BridgeManager>::getInstance().LogInWidgetIns()->show();
    ui->pushButton_9->setVisible(false);
    ui->pushButton_10->setVisible(false);
    ui->pushButton_11->setVisible(false);
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
        jumpWriteSetting(1);
    });
    //按钮3控制水电合用
    connect(ui->pushButton_3,&QPushButton::clicked,this,[=]{
        jumpWriteSetting(2);
    });
    //按钮4控制电梯专用
    connect(ui->pushButton_4,&QPushButton::clicked,this,[=]{
        jumpWriteSetting(3);
    });
    //按钮6控制空调专用
    connect(ui->pushButton_6,&QPushButton::clicked,this,[=]{
        jumpWriteSetting(4);
    });
    //按钮8控制地下管网窨井
    connect(ui->pushButton_8,&QPushButton::clicked,this,[=]{
        jumpWriteSetting(5);
    });
    //按钮7控制消防
    connect(ui->pushButton_7,&QPushButton::clicked,this,[=]{
        jumpWriteSetting(6);
    });
    //按钮5控制合用
    connect(ui->pushButton_5,&QPushButton::clicked,this,[=]{
        jumpWriteSetting(7);
    });

    //收到清除配置信号
    connect(Singleton<BridgeManager>::getInstance().IndepElectINS(),&IndepElect::clearCfg,this,[=]{
        m_uiSelect->setValue("uiselect/electOnly",0);
        Singleton<BridgeManager>::getInstance().IndepElectINS()->hide();
        this->show();
    });
    //收到登录信号
    connect(Singleton<BridgeManager>::getInstance().LogInWidgetIns(),&LogInWidget::login,this,[=]{
        ui->pushButton_9->setVisible(true);
        ui->pushButton_10->setVisible(true);
        ui->pushButton_11->setVisible(true);
        this->show();
        Singleton<BridgeManager>::getInstance().IndepElectINS()->hide();
    });

}

void Widgetui::jumpWriteSetting(int _var)
{
    m_uiSelect->setValue("uiselect/electOnly",_var);
    qDebug()<<m_uiSelect->value("uiselect/electOnly");
    emit Singleton<BridgeManager>::getInstance().SignPriEquip(m_uiSelect->value("uiselect/electOnly").toInt());
    this->hide();
    Singleton<BridgeManager>::getInstance().IndepElectINS()->show();
}

