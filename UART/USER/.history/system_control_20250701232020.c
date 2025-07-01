uint8 cmd_string111[7] = {0x5A,0xA5,0x04,0x80,0x03,0x00,0x4B}; //换页指令，切换到第76页

// Get_IO_Inf() 函数已迁移到 io_handler.c 模块

/**
  * @brief  处理点火前的相关准备工作
  * @param  无
  * @retval 0: 点火条件未满足，1: 点火条件已满足
  */ 