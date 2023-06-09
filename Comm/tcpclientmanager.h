#ifndef TCPCLIENTMANAGER_H
#define TCPCLIENTMANAGER_H

#include <QObject>
#include "Comm/tcpclientmodel.h"

class TcpClientManager : public QObject
{
    SINGLETON(TcpClientManager)
    Q_OBJECT


signals:

    void readSeriSetting(QString _strDom);
    void writeSeriSetting(const QVariantList &VL_SP,const QVariantList &VL_Baud,
                          const QVariantList &VL_CB,const QVariantList &VL_DB,const QVariantList &VL_SB);

    void finishedCountSignal();
    void startedCountSignal();
    void showFinishedCountUiSignal();
    void msgParse(const QString &_rev_msg);
    void modelSend(const QByteArray &_data);
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
