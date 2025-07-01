#ifndef __CONFIG_MANAGER_H
#define __CONFIG_MANAGER_H

#include "main.h"
#include "global_data.h"

/* 配置存储结构体 */
typedef struct {
    uint32_t zhuan_huan_temperture_value;   /* 转换温度值 */
    uint32_t Auto_stop_pressure;            /* 自动停炉压力 */
    uint32_t Auto_start_pressure;           /* 自动起炉压力 */
    uint32_t Sys_Lock_Set;                  /* 远程一键停机设置 */
    uint32_t ignition_time;                 /* 统计点火时间 */
    uint32_t wifi_record;                   /* WiFi连接记录 */
    uint32_t WIFI_MAC;                      /* WiFi MAC地址 */
} sys_config_t;

/* 管理员配置结构体 */
typedef struct {
    uint32_t First_Blow_Time;               /* 前扫时间 */
    uint32_t Last_Blow_Time;                /* 后扫时间 */
    uint32_t Wen_Huo_Time;                  /* 温火时间 */
    uint32_t Dian_Huo_Power;                /* 点火功率 */
    uint32_t Max_Work_Power;                /* 最大工作功率 */
    uint32_t Fan_Speed_Check;               /* 风机转速检测使能 */
    uint32_t Fan_Speed_Value;               /* 风机转速值 */
    uint32_t Fan_Pulse_Rpm;                 /* 风机脉冲转速关系 */
    uint32_t Fan_Fire_Value;                /* 风机着火转速 */
    uint32_t Danger_Smoke_Value;            /* 危险烟气温度 */
    uint32_t Supply_Max_Time;               /* 补水最大时间 */
    uint32_t DeviceMaxPressureSet;          /* 设备最大压力设定 */
    uint32_t ModBus_Address;                /* ModBus通讯地址 */
    uint32_t Device_Style;                  /* 设备类型选择 */
    uint32_t Water_BianPin_Enabled;         /* 变频补水使能 */
    uint32_t Water_Max_Percent;             /* 补水最大百分比 */
    uint32_t YuRe_Enabled;                  /* 预热使能 */
    uint32_t Inside_WenDu_ProtectValue;     /* 内部温度保护值 */
    uint32_t LianXu_PaiWu_Enabled;          /* 连续排污使能 */
    uint32_t LianXu_PaiWu_DelayTime;        /* 连续排污延时 */
    uint32_t LianXu_PaiWu_OpenSecs;         /* 连续排污开启秒数 */
    uint32_t Admin_Work_Day;                /* 管理员工作日期 */
    uint32_t Admin_Save_Year;               /* 管理员保存年份 */
    uint32_t Admin_Save_Month;              /* 管理员保存月份 */
    uint32_t Admin_Save_Day;                /* 管理员保存日期 */
} sys_admin_t;

/* 公共接口函数 */
void sys_control_config_function(void);
void Check_Config_Data_Function(void);
void clear_struct_memory(void);

/* Flash存储接口函数 - 需要实现 */
uint8_t Write_Internal_Flash(void);
uint8_t Write_Admin_Flash(void);
uint8_t Write_Second_Flash(void);

/* 配置验证状态 */
typedef enum {
    CONFIG_OK = 0,
    CONFIG_ERROR_INVALID_VALUE,
    CONFIG_ERROR_OUT_OF_RANGE,
    CONFIG_ERROR_FLASH_FAIL
} config_result_t;

/* Flash地址定义 - 需要根据实际硬件配置 */
#define FLASH_BKP_DATA              0x12345678
#define CHECK_FLASH_ADDRESS         0x08000000
#define INTERNAL_FLASH_START        0x08008000
#define ADMIN_FLASH_START           0x08010000
#define SECOND_FLASH_START          0x08018000

#endif /* __CONFIG_MANAGER_H */ 