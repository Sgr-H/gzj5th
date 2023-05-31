#ifndef EQUIPOPERA_H
#define EQUIPOPERA_H

#include <QWidget>

namespace Ui {
class EquipOpera;
}

class EquipOpera : public QWidget
{
    Q_OBJECT

public:
    explicit EquipOpera(QWidget *parent = nullptr);
    ~EquipOpera();

private:
    Ui::EquipOpera *ui;
    //变量
    QStandardItemModel *standItemModel1;
    QStandardItemModel *standItemModel2;
    //函数
    void CreateView();
    void CreateView2();
    void uiConnect();
};

#endif // EQUIPOPERA_H
