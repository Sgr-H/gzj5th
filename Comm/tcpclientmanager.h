#ifndef TCPCLIENTMANAGER_H
#define TCPCLIENTMANAGER_H

#include <QObject>
#include "Comm/tcpclientmodel.h"

class TcpClientManager : public QObject
{
    SINGLETON(TcpClientManager)
    Q_OBJECT


signals:

    void finishedCountSignal();
    void startedCountSignal();
    void showFinishedCountUiSignal();
    void msgParse(const QString _rev_msg);
    void modelSend(const char *_data);
public slots:
    void quitCountThreadSlot();
private:
    //变量
    QThread *threadCount;
    TcpClientModel *tcpClientModel=nullptr;
    //函数
    void initController();

};

#endif // TCPCLIENTMANAGER_H
