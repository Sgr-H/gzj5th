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

private:
    Ui::Widgetui *ui;
};
#endif // WIDGETUI_H
