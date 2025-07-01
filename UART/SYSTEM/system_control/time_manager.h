#ifndef __TIME_MANAGER_H
#define __TIME_MANAGER_H

#include "main.h"
#include "global_data.h"

/* 系统工作时间结构体 */
typedef struct {
    uint8_t sec;                    /* 秒 */
    uint8_t min;                    /* 分钟 */
    uint32_t hour;                  /* 小时 */
    uint16_t days;                  /* 天数 */
    uint32_t all_minutes;           /* 总累计时间(分钟) */
    uint32_t un_paiwu_minutes;      /* 未排污时间(分钟) */
} sys_work_time_t;

/* 时间管理状态枚举 */
typedef enum {
    TIME_STATE_IDLE = 0,            /* 时间计时停止 */
    TIME_STATE_WORKING,             /* 工作时间计时 */
    TIME_STATE_PAUSED               /* 时间计时暂停 */
} time_state_t;

/* 定时任务类型枚举 */
typedef enum {
    TIMER_TYPE_SYSTEM_WORK = 0,     /* 系统工作时间 */
    TIMER_TYPE_ADMIN_LOCK,          /* 管理员锁定时间 */
    TIMER_TYPE_WIFI_LOCK,           /* WiFi锁定时间 */
    TIMER_TYPE_PAIWU_WARNING        /* 排污警告时间 */
} timer_type_t;

/* 管理员时间锁定配置 */
typedef struct {
    uint16_t year;                  /* 年份 */
    uint8_t month;                  /* 月份 */
    uint8_t day;                    /* 日期 */
    uint8_t enabled;                /* 使能标志 */
} admin_time_lock_t;

/* WiFi时间锁定配置 */
typedef struct {
    uint16_t year;                  /* 年份 */
    uint8_t month;                  /* 月份 */
    uint8_t day;                    /* 日期 */
    uint8_t enabled;                /* 使能标志 */
} wifi_time_lock_t;

/* 公共接口函数 */
uint8_t sys_work_time_function(void);
uint8_t Admin_Work_Time_Function(void);
uint8_t Wifi_Lock_Time_Function(void);

/* 时间管理常量 */
#define TIME_MANAGER_1_SECOND       1000    /* 1秒时间基准(ms) */
#define TIME_MANAGER_1_MINUTE       60      /* 1分钟 = 60秒 */
#define TIME_MANAGER_1_HOUR         3600    /* 1小时 = 3600秒 */
#define TIME_MANAGER_1_DAY          86400   /* 1天 = 86400秒 */

/* 最大时间限制 */
#define MAX_WORK_MINUTES            0xFFFFFFFF  /* 最大工作分钟数 */
#define MAX_WORK_HOURS              0xFFFF      /* 最大工作小时数 */
#define MAX_WORK_DAYS               0xFFFF      /* 最大工作天数 */

/* 时间管理结果枚举 */
typedef enum {
    TIME_OK = 0,
    TIME_ERROR_INVALID_PARAM,
    TIME_ERROR_OVERFLOW,
    TIME_ERROR_LOCKED
} time_result_t;

#endif /* __TIME_MANAGER_H */ 