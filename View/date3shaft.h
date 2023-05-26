#ifndef DATE3SHAFT_H
#define DATE3SHAFT_H

#include <QWidget>

namespace Ui {
class date3Shaft;
}

class date3Shaft : public QWidget
{
    Q_OBJECT

public:
    explicit date3Shaft(QWidget *parent = nullptr);
    ~date3Shaft();

private:
    Ui::date3Shaft *ui;
    //变量
    QStandardItemModel *standItemModel1;
    QStandardItemModel *standItemModel2;
    //函数
    void CreateView();
    void CreateView2();
    void uiConnect();
};

#endif // DATE3SHAFT_H
