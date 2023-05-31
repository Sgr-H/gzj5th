#include "equipopera.h"
#include "ui_equipopera.h"

EquipOpera::EquipOpera(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EquipOpera)
{
    ui->setupUi(this);
    CreateView();
    CreateView2();
    uiConnect();
}

EquipOpera::~EquipOpera()
{
    delete ui;
}

void EquipOpera::CreateView()
{
    standItemModel1=new QStandardItemModel();
    //添加行头
    standItemModel1->setRowCount(1);   //设置行头内容
    standItemModel1->setHeaderData(0,Qt::Vertical,QStringLiteral("设备\n状态"));

    {
        standItemModel1->setItem(0,0,new QStandardItem(tr("0或1")));
        standItemModel1->setItem(0,1,new QStandardItem(tr("0或1")));
        standItemModel1->setItem(0,2,new QStandardItem(tr("0或1")));
        standItemModel1->setItem(0,3,new QStandardItem(tr("0或1")));
        standItemModel1->setItem(0,4,new QStandardItem(tr("0或1")));
        standItemModel1->setItem(0,5,new QStandardItem(tr("0或1")));
        standItemModel1->setItem(0,6,new QStandardItem(tr("0或1")));
        standItemModel1->setItem(0,7,new QStandardItem(tr("0或1")));
    }

    ui->tableView->setModel(standItemModel1);

    ui->tableView->horizontalHeader()->hide();//隐藏行

    ui->tableView->verticalHeader()->setSectionResizeMode(0,QHeaderView::Stretch);//设定行表头弹性拉伸
    for (int var = 0; var < 8; ++var) {
        ui->tableView->horizontalHeader()->setSectionResizeMode(var,QHeaderView::Stretch);//设定行表头弹性拉伸
    }

//    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);  //设置表格属性只读，不能编辑

}

void EquipOpera::CreateView2()
{
    standItemModel2=new QStandardItemModel();
    //添加行头
    standItemModel2->setRowCount(2);   //设置行头内容
    standItemModel2->setHeaderData(0,Qt::Vertical,QStringLiteral("输出状态"));
    standItemModel2->setHeaderData(1,Qt::Vertical,QStringLiteral("输入1或0"));

    {
        standItemModel2->setItem(0,0,new QStandardItem(tr("吸合\n断开")));
        standItemModel2->setItem(0,1,new QStandardItem(tr("吸合\n断开")));
        standItemModel2->setItem(0,2,new QStandardItem(tr("吸合\n断开")));
        standItemModel2->setItem(0,3,new QStandardItem(tr("吸合\n断开")));
        standItemModel2->setItem(0,4,new QStandardItem(tr("吸合\n断开")));
        standItemModel2->setItem(0,5,new QStandardItem(tr("吸合\n断开")));
        standItemModel2->setItem(0,6,new QStandardItem(tr("吸合\n断开")));
        standItemModel2->setItem(0,7,new QStandardItem(tr("吸合\n断开")));
    }

    ui->tableView_2->setModel(standItemModel2);

    ui->tableView_2->horizontalHeader()->hide();//隐藏行

    ui->tableView_2->verticalHeader()->setSectionResizeMode(0,QHeaderView::Stretch);//设定行表头弹性拉伸
    ui->tableView_2->verticalHeader()->setSectionResizeMode(1,QHeaderView::Stretch);//设定行表头弹性拉伸
    for (int var = 0; var < 4; ++var) {
        ui->tableView_2->horizontalHeader()->setSectionResizeMode(var,QHeaderView::Stretch);//设定行表头弹性拉伸
    }

//    ui->tableView_2->setEditTriggers(QAbstractItemView::NoEditTriggers);  //设置表格属性只读，不能编辑

}

void EquipOpera::uiConnect()
{
    connect(ui->pushButton,&QPushButton::clicked,this,[=]{
        this->hide();
    });
}
