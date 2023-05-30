#ifndef __COOLING_MODBUS_PROTOCOL_H
#define __COOLING_MODBUS_PROTOCOL_H

#include "stdio.h"
#include "stdarg.h"
#include "string.h"
#include "stdint.h"
#include "stm32h7xx_hal.h"
#include "test.h"   // 测试文件，模拟线圈数据来源，发布前应使用实体数据替换
#include <string.h>

typedef unsigned int       uint32_t; 		// 消除vscode异常提示
#define USART_REC_LEN  			200  		// 定义最大接收字节数 200
#define RXBUFFERSIZE            1           // 缓存大小

typedef enum
{
    Cooling_OK       = 0x00,
    Cooling_ERROR    = 0x01,
    Cooling_BUSY     = 0x02,
    Cooling_TIMEOUT  = 0x03
} Cooling_StatusTypeDef;//函数执行状态

typedef enum
{
    Cooling_STOP     = 0x00,
    Cooling_GET_STATE    = 0x01,
    Cooling_CHECK     = 0x02,
    Cooling_CMD  = 0x03
} Cooling_StateTypeDef;//状态机定义

typedef enum
{
    SYSTEM_ON               = 0x00,
    SYSTEM_OFF              = 0x01,
    SYSTEM_GET_DATA         = 0x02,
    SYSTEM_SET_TEMP_DATA    = 0x03
} Cooling_OperateTypeDef;//功能码定义


typedef struct
{
    uint16_t CoolingRunState;       //0x0000 制冷开机/关机
    uint16_t PIDProportion ;        //0x0001 PID比例值(0-250)
    uint16_t PIDIntegral;           //0x0002 PID积分值(0-250)
    uint16_t PIDDifferential;       //0x0003 PID微分值(0-250)
    uint16_t PIDSelfTune;           //0x0004 PID自整定开关，取值范围0-1
    uint16_t TargetTemperature;     //0x0005 设定温度 初始化值20度
    uint16_t LowAlarmTemperature;   //0x0006 低温报警
    uint16_t HighAlarmTemperature;  //0x0007 高温报警
    uint16_t TemperatureCalibration;//0x0008 温度校准
    uint16_t OutletTemperature;     //0x0009 出口温度
    uint16_t InletTemperature;      //0x000A 入口温度
    uint16_t HotSideTemperature;    //0x000B 热端温度      
    uint16_t CoolingTemperature4;   //0x000C 制冷温度4
    uint16_t CoolingTemperature5;   //0x000D 制冷温度5
    uint16_t CoolingTemperature6;   //0x000E 制冷温度6
    uint16_t WaterPumpFlowRate;     //0x000F 水泵流量
    uint16_t liquidheight;          //0x0010 液位高度
    uint16_t PSD;                   //0x0011 寄存器状态
    uint16_t CoolRevsionLow;        //0x0012 低版本号
    uint16_t CoolRevsionHigh;       //0x0013 高版本号
} Modbus_Report_Pack_TypeDef;


/**
 * @brief 实体调试需判定对齐规则
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
    // char *info[1000];                       /* 液冷控制器信息描述,1k缓存*/
    
    Cooling_StatusTypeDef (* Init)();       /*!< 配置用户通讯接口   */
    Cooling_StatusTypeDef (* Run)();        /*!< 启动液冷控制器  建议工作频率20hz   */      
    Cooling_StatusTypeDef (* Stop)();       /*!< 停止液冷控制器     */      
    Cooling_StatusTypeDef (* RxCplt)();       /*!< 停止液冷控制器     */      
    void (* UpdataPack)();                  /*!< 通过串口发送modbus命令更新液冷数据寄存器   */      
    
} Cooling_HandleTypeDef;

extern Cooling_HandleTypeDef Cooling_Handle; //液冷控制器单例对象
extern Cooling_StatusTypeDef CoolingCreate(UART_HandleTypeDef *huartcooling);


// void Usart1_init(uint32_t bound);         //串口初始化函数

#endif /* __COOLING_MODBUS_PROTOCOL_H */