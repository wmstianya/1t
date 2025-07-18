
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/
/*2020年10月13日14:14:21    版本V1.1.3,,修改超压停炉或待机停炉，火焰残留时间随后吹扫时间而定*/
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/

/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/
/*2020年10月13日14:14:21    版本V1.1.4,,增加外置火焰模块的配置,对水位图片进行了细分，改正火焰残留时间的问题*/
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/

/*2020年11月21日13:46:03 v2.1.1   对LCD通信进行了CRC校验，增加三级用户管理*/

/*2020年11月22日14:23:03 版本升级到V2.1.2,对运行时极低水位报警，迟钝6秒处理*/


/*2021年3月16日12:45:01    V3.1.2电阻屏程序调试，投入使用*/

/*2021年5月3日12:45:01    V3.1.3   */

/*2021年5月14日15:16:46 V3.1.4，修改报警程序,报警继电器的BUG*/

/*2021年6月7日13:41:49 V3.1.5修改前后吹扫时间，最高上限为300s*/

/*2021年6月21日14:10:11    V3.2.1 修改对屏通信的频率，触碰灵敏度提高*/

/*2021年7月31日15:50:02 版本升级到V3.2.2,将登录密码形式进行了更改，正常管理员登录密码为778899，可运行时间管理密码为147258*/

/*2021年8月31日10:39:35 版本审计到V3.3.1,     修正超高水位在运行过程中，水位不准的显示问题*/

/*2021年10月4日09:41:34 版本升级到3.5.1，增加双火焰检测*/

/*2021年10月10日15:05:53 版本升级到V3.6.1, 增加高温蒸汽余热回收使用的电磁阀*/

/*2021年10月21日14:29:12 版本升级到V3.6.2, 修改补水过程中，以高水位停，中水位补的旧逻辑， 改为 中或低丢失后，都可以继续补水8秒， 逻辑错误9秒的的程序
										修正V3.3.1,超高水位显示的遗留问题*/

/*2021年10月22日12:49:15 版本升级到V3.6.3, 修改火焰显示延迟的问题，针对主副火焰两个输入口不进行滤波*/

/*2021年10月23日17:22:36 针对水位逻辑故障报警，在运行过程中，出现该错误会立即强制补水，在规定时间内仍出现，则报故障*/

/*2021年12月28日16:14:56 版本升级到V3.6.5,     修正多机联控过程中，大小需求*/

/*2022年5月6日10:55:55 版本审计到V3.6.6*/

/*2022年5月12日09:39:22    屏的波特率升级到38400， 增加对温控盒的通信保护措施*/

/*2022年6月7日14:48:05 升级到V402,根据停炉压力的温度进行蒸汽温度保护*/

/*2022年7月12日09:59:34 升级到V403     , 1,修改假水位出现后，强制补水失效的问题，  
									2  修改故障信息记录清除的问题，
									3  外置通信保护时，高压点火只持续3秒给明火
									4， 默认外置温度的初始值为245度和173度，针对额定8公斤压力
									5,  手动模式不再报水位逻辑故障*/
/*2022-10-8 14:08:032 针对运行中火焰熄灭一次报警的情况，改成累积三次报警，当任何一次报警后，正常运行半小时，则对记录次数清零*/

/*2022年10月9日10:20:27    针对输入检测，由上升沿检测改成下降沿检测*/

/*2022年11月28日16:27:53 版本升级到409，针对压力变送器的闪跳问题进行滤波，防止误报*/

/*2022年12月29日13:58:42 版本升级到410，针对压力变送器常规值做了滤波，防止误超压停炉*/

/*2023年1月11日16:05:44 版本升级到411,针对热保和压控做了5秒滤波*/

/*2023年2月10日11:21:25 版本升级到V412，针对本地通信，增加相应的数据点位*/

/*2023年7月19日16:11:03 版本升级到V413 修改蒸汽压力调节界面，显示数据不准的问题*/

/*2023年8月8日14:34:45 版本升级到V4.1.5 在串口4上增加老版本联控接口*/

