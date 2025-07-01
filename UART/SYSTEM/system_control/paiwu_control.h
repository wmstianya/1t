#ifndef __PAIWU_CONTROL_H
#define __PAIWU_CONTROL_H

#include "main.h"
#include "global_data.h"

/* 排污控制状态枚举 */
typedef enum {
    PAIWU_STATE_IDLE = 0,           /* 排污待机 */
    PAIWU_STATE_OPENING = 1,        /* 排污阀开启 */
    PAIWU_STATE_DRAINING = 2,       /* 排污进行中 */
    PAIWU_STATE_WATER_SUPPLY = 3,   /* 补水阶段 */
    PAIWU_STATE_COMPLETE = 4        /* 排污完成 */
} paiwu_state_t;

/* 连续排污配置 */
typedef struct {
    uint32_t delay_time;            /* 延时时间(分钟) */
    uint32_t open_seconds;          /* 开启时间(秒) */
    uint8_t enabled;                /* 使能标志 */
} lianxu_paiwu_config_t;

/* 排污警告配置 */
typedef struct {
    uint16_t max_time;              /* 最大未排污时间(分钟) */
    uint16_t warning_time;          /* 警告时间阈值(分钟) */
} paiwu_warning_config_t;

/* 公共接口函数 */
uint8_t Auto_Pai_Wu_Function(void);
uint8_t IDLE_Auto_Pai_Wu_Function(void);
uint8_t PaiWu_Warnning_Function(void);
uint8_t YunXingZhong_TimeAdjustable_PaiWu_Function(void);
uint8_t LianXu_Paiwu_Control_Function(void);

/* 排污控制常量 */
#define PAIWU_DEFAULT_PRESSURE      5       /* 默认排污压力阈值 */
#define PAIWU_DRAIN_TIME_MIN        15      /* 最小排污时间(秒) */
#define PAIWU_DRAIN_TIME_MAX        60      /* 最大排污时间(秒) */
#define PAIWU_SUPPLY_TIMEOUT        60      /* 补水超时时间(秒) */
#define PAIWU_WARNING_TIME          480     /* 排污警告时间(分钟) */

/* 排污结果代码 */
typedef enum {
    PAIWU_OK = 0,
    PAIWU_IN_PROGRESS,
    PAIWU_ERROR_TIMEOUT,
    PAIWU_ERROR_WATER_LEVEL,
    PAIWU_ERROR_PRESSURE
} paiwu_result_t;

#endif /* __PAIWU_CONTROL_H */ 