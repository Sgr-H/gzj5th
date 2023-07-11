#include "indepelect.h"
#include "ui_indepelect.h"
#include "bridgemanager.h"

IndepElect::IndepElect(QWidget *parent) :
    FramelessWidget(parent),
    ui(new Ui::IndepElect)
{
    ui->setupUi(this);

    init();
    //测试用按钮隐藏
    ui->pushButton->setVisible(false);
    ui->pushButton_2->setVisible(false);
    m_priStackWidgetCurrentPage=m_stackWidgetCurrentPage;
    uiConnect();

    //滑动
    QScroller *scl = QScroller::scroller(ui->scrollArea);
    scl->grabGesture(ui->scrollArea,QScroller::LeftMouseButtonGesture);
}

IndepElect::~IndepElect()
{
    delete ui;
}

//界面跳转重新布局
void IndepElect::SlotPriEquip(const int &var)
{
    m_priStackWidgetCurrentPage=m_stackWidgetCurrentPage;
    m_stackWidgetCurrentPage=var;
    if(m_stackWidgetCurrentPage>0)
        m_stackWidgetCurrentPage--;
    if(m_priStackWidgetCurrentPage!=m_stackWidgetCurrentPage){
        deleteAllitemsOfLayout(ui->horizontalLayout_3);
        deleteAllitemsOfLayout(ui->horizontalLayout_9);
        deleteAllitemsOfLayout(ui->horizontalLayout_18);
        deleteAllitemsOfLayout(ui->horizontalLayout_19);
        deleteAllitemsOfLayout(ui->horizontalLayout_20);
        deleteAllitemsOfLayout(ui->horizontalLayout_21);
        deleteAllitemsOfLayout(ui->gridLayout_20);
        switch (m_stackWidgetCurrentPage) {
        case 0:
            ui->horizontalLayout_9->addWidget(ui->frame_2);
            break;
        case 1:
            //                ui->horizontalLayout_9->removeWidget(ui->frame_2);
            ui->horizontalLayout_3->addWidget(ui->frame);
            ui->horizontalLayout_3->addWidget(ui->frame_2);
            break;
        case 2:
            ui->horizontalLayout_18->addWidget(ui->frame_3);
            break;
        case 3:
            ui->horizontalLayout_19->addWidget(ui->frame_4);
            break;
        case 4:
            ui->horizontalLayout_20->addWidget(ui->frame_5);
            break;
        case 5:
            ui->horizontalLayout_21->addWidget(ui->frame_8);
            break;
        case 6:
            ui->gridLayout_20->addWidget(ui->frame_2);
            ui->gridLayout_20->addWidget(ui->frame);
            ui->gridLayout_20->addWidget(ui->frame_3);
            ui->gridLayout_20->addWidget(ui->frame_4);
            ui->gridLayout_20->addWidget(ui->frame_5);
            ui->gridLayout_20->addWidget(ui->frame_8);
            //            ui->scrollArea->widget()->setLayout(ui->gridLayout_20);
            break;
        default:
            break;
        }
    }
    ui->stackedWidget->setCurrentIndex(m_stackWidgetCurrentPage);
}

void IndepElect::timeUpdata()
{
    QDateTime time =QDateTime::currentDateTime();
    timeNow=time.toString("yyyy-MM-dd hh:mm:ss ddd");
    ui->label_time->setText(timeNow);
}

void IndepElect::init()
{
    timerFlush=new QTimer(this);
    timerFlush->start(1000);
}

void IndepElect::uiConnect()
{
    //跳转数据界面1
    connect(ui->pushButton,&QPushButton::clicked,this,[=]{
        Singleton<BridgeManager>::getInstance().date1ViewINS()->show();
        //        this->hide();
        //        emit showWidgetUI();
    });
    //清除配置信息
    connect(ui->pushButton_2,&QPushButton::clicked,this,&IndepElect::clearCfg);
    //跳转到登录界面
    connect(ui->pushButton_3,&QPushButton::clicked,[=]{
        Singleton<BridgeManager>::getInstance().LogInWidgetIns()->show();
    });
    //跳转日志
    connect(ui->logbtn,&QPushButton::clicked,[=]{
        Singleton<BridgeManager>::getInstance().logPrintWidgetINS()->show();
    });
    //刷新时间
    connect(timerFlush,&QTimer::timeout,this,&IndepElect::timeUpdata);

    //跳转电表数据界面2
    connect(ui->pushButton_4,&QPushButton::clicked,this,[=]{
        Singleton<BridgeManager>::getInstance().date2ViewINS()->setDeviceSelect(1);
        Singleton<BridgeManager>::getInstance().date2ViewINS()->show();
    });
    //跳转水表数据界面2
    connect(ui->pushButton_5,&QPushButton::clicked,this,[=]{
        Singleton<BridgeManager>::getInstance().date2ViewINS()->setDeviceSelect(2);
        Singleton<BridgeManager>::getInstance().date2ViewINS()->show();
    });
    //跳转电梯数据界面3
    connect(ui->pushButton_6,&QPushButton::clicked,this,[=]{
        Singleton<BridgeManager>::getInstance().date3liftINS()->show();
    });
    //跳转空调数据界面3
    connect(ui->pushButton_7,&QPushButton::clicked,this,[=]{
        Singleton<BridgeManager>::getInstance().date3AircINS()->show();
    });
    //跳转窨井数据界面3
    connect(ui->pushButton_8,&QPushButton::clicked,this,[=]{
        Singleton<BridgeManager>::getInstance().date3ShaftINS()->show();
    });
    //测试按钮
    connect(ui->pushButton_9,&QPushButton::clicked,this,[=]{
        QApplication *app;
        app->exit(0);
//        Singleton<BridgeManager>::getInstance().SerialSettingINS()->show();
    });
}

//清空布局
void IndepElect::deleteAllitemsOfLayout(QLayout *layout)
{
    QLayoutItem *child;
    while ((child = layout->takeAt(0)) != nullptr)
    {
        //setParent为NULL，防止删除之后界面不消失
        if(child->widget())
        {
            child->widget()->setParent(nullptr);
        }
        else if(child->layout())
        {
            deleteAllitemsOfLayout(child->layout());
        }
        delete child;
    }
}

void IndepElect::DIOVisial(int var)
{
    if(var==0)
        ui->pushButton->setVisible(false);
    else
        ui->pushButton->setVisible(true);
}
