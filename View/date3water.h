#ifndef DATE3WATER_H
#define DATE3WATER_H

#include <QWidget>

namespace Ui {
class date3Water;
}

class date3Water : public QWidget
{
    Q_OBJECT

public:
    explicit date3Water(QWidget *parent = nullptr);
    ~date3Water();

private:
    Ui::date3Water *ui;
    //变量
    QStandardItemModel *standItemModel1;
    QStandardItemModel *standItemModel2;
    //函数
    void initdate3Water();
    void uiConnect();
    void CreateView();
    void CreateView2();
};

#endif // DATE3WATER_H
