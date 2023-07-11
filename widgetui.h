#ifndef WIDGETUI_H
#define WIDGETUI_H

#include <QWidget>
#include "framelesscore/framelesswidget.h"
QT_BEGIN_NAMESPACE
namespace Ui { class Widgetui; }
QT_END_NAMESPACE

class Widgetui : public FramelessWidget
{
    Q_OBJECT

public:
    Widgetui(QWidget *parent = nullptr);
    ~Widgetui();
signals:

public slots:

private:
    //函数
    void init();
    void initGlobal();
    void jumpWriteSetting(int _var);
    //变量
    Ui::Widgetui *ui;
    QSettings *m_uiSelect=nullptr;
};
#endif // WIDGETUI_H
