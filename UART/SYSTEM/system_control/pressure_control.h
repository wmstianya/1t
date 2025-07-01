#ifndef __PRESSURE_CONTROL_H
#define __PRESSURE_CONTROL_H

#include "main.h"
#include "global_data.h"

/* 压力控制模式枚举 */
typedef enum {
    PRESSURE_MODE_NORMAL = 0,       /* 普通锅炉压力控制 */
    PRESSURE_MODE_XB = 1            /* 相变机组压力控制 */
} pressure_mode_t;

/* 压力控制状态枚举 */
typedef enum {
    PRESSURE_STATE_STABLE = 0,      /* 压力稳定 */
    PRESSURE_STATE_RISING,          /* 压力上升 */
    PRESSURE_STATE_FALLING,         /* 压力下降 */
    PRESSURE_STATE_OVERPRESSURE     /* 超压状态 */
} pressure_state_t;

/* 压力控制参数结构体 */
typedef struct {
    uint16_t target_pressure;       /* 目标压力值(0.01MPa) */
    uint16_t stop_pressure;         /* 停炉压力值(0.01MPa) */
    uint16_t start_pressure;        /* 启炉压力值(0.01MPa) */
    uint16_t max_pressure;          /* 最大允许压力(0.01MPa) */
    uint8_t air_min;                /* 最小风量百分比 */
    uint8_t air_max;                /* 最大风量百分比 */
    uint16_t yacha_value;           /* 差压值(相变机组) */
} pressure_config_t;

/* 压力变化速度结构体 */
typedef struct {
    uint16_t old_pressure;          /* 上次压力值 */
    uint16_t change_time;           /* 压力变化时间 */
    uint8_t is_fast_change;         /* 是否快速变化 */
} pressure_speed_t;

/* 公共接口函数 */
uint8_t System_Pressure_Balance_Function(void);
uint8_t XB_System_Pressure_Balance_Function(void);
uint8_t Speed_Pressure_Function(void);

/* 压力控制常量 */
#define PRESSURE_MIN_POWER              20      /* 最小功率百分比 */
#define PRESSURE_MAX_POWER              100     /* 最大功率百分比 */
#define PRESSURE_CHANGE_THRESHOLD       5       /* 压力变化阈值 */
#define PRESSURE_ADJUST_FAST_TIME       1       /* 快速调整时间间隔(秒) */
#define PRESSURE_ADJUST_SLOW_TIME       5       /* 慢速调整时间间隔(秒) */

/* 相变机组专用常量 */
#define XB_PRESSURE_DIFF_VALUE          65      /* 相变压力差值 */
#define XB_MAX_PRESSURE                 150     /* 相变最大压力(1.5MPa) */

/* 压力控制结果枚举 */
typedef enum {
    PRESSURE_CTRL_OK = 0,
    PRESSURE_CTRL_OVERPRESSURE,
    PRESSURE_CTRL_ERROR_SENSOR,
    PRESSURE_CTRL_ERROR_ACTUATOR
} pressure_ctrl_result_t;

#endif /* __PRESSURE_CONTROL_H */ 