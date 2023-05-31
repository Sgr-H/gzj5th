#ifndef LOGINWIDGET_H
#define LOGINWIDGET_H

#include <QWidget>
#include "framelesscore/framelesswidget.h"

namespace Ui {
class LogInWidget;
}

class LogInWidget : public FramelessWidget
{
    Q_OBJECT

public:
    LogInWidget(QWidget *parent = nullptr);
    ~LogInWidget();
signals:
    void login(); //登录主界面信号
    void close_window(); //关闭登录界面信号

public slots:
    void btn_return_clicked(); //重置按钮按下后触发的事件
    void btn_log_clicked(); //登录按钮按下后触发的事件
    void timeUpdata(void);
private:
    Ui::LogInWidget *ui;
    QString m_username;  // 自己设定的账号
    QString m_password;  // 自己设定的密码
    //时间刷新
    QTimer *timerFlush = nullptr;
    //存储时间
    QString timeNow=nullptr;
};

#endif // LOGINWIDGET_H
