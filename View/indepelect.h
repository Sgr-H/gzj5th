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
signals:
    void showWidgetUI();//显示主界面
    void clearCfg();//清除配置文件
public slots:
    void SlotPriEquip(const int &var);
private:
    //变量
    Ui::IndepElect *ui;
    int m_stackWidgetCurrentPage=0;
    int m_priStackWidgetCurrentPage=0;
    //函数
    void deleteAllitemsOfLayout(QLayout* layout);
};

#endif // INDEPELECT_H
