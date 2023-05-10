#include "indepelect.h"
#include "ui_indepelect.h"
#include "bridgemanager.h"
IndepElect::IndepElect(QWidget *parent) :
    FramelessWidget(parent),
    ui(new Ui::IndepElect)
{
    ui->setupUi(this);

    m_priStackWidgetCurrentPage=m_stackWidgetCurrentPage;

    connect(ui->pushButton,&QPushButton::clicked,this,[=]{
        this->hide();
        emit showWidgetUI();
    });
    connect(ui->pushButton_2,&QPushButton::clicked,this,&IndepElect::clearCfg);
}

IndepElect::~IndepElect()
{
    delete ui;
}

void IndepElect::SlotPriEquip(const int &var)
{
    m_priStackWidgetCurrentPage=m_stackWidgetCurrentPage;
    m_stackWidgetCurrentPage=var;
    if(m_stackWidgetCurrentPage>0)
        m_stackWidgetCurrentPage--;
    if(m_priStackWidgetCurrentPage!=m_stackWidgetCurrentPage){
        switch (m_stackWidgetCurrentPage) {
        case 0:
            if(m_priStackWidgetCurrentPage==1){
//                ui->horizontalLayout_3->removeWidget(ui->frame_2);
                deleteAllitemsOfLayout(ui->horizontalLayout_3);
                ui->horizontalLayout_9->addWidget(ui->frame_2);
            }
            break;
        case 1:
            if(m_priStackWidgetCurrentPage==0){
//                ui->horizontalLayout_9->removeWidget(ui->frame_2);
                deleteAllitemsOfLayout(ui->horizontalLayout_9);
                ui->horizontalLayout_3->addWidget(ui->frame);
                ui->horizontalLayout_3->addWidget(ui->frame_2);
            }
            break;
        default:
            break;
        }
    }
    ui->stackedWidget->setCurrentIndex(m_stackWidgetCurrentPage);
}

//清空布局
void IndepElect::deleteAllitemsOfLayout(QLayout *layout)
{
    QLayoutItem *child;
        while ((child = layout->takeAt(0)) != nullptr)
        {
            //setParent为NULL，防止删除之后界面不消失
            if(child->widget())
            {
                child->widget()->setParent(nullptr);
            }
            else if(child->layout())
            {
                deleteAllitemsOfLayout(child->layout());
            }
            delete child;
        }
}
