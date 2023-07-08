#include "logprintwidget.h"
#include "ui_logprintwidget.h"
#include "qtconcurrentrun.h"
logPrintWidget::logPrintWidget(QWidget *parent) :
    FramelessWidget(parent),
    ui(new Ui::logPrintWidget)
{
    ui->setupUi(this);
    this->setGeometry(0,0,1024,600);

    connect(this,&logPrintWidget::SignUpdateTB,this,&logPrintWidget::SlotsUpdateTB);
    connect(ui->flushBtn, &QPushButton::clicked, this, &logPrintWidget::flushFile);
    //返回
    connect(ui->returnBtn,&QPushButton::clicked,this,&logPrintWidget::close);
    QScroller *scl = QScroller::scroller(ui->textBrowser);
    scl->grabGesture(ui->textBrowser,QScroller::LeftMouseButtonGesture);
    emit ui->flushBtn->clicked();
    //        ui->textBrowser->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    //    QScrollerProperties properties = scl->scrollerProperties();
    //    properties.setScrollMetric(QScrollerProperties::DragVelocitySmoothingFactor,0.1);//滑动
    //    properties.setScrollMetric(QScrollerProperties::FrameRate,QScrollerProperties::Fps60);
    //    properties.setScrollMetric(QScrollerProperties::SnapTime,0.1);//设置滚动曲线的时间因子。设置滚动的时长,值越小，滚动时间越长
    //    properties.setScrollMetric(QScrollerProperties::MaximumVelocity,0.1);//设置自动滚动能达到得最大速度，m/s
    //    scl->setScrollerProperties(properties);
}

logPrintWidget::~logPrintWidget()
{
    delete ui;
}

void logPrintWidget::test()
{
    QString data;
    QFile file(QCoreApplication::applicationDirPath() + "/" +"log/log.txt");
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug()<<"文件未打开!";
    }
    while(!file.atEnd())
    {
        QByteArray array = file.readLine();
        QString str(array);
        data.prepend(str);
    }
    file.close();
    emit logPrintWidget::SignUpdateTB(data);
}

void logPrintWidget::flushFile()
{
    QtConcurrent::run(this,&logPrintWidget::test);
}

void logPrintWidget::SlotsUpdateTB(const QString &_data)
{
    ui->textBrowser->setText(_data);
}

