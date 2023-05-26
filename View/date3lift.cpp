#include "date3lift.h"
#include "ui_date3lift.h"

date3lift::date3lift(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::date3lift)
{
    ui->setupUi(this);
    uiConnect();
    CreateView();
}

date3lift::~date3lift()
{
    delete ui;
}

void date3lift::CreateView()
{
    standItemModel1=new QStandardItemModel();
    //添加行头
    standItemModel1->setRowCount(12);   //设置行头内容
    standItemModel1->setColumnCount(6);
    standItemModel1->setHeaderData(0,Qt::Vertical,QStringLiteral("楼层位置"));
    standItemModel1->setHeaderData(1,Qt::Vertical,QStringLiteral("前后门开关状态"));
    standItemModel1->setHeaderData(2,Qt::Vertical,QStringLiteral("上下行运行状态"));
    standItemModel1->setHeaderData(3,Qt::Vertical,QStringLiteral("超载满载信息"));
    standItemModel1->setHeaderData(4,Qt::Vertical,QStringLiteral("检修状态"));
    standItemModel1->setHeaderData(5,Qt::Vertical,QStringLiteral("应急电源运行"));
    standItemModel1->setHeaderData(6,Qt::Vertical,QStringLiteral("消防状态"));
    standItemModel1->setHeaderData(7,Qt::Vertical,QStringLiteral("停止状态"));
    standItemModel1->setHeaderData(8,Qt::Vertical,QStringLiteral("电梯运行时间"));
    standItemModel1->setHeaderData(9,Qt::Vertical,QStringLiteral("电梯运行次数"));
    standItemModel1->setHeaderData(10,Qt::Vertical,QStringLiteral("设备地址"));
    standItemModel1->setHeaderData(11,Qt::Vertical,QStringLiteral("总线名"));

    for (int var = 0; var < 6; ++var) {
        QString tmpstr=QString(tr("电梯%1").arg(var+1));
        standItemModel1->setHeaderData(var,Qt::Horizontal,tmpstr);
    }

    ui->tableView->setModel(standItemModel1);

    for (int var = 0; var < 12; ++var) {
        ui->tableView->verticalHeader()->setSectionResizeMode(var,QHeaderView::Stretch);//设定行表头弹性拉伸
        if(var<6)
            ui->tableView->horizontalHeader()->setSectionResizeMode(var,QHeaderView::Stretch);
    }
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);  //设置表格属性只读，不能编辑
}

void date3lift::uiConnect()
{
    connect(ui->pushButton,&QPushButton::clicked,this,[=]{
        this->hide();
    });
}
