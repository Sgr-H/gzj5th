#ifndef INDEPELECT_H
#define INDEPELECT_H

#include <QWidget>
#include "framelesscore/framelesswidget.h"
namespace Ui {
class IndepElect;
}

class IndepElect : public FramelessWidget
{
    Q_OBJECT

public:
    IndepElect(QWidget *parent = nullptr);
    ~IndepElect();
    //函数
    void DIOVisial(int var);

signals:
    void showWidgetUI();//显示主界面
    void clearCfg();//清除配置文件
public slots:
    void SlotPriEquip(const int &var);
    void timeUpdata(void);
private:
    //变量
    Ui::IndepElect *ui;
    //时间刷新
    QTimer *timerFlush = nullptr;
    //存储时间
    QString timeNow=nullptr;
    int m_stackWidgetCurrentPage=0;
    int m_priStackWidgetCurrentPage=0;
    //函数
    void init();
    void uiConnect();
    void deleteAllitemsOfLayout(QLayout* layout);
};

#endif // INDEPELECT_H
