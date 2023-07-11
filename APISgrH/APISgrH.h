#ifndef APISGRH_H
#define APISGRH_H
//写入自己的专属配置

//gzj协议
#define gzj_firmware "2207150200"
#define gzj_hardware "1.1"

#define gzj_noneStr ""
#define gzj_RequestC "RN"
#define gzj_ProtocolV "Ver"
#define gzj_FunctionC "FN"
#define gzj_OperationC "OP"
#define gzj_AnswerF "AF"
#define gzj_DataOP "Data"
#define gzj_Result "Result"
#define gzj_ErrorC "EC"

#define Ver_gzjVersion "1.0"
#define FN_gzjHeartBeat "A1"
#define FN_gzjDeviceTI "A2"
#define FN_gzjTargetTI "A3"
#define FN_gzjDeviceMI "A4"
#define FN_gzjCircCT "A5"
#define FN_gzjFireware "B1"
#define FN_gzjHadrware "B2"
#define FN_gzjBatteryVS "B3"
#define FN_gzjPowerCS "B4"
#define FN_gzjTimeSync "C1"
#define FN_gzjSeriS "C2"
#define OP_gzjNone "00"
#define OP_gzjRead "03"
#define OP_gzjWrite "06"
#define OP_gzjWriteSpi "16"
#define AF_gzjNoAnswer 0
#define AF_gzjAnswerNoData 1
#define AF_gjzAnswerData 2
#define Result_gzjSuccess 1
#define Result_gzjError 0
#define EC_gzjNoEC 0

#define domIsGZJprotocol dom.HasMember(gzj_RequestC) && dom[gzj_RequestC].IsString() && dom.HasMember(gzj_ProtocolV) && dom[gzj_ProtocolV].GetString()==tr(Ver_gzjVersion) && dom.HasMember(gzj_FunctionC) && dom[gzj_FunctionC].IsString() && dom.HasMember(gzj_OperationC) && dom[gzj_OperationC].IsString() && dom.HasMember(gzj_AnswerF) && dom[gzj_AnswerF].IsInt()


class SeriSettings
{
public:
    SeriSettings();
    SeriSettings(const QString &str_portN ,const int &i_Parity ,const int &i_baud ,const int &i_dateB ,const int &i_stopB ,const int &i_flowC);
    void setSeriSettings(const QString &str_portN ,const int &i_Parity ,const int &i_baud ,const int &i_dateB ,const int &i_stopB ,const int &i_flowC);
    QString PortName;
    int parity;
    int baud;
    int dataBits;
    int stopBits;
    int flowControl;
};
//结构体
//设备类型信息表
class struct_deviceTI
{
public:
    QVariantList VL_TN;
    QVariantList VL_PN;
    QVariantList VL_Name;
    QVariantList VL_EnName;
};
//指标类型信息表
class struct_targetTI
{
public:
    QVariantList VL_TN;
    QVariantList VL_Type;
    QVariantList VL_Name;
    QVariantList VL_EnName;
    QVariantList VL_Unit;
};
//网关所接设备型号信息表
class struct_deviceMI
{
public:
    QVariantList VL_TN;
    QVariantList VL_IT;
    QVariantList VL_PN;
    QVariantList VL_CMD;
    QVariantList VL_PS;
    QVariantList VL_RB;
    QVariantList VL_PB;
    QVariantList VL_TM;
    QVariantList VL_SI;
    QVariantList VL_DL;
    QVariantList VL_DT;
    QVariantList VL_Formula;
    QVariantList VL_UL;
    QVariantList VL_LL;
};
//循环采集配置
class struct_circCT
{
public:
   QVariantList VL_TN;
   QVariantList VL_Addr;
   QVariantList VL_VA;
   QVariantList VL_SP;
   QVariantList VL_IT;
   QVariantList VL_CF;
   QVariantList VL_UF;
};
//Analytic package解析套餐
class struct_analyticP
{
public:
    QVariant VL_RB;
    QVariant VL_PB;
    QVariant VL_TM;
    QVariant VL_SI;
    QVariant VL_DL;
    QVariant VL_DT;
    QVariant VL_Formula;
    QVariant VL_UL;
    QVariant VL_LL;
};
//网关所接设备型号信息表File文件存储
class struct_deviceMIF
{
public:
    QVariantList VL_TN;
    QVariantList VL_IT;
    QVariantList VL_PN;
    QVariantList VL_CMD;
    QVariantList VL_PS;
    QList<struct_analyticP> VL_AP;
};

