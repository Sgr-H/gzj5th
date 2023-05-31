#include "date3shaft.h"
#include "ui_date3shaft.h"

date3Shaft::date3Shaft(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::date3Shaft)
{
    ui->setupUi(this);
    CreateView();
    CreateView2();
    uiConnect();

}

date3Shaft::~date3Shaft()
{
    delete ui;
}

void date3Shaft::CreateView()
{
    standItemModel1=new QStandardItemModel();
    //添加行头
    standItemModel1->setRowCount(8);   //设置行头内容
    standItemModel1->setColumnCount(32);
    standItemModel1->setHeaderData(0,Qt::Vertical,QStringLiteral("液位"));
    standItemModel1->setHeaderData(1,Qt::Vertical,QStringLiteral("溶解氧(mg/L)"));
    standItemModel1->setHeaderData(2,Qt::Vertical,QStringLiteral("浊度(NTU)"));
    standItemModel1->setHeaderData(3,Qt::Vertical,QStringLiteral("电导率(us/cm)"));
    standItemModel1->setHeaderData(4,Qt::Vertical,QStringLiteral("水温(℃)"));
    standItemModel1->setHeaderData(5,Qt::Vertical,QStringLiteral("PH值"));
    standItemModel1->setHeaderData(6,Qt::Vertical,QStringLiteral("传感器地址"));
    standItemModel1->setHeaderData(7,Qt::Vertical,QStringLiteral("485总线名"));

    for (int var = 0; var < 32; ++var) {
        QString tmpstr=QString(tr("窨井%1").arg(var+1));
        standItemModel1->setHeaderData(var,Qt::Horizontal,tmpstr);
    }

    ui->tableView->setModel(standItemModel1);

    for (int var = 0; var < 8; ++var) {
        ui->tableView->verticalHeader()->setSectionResizeMode(var,QHeaderView::Stretch);//设定行表头弹性拉伸
    }
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);  //设置表格属性只读，不能编辑

    //滚动
    QScroller *scl = QScroller::scroller(ui->tableView);
    scl->grabGesture(ui->tableView,QScroller::LeftMouseButtonGesture);
    ui->tableView->setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);
    ui->tableView->horizontalScrollBar()->hide();               //隐藏滚动条
}

void date3Shaft::CreateView2()
{
    standItemModel2=new QStandardItemModel();
    //添加行头
    standItemModel2->setRowCount(3);   //设置行头内容
    standItemModel2->setColumnCount(5);
    standItemModel2->setHeaderData(0,Qt::Vertical,QStringLiteral("污染限值"));
    standItemModel2->setHeaderData(1,Qt::Vertical,QStringLiteral("溶解氧需大于："));
    standItemModel2->setHeaderData(2,Qt::Vertical,QStringLiteral("PH值"));

    {
        //填写具体数值
        standItemModel2->setItem(0,0,new QStandardItem(tr("1类水")));
        standItemModel2->setItem(0,1,new QStandardItem(tr("2类水")));
        standItemModel2->setItem(0,2,new QStandardItem(tr("3类水")));
        standItemModel2->setItem(0,3,new QStandardItem(tr("4类水")));
        standItemModel2->setItem(0,4,new QStandardItem(tr("5类水")));

        standItemModel2->setItem(1,0,new QStandardItem(tr("7.5")));
        standItemModel2->setItem(1,1,new QStandardItem(tr("6")));
        standItemModel2->setItem(1,2,new QStandardItem(tr("5")));
        standItemModel2->setItem(1,3,new QStandardItem(tr("3")));
        standItemModel2->setItem(1,4,new QStandardItem(tr("2")));

        standItemModel2->setItem(2,0,new QStandardItem(tr("6.5~9.5")));

        standItemModel2->item(2,0)->setTextAlignment(Qt::AlignCenter);           //设置表格内容居中
    }
    ui->tableView_2->setModel(standItemModel2);

    ui->tableView_2->horizontalHeader()->hide();//隐藏行

    for (int var = 0; var < 3; ++var) {
        ui->tableView_2->verticalHeader()->setSectionResizeMode(var,QHeaderView::Stretch);//设定行表头弹性拉伸
    }
    for (int var = 0; var < 5; ++var) {
        ui->tableView_2->horizontalHeader()->setSectionResizeMode(var,QHeaderView::Stretch);//设定行表头弹性拉伸
    }

    ui->tableView_2->setSpan(2,0,1,5);//合并单元格
    ui->tableView_2->setEditTriggers(QAbstractItemView::NoEditTriggers);  //设置表格属性只读，不能编辑

}

void date3Shaft::uiConnect()
{
    connect(ui->pushButton,&QPushButton::clicked,this,[=]{
        this->hide();
    });
}
