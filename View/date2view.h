#ifndef DATE2VIEW_H
#define DATE2VIEW_H

#include <QWidget>

namespace Ui {
class date2View;
}

class date2View : public QWidget
{
    Q_OBJECT

public:
    explicit date2View(QWidget *parent = nullptr);
    ~date2View();
    void CreateView();
    void setDeviceSelect(int _var);

private:
    //变量
    QPushButton *m_4851Btn;
    QPushButton *m_4852Btn;
    QPushButton *m_4853Btn;
    QPushButton *m_4854Btn;
    QPushButton *m_mbusBtn;
    QStandardItemModel *standItemModel1;
    Ui::date2View *ui;
    //标记位
    quint8 deviceSelct;
    //函数
    void uiConnect();
};

#endif // DATE2VIEW_H
