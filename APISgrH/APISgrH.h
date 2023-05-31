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
#define OP_gzjNone "00"
#define OP_gzjRead "03"
#define OP_gzjWrite "06"
#define OP_gzjWriteSpi "16"
#define AF_gzjNoAnswer 0
#define AF_gzjAnswerData 1
#define AF_gjzAnswerNoData 2


#endif // APISGRH_H
