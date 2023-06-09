#ifndef __TEST_H
#define __TEST_H

#include "stdint.h"


typedef enum
{
    BatNULL     = 0x00,
    BatLevel8   = 0x01,
    BatRound    = 0x02,
    BatRF       = 0x03
} BatIDLink;

typedef struct
{
    BatIDLink BatID;          //拍子ID连接
    float BAT_Temperature;       //0x0001 线圈温度
} BAT_DATA_Pack_TypeDef;

/**
  * 治疗方案
  */
typedef struct
{
	uint8_t Msg1;	    //绝对强度
	uint16_t Msg2;     //预留
	uint32_t Msg_a;    //从内频率
	uint32_t Msg_b;    //从间频率
	uint16_t Msg_d;    //串内从数
	uint16_t Msg_c;    //从内个数
	uint16_t Msg_e;    //串数
	uint16_t Msg_f;    //间歇时间
	uint16_t Msg8;     //脉冲个数
	uint16_t Msg9;     //脉冲时间

} TreatProject_T; 


extern TreatProject_T stTreatProject;

extern BAT_DATA_Pack_TypeDef BAT_DATA_Pack;
void BATinit(void);


#endif //__TEST_H
