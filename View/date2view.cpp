#include "date2view.h"
#include "ui_date2view.h"
#include "bridgemanager.h"

date2View::date2View(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::date2View)
{
    ui->setupUi(this);
    this->setGeometry(0,0,1024,600);
    CreateView();
    uiConnect();
}

date2View::~date2View()
{
    delete ui;
}

void date2View::CreateView()
{
    m_4851Btn = new QPushButton("485_1");
    m_4852Btn = new QPushButton("485_2");
    m_4853Btn = new QPushButton("485_3");
    m_4854Btn = new QPushButton("485_4");
    m_mbusBtn = new QPushButton("M-BUS");

    standItemModel1 = new QStandardItemModel();
    standItemModel1->setColumnCount(33);

    for(int i=0;i<5;i++)
    {
        for (int j = 0; j < 32; ++j) {
            QStandardItem *standItem1 = new QStandardItem(tr("%1").arg(j+1));
            standItemModel1->setItem(i,j+1,standItem1);                                //表格第j行，第0列添加一项内容
            standItemModel1->item(i,j+1)->setForeground(QBrush(QColor(255,0,0)));      //设置字符颜色
            standItemModel1->item(i,j+1)->setTextAlignment(Qt::AlignCenter);           //设置表格内容居中
        }
    }

    ui->tableView->setModel(standItemModel1);    //挂载表格模型
    ui->tableView->verticalHeader()->hide();    //隐藏默认显示的行头
    ui->tableView->horizontalHeader()->hide();  //隐藏默认显示的列头
    for (int var = 0; var < 5; ++var) {
        ui->tableView->setRowHeight(var,80);       //设定表格第0列宽度
    }

    ui->tableView->setIndexWidget(standItemModel1->index(0,0),m_4851Btn);         //向表格单元添加一个控件
    ui->tableView->setIndexWidget(standItemModel1->index(1,0),m_4852Btn);         //向表格单元添加一个控件
    ui->tableView->setIndexWidget(standItemModel1->index(2,0),m_4853Btn);         //向表格单元添加一个控件
    ui->tableView->setIndexWidget(standItemModel1->index(3,0),m_4854Btn);         //向表格单元添加一个控件
    ui->tableView->setIndexWidget(standItemModel1->index(4,0),m_mbusBtn);         //向表格单元添加一个控件

    //滚动
    QScroller *scl = QScroller::scroller(ui->tableView);
    scl->grabGesture(ui->tableView,QScroller::LeftMouseButtonGesture);
    ui->tableView->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    ui->tableView->setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);
    ui->tableView->horizontalScrollBar()->hide();               //隐藏滚动条

}

void date2View::uiConnect()
{
    connect(ui->pushButton,&QPushButton::clicked,this,&date2View::hide);//隐藏该界面
    connect(ui->pushButton_4,&QPushButton::clicked,this,[=]{
       Singleton<BridgeManager>::getInstance().date3ElectINS()->show();
    });
}
