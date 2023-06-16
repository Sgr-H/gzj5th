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
    void msgParse(const QString &_rev_msg);
private:
    void A2_00_2(Document &dom);//A2网关主动请求
    void A2_06_0(Document &dom);//A2上位机写网关操作
    void A2_03_0(Document &dom);//A2上位机读取网关

    void A3_00_2(Document &dom);//A3网关主动请求（操作码00）
    void A3_03_0(Document &dom);//A3上位机读取网关（操作码03）
    void A3_06_0(Document &dom);//A3上位机写网关（操作码06）

    void A4_00_2(Document &dom);//A4网关主动请求（操作码00）
    void A4_03_0(Document &dom);//A4上位机读取网关（操作码03）
    void A4_06_0(Document &dom);//A4上位机写网关（操作码06）

    void A5_00_2(Document &dom);//A5网关主动请求（操作码00）
    void A5_03_0(Document &dom);//A5上位机读取网关（操作码03）
    void A5_06_0(Document &dom);//A5上位机写网关（操作码06）

    void B1_03_0(Document &dom);//B1固件版本读取指令B1（操作码03）
    void B2_03_0(Document &dom);//B2硬件版本读取指令B2（操作码03）
    void B3_03_0(Document &dom);//B3电池电压状态读取指令B3（操作码03）
    void B4_03_0(Document &dom);//B4电源供电状态读取指令B4（操作码03）

    void C1_03_0(Document &dom);//C1时间同步（操作码03）
    void C1_06_0(Document &dom);//C1时间同步（操作码06）

    void C2_03_0(const QString &dom);//读串口配置（操作码03）
    void C2_06_0(Document &dom);//写串口配置（操作码06）
    //变量
};

#endif // TCPCLIENTMODEL_H
