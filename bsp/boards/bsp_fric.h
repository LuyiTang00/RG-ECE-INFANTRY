#ifndef BSP_FRIC_H
#define BSP_FRIC_H
#include "struct_typedef.h"
//1320 speed level 2 single shoot - fric_down
//1400 speed level 2 continuous shoot- fric_up
//1206 speed level 1 single 18m/s
//1170 speed level 0 15m/s
//1265 spedd level 2 22 m/s

#define FRIC_UP 1097
#define FRIC_DOWN 1097		
#define FRIC_OFF 1000

#define FRIC_LV1 1097
#define FRIC_LV2 1114
#define FRIC_LV3 1114

/*
程序 12.5 = referee枪口初速 <= 15m/s
程序 14.70 = referee枪口初速 <= 18m/s

最多1 - 1.5m/s
*/
#define M3508_FRIC_LIM1 12.5
#define M3508_FRIC_LIM2 14.7

#define M3508_FRIC_STOP 0


extern void fric_off(void);
extern void fric1_on(uint16_t cmd);
extern void fric2_on(uint16_t cmd);

extern void M3508_fric_wheel_spin_control(fp32 left_fric_speed, fp32 right_fric_speed);
#endif

/*
		注意 现在PID 800 100 600 为了完全避免超调，可能还需要将800  改小
		// 15:48 offset 3m/s 此时15m/s程序 出来18m/s; 
		// 1551 测试程序设置 12.5m/s 裁判系统测速 14.5-14.7m/s 
		offset 2-2.5
				最低13.8 最高14.7
		
		//1739 现在测试18m/s
		//程序15.5 ; 裁判系统: 18.7-18.9; 即offset需要大于2.5
		//程序13.5 ; 裁判系统: 16.3
		//程序14.5 ; 裁判系统: 17.1 - 17.7.8; 16.7.6出现过 offset 3.5 可能是3-3.5
		//程序15 裁判系统 17.8.9 18
		//prog 14.75 referee 17.8 17.9multiple time 18.0multiple time one-time(18.1) offset 3.25
		//recommend 14.70-14.73  offset3.25
		
		
		
		//2013 现在测试22m/s
		//prog 18m/s referee 21.7 22.2 等 offset 4
		
		//2045 现在测试30m/s
		24.5
		*/

