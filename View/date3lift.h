#ifndef DATE3LIFT_H
#define DATE3LIFT_H

#include <QWidget>

namespace Ui {
class date3lift;
}

class date3lift : public QWidget
{
    Q_OBJECT

public:
    explicit date3lift(QWidget *parent = nullptr);
    ~date3lift();

private:
    Ui::date3lift *ui;
    //变量
    QStandardItemModel *standItemModel1;
    //函数
    void CreateView();
    void uiConnect();
};

#endif // DATE3LIFT_H
