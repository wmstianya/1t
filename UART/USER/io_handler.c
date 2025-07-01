/**
  ******************************************************************************
  * @file    io_handler.c
  * @author  System Control Team
  * @version V1.0
  * @date    2025-01-13
  * @brief   IO处理模块实现文件
  *          负责所有IO信号的读取、去抖动、状态管理
  ******************************************************************************
  * @attention
  * 本模块包含以下功能：
  * - IO信号读取和缓存
  * - 去抖动算法实现
  * - 事件驱动的IO处理
  * - 性能统计和监控
  ******************************************************************************
  */

#include "io_handler.h"
#include "bsp_led.h"

// 外部声明的全局变量
extern IO_DATA IO_Status;
extern SYS_FLAG sys_flag;
extern SYS_DATA sys_data;
extern TEMPERATURE_DATA Temperature_Data;
extern SYS_ADMIN Sys_Admin;

// 静态变量定义
static ioCacheT ioCache;
static ioPerfT ioPerformanceMetrics;

/**
  * @brief  IO系统初始化
  * @param  无
  * @retval 无
  */
void ioSystemInit(void)
{
    // 初始化IO缓存结构
    ioCache.hotProtect.rawState = 0;
    ioCache.hotProtect.filteredState = 0;
    ioCache.hotProtect.prevFilteredState = 0;
    ioCache.hotProtect.isStable = 0;
    ioCache.hotProtect.stableCounter = 0;
    ioCache.hotProtect.maxCounter = 50; // 50ms去抖动
    
    ioCache.hpressureSignal.rawState = 0;
    ioCache.hpressureSignal.filteredState = 0;
    ioCache.hpressureSignal.prevFilteredState = 0;
    ioCache.hpressureSignal.isStable = 0;
    ioCache.hpressureSignal.stableCounter = 0;
    ioCache.hpressureSignal.maxCounter = 30; // 30ms去抖动
    
    ioCache.waterLogicError.rawState = 0;
    ioCache.waterLogicError.filteredState = 0;
    ioCache.waterLogicError.prevFilteredState = 0;
    ioCache.waterLogicError.isStable = 0;
    ioCache.waterLogicError.stableCounter = 0;
    ioCache.waterLogicError.maxCounter = 100; // 100ms去抖动
    
    // 初始化错误标志
    ioCache.hardwareFaultFlag = 0;
    ioCache.waterErrorFlag = 0;
    ioCache.thermalErrorFlag = 0;
    ioCache.pressureErrorFlag = 0;
    
    // 初始化性能统计
    ioPerformanceMetrics.getIoInfCalls = 0;
    ioPerformanceMetrics.eventsProcessed = 0;
    ioPerformanceMetrics.debounceSkips = 0;
}

/**
  * @brief  去抖动算法实现
  * @param  pin: IO引脚过滤结构体指针
  * @param  newRawState: 新的原始状态
  * @param  debounceThreshold: 去抖动阈值
  * @retval 返回过滤后的稳定状态
  */
static uint8_t debounceIoPin(ioFilteredPinT* pin, uint8_t newRawState, uint32_t debounceThreshold)
{
    pin->rawState = newRawState;
    
    if (pin->rawState == pin->filteredState) {
        // 状态一致，重置计数器
        pin->stableCounter = 0;
        pin->isStable = 1;
    } else {
        // 状态不一致，增加计数器
        pin->stableCounter++;
        
        if (pin->stableCounter >= debounceThreshold) {
            // 达到去抖动阈值，更新过滤状态
            pin->prevFilteredState = pin->filteredState;
            pin->filteredState = pin->rawState;
            pin->stableCounter = 0;
            pin->isStable = 1;
            return 1; // 状态发生变化
        } else {
            pin->isStable = 0;
            ioPerformanceMetrics.debounceSkips++;
        }
    }
    
    return 0; // 状态未变化或未稳定
}

/**
  * @brief  处理水位逻辑错误
  * @param  无
  * @retval 无
  */
