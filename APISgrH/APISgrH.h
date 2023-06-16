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

//结构体
struct struct_deviceTI
{
    QVariantList VL_TN;
    QVariantList VL_PN;
    QVariantList VL_Name;
    QVariantList VL_EnName;
};
struct struct_targetTI
{
    QVariantList VL_TN;
    QVariantList VL_Type;
    QVariantList VL_Name;
    QVariantList VL_EnName;
    QVariantList VL_Unit;
};
struct struct_deviceMI
{
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
struct struct_circCT
{
    QVariantList VL_TN;
    QVariantList VL_Addr;
    QVariantList VL_VA;
    QVariantList VL_SP;
    QVariantList VL_CMD;
    QVariantList VL_CF;
    QVariantList VL_UF;
};

#endif // APISGRH_H
