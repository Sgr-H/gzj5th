#ifndef APISGRH_H
#define APISGRH_H
//写入自己的专属配置

//gzj协议
#define gzj_noneStr ""
#define gzj_RequestC "RN"
#define gzj_ProtocolV "Ver"
#define gzj_FunctionC "FN"
#define gzj_OperationC "OP"
#define gzj_AnswerF "AF"
#define gzj_DataOP "Data"

#define Ver_gzjVersion "1.0"
#define FN_gzjHeartBeat "A1"
#define FN_gzjDeviceTI "A2"
#define OP_gzjNone "00"
#define OP_gzjRead "03"
#define OP_gzjWrite "06"
#define OP_gzjWriteSpi "16"
#define AF_gzjNoAnswer 0
#define AF_gzjAnswerNoData 1
#define AF_gjzAnswerData 2

#define domIsGZJprotocol dom.HasMember(gzj_RequestC) && dom[gzj_RequestC].IsString() && dom.HasMember(gzj_ProtocolV) && dom[gzj_ProtocolV].GetString()==tr(Ver_gzjVersion) && dom.HasMember(gzj_FunctionC) && dom[gzj_FunctionC].IsString() && dom.HasMember(gzj_OperationC) && dom[gzj_OperationC].IsString() && dom.HasMember(gzj_AnswerF) && dom[gzj_AnswerF].IsInt()


#endif // APISGRH_H
