#ifndef SERIALSETTINGMODEL_H
#define SERIALSETTINGMODEL_H

#include <QObject>

class SerialSettingModel : public QObject
{
    Q_OBJECT
public:
    explicit SerialSettingModel(QObject *parent = nullptr);

signals:

public slots:
    void countSlot();
    void msgParse(const QByteArray &_collect_ba, const QByteArray &_byte_array);
};

#endif // SERIALSETTINGMODEL_H