//采集指令类
class struct_collectI
{
public:
    QVariantList VL_VA;
    QVariantList VL_TN;
    QVariantList VL_Addr;
    QVariantList VL_SP;
    QVariantList VL_CMD;
    QVariantList VL_CF;
    QVariantList VL_CFT;
    QVariantList VL_CFlag;
    QVariantList VL_Result;
    QVariantList VL_EC;
};
//上传指令类
class struct_uploadI
{
public:
    QVariantList VL_VA;
    QVariantList VL_ID;
    QVariantList VL_Value;
    QVariantList VL_CT;
    QVariantList VL_UF;
    QVariantList VL_UFT;
    QVariantList VL_Offli;
    QVariantList VL_State;
    QVariantList VL_CFlag;
    QVariantList VL_ThdChance;

};
//预解析类
class struct_preanalysis
{
public:
    QVariantList VL_VA;
    QVariantList VL_TN;
    QVariantList VL_Preparse;
    QVariantList VL_CMD;
    QVariantList VL_CFlag;
};
//串口全局变量封装
class APISeri
{
public:
    static bool SFF_b_gzj;
    static int SESA5_i_gzj;
    static int SESA6_i_gzj;
    static int SESA7_i_gzj;
    static int CF_i_gzj;
    static int UF_i_gzj;
    static bool A6Exist_b_gzj;
    static bool A7Exist_b_gzj;
};
//全局变量
class APISgrH
{
public:
    APISgrH();
    //全局变量
    //成员变量设置函数
    static void set_deviceTI(const struct_deviceTI &SDTI){
        QMutexLocker locker(&deviceTI_mutex);
        deviceTI_SDTI_gzj=SDTI;
    }
    static void set_targetTI(const struct_targetTI &STTI){
        QMutexLocker locker(&targetTI_mutex);
        targetTI_STTI_gzj=STTI;
    }
    static void set_circCT(const struct_circCT &SCCI){
        QMutexLocker locker(&circCT_mutex);
        circCT_SCCT_gzj=SCCI;
    }
    static void set_deviceMIF(const struct_deviceMIF &SDMIF){
        QMutexLocker locker(&deviceMIF_mutex);
        deviceMIF_SDMIF_gzj=SDMIF;
    }

    //成员变量获取函数
    static struct_deviceTI get_deviceTI(){
        QMutexLocker locker(&deviceTI_mutex);
        return deviceTI_SDTI_gzj;
    }
    static struct_targetTI get_targetTI(){
        QMutexLocker locker(&targetTI_mutex);
        return targetTI_STTI_gzj;
    }
    static struct_circCT get_circCT(){
        QMutexLocker locker(&circCT_mutex);
        return circCT_SCCT_gzj;
    }
    static struct_deviceMIF get_deviceMIF(){
        QMutexLocker locker(&deviceMIF_mutex);
        return deviceMIF_SDMIF_gzj;
    }
    //简单变量
    static int a_i_gzj;
    static int TRT_i_gzj;
    static int DRT_i_gzj;
    static int DLUL_i_gzj;
    static int RTCT_i_gzj;
    static int seriThreadNameSN;
    //类变量
    static struct_circCT circCT_SCCT_gzj;
    static struct_deviceMI deviceMI_SDMI_gzj;
    static struct_deviceTI deviceTI_SDTI_gzj;
    static struct_targetTI targetTI_STTI_gzj;
    static struct_deviceMIF deviceMIF_SDMIF_gzj;
    //锁
    static QMutex seriThreadNameSN_mutex;
    static QMutex circCT_mutex;
    static QMutex deviceMI_mutex;
    static QMutex deviceTI_mutex;
    static QMutex targetTI_mutex;
    static QMutex deviceMIF_mutex;

};

#endif // APISGRH_H