static void processWaterLogicError(void)
{
    uint8_t Error_Buffer = FALSE;
    
    // 检查水位逻辑错误条件
    if (IO_Status.Target.water_high == WATER_OK) {
        if (IO_Status.Target.water_mid == WATER_LOSE || IO_Status.Target.water_protect == WATER_LOSE) {
            Error_Buffer = OK;
        }
    }
    
    if (IO_Status.Target.water_mid == WATER_OK) {
        if (IO_Status.Target.water_protect == WATER_LOSE) {
            Error_Buffer = OK;
        }
    }
    
    if (Error_Buffer) {
        if (sys_flag.flame_state) {
            sys_flag.Force_Supple_Water_Flag = OK;
            sys_flag.Force_Flag = OK;
        } else {
            sys_flag.Force_Supple_Water_Flag = 0;
        }
        sys_flag.Error16_Flag = OK;
    } else {
        sys_flag.Force_Flag = FALSE;
        sys_flag.Error16_Flag = 0;
        sys_flag.Error16_Count = 0;
    }
    
    // 强制补水时间控制
    if (sys_flag.Force_Count >= 5) {
        sys_flag.Force_Supple_Water_Flag = 0;
        sys_flag.Force_Flag = FALSE;
        sys_flag.Force_Count = 0;
    }
    
    // 错误计数和处理
    uint8_t Error16_Time = 8;
    if (sys_data.Data_10H == 0) {
        Error16_Time = 5;
    }
    if (sys_flag.flame_state && sys_data.Data_10H == 2) {
        if (IO_Status.Target.water_protect) {
            Error16_Time = 8;
        } else {
            Error16_Time = 5;
        }
    } else {
        Error16_Time = 10;
    }
    
    if (sys_flag.Error16_Count >= Error16_Time) {
        if (sys_flag.Error_Code == 0) {
            sys_flag.Error_Code = ERROR8_WATER_LOGIC;
        }
        sys_flag.Error16_Flag = FALSE;
        sys_flag.Error16_Count = 0;
    }
}

/**
  * @brief  处理热保护错误
  * @param  无
  * @retval 无
  */
static void processThermalProtectionError(void)
{
    if (IO_Status.Target.hot_protect == THERMAL_BAD) {
        if (sys_flag.Error15_Flag == 0) {
            sys_flag.Error15_Count = 0;
        }
        
        sys_flag.Error15_Flag = OK;
        
        if (sys_flag.Error15_Count > 1) {
            if (sys_flag.Error_Code == 0) {
                sys_flag.Error_Code = ERROR15_REBAO_BAD;
            }
        }
    } else {
        sys_flag.Error15_Flag = 0;
        sys_flag.Error15_Count = 0;
    }
}

/**
  * @brief  处理压力错误
  * @param  无
  * @retval 无
  */
static void processPressureError(void)
{
    // 机械式压力检测信号
    if (IO_Status.Target.hpressure_signal == PRESSURE_ERROR) {
        if (sys_flag.Error1_Flag == 0) {
            sys_flag.Error1_Count = 0;
        }
        
        sys_flag.Error1_Flag = OK;
        
        // 若蒸汽压力超出安全范围，故障，报警
        if (sys_flag.Error1_Count > 1) {
            if (sys_flag.Error_Code == 0) {
                sys_flag.Error_Code = ERROR1_YAKONG_PROTECT; // 蒸汽压力超出安全范围报警
            }
        }
    } else {
        sys_flag.Error1_Flag = 0;
        sys_flag.Error1_Count = 0;
    }
}

/**
  * @brief  处理IO事件
  * @param  无
  * @retval 无
  */
static void processIoEvents(void)
{
    // 处理水位逻辑错误
    processWaterLogicError();
    
    // 处理热保护错误
    processThermalProtectionError();
    
    // 处理压力错误
    processPressureError();
    
    // 更新性能统计
    ioPerformanceMetrics.eventsProcessed++;
}

/**
  * @brief  主要的IO信息获取和处理函数
  * @param  无
  * @retval 无
  * @note   从system_control.c迁移的核心IO处理函数
  */
void Get_IO_Inf(void)
{
    // 更新调用统计
    ioPerformanceMetrics.getIoInfCalls++;
    
    // 处理IO事件
    processIoEvents();
}

/**
  * @brief  获取IO性能统计数据
  * @param  perfData: 性能数据结构体指针
  * @retval 无
  */
void getIoPerformanceMetrics(ioPerfT* perfData)
{
    if (perfData != NULL) {
        perfData->getIoInfCalls = ioPerformanceMetrics.getIoInfCalls;
        perfData->eventsProcessed = ioPerformanceMetrics.eventsProcessed;
        perfData->debounceSkips = ioPerformanceMetrics.debounceSkips;
    }
}

/*********************************************END OF FILE**********************/ 