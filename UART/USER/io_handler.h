#ifndef __IO_HANDLER_H
#define __IO_HANDLER_H

#include "main.h"

/* 错误代码定义 */
#define ERROR1_YAKONG_PROTECT     1    /* 机械压力保护 */
#define ERROR8_WATER_LOGIC        8    /* 水位逻辑错误 */
#define ERROR15_REBAO_BAD        15    /* 燃烧器热保护 */

/* IO引脚状态结构体 */
typedef struct {
    uint8_t rawState;           /* 硬件原始状态 */
    uint8_t filteredState;      /* 去抖动后状态 */
    uint8_t prevFilteredState;  /* 前一次过滤状态 */
    uint8_t isStable;           /* 状态是否稳定 */
    uint32_t stableCounter;     /* 去抖动计数器 */
    uint32_t maxCounter;        /* 最大计数值 */
} ioFilteredPinT;

/* IO缓存结构体 */
typedef struct {
    ioFilteredPinT hotProtect;
    ioFilteredPinT hpressureSignal;
    ioFilteredPinT waterLogicError;
    uint8_t hardwareFaultFlag;
    uint8_t waterErrorFlag;
    uint8_t thermalErrorFlag;
    uint8_t pressureErrorFlag;
} ioCacheT;

/* IO性能统计结构体 */
typedef struct {
    uint32_t getIoInfCalls;
    uint32_t eventsProcessed;
    uint32_t debounceSkips;
} ioPerfT;

/* 公共接口函数 */
void ioSystemInit(void);
void Get_IO_Inf(void);
void getIoPerformanceMetrics(ioPerfT* perfData);

/* 错误码枚举 */
typedef enum {
    IO_OK = 0,
    IO_ERROR_TIMEOUT,
    IO_ERROR_HARDWARE,
    IO_ERROR_INVALID_STATE
} io_error_t;

#endif /* __IO_HANDLER_H */ 