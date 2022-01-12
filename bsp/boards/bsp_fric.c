#include "bsp_fric.h"
#include "main.h"
#include "shoot.h"
#include "arm_math.h"

extern TIM_HandleTypeDef htim1;
extern shoot_control_t shoot_control;   

void fric_off(void)
{
    __HAL_TIM_SetCompare(&htim1, TIM_CHANNEL_1, FRIC_OFF);
    __HAL_TIM_SetCompare(&htim1, TIM_CHANNEL_2, FRIC_OFF);
}
void fric1_on(uint16_t cmd)
{
    __HAL_TIM_SetCompare(&htim1, TIM_CHANNEL_1, cmd);
}
void fric2_on(uint16_t cmd)
{
    __HAL_TIM_SetCompare(&htim1, TIM_CHANNEL_2, cmd);
}

/*
SZL 12-30-2021 M3508 摩擦轮 射击速度 控制

*/
void M3508_fric_wheel_spin_control(fp32 left_fric_speed, fp32 right_fric_speed)
{
		//fp32 temp = 0.0f;
		//fp32 vector_rate = 0.0f;
		shoot_control.left_fricMotor.fricW_speed_set = left_fric_speed;
		shoot_control.right_fricMotor.fricW_speed_set = right_fric_speed;
	
		//添加M3508_fric_wheel_spin_control 限制幅度 按照Wheel speed限制幅度
		/*
		temp = fabs(shoot_control.left_fricMotor.fricW_speed_set);
		if(temp > shoot_control.currentLIM_shoot_speed)
		{
			shoot_control.left_fricMotor.fricW_speed_set = (-shoot_control.currentLIM_shoot_speed);
			shoot_control.right_fricMotor.fricW_speed_set = shoot_control.currentLIM_shoot_speed;
		}
		
		temp = shoot_control.right_fricMotor.fricW_speed_set;
		if(temp > shoot_control.currentLIM_shoot_speed)
		{
			shoot_control.left_fricMotor.fricW_speed_set = (-shoot_control.currentLIM_shoot_speed);
			shoot_control.right_fricMotor.fricW_speed_set = shoot_control.currentLIM_shoot_speed;
		}
		*/
	
		PID_calc(&shoot_control.left_fric_motor_pid, shoot_control.left_fricMotor.fricW_speed, left_fric_speed); //left_fric_speed 改
		PID_calc(&shoot_control.right_fric_motor_pid, shoot_control.right_fricMotor.fricW_speed, right_fric_speed);
	
		shoot_control.left_fricMotor.fricW_given_current = shoot_control.left_fric_motor_pid.out;
		shoot_control.right_fricMotor.fricW_given_current = shoot_control.right_fric_motor_pid.out;
	
		CAN_cmd_friction_wheel(shoot_control.left_fricMotor.fricW_given_current, shoot_control.right_fricMotor.fricW_given_current);

}

