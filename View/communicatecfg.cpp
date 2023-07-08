#include "communicatecfg.h"
#include "ui_communicatecfg.h"

CommunicateCfg::CommunicateCfg(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CommunicateCfg)
{
    ui->setupUi(this);
    connect(ui->pushButton_13,&QPushButton::clicked,this,[=]{
        this->hide();
    });
}

CommunicateCfg::~CommunicateCfg()
{
    delete ui;
}

