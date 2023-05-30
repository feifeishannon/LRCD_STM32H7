

#include "test.h"

BAT_DATA_Pack_TypeDef BAT_DATA_Pack;

void BATinit(void){
    BAT_DATA_Pack.BatID = BatLevel8;//平八线圈id
    BAT_DATA_Pack.BAT_Temperature = 20.0;//线圈温度设定为20度
}