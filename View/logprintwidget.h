#ifndef LOGPRINTWIDGET_H
#define LOGPRINTWIDGET_H

#include <QWidget>
#include "framelesscore/framelesswidget.h"
namespace Ui {
class logPrintWidget;
}

class logPrintWidget : public FramelessWidget
{
    Q_OBJECT

public:
    explicit logPrintWidget(QWidget *parent = nullptr);
    ~logPrintWidget();

private:
    Ui::logPrintWidget *ui;
};

#endif // LOGPRINTWIDGET_H
