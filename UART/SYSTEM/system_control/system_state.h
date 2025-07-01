#ifndef __SYSTEM_STATE_H
#define __SYSTEM_STATE_H

#include "main.h"
#include "global_data.h"

/* 系统状态枚举 */
typedef enum {
    SYS_IDLE = 0,       /* 待机 */
    SYS_ALARM,          /* 报警 */
    SYS_WORK,           /* 运行 */
    SYS_MANUAL,         /* 手动 */
    SYS_CLEAN_MODE      /* 清洗模式 */
} sys_state_t;

/* 系统启动阶段 */
typedef enum {
    SYS_LAUNCH_SELF_CHECK = 0,      /* 系统自检 */
    SYS_LAUNCH_IGNITION = 1,        /* 系统点火 */
    SYS_LAUNCH_RUNNING = 2          /* 系统运行 */
} sys_launch_stage_t;

/* 待机状态索引 */
typedef enum {
    IDLE_STATE_NORMAL = 0,          /* 普通待机状态 */
    IDLE_STATE_AFTER_BLOW = 1,      /* 等待后扫时间 */
    IDLE_STATE_COOLING = 2          /* 等待温度下降 */
} idle_state_index_t;

/* 公共接口函数 */
void System_All_Control(void);
void Sys_Launch_Function(void);
void System_Idel_Function(void);
uint8_t sys_start_cmd(void);
void sys_close_cmd(void);
void Last_Blow_Start_Fun(void);
void Last_Blow_End_Fun(void);
uint8_t Power_ON_Begin_Check_Function(void);
uint8_t Auto_StartOrClose_Process_Function(void);

/* 系统状态管理相关常量 */
#define SYS_LAUNCH_MAX_STAGES       3
#define AFTER_BLOW_DEFAULT_TIME     30000   /* 默认后扫时间30秒 */
#define COOLING_DEFAULT_TIME        10000   /* 默认冷却时间10秒 */

#endif /* __SYSTEM_STATE_H */ 