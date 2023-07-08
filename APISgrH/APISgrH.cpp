#include "APISgrH/APISgrH.h"
int APISgrH::a_i_gzj=10;
int APISgrH::TRT_i_gzj=3;
int APISgrH::DRT_i_gzj=10;
int APISgrH::DLUL_i_gzj=9999;
int APISgrH::RTCT_i_gzj=6000;
int APISgrH::seriThreadNameSN=1;
struct_deviceTI APISgrH::deviceTI_SDTI_gzj;
QMutex APISgrH::deviceTI_mutex;
QMutex APISgrH::seriThreadNameSN_mutex;
SeriSettings::SeriSettings()
{

}

SeriSettings::SeriSettings(const QString &str_portN ,const int &i_Parity ,const int &i_baud ,const int &i_dateB ,const int &i_stopB ,const int &i_flowC):
    PortName(str_portN),parity(i_Parity),baud(i_baud),dataBits(i_dateB),stopBits(i_stopB),flowControl(i_flowC)
{

}

void SeriSettings::setSeriSettings(const QString &str_portN, const int &i_Parity, const int &i_baud, const int &i_dateB, const int &i_stopB, const int &i_flowC)
{
    this->PortName=str_portN;
    this->parity=i_Parity;
    this->baud=i_baud;
    this->dataBits=i_dateB;
    this->stopBits=i_stopB;
    this->flowControl=i_flowC;
}
