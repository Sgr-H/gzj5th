#include "date1view.h"
#include "ui_date1view.h"

date1View::date1View(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::date1View)
{
    ui->setupUi(this);

    CreateView();
}

date1View::~date1View()
{
    delete ui;
}

void date1View::CreateView()
{
    standItemModel1 = new QStandardItemModel();
    standItemModel2 = new QStandardItemModel();
    //添加表头
    standItemModel1->setColumnCount(2);
    standItemModel1->setHeaderData(0,Qt::Horizontal,QStringLiteral(""));   //设置表头内容
    standItemModel1->setHeaderData(1,Qt::Horizontal,QStringLiteral("设备\n状态"));
    standItemModel2->setColumnCount(2);
    standItemModel2->setHeaderData(0,Qt::Horizontal,QStringLiteral("继电器"));   //设置表头内容
    standItemModel2->setHeaderData(1,Qt::Horizontal,QStringLiteral("输出状态状态"));

    for(int i=0;i<8;i++)
    {
        QStandardItem *standItem1 = new QStandardItem(tr("输入%1").arg(i+1));
        QStandardItem *standItem2 = new QStandardItem(tr("0或1"));
        standItemModel1->setItem(i,0,standItem1);                                //表格第i行，第0列添加一项内容
        standItemModel1->item(i,0)->setForeground(QBrush(QColor(255,0,0)));      //设置字符颜色
        standItemModel1->item(i,0)->setTextAlignment(Qt::AlignCenter);           //设置表格内容居中
        standItemModel1->setItem(i,1,standItem2);                                //表格第i行，第1列添加一项内容
    }
    for(int i=0;i<4;i++)
    {
        QStandardItem *standItem1 = new QStandardItem(tr("输出%1").arg(i+1));
        QStandardItem *standItem2 = new QStandardItem(tr("吸合断开"));
        standItemModel2->setItem(i,0,standItem1);                                //表格第i行，第0列添加一项内容
        standItemModel2->item(i,0)->setForeground(QBrush(QColor(255,0,0)));      //设置字符颜色
        standItemModel2->item(i,0)->setTextAlignment(Qt::AlignCenter);           //设置表格内容居中
        standItemModel2->setItem(i,1,standItem2);                                //表格第i行，第1列添加一项内容
    }

    ui->tableView->setModel(standItemModel1);    //挂载表格模型
    ui->tableView_2->setModel(standItemModel2);    //挂载表格模型

    ui->tableView->verticalHeader()->hide();    //隐藏默认显示的行头
    ui->tableView_2->verticalHeader()->hide();    //隐藏默认显示的行头


    //设置表格属性
        ui->tableView->horizontalHeader()->setDefaultAlignment(Qt::AlignCenter);        //表头信息显示居中
        ui->tableView->horizontalHeader()->setSectionResizeMode(0,QHeaderView::Fixed);  //设定表头列宽不可变
        ui->tableView->horizontalHeader()->setSectionResizeMode(1,QHeaderView::Stretch);//设定第2列表头弹性拉伸
        ui->tableView->setColumnWidth(0,100);       //设定表格第0列宽度

        ui->tableView_2->horizontalHeader()->setDefaultAlignment(Qt::AlignCenter);        //表头信息显示居中
        ui->tableView_2->horizontalHeader()->setSectionResizeMode(0,QHeaderView::Fixed);  //设定表头列宽不可变
        ui->tableView_2->horizontalHeader()->setSectionResizeMode(1,QHeaderView::Stretch);//设定第2列表头弹性拉伸
        ui->tableView_2->setColumnWidth(0,100);       //设定表格第0列宽度


        ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows); //设置选中时整行选中
        ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);  //设置表格属性只读，不能编辑
        ui->tableView_2->setSelectionBehavior(QAbstractItemView::SelectRows); //设置选中时整行选中
        ui->tableView_2->setEditTriggers(QAbstractItemView::NoEditTriggers);  //设置表格属性只读，不能编辑
    //    ui->tableView->setContextMenuPolicy(Qt::CustomContextMenu);         //需要在表格使用右键菜单，需要启动该属性
    //    ui->tableView->sortByColumn(0,Qt::AscendingOrder);                 //表格第0列，按降序排列
}
