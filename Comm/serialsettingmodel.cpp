#include "serialsettingmodel.h"

SerialSettingModel::SerialSettingModel(QObject *parent) : QObject(parent)
{

}

void SerialSettingModel::countSlot()
{

}

void SerialSettingModel::msgParse(const QByteArray &_collect_ba, const QByteArray &_byte_array)
{
    qDebug()<<_collect_ba<<_byte_array;
}

