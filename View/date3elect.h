#ifndef DATE3ELECT_H
#define DATE3ELECT_H

#include <QWidget>

namespace Ui {
class date3Elect;
}

class date3Elect : public QWidget
{
    Q_OBJECT

public:
    explicit date3Elect(QWidget *parent = nullptr);
    ~date3Elect();

private:
    Ui::date3Elect *ui;
    //变量
    QStandardItemModel *standItemModel1;
    QStandardItemModel *standItemModel2;
    //标记位
    quint8 electOrTemp;
    //函数
    void initdate3Elect();
    void CreateView();
    void CreateView2();
    void uiConnect();
};

#endif // DATE3ELECT_H
