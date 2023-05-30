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

extern BAT_DATA_Pack_TypeDef BAT_DATA_Pack;


#endif //__TEST_H