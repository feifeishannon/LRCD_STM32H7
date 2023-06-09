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
    BatIDLink BatID;          //����ID����
    float BAT_Temperature;       //0x0001 ��Ȧ�¶�
} BAT_DATA_Pack_TypeDef;

/**
  * ���Ʒ���
  */
typedef struct
{
	uint8_t Msg1;	    //����ǿ��
	uint16_t Msg2;     //Ԥ��
	uint32_t Msg_a;    //����Ƶ��
	uint32_t Msg_b;    //�Ӽ�Ƶ��
	uint16_t Msg_d;    //���ڴ���
	uint16_t Msg_c;    //���ڸ���
	uint16_t Msg_e;    //����
	uint16_t Msg_f;    //��Ъʱ��
	uint16_t Msg8;     //�������
	uint16_t Msg9;     //����ʱ��

} TreatProject_T; 


extern TreatProject_T stTreatProject;

extern BAT_DATA_Pack_TypeDef BAT_DATA_Pack;
void BATinit(void);


#endif //__TEST_H
