#ifndef TCPCLIENTMODEL_H
#define TCPCLIENTMODEL_H

#include <QObject>
using namespace rapidjson;
class TcpClientModel : public QObject
{
    Q_OBJECT
public:
    explicit TcpClientModel(QObject *parent = nullptr);

signals:

public slots:
    void countSlot();
    void msgParse(const QString _rev_msg);
private:
    void A2_06_0(Document &dom);//上位机写网关操作
    void A2_03_0(Document &dom);//上位机读取网关
    //变量

};

#endif // TCPCLIENTMODEL_H
