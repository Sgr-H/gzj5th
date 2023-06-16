#ifndef SERIALSETTINGMANAGER_H
#define SERIALSETTINGMANAGER_H

#include <QObject>
#include "Comm/serialsettingmodel.h"

class SerialSettingManager : public QObject
{
    SINGLETON(SerialSettingManager)
    Q_OBJECT

signals:
    void finishedCountSignal();
    void startedCountSignal();
    void showFinishedCountUiSignal();
    void msgParse(const QByteArray &_collect_ba, const QByteArray &_byte_array);
    void modelSend(const QByteArray &_data);
public slots:
    void quitCountThreadSlot();
private:
    //变量
    QThread *threadCount;
    SerialSettingModel *serialSettingModel=nullptr;
    //函数
    void initController();
};

#endif // SERIALSETTINGMANAGER_H
