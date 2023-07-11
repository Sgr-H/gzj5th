#include "widgetui.h"
#include "ui_widgetui.h"
#include "bridgemanager.h"
#include "gzjsqlite.h"

Widgetui::Widgetui(QWidget *parent)
    : FramelessWidget(parent)
    , ui(new Ui::Widgetui)
{
    ui->setupUi(this);
    //    Singleton<BridgeManager>::getInstance().LogInWidgetIns()->show();
    ui->pushButton_9->setVisible(false);
    ui->pushButton_10->setVisible(false);
    ui->pushButton_11->setVisible(false);
    ui->radioButton->setVisible(false);
    this->show();
    init();
    initGlobal();
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
        if(!ui->pushButton_9->isVisible())
            ui->pushButton_9->setVisible(true);
        if(!ui->pushButton_10->isVisible())
            ui->pushButton_10->setVisible(true);
        if(!ui->pushButton_11->isVisible())
            ui->pushButton_11->setVisible(true);
        if(!ui->radioButton->isVisible())
            ui->radioButton->setVisible(true);
        this->show();
        Singleton<BridgeManager>::getInstance().IndepElectINS()->hide();
    });
    //显示设备开关量单选按钮
    connect(ui->radioButton,&QRadioButton::toggled,this,[=]{
        if(ui->radioButton->isChecked())
            Singleton<BridgeManager>::getInstance().IndepElectINS()->DIOVisial(1);
        else
            Singleton<BridgeManager>::getInstance().IndepElectINS()->DIOVisial(0);
    });
    //设备操作按钮跳转
    connect(ui->pushButton_10,&QPushButton::clicked,this,[=]{
        Singleton<BridgeManager>::getInstance().EquipOperaINS()->show();
    });
    //通讯参数配置按钮跳转
    connect(ui->pushButton_9,&QPushButton::clicked,this,[=]{
        Singleton<BridgeManager>::getInstance().CommunicateCfgINS()->show();
    });
}