/*2023年8月28日15:31:04 版本升级到V4.1.6,解决运行中火焰熄灭三次的问题， 运行中出现水位极低后转后吹扫，再出现后就报警*/

/*2023年8月31日09:38:40 版本升级到V4.1.8 针对SPI通信速率进行调整，由原来的10us 改成100us，解决温度突跳的问题*/

/*2023年9月21日09:53:35 版本升级到V4.1.9 ,修正物联网远传，Access_Mode_flag,检测的问题，修正拨码开关配置为上拉输入*/

/*2023年10月13日11:30:59 版本升级到V4.2.0 修正上个版本 Dian_Huo_Air_Level(); 中按照最大点火转速点火，现改为实际点火转速*/

/*2023年10月17日12:22:33 版本升级到V4.2.1 修正点火时，燃气阀组开之前，高压现包关掉的事*/

/*2023年11月14日12:01:29 版本升级到V4.2.2 自动排污功能恢复到以前的状态
										  修正同一故障，在短时间内频繁报警的问题*/

/*2023年11月27日11:55:40 版本升级到V4.2.3 启动压力改为小于停炉压力，在后吹扫结束后检查当前压力，满足直接跳过前吹扫
											风速稳定的时间由6秒，变8秒*/

/*2023年12月12日10:41:25    版本升级到V4.3.0 ,更新物联网程序测试
											增加熄火反应延迟，持续2秒丢失火焰认为火焰熄灭*/

/*2024年3月18日19:04:02     升级变频补水事项*/

/*2024年5月30日16:32:03 增加定时开关机功能，待测试, 2024年6月6日10:17:48  已经完成测试*/

/*2024年7月10日15:07:29 增加针对频繁启停，调整功率运行时间的问题*/

/*2024年7月30日11:05:25 V4.3.5 本体你默认保护值调整到270度*/

/*2024年8月11日16:57:04 V4.3.6    支持本地联控功能，修改了串口4*/

/********************************************************************/

//相变增加  ：输入口6 == 内胆机械压控保护， 压变2作为内胆压力变送器使用

/*2024年10月20日10:41:18 10月19号南通两台相变调试结束，一键启动有时会出现，从机短暂失联。急停重新上电，有时会出现，火焰自检异常。这个需要在机器上频繁测试下*/
/*2024年10月20日10:42:52 版本变为V4.3.8, 需要在机器上进行测试
				*/

/*2024年11月12日10:55:47 版本变为V4.3.9,   @@检查出从机变频补水功能开启时，进水阀通信失联不报警，只认主机报警，问题已经解决*/

/*2024年11月19日11:43:59 版本变为V4.4.0,针对运行状态下关闭从机，从机若在运行状态中，不会自动关闭的问题
						高压侧压力保护值，设定为 15公斤*/

/**************************************************************************************/
/*2024年11月21日14:16:51 版本变为450，针对相变机组，燃烧机追踪高压侧的压力，压差系数按照0.45Mpa执行，启动压力还是根据用户设定压力来启动*/

/*2024年11月23日17:02:27 版本变为451，修正两台设备负荷调节控制启停的问题*/

/*2024年11月27日14:11:50 版本变为452，将连续排污阀用于真空放气阀，当内部压力大于0.01Mpa就会关闭连续排污阀
										将相变极低水位保护，做了5秒的延迟判定，续连续持续5秒极低水位后，才会报警
										前吹扫过程中，遇到超高水位需要停止，加了判定*/

/*2024年12月10日09:18:18 版本升级为V453          针对相变高压极低水位异常和运行中火焰熄灭异常，后吹直接改前吹，点火，以前是得等到低于启动压力点火*/

/*2024年12月18日10:03:26    版本升级到454，修改物联网远程锁机，更改MCGS界面的用户管理*/

/*2024年12月23日10:32:13 版本升级到455，运行中高压侧极低水位出现，本体温度大于230度，连续4次后，则报警*/

/*2024年12月30日10:46:39    版本升级到456，升级后吹扫结束后，再检查高压侧极低水位，自动排污第一阶段时间，由10秒改为25秒*/

