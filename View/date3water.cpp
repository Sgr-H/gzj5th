#include "date3water.h"
#include "ui_date3water.h"
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QValueAxis>

QT_CHARTS_USE_NAMESPACE
date3Water::date3Water(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::date3Water)
{
    ui->setupUi(this);
    initdate3Water();
    uiConnect();
    CreateView();
    CreateView2();
    CreateView3();
    CreateView4();
}

date3Water::~date3Water()
{
    delete ui;
}

void date3Water::initdate3Water()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void date3Water::uiConnect()
{
    //返回
    connect(ui->pushButton_6,&QPushButton::clicked,this,[=]{
        this->hide();
    });
    //历史数据
    connect(ui->pushButton_4,&QPushButton::clicked,this,[=]{
        ui->stackedWidget->setCurrentIndex(3);
    });
    //实时数据
    connect(ui->pushButton_2,&QPushButton::clicked,this,[=]{
        ui->stackedWidget->setCurrentIndex(0);
    });
    //曲线
    connect(ui->pushButton_5,&QPushButton::clicked,this,[=]{
        ui->stackedWidget->setCurrentIndex(2);
    });

    //历史界面选择日期
    connect(ui->pushButton_7,&QPushButton::clicked,[=]{
        QDate str1,str2;
        str1=ui->calendarWidget->selectedDate();
        str2=ui->calendarWidget_2->selectedDate();
        if(str1 <= str2)
            ui->stackedWidget->setCurrentIndex(1);
        else
            QMessageBox::critical(this,"critical",tr("起始日期不可大于结束日期"));
    });
}

void date3Water::CreateView()
{
    standItemModel1=new QStandardItemModel();
    //添加列头
    standItemModel1->setRowCount(2);
    standItemModel1->setHeaderData(0,Qt::Vertical,QStringLiteral("指标名"));   //设置列头内容
    standItemModel1->setHeaderData(1,Qt::Vertical,QStringLiteral("用水量"));

    ui->tableView->setModel(standItemModel1);
    ui->tableView->horizontalHeader()->hide();

    for (int var = 0; var < 2; ++var) {
        ui->tableView->verticalHeader()->setSectionResizeMode(var,QHeaderView::Stretch);//设定行表头弹性拉伸
    }
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);  //设置表格属性只读，不能编辑
}

void date3Water::CreateView2()
{
    standItemModel2=new QStandardItemModel();
    //添加列头
    standItemModel2->setRowCount(4);
    {
        QStandardItem *standItem1 = new QStandardItem(tr("地址名\n状态"));
        standItemModel2->setItem(1,0,standItem1);                                //表格第j行，第0列添加一项内容
        standItemModel2->item(1,0)->setTextAlignment(Qt::AlignCenter);           //设置表格内容居中
    }
    {
        QStandardItem *standItem1 = new QStandardItem(tr("总线名"));
        standItemModel2->setItem(3,0,standItem1);                                //表格第j行，第0列添加一项内容
        standItemModel2->item(3,0)->setTextAlignment(Qt::AlignCenter);           //设置表格内容居中
    }

    {
        //填写具体数值
        standItemModel2->setItem(0,1,new QStandardItem(tr("泵1")));
        standItemModel2->setItem(0,2,new QStandardItem(tr("泵2")));
        standItemModel2->setItem(0,3,new QStandardItem(tr("泵3")));
        standItemModel2->setItem(0,4,new QStandardItem(tr("泵4")));
        standItemModel2->setItem(0,5,new QStandardItem(tr("阀门1")));
        standItemModel2->setItem(0,6,new QStandardItem(tr("阀门2")));
        standItemModel2->setItem(0,7,new QStandardItem(tr("阀门3")));
        standItemModel2->setItem(0,8,new QStandardItem(tr("阀门4")));
    }

    ui->tableView_2->setModel(standItemModel2);
    ui->tableView_2->horizontalHeader()->hide();
    ui->tableView_2->verticalHeader()->hide();
    for (int var = 0; var < 4; ++var) {
        ui->tableView_2->verticalHeader()->setSectionResizeMode(var,QHeaderView::Stretch);//设定行表头弹性拉伸
    }
    for (int var = 0; var < 9; ++var) {
        ui->tableView_2->horizontalHeader()->setSectionResizeMode(var,QHeaderView::Stretch);//设定行表头弹性拉伸
    }

    ui->tableView_2->setSpan(1,0,2,1);//合并单元格

    ui->tableView_2->setEditTriggers(QAbstractItemView::NoEditTriggers);  //设置表格属性只读，不能编辑
}

void date3Water::CreateView3()
{
    standItemModel3=new QStandardItemModel();
    //    standItemModel3->setColumnCount(33);
    QStandardItem *standItem1 = new QStandardItem(tr("时间日期"));
    standItemModel3->setItem(0,0,standItem1);                                //表格第j行，第0列添加一项内容
    standItemModel3->item(0,0)->setTextAlignment(Qt::AlignCenter);           //设置表格内容居中

    ui->tableView_3->setModel(standItemModel3);
    ui->tableView_3->verticalHeader()->hide();    //隐藏默认显示的行头
    ui->tableView_3->horizontalHeader()->hide();

    ui->tableView_3->setEditTriggers(QAbstractItemView::NoEditTriggers);  //设置表格属性只读，不能编辑
}

void date3Water::CreateView4()
{

    QLineSeries *series1 = new QLineSeries();

    QChart *chart = new QChart();
    chart->legend()->hide();

    //添加数据
    series1->append(0, 6);
    series1->append(2, 4);
    series1->append(3, 8);
    series1->append(7, 4);
    series1->append(10, 5);
    *series1 << QPointF(11, 1) << QPointF(13, 3) << QPointF(17, 6) << QPointF(18, 3) << QPointF(20, 2);

    chart->addSeries(series1);
    chart->setTitle("一天内每小时用水量");
    //设置xy轴坐标
    QValueAxis *axisX=new QValueAxis;
    axisX->setRange(0,24);
    axisX->setTickCount(25);
    axisX->setTitleText("时间");
    axisX->setLabelFormat("%i");
    QValueAxis *axisY=new QValueAxis;
    axisY->setTitleText("日区间用水量");
    axisY->setMin(0);
    chart->addAxis(axisY,Qt::AlignLeft);
    chart->addAxis(axisX,Qt::AlignBottom);
    series1->attachAxis(axisX);
    series1->attachAxis(axisY);

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    ui->horizontalLayout_6->addWidget(chartView);

}
