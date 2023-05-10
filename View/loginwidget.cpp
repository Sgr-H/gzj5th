#include "loginwidget.h"
#include "ui_loginwidget.h"

LogInWidget::LogInWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LogInWidget)
{
    ui->setupUi(this);
}

LogInWidget::~LogInWidget()
{
    delete ui;
}
