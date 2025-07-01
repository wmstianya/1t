#ifndef __IGNITION_CONTROL_H
#define __IGNITION_CONTROL_H

#include "main.h"
#include "global_data.h"

/* 点火状态枚举 */
typedef enum {
    IGNITION_IDLE = 0,
    IGNITION_PREPARE = 1,
    IGNITION_FAN_SWITCH = 2,
    IGNITION_VALVE_OPEN = 3,
    IGNITION_VALVE_DELAY = 4,
    IGNITION_GAS_OPEN = 5,
    IGNITION_VALVE_CLOSE = 6,
    IGNITION_FLAME_CHECK = 7,
    IGNITION_COMPLETE = 20
} ignition_state_t;

/* 点火结果枚举 */
typedef enum {
    IGNITION_SUCCESS = 1,
    IGNITION_IN_PROGRESS = 0,
    IGNITION_ERROR_NO_FLAME = 2,
    IGNITION_ERROR_TIMEOUT = 3,
    IGNITION_ERROR_SAFETY = 4
} ignition_result_t;

/* 点火配置参数 */
typedef struct {
    uint32_t valve_open_time;    /* 点火阀开启时间 (ms) */
    uint32_t gas_open_time;      /* 燃气阀开启时间 (ms) */
    uint32_t flame_check_delay;  /* 火焰检测延时 (ms) */
    uint32_t warm_fire_time;     /* 小火时间 (ms) */
} ignition_config_t;

/* 公共接口函数 */
uint8_t Before_Ignition_Prepare(void);
uint8_t Sys_Ignition_Fun(void);
void Ignition_Check_Fun(void);

/* 最大点火次数 */
#define MAX_IGNITION_TIMES 3

#endif /* __IGNITION_CONTROL_H */ 