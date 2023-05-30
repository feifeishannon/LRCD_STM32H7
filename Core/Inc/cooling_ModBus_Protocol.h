#ifndef __COOLING_MODBUS_PROTOCOL_H
#define __COOLING_MODBUS_PROTOCOL_H

#include "stdio.h"
#include "stdarg.h"
#include "string.h"
#include "stdint.h"
#include "stm32h7xx_hal.h"
#include "test.h"   // �����ļ���ģ����Ȧ������Դ������ǰӦʹ��ʵ�������滻
#include <string.h>

typedef unsigned int       uint32_t; 		// ����vscode�쳣��ʾ
#define USART_REC_LEN  			200  		// �����������ֽ��� 200
#define RXBUFFERSIZE            1           // �����С

typedef enum
{
    Cooling_OK       = 0x00,
    Cooling_ERROR    = 0x01,
    Cooling_BUSY     = 0x02,
    Cooling_TIMEOUT  = 0x03
} Cooling_StatusTypeDef;//����ִ��״̬

typedef enum
{
    Cooling_STOP     = 0x00,
    Cooling_GET_STATE    = 0x01,
    Cooling_CHECK     = 0x02,
    Cooling_CMD  = 0x03
} Cooling_StateTypeDef;//״̬������

typedef enum
{
    SYSTEM_ON               = 0x00,
    SYSTEM_OFF              = 0x01,
    SYSTEM_GET_DATA         = 0x02,
    SYSTEM_SET_TEMP_DATA    = 0x03
} Cooling_OperateTypeDef;//�����붨��


typedef struct
{
    uint16_t CoolingRunState;       //0x0000 ���俪��/�ػ�
    uint16_t PIDProportion ;        //0x0001 PID����ֵ(0-250)
    uint16_t PIDIntegral;           //0x0002 PID����ֵ(0-250)
    uint16_t PIDDifferential;       //0x0003 PID΢��ֵ(0-250)
    uint16_t PIDSelfTune;           //0x0004 PID���������أ�ȡֵ��Χ0-1
    uint16_t TargetTemperature;     //0x0005 �趨�¶� ��ʼ��ֵ20��
    uint16_t LowAlarmTemperature;   //0x0006 ���±���
    uint16_t HighAlarmTemperature;  //0x0007 ���±���
    uint16_t TemperatureCalibration;//0x0008 �¶�У׼
    uint16_t OutletTemperature;     //0x0009 �����¶�
    uint16_t InletTemperature;      //0x000A ����¶�
    uint16_t HotSideTemperature;    //0x000B �ȶ��¶�      
    uint16_t CoolingTemperature4;   //0x000C �����¶�4
    uint16_t CoolingTemperature5;   //0x000D �����¶�5
    uint16_t CoolingTemperature6;   //0x000E �����¶�6
    uint16_t WaterPumpFlowRate;     //0x000F ˮ������
    uint16_t liquidheight;          //0x0010 Һλ�߶�
    uint16_t PSD;                   //0x0011 �Ĵ���״̬
    uint16_t CoolRevsionLow;        //0x0012 �Ͱ汾��
    uint16_t CoolRevsionHigh;       //0x0013 �߰汾��
} Modbus_Report_Pack_TypeDef;


/**
 * @brief ʵ��������ж��������
 * 
 */
typedef struct
{
    Modbus_Report_Pack_TypeDef modbusReport;
    UART_HandleTypeDef *huart;
    float currentTemperature;
    float targetTemperature;
    uint8_t modbus_count;
    uint16_t coolingPSD;
    // char *info[1000];                       /* Һ���������Ϣ����,1k����*/
    
    Cooling_StatusTypeDef (* Init)();       /*!< �����û�ͨѶ�ӿ�   */
    Cooling_StatusTypeDef (* Run)();        /*!< ����Һ�������  ���鹤��Ƶ��20hz   */      
    Cooling_StatusTypeDef (* Stop)();       /*!< ֹͣҺ�������     */      
    Cooling_StatusTypeDef (* RxCplt)();       /*!< ֹͣҺ�������     */      
    void (* UpdataPack)();                  /*!< ͨ�����ڷ���modbus�������Һ�����ݼĴ���   */      
    
} Cooling_HandleTypeDef;

extern Cooling_HandleTypeDef Cooling_Handle; //Һ���������������
extern Cooling_StatusTypeDef CoolingCreate(UART_HandleTypeDef *huartcooling);


// void Usart1_init(uint32_t bound);         //���ڳ�ʼ������

#endif /* __COOLING_MODBUS_PROTOCOL_H */