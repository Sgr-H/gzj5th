#include "date3elect.h"
#include "ui_date3elect.h"

date3Elect::date3Elect(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::date3Elect)
{
    ui->setupUi(this);
    this->setGeometry(0,0,1024,600);
    initdate3Elect();
    CreateView();
    CreateView2();
    uiConnect();
}

date3Elect::~date3Elect()
{
    delete ui;
}

void date3Elect::initdate3Elect()
{
    ui->stackedWidget->setCurrentIndex(0);
    electOrTemp=1;
    ui->pushButton->setStyleSheet(tr("QPushButton{background-color: rgb(204, 0, 0);}"));
}

void date3Elect::CreateView()
{
    standItemModel1 = new QStandardItemModel();
    //添加列头
    standItemModel1->setRowCount(12);
    standItemModel1->setHeaderData(0,Qt::Vertical,QStringLiteral("指标名"));   //设置列头内容
    standItemModel1->setHeaderData(1,Qt::Vertical,QStringLiteral("A相电压"));
    standItemModel1->setHeaderData(2,Qt::Vertical,QStringLiteral("B相电压"));
    standItemModel1->setHeaderData(3,Qt::Vertical,QStringLiteral("C相电压"));
    standItemModel1->setHeaderData(4,Qt::Vertical,QStringLiteral("AB线电压"));
    standItemModel1->setHeaderData(5,Qt::Vertical,QStringLiteral("BC线电压"));
    standItemModel1->setHeaderData(6,Qt::Vertical,QStringLiteral("AC线电压"));
    standItemModel1->setHeaderData(7,Qt::Vertical,QStringLiteral("A相电流"));
    standItemModel1->setHeaderData(8,Qt::Vertical,QStringLiteral("B相电流"));
    standItemModel1->setHeaderData(9,Qt::Vertical,QStringLiteral("C相电流"));
    standItemModel1->setHeaderData(10,Qt::Vertical,QStringLiteral("正向有功功率"));
    standItemModel1->setHeaderData(11,Qt::Vertical,QStringLiteral("用电累计总量"));





    QStandardItem *standItem1 = new QStandardItem(tr("输入%1").arg(1));
    standItemModel1->setItem(1,1,standItem1);                                //表格第i行，第0列添加一项内容
    standItemModel1->item(1,1)->setForeground(QBrush(QColor(255,0,0)));      //设置字符颜色
    standItemModel1->item(1,1)->setTextAlignment(Qt::AlignCenter);           //设置表格内容居中

    ui->tableView->setModel(standItemModel1);
    ui->tableView->horizontalHeader()->hide();

    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);  //设置表格属性只读，不能编辑
}

void date3Elect::CreateView2()
{

}

void date3Elect::uiConnect()
{
    //测试用日期控件
    connect(ui->calendarWidget,&QCalendarWidget::selectionChanged,[=]{
        qDebug()<< ui->calendarWidget->selectedDate().toString("yyyy-MM-dd");
    });
    connect(ui->calendarWidget_2,&QCalendarWidget::selectionChanged,[=]{
        qDebug()<< ui->calendarWidget_2->selectedDate().toString("yyyy-MM-dd");
    });

    //隐藏当前界面
    connect(ui->pushButton_10,&QPushButton::clicked,[=]{
        this->hide();
    });
    //日期确认到下一个
    connect(ui->pushButton_4,&QPushButton::clicked,[=]{
        ui->stackedWidget->setCurrentIndex(1);
    });
    //历史界面选择日期
    connect(ui->pushButton_7,&QPushButton::clicked,[=]{
        QDate str1,str2;
        str1=ui->calendarWidget->selectedDate();
        str2=ui->calendarWidget_2->selectedDate();
        if(str1 < str2)
            ui->stackedWidget->setCurrentIndex(2);
        else
            QMessageBox::critical(this,"critical",tr("起始日期不可大于结束日期"));
    });
    //实时数据第一页
    connect(ui->pushButton_2,&QPushButton::clicked,[=]{
        ui->stackedWidget->setCurrentIndex(0);
    });
    //电表按钮
    connect(ui->pushButton,&QPushButton::clicked,[=]{
        ui->stackedWidget->setCurrentIndex(0);
        ui->pushButton->setStyleSheet(tr("QPushButton{background-color: rgb(204, 0, 0);}"));
        ui->pushButton_3->setStyleSheet(tr("QPushButton{background-color: rgb(255, 255, 255);}"));
    });
    //温控器按钮
    connect(ui->pushButton_3,&QPushButton::clicked,[=]{
        ui->pushButton_3->setStyleSheet(tr("QPushButton{background-color: rgb(204, 0, 0);}"));
        ui->pushButton->setStyleSheet(tr("QPushButton{background-color: rgb(255, 255, 255);}"));
    });
}