/*2025年1月8日11:21:12 版本升级到457,将所有输入口数据上传到屏*/

/*2025年1月13日13:56:16 版本升级到458.增加待机和超压停炉状态时，高压侧低水位的检测延迟，延迟5秒*/

/*2025年2月6日12:24:44 版本升级到459，增加超压状态时，高压侧低水位报警时间由5秒变为10秒， 接触待机状态高压内胆低水位检测*/

/*2025年2月17日10:34:20 版本升级到460，继续优化相变机，高压侧低水位检测报警*/

/*2025年4月9日17:29:06 版本升级到V461,解决前吹扫判定水位，造成前吹时间不够的因素*/

/*2025年5月16日17:43:12 版本升级到V470           升级解决主机排烟温度报警后，调节排烟温度报警值，多次复位不掉后，主机二次启动的问题，*/


#include "main.h"


const uint16 Soft_Version = 470;/*2025年5月16日17:44:25*/


int main(void)
 { 
//*****外部晶振12Mhz配置****************//	 
	HSE_SetSysClk(RCC_PLLMul_9);//本文件外部晶振为8Mhz RCC_PLLMul_6  改变成9 ，那什么f103.h,  文件中晶振Hz也需要修改
	SysTick_Init();
//设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	NVIC_Configuration(); 	 
//*********蜂鸣器端口，火焰检测端口配置****//
  	LED_GPIO_Config();
	IO_Interrupt_Config();

//*********继电器端口配置******************//
	RELAYS_GPIO_Config();

// ***************ADC 初始化****************//
	ADCx_Init();  
	ADS1220Init();
    ADS1220Config();
//*****************SPI初始化**************************//
	SPI_Config_Init();
	JTAG_Diable();
//***************串口1初始化为9600 for    RS485A1B1****//
	uart_init(9600);//优先级2:0
//***************串口2     A2 B2初始化为19200       for 10.1寸外置的屏*****//
	uart2_init(9600);//优先级2:1
//***************串口3初始化为9600       for 设备内部通信准备******//
	uart3_init(9600); //优先级2:2	 
//***************串口4初始化为 联控或者本地通信 ****//
	uart4_init(9600); //优先级2:2	 

	
//***配置1ms定时中断,包括全串口接收周期时间配置***//
	TIM4_Int_Init(1000,71);//1ms定时中断
//***配置0.1ms定时中断,用于风机速度检测***//
	//TIM5_Int_Init(99,71); //默认关闭，需主动开启和关闭
//***************配置蜂鸣器 输出2.7Khz************//
	TIM2_Int_Init(1000,71);  //优先级0:3
//***************配置PWM定时器，2khz可调************//
	TIM3_PWM_Init(); 
//***************开机上电蜂鸣器滴一下************//
	BEEP_TIME(300); 
			
//**************对程序用到的结构体进行初始化处理*//
	clear_struct_memory(); 
	
//**************CPU ID 加密****************************// 

	Write_CPU_ID_Encrypt();
	
	
	sys_flag.Address_4 = PortPin_Scan(SLAVE_ADDRESS_PORT,SLAVE_PIN_1);
	sys_flag.Address_3 = PortPin_Scan(SLAVE_ADDRESS_PORT,SLAVE_PIN_2);
	sys_flag.Address_2 = PortPin_Scan(GPIOA,SLAVE_PIN_3);
	sys_flag.Address_1 = PortPin_Scan(GPIOA,SLAVE_PIN_4);//该引脚未使用

	
	sys_flag.Address_Number = sys_flag.Address_1 * 1 + sys_flag.Address_2 * 2  + sys_flag.Address_3 * 4 + sys_flag.Address_4 * 8;
	
//u1_printf("\n*地址参数= %d\n",sys_flag.Address_Number);

//**************系统参数默认配置，前吹扫，停炉温度等***//	
	sys_control_config_function(); //
	
	SysTick_Delay_ms(1000);
	SysTick_Delay_ms(1000); //等待系统稳定，防止IO口进入误检测
	
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++调试用，待删除
//写内存，设标志，提示成功激活，再次进入，不再提示激活信息	
	read_serial_data();	//15ms
	read_serial_data();	//15ms
	read_serial_data();	//15ms
	read_serial_data();	//15ms
	read_serial_data();	//15ms
	read_serial_data();	//15ms
	read_serial_data();	//15ms

	Flash_Read_Protect();
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	Close_All_Realys_Function();

	//
// 单步调试时，需要关闭看门狗，用JLINK时，可以不关闭 	 
	 IWDG_Config(IWDG_Prescaler_64 ,900);//若超时没有喂狗则复位


//**************针对LCD自带RTC和主板RTC时间同步********//	
	
	while(1)
	{	
		
	
//***********副系统SPI 炉内温度读取***********************//
		SpiReadData();
//***********喂狗程序***********//
		IWDG_Feed();
//***********炉体温度和烟气温度，两个压力值的处理***********//
		ADC_Process();
//***********读取并转串口的数据**********根据设备类型进行切换*************//
		read_serial_data();	//15ms
//1s时间到，****************************************************//
		One_Sec_Check();
//***********串口1 A1B1远程控制 传感器485通信解析,都要根据设备类型来选择***********//		
		ModBus_Communication();
//**********继电器需要过零控制，检测不到中断，需要强制处理******************************************//
		Relays_NoInterrupt_ON_OFF();
//***********机器地址和设备类型的判定***********************//
		switch (sys_flag.Address_Number)
			{
				case 0: //主控设备
						//根据设备类型进行切换
						
						//***********串口2 A2B210.1 LCD下发命令解析****************//
							ModBus2LCD_Communication();
						
						switch (Sys_Admin.Device_Style)
							{
								case 0:  //常规单体1吨D级蒸汽发生器
								case 1:  //相变单模块蒸汽发生器
								case 2:
								case 3:
									
										XiangBian_Steam_AddFunction();
								//***********串口3 多机联控和本地变频补水通信，485通信解析***********//	
										Modbus3_UnionTx_Communication();
										ModBus_Uart3_LocalRX_Communication();
								//*******还需要有联控的功能数据********************************8
										Union_MuxJiZu_Control_Function();
								//*******处理串口4接收的数据*****************************88
										ModBus_Uart4_Local_Communication();  //
								//***********前后吹扫，点火功率边界值检查***********//
										Check_Config_Data_Function();
								//*************锅炉主控程序+++++++设备补水功能******************//	
										System_All_Control();
								//***********风机风速判断***********//
										Fan_Speed_Check_Function();
										Speed_Pressure_Function();
										PaiWu_Warnning_Function();  //排污提醒程序
										LianXu_Paiwu_Control_Function(); //连续排污功能项
								//**********报警输出继电器8**************//
										Alarm_Out_Function();

										break;
								
								default:
									Sys_Admin.Device_Style = 0;

										break;
							}

						break;
				case 1:
				case 2:
				case 3:
				case 4:  //从属设备
					//*******处理串口3      变频进水阀************************
						Modbus3_UnionTx_Communication();
						ModBus_Uart3_LocalRX_Communication();
					//*******处理串口4接收的数据*****************************88
						ModBus_Uart4_Local_Communication();  //
					//***********前后吹扫，点火功率边界值检查***********//
						Check_Config_Data_Function();
					//*************锅炉主控程序+++++++设备补水功能******************//	
						XiangBian_Steam_AddFunction();
						System_All_Control();
					//***********风机风速判断***********//
						Fan_Speed_Check_Function();
						Speed_Pressure_Function();
						PaiWu_Warnning_Function();  //排污提醒程序
						LianXu_Paiwu_Control_Function(); //连续排污功能项
						break;
				default:
				
						break;
			}
		

//***********运行时间和运行信息管理***********//
		Admin_Work_Time_Function();
	 






//***********水平衡处理函数************//		
		
			

		

	



 
  }
}



	
	


