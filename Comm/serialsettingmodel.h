#ifndef SERIALSETTINGMODEL_H
#define SERIALSETTINGMODEL_H

#include <QObject>
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

public slots:
    void countSlot();
    void msgParse(const QByteArray &_collect_ba, const QByteArray &_byte_array);
    void initCCI();
private:
    QList<circulateCI> * m_L_CCI;
};

#endif // SERIALSETTINGMODEL_H
