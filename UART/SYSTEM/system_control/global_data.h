#ifndef __GLOBAL_DATA_H
#define __GLOBAL_DATA_H

#include <stdint.h>

/* 基本数据类型重定义 */
typedef unsigned char   uint8;
typedef unsigned short  uint16;
typedef unsigned int    uint32;

/* 基本常量定义 */
#define OK              1
#define FALSE           0
#define SUCCESS         1
#define FAIL            0

/* 系统状态常量 */
#define SYS_IDLE        0       /* 系统待机 */
#define SYS_ALARM       1       /* 系统报警 */
#define SYS_WORK        2       /* 系统运行 */
#define SYS_MANUAL      3       /* 手动模式 */

/* IO状态定义 */
#define FLAME_OK        0x01    /* 有火焰 */
#define FLAME_OUT       0x00    /* 无火焰 */
#define WATER_OK        0x01    /* 有水位信号 */
#define WATER_LOSE      0x00    /* 无水位信号 */
#define GAS_ON          0x00    /* 燃气压力正常 */
#define GAS_OUT         0x01    /* 没有燃气 */
#define THERMAL_OK      0x01    /* 热保护正常 */
#define THERMAL_BAD     0x00    /* 热保护故障 */
#define PRESSURE_OK     0x01    /* 机械式压力信号正常 */
#define PRESSURE_ERROR  0x00    /* 机械式压力超压故障 */

/* 系统信息结构体 */
typedef struct {
    uint8_t Data_10H;           /* 系统状态 */
    uint8_t Data_l1H;           /* IO输入状态数据存储 */
    uint8_t Data_12H;           /* 当前异常状态记录 */
    uint8_t Data_l3H;           /* 继电器输出状态 */
    uint8_t Data_14H;           /* 故障标志位 */
    uint8_t Data_l5H;           /* 扩展故障标志位 */
    uint8_t Data_16H;           /* 回水温度高位 */
    uint8_t Data_l7H;           /* 回水温度低位 */
    uint8_t Data_18H;           /* 出水温度高位 */
    uint8_t Data_19H;           /* 出水温度低位 */
    uint8_t Data_1AH;           /* 烟气温度高位 */
    uint8_t Data_1BH;           /* 烟气温度低位 */
    uint8_t Data_1CH;           /* 压力值高位 */
    uint8_t Data_1DH;           /* 压力值低位 */
    uint8_t Data_1EH;           /* 同步风机百分比设定值 */
    uint8_t Data_1FH;           /* 风机转速百分比 */
    // 更多数据字段...
} sys_inf_t;

/* IO数据联合体 */
typedef union {
    struct {
        uint8_t water_protect;      /* 极低水位保护 */
        uint8_t water_mid;          /* 中水位信号 */
        uint8_t water_high;         /* 高水位信号 */
        uint8_t water_shigh;        /* 超高水位信号 */
        uint8_t flame_signal;       /* 火焰信号 */
        uint8_t xb_hpress_ykong;    /* 内部高压遥控 */
        uint8_t xb_water_low;       /* 相变水位低 */
        uint8_t xb_water_high;      /* 相变水位高 */
        uint8_t gas_low_pressure;   /* 燃气压力低状态 */
        uint8_t air_door;           /* 风压开关 */
        uint8_t hot_protect;        /* 热保护开关 */
        uint8_t hpressure_signal;   /* 机械式压力开关信号 */
    } Target;
    struct {
        uint8_t SER1_Data[8];
        uint8_t SER2_Data[8];
    } Data;
} io_data_t;

/* 系统标志位结构体 */
typedef struct {
    volatile uint8_t Error1_Count;         /* 错误1计数 */
    volatile uint8_t Error1_Flag;          /* 错误1标志 */
    volatile uint8_t Error15_Count;        /* 错误15计数 */
    volatile uint8_t Error15_Flag;         /* 错误15标志 */
    volatile uint8_t Error16_Count;        /* 错误16计数 */
    volatile uint8_t Error16_Flag;         /* 错误16标志 */
    volatile uint8_t Force_Count;          /* 强制计数 */
    volatile uint8_t Force_Flag;           /* 强制标志 */
    
    uint8_t flame_state;                   /* 火焰状态 */
    uint8_t Force_Supple_Water_Flag;       /* 强制补水标志 */
    uint8_t Lock_Error;                    /* 锁定错误标志 */
    uint8_t Error_Code;                    /* 错误代码 */
    uint8_t Paiwu_Flag;                    /* 排污标志 */
    uint8_t get_60_percent_flag;           /* 达到60%标志 */
    uint8_t Ignition_Count;                /* 点火次数计数 */
    uint8_t Water_Percent;                 /* 水泵变频百分比 */
    
    uint16_t Fan_Rpm;                      /* 风机转速 */
    volatile uint16_t Fan_count;           /* 风机脉冲计数 */
    
    volatile uint8_t Work_1sec_Flag;       /* 1秒工作标志 */
    volatile uint8_t Power_1_Sec;          /* 功率调节1秒标志 */
    volatile uint8_t Power_5_Sec;          /* 功率调节5秒标志 */
    volatile uint8_t Pressure_1sFlag;      /* 压力1秒标志 */
    
    // 更多标志位...
} sys_flags_t;

/* 全局变量声明 */
extern uint32_t sys_control_time;         /* 系统控制时间 */
extern uint8_t sys_time_up;               /* 定时结束标志 */
extern uint8_t sys_time_start;            /* 定时器启动标志 */
extern uint8_t target_percent;            /* 目标设定功率百分比 */
extern uint8_t now_percent;               /* 当前设定的实时功率 */

extern sys_inf_t sys_data;               /* 系统数据 */
extern io_data_t IO_Status;              /* IO状态 */
extern sys_flags_t sys_flag;             /* 系统标志 */

/* 跳转类型枚举 */
typedef enum {
    First, Second, Third, Fourth, Five, Six, Seven, Eight,
    Nine, Ten, ELeven, Twleve, Thirteen, Fourteen, Fifteen, Sixteen
} JUMP_TYPE;

extern JUMP_TYPE Jump_Step;

/* 常用宏定义 */
#define FLAME_SIGNAL_FILTER_TIME    3       /* 火焰信号滤波时间 */
#define WATER_LEVEL_CHECK_TIME      5       /* 水位检查时间 */
#define PRESSURE_CHECK_TIME         2       /* 压力检查时间 */

#endif /* __GLOBAL_DATA_H */ 