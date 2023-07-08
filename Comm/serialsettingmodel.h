#ifndef SERIALSETTINGMODEL_H
#define SERIALSETTINGMODEL_H

#include <QObject>
using namespace rapidjson;

struct circulateCI
{
    int CCI_TN;
    QString CCI_Addr;
    int CCI_VA;
    QString CCI_SP;
    QString CCI_CMD;
    QString CCI_CF;
    QString CCI_UF;
    int CCI_CFT;
    int CCI_UFT;
    QVariantList CCI_ID;
    QVariantList CCI_Value;
};
class SerialSettingModel : public QObject
{
    Q_OBJECT
public:
    explicit SerialSettingModel(QObject *parent = nullptr);

signals:
    void SModelSignToTcpSend(const QByteArray &_data);
public slots:
    void countSlot();
    void msgParse(const QByteArray &_collect_ba, const QByteArray &_byte_array);
    void initCCI();
private:
    QList<circulateCI> * m_L_CCI;
    //函数
    bool A5isEmpty();
    bool A4isEmpty();
};

#endif // SERIALSETTINGMODEL_H
