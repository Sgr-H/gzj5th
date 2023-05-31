#include "loginwidget.h"
#include "ui_loginwidget.h"

LogInWidget::LogInWidget(QWidget *parent) :
    FramelessWidget(parent),
    ui(new Ui::LogInWidget)
{
    ui->setupUi(this);
    this->setGeometry(0,0,1024,600);
    timerFlush=new QTimer(this);
    timerFlush->start(1000);
    //返回按钮
    connect(ui->btn_return,&QPushButton::clicked,this,&LogInWidget::btn_return_clicked);
    //登录按钮
    connect(ui->btn_log,&QPushButton::clicked,this,&LogInWidget::btn_log_clicked);
    //出发关闭登录窗口的信号连接
    connect(this,&LogInWidget::close_window,this,&LogInWidget::close);
    //刷新时间
    connect(timerFlush,&QTimer::timeout,this,&LogInWidget::timeUpdata);

    ui->edit_pw->setEchoMode(QLineEdit::Password);//输入的时候就显示圆点
    m_username = "gzj";
    m_password = "gzj";
}

LogInWidget::~LogInWidget()
{
    delete ui;
}

void LogInWidget::btn_return_clicked()
{
    emit(close_window());

}

void LogInWidget::btn_log_clicked()
{
    // 从输入框获取账号
    QString name = ui->edit_name->text();
    // 从输入框获取密码
    QString password = ui->edit_pw->text();

    //账号和密码匹配正确
    if (name == m_username && password == m_password)
    {
//        ui->edit_name->setText("");
//        ui->edit_pw->setText("");
        emit(login());
        emit(close_window());
    }
    else // 账号或密码错误
        QMessageBox::information(this, "Warning","Username or Password is wrong !");

}

void LogInWidget::timeUpdata()
{
    QDateTime time =QDateTime::currentDateTime();
    timeNow=time.toString("yyyy-MM-dd hh:mm:ss ddd");
    ui->label->setText(timeNow);
}