void Widgetui::initGlobal()
{
    //初始化deviceTI全局列表
    struct_deviceTI structDTI;
    QSqlQuery sql_query(Singleton<GzjSqlite>::getInstance().sqlDatabase);
    QString select_sql = "select TN ,PN ,Name ,EnName from deviceTI";

    if(!sql_query.exec(select_sql)){
        Singleton<Log>::getInstance().debug("exec fail: "+sql_query.lastError().text());
    }
    else
    {
        while(sql_query.next())
        {
            structDTI.VL_TN<<sql_query.value(0).toString();
            structDTI.VL_PN<<sql_query.value(1).toString();
            structDTI.VL_Name<<sql_query.value(2).toString();
            structDTI.VL_EnName<<sql_query.value(3).toString();
        }
    }
    APISgrH::set_deviceTI(structDTI);

    //初始化targetTI全局列表
    struct_targetTI structTTI;
    select_sql = "select TN ,Type ,Name ,EnName ,Unit from targetTI";

    if(!sql_query.exec(select_sql)){
        Singleton<Log>::getInstance().debug("exec fail: "+sql_query.lastError().text());
    }
    else
    {
        while(sql_query.next())
        {
            structTTI.VL_TN<<sql_query.value(0).toString();
            structTTI.VL_Type<<sql_query.value(1).toInt();
            structTTI.VL_Name<<sql_query.value(2).toString();
            structTTI.VL_EnName<<sql_query.value(3).toString();
            structTTI.VL_Unit<<sql_query.value(4).toString();
        }
    }
    APISgrH::set_targetTI(structTTI);

    //初始化circCT全局列表
    struct_circCT strucCT;
    select_sql = "select TN ,Addr ,VA ,SP ,IT ,CF ,UF from circCT";

    if(!sql_query.exec(select_sql)){
        Singleton<Log>::getInstance().debug("exec fail: "+sql_query.lastError().text());
    }
    else
    {
        while(sql_query.next())
        {
            strucCT.VL_TN<<sql_query.value(0).toInt();
            strucCT.VL_Addr<<sql_query.value(1).toString();
            strucCT.VL_VA<<sql_query.value(2).toString();
            strucCT.VL_SP<<sql_query.value(3).toString();
            strucCT.VL_IT<<sql_query.value(4).toString();
            strucCT.VL_CF<<sql_query.value(5).toString();
            strucCT.VL_UF<<sql_query.value(6).toString();
        }
    }
    APISgrH::set_circCT(strucCT);

    //初始化deviceMIF全局列表
    QString fileDir = QCoreApplication::applicationDirPath() + "/etc/JsonDeviceMI.txt";
    QFile file(fileDir);
    //对文件进行写操作
    if(!file.open(QIODevice::ReadOnly)){
        qDebug()<<"文件打开失败";
    }
    //文件中读json字符串
    QByteArray dataDMIF;
    dataDMIF=file.readAll();
    Document DDMIF;
    if(!DDMIF.Parse(dataDMIF.toStdString().c_str()).HasParseError()){
        if(DDMIF.HasMember("Data")){
            Value Data(rapidjson::kArrayType);
            Data=DDMIF["Data"];
            struct_deviceMIF structDMIF;
            struct_analyticP structAP;
            //先取Array
            if (Data.IsArray() && !Data.Empty())
            {
                rapidjson::Value tempData;
                for (rapidjson::SizeType i = 0; i < Data.Size(); i++)
                {
                    tempData = Data[i];
                    if (tempData.IsObject())
                    {

                        if (tempData.HasMember("TN") && tempData.HasMember("IT")&& tempData.HasMember("PN")
                                && tempData.HasMember("CMD")&& tempData.HasMember("PS")&& tempData.HasMember("AP"))
                        {
                            structDMIF.VL_TN<<tempData["TN"].GetInt();
                            structDMIF.VL_IT<<tr(tempData["IT"].GetString());
                            structDMIF.VL_PN<<tempData["PN"].GetInt();
                            structDMIF.VL_CMD<<tr(tempData["CMD"].GetString());
                            structDMIF.VL_PS<<tempData["PS"].GetInt();

                            Value Data2;
                            Data2 = tempData["AP"];
                            if (Data2.IsArray() && !Data2.Empty())
                            {
                                Value tempData2;
                                for (rapidjson::SizeType i = 0; i < Data2.Size(); i++)
                                {
                                    tempData2 = Data2[i];
                                    if (tempData2.IsObject())
                                    {
                                        if (tempData2.HasMember("TN") && tempData2.HasMember("IT")&& tempData2.HasMember("PN")
                                                && tempData2.HasMember("CMD")&& tempData2.HasMember("PS")&& tempData2.HasMember("AP"))
                                        {
                                            structAP.VL_RB=tempData2["RB"].GetInt();
                                            structAP.VL_PB=tempData2["PB"].GetInt();
                                            structAP.VL_TM=tempData2["TM"].GetInt();
                                            structAP.VL_SI=tr(tempData2["SI"].GetString());
                                            structAP.VL_DL=tempData2["DL"].GetInt();
                                            structAP.VL_DT=tr(tempData2["DT"].GetString());
                                            structAP.VL_Formula=tr(tempData2["Formula"].GetString());
                                            structAP.VL_UL=tempData2["UL"].GetDouble();
                                            structAP.VL_LL=tempData2["LL"].GetDouble();
                                        }
                                    }
                                }
                            }
                            structDMIF.VL_AP<<structAP;
                        }
                    }
                }
            }
            APISgrH::set_deviceMIF(structDMIF);
        }
    }
    //关闭文件
    file.close();
}

void Widgetui::jumpWriteSetting(int _var)
{
    m_uiSelect->setValue("uiselect/electOnly",_var);
    qDebug()<<m_uiSelect->value("uiselect/electOnly");
    emit Singleton<BridgeManager>::getInstance().SignPriEquip(m_uiSelect->value("uiselect/electOnly").toInt());
    this->hide();
    Singleton<BridgeManager>::getInstance().IndepElectINS()->show();
}

