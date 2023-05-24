#ifndef DATE1VIEW_H
#define DATE1VIEW_H

#include <QWidget>

namespace Ui {
class date1View;
}

class date1View : public QWidget
{
    Q_OBJECT

public:
    explicit date1View(QWidget *parent = nullptr);
    ~date1View();
    void CreateView();
    void uiConnect();
private:
    //变量
    Ui::date1View *ui;
    QStandardItemModel *standItemModel1;
    QStandardItemModel *standItemModel2;
};

#endif // DATE1VIEW_H
