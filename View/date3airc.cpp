#include "date3airc.h"
#include "ui_date3airc.h"

date3Airc::date3Airc(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::date3Airc)
{
    ui->setupUi(this);
    initDate3Airc();
    uiConnect();
    CreateView();
    CreateView2();
}

date3Airc::~date3Airc()
{
    delete ui;
}

void date3Airc::airCbtn_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void date3Airc::CreateView()
{

    //添加行头
    standItemModel1->setRowCount(10);   //设置行头内容
    standItemModel1->setColumnCount(33);
    standItemModel1->setHeaderData(0,Qt::Vertical,QStringLiteral(" "));
    standItemModel1->setHeaderData(1,Qt::Vertical,QStringLiteral("用电量"));
    standItemModel1->setHeaderData(2,Qt::Vertical,QStringLiteral("温度"));
    standItemModel1->setHeaderData(3,Qt::Vertical,QStringLiteral("开关机状态"));
    standItemModel1->setHeaderData(4,Qt::Vertical,QStringLiteral("运行模式"));
    standItemModel1->setHeaderData(5,Qt::Vertical,QStringLiteral("运行时间"));
    standItemModel1->setHeaderData(6,Qt::Vertical,QStringLiteral("故障状态"));
    standItemModel1->setHeaderData(7,Qt::Vertical,QStringLiteral("故障时间"));
    standItemModel1->setHeaderData(8,Qt::Vertical,QStringLiteral("空调地址"));
    standItemModel1->setHeaderData(9,Qt::Vertical,QStringLiteral("总线名"));

    ui->tableView->setModel(standItemModel1);
    ui->tableView->horizontalHeader()->hide();


    for (int var = 0; var < 10; ++var) {
        ui->tableView->verticalHeader()->setSectionResizeMode(var,QHeaderView::Stretch);//设定行表头弹性拉伸
    }

    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);  //设置表格属性只读，不能编辑

    QList<QString> aircBtns;
    aircBtns << "aircbtn1" << "aircbtn2" << "aircbtn3" << "aircbtn4"<< "aircbtn5" << "aircbtn6"<< "aircbtn7" << "aircbtn8";
    for (int i = 0; i < aircBtns.count(); i++) {
            QPushButton *btn = new QPushButton;
            connect(btn, &QPushButton::clicked, this, &date3Airc::airCbtn_clicked);     //关联信号与槽函数
            btn->setObjectName(aircBtns.at(i));     //设置标识,区别按钮
            btn->setText(tr("空调%1").arg(i+1));      //按钮文本
            ui->tableView->setIndexWidget(standItemModel1->index(0,i),btn);         //向表格单元添加一个控件
        }

    //滚动
    QScroller *scl = QScroller::scroller(ui->tableView);
    scl->grabGesture(ui->tableView,QScroller::LeftMouseButtonGesture);
    ui->tableView->setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);
    ui->tableView->horizontalScrollBar()->hide();               //隐藏滚动条
}

void date3Airc::CreateView2()
{

    //添加行头
    standItemModel2->setRowCount(3);   //设置行头内容
    standItemModel2->setColumnCount(8);
    standItemModel2->setHeaderData(0,Qt::Vertical,QStringLiteral("设置温度"));
    standItemModel2->setHeaderData(1,Qt::Vertical,QStringLiteral("设置模式"));
    standItemModel2->setHeaderData(2,Qt::Vertical,QStringLiteral("启动/停止"));
    for (int var = 0; var < 8; ++var) {
        QString tmpstr=QString(tr("空调%1").arg(var+1));
        standItemModel2->setHeaderData(var,Qt::Horizontal,tmpstr);
    }

    ui->tableView_2->setModel(standItemModel2);

    for (int var = 0; var < 3; ++var) {
        ui->tableView_2->verticalHeader()->setSectionResizeMode(var,QHeaderView::Stretch);//设定行表头弹性拉伸
    }
    ui->tableView_2->setEditTriggers(QAbstractItemView::NoEditTriggers);  //设置表格属性只读，不能编辑

    //滚动
    QScroller *scl = QScroller::scroller(ui->tableView_2);
    scl->grabGesture(ui->tableView_2,QScroller::LeftMouseButtonGesture);
    ui->tableView_2->setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);
    ui->tableView_2->horizontalScrollBar()->hide();               //隐藏滚动条

}

void date3Airc::uiConnect()
{
    connect(ui->pushButton,&QPushButton::clicked,this,[=]{
        if(ui->stackedWidget->currentIndex()==1)
            ui->stackedWidget->setCurrentIndex(0);
        else
            this->hide();
    });
    connect(m_aircBtn1,&QPushButton::clicked,this,[=]{
        ui->stackedWidget->setCurrentIndex(1);
    });
}

void date3Airc::initDate3Airc()
{
    //初始化参数
    standItemModel1=new QStandardItemModel();
    standItemModel2=new QStandardItemModel();

    m_aircBtn1=new QPushButton(tr("空调1"));
    ui->stackedWidget->setCurrentIndex(0);
}
