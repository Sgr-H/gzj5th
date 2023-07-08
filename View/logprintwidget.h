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
    void test();
signals:
    void SignUpdateTB(const QString&_data);
public slots:
    void flushFile();
    void SlotsUpdateTB(const QString&_data);
private:

    Ui::logPrintWidget *ui;
};

#endif // LOGPRINTWIDGET_H
