#ifndef COMMUNICATECFG_H
#define COMMUNICATECFG_H

#include <QWidget>

namespace Ui {
class CommunicateCfg;
}

class CommunicateCfg : public QWidget
{
    Q_OBJECT

public:
    explicit CommunicateCfg(QWidget *parent = nullptr);
    ~CommunicateCfg();

private:
    Ui::CommunicateCfg *ui;
};

#endif // COMMUNICATECFG_H
