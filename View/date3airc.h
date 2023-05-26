#ifndef DATE3AIRC_H
#define DATE3AIRC_H

#include <QWidget>

namespace Ui {
class date3Airc;
}

class date3Airc : public QWidget
{
    Q_OBJECT

public:
    explicit date3Airc(QWidget *parent = nullptr);
    ~date3Airc();
public slots:
    void airCbtn_clicked();
private:
    Ui::date3Airc *ui;
    //变量
    QStandardItemModel *standItemModel1;
    QStandardItemModel *standItemModel2;
    QPushButton *m_aircBtn1;
    //函数
    void CreateView();
    void CreateView2();
    void uiConnect();
    void initDate3Airc();
};

#endif // DATE3AIRC_H
