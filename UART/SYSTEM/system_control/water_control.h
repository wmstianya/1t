#ifndef __WATER_CONTROL_H
#define __WATER_CONTROL_H

#include "main.h"
#include "global_data.h"

/* 水位状态枚举 */
typedef enum {
    WATER_LEVEL_PROTECT = 0,
    WATER_LEVEL_MID = 1,
    WATER_LEVEL_HIGH = 2,
    WATER_LEVEL_SUPER_HIGH = 3
} water_level_t;

/* 水泵控制模式 */
typedef enum {
    WATER_MODE_NORMAL = 0,     /* 普通补水模式 */
    WATER_MODE_FREQUENCY = 1   /* 变频补水模式 */
} water_mode_t;

/* 双机水控制逻辑结构体 */
typedef struct {
    uint8_t zstate_Flag;    /* 主机状态标志 */
    uint8_t cstate_Flag;    /* 从机状态标志 */
    uint8_t zSignal;        /* 主机信号 */
    uint8_t cSignal;        /* 从机信号 */
    uint8_t zCommand;       /* 主机命令 */
    uint8_t cCommand;       /* 从机命令 */
    uint8_t pump_Signal;    /* 水泵信号 */
    uint16_t zc_Open_Time;  /* 电磁阀开启时间 */
    uint16_t pump_Close_Time; /* 水泵关闭延时 */
} logic_Water_t;

/* 公共接口函数 */
uint8_t Water_Balance_Function(void);
uint8_t Water_BianPin_Function(void);
uint8_t ShuangPin_Water_Balance_Function(void);
uint8_t Double_Water_BianPin_Function(void);
uint8_t Double_WaterPump_LogicFunction(void);
uint8_t Special_Water_Supply_Function(void);
uint8_t WaterLevel_Unchange_Check(void);

/* 配置参数 */
#define WATER_SUPPLY_TIMEOUT_MAX    300     /* 补水超时最大时间(秒) */
#define WATER_PERCENT_MIN           18      /* 最小变频百分比 */
#define WATER_PERCENT_MAX           99      /* 最大变频百分比 */

#endif /* __WATER_CONTROL_H */ 