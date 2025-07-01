#ifndef __UTILS_H
#define __UTILS_H

#include "main.h"
#include "global_data.h"

/* 工具函数返回值枚举 */
typedef enum {
    UTIL_OK = 0,
    UTIL_ERROR_INVALID_PARAM,
    UTIL_ERROR_TIMEOUT,
    UTIL_ERROR_HARDWARE
} util_result_t;

/* 字节位操作工具函数 */
uint8_t byte_to_bit(void);

/* LCD数据处理函数 */
void copy_to_lcd(void);
void Load_LCD_Data(void);

/* 系统检查函数 */
void One_Sec_Check(void);

/* 风机相关函数 */
void Fan_Speed_Check_Function(void);

/* 硬件保护函数 */
void HardWare_Protect_Relays_Function(void);

/* 系统特殊功能 */
uint8_t XiangBian_Steam_AddFunction(void);
uint8_t GetOut_Mannual_Function(void);
void JTAG_Diable(void);

/* 位操作宏定义 */
#define SET_BIT(reg, bit)       ((reg) |= (1U << (bit)))
#define CLEAR_BIT(reg, bit)     ((reg) &= ~(1U << (bit)))
#define TOGGLE_BIT(reg, bit)    ((reg) ^= (1U << (bit)))
#define GET_BIT(reg, bit)       (((reg) >> (bit)) & 1U)

/* 位掩码操作宏 */
#define SET_BIT_0   0x01
#define SET_BIT_1   0x02
#define SET_BIT_2   0x04
#define SET_BIT_3   0x08
#define SET_BIT_4   0x10
#define SET_BIT_5   0x20
#define SET_BIT_6   0x40
#define SET_BIT_7   0x80

#define RST_BIT_0   0xFE
#define RST_BIT_1   0xFD
#define RST_BIT_2   0xFB
#define RST_BIT_3   0xF7
#define RST_BIT_4   0xEF
#define RST_BIT_5   0xDF
#define RST_BIT_6   0xBF
#define RST_BIT_7   0x7F

/* 通用常量定义 */
#define OK          1
#define FALSE       0
#define SUCCESS     1
#define FAIL        0

/* 数值范围检查宏 */
#define IS_IN_RANGE(val, min, max)     ((val) >= (min) && (val) <= (max))
#define CLAMP(val, min, max)           ((val) < (min) ? (min) : ((val) > (max) ? (max) : (val)))

/* 数组长度计算宏 */
#define ARRAY_SIZE(arr)                (sizeof(arr) / sizeof((arr)[0]))

#endif /* __UTILS_H */ 