#ifndef __ERROR_HANDLER_H
#define __ERROR_HANDLER_H

#include "main.h"
#include "global_data.h"

/* 错误代码枚举 */
typedef enum {
    NO_ERROR = 0,                           /* 无故障 */
    ERROR1_YAKONG_PROTECT,                  /* 1 机械压力保护 */
    ERROR2_YABIAN_PROTECT,                  /* 2 压力变送器超限 */
    ERROR3_LOW_GAS,                         /* 3 燃气压力低保护 */
    ERROR5_LOW_WATER,                       /* 5 极低水位保护 */
    ERROR6_SUPPLY_WATER_TOO_LONG,           /* 6 水泵超时保护 */
    ERROR7_FLAME_ZIJIAN,                    /* 7 火焰自检 */
    ERROR8_WATER_LOGIC,                     /* 8 水位逻辑错误 */
    ERROR9_AIR_PRESSURE_BAD,                /* 9 风压异常 */
    ERROR10_STEAM_VALUE_BAD,                /* 10 出水温度超出设定值 */
    ERROR11_DIANHUO_BAD,                    /* 11 点火失败 */
    ERROR12_FLAME_LOSE,                     /* 12 运行中火焰熄灭 */
    ERROR13_AIR_CONTROL_FAIL,               /* 13 风门控制失效 */
    ERROR14_BENTI_VALUE_BAD,                /* 14 本体温度异常 */
    ERROR15_REBAO_BAD,                      /* 15 燃烧器热保护 */
    ERROR16_SMOKE_VALUE_HIGH,               /* 16 烟气温度超限 */
    ERROR17_OUTWENKONG_TX_BAD,              /* 17 外置安全通讯超时 */
    ERROR18_SUPPLY_WATER_ERROR,             /* 18 补水器故障 */
    ERROR19_SUPPLY_WATER_UNTALK,            /* 19 补水器通讯丢失 */
    ERROR20_XB_HIGH_PRESSURE_YABIAN_BAD,    /* 20 相变高压差压变送器超压 */
    ERROR21_XB_HIGH_PRESSURE_YAKONG_BAD,    /* 21 相变高压机械压力超压 */
    ERROR22_XB_HIGH_PRESSURE_WATER_LOW      /* 22 相变高压水位低 */
} error_code_t;

/* 异常事件结构体 */
typedef struct {
    uint8_t flameout_event;         /* 运行中火焰熄灭异常 */
    uint8_t flameout_count;         /* 记录运行中火焰熄灭次数 */
    uint8_t overheat_event;         /* 炉膛超温异常 */
    uint8_t overheat_count;         /* 炉膛超温次数记录 */
    uint8_t airdoor_event;          /* 风门故障异常 */
    uint8_t burner_heat_protect_event;      /* 燃烧器热保护异常 */
    uint8_t burner_heat_protect_count;      /* 燃烧器热保护异常计数 */
    uint8_t target_complete_event;          /* 达到设定温度停炉事件 */
} ab_events_t;

/* 公共接口函数 */
void Self_Check_Function(void);
uint8_t Idel_Check_Fun(void);
void Abnormal_Check_Fun(void);
void Abnormal_Events_Response(void);
void Err_Response(void);
void IDLE_Err_Response(void);
void Lcd_Err_Refresh(void);
void Lcd_Err_Read(void);

/* 错误处理状态 */
typedef enum {
    ERROR_STATE_NONE = 0,
    ERROR_STATE_DETECTED,
    ERROR_STATE_PROCESSING,
    ERROR_STATE_RECOVERED
} error_state_t;

#endif /* __ERROR_HANDLER_H */ 