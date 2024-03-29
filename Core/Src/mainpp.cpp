/*
 * mainpp.cpp
 *
 *  Created on: Mar 29, 2024
 *      Author: S Vedram
 */
#include "math.h"

#include <mainpp.h>
#include <ros.h>
#include <geometry_msgs/Twist.h>
#include <std_msgs/Int16.h>

#include "main.h"
#include "dma.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

ros::NodeHandle nh;
float vels[4]; // [FR, FL, RL, RR]
int16_t angs[4]; // [FR, FL, RL, RR]
int16_t fr = 0, fl = 0, rl = 0, rr = 0;
int16_t fr_s, fl_s, rl_s, rr_s = 0;
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_PIN)
{
	if(GPIO_PIN == steer_fr_ChannelA_Pin)
	{
		if(HAL_GPIO_ReadPin(steer_fr_ChannelA_GPIO_Port, steer_fr_ChannelA_Pin) == 1)
		{
			if(HAL_GPIO_ReadPin(steer_fr_ChannelB_GPIO_Port, steer_fr_ChannelB_Pin) == 1) fr++;
			else if(HAL_GPIO_ReadPin(steer_fr_ChannelB_GPIO_Port, steer_fr_ChannelB_Pin) == 0) fr--;
		}
		else if(HAL_GPIO_ReadPin(steer_fr_ChannelA_GPIO_Port, steer_fr_ChannelA_Pin) == 0)
		{
			if(HAL_GPIO_ReadPin(steer_fr_ChannelB_GPIO_Port, steer_fr_ChannelB_Pin) == 0) fr++;
			else if(HAL_GPIO_ReadPin(steer_fr_ChannelB_GPIO_Port, steer_fr_ChannelB_Pin) == 1) fr--;
		}
	}
	else if(GPIO_PIN == steer_fl_ChannelA_Pin)
	{
		if(HAL_GPIO_ReadPin(steer_fl_ChannelA_GPIO_Port, steer_fl_ChannelA_Pin) == 1)
		{
			if(HAL_GPIO_ReadPin(steer_fl_ChannelB_GPIO_Port, steer_fl_ChannelB_Pin) == 0) fl++;
			else if(HAL_GPIO_ReadPin(steer_fl_ChannelB_GPIO_Port, steer_fl_ChannelB_Pin) == 1) fl--;
		}
		else if(HAL_GPIO_ReadPin(steer_fl_ChannelA_GPIO_Port, steer_fl_ChannelA_Pin) == 0)
		{
			if(HAL_GPIO_ReadPin(steer_fl_ChannelB_GPIO_Port, steer_fl_ChannelB_Pin) == 1) fl++;
			else if(HAL_GPIO_ReadPin(steer_fl_ChannelB_GPIO_Port, steer_fl_ChannelB_Pin) == 0) fl--;
		}
	}
	else if(GPIO_PIN == steer_rl_ChannelA_Pin)
	{
		if(HAL_GPIO_ReadPin(steer_rl_ChannelA_GPIO_Port, steer_rl_ChannelA_Pin) == 1)
		{
			if(HAL_GPIO_ReadPin(steer_rl_ChannelB_GPIO_Port, steer_rl_ChannelB_Pin) == 0) rl++;
			else if(HAL_GPIO_ReadPin(steer_rl_ChannelB_GPIO_Port, steer_rl_ChannelB_Pin) == 1) rl--;
		}
		else if(HAL_GPIO_ReadPin(steer_rl_ChannelA_GPIO_Port, steer_rl_ChannelA_Pin) == 0)
		{
			if(HAL_GPIO_ReadPin(steer_rl_ChannelB_GPIO_Port, steer_rl_ChannelB_Pin) == 1) rl++;
			else if(HAL_GPIO_ReadPin(steer_rl_ChannelB_GPIO_Port, steer_rl_ChannelB_Pin) == 0) rl--;
		}
	}
	else if(GPIO_PIN == steer_rr_ChannelA_Pin)
	{
		if(HAL_GPIO_ReadPin(steer_rr_ChannelA_GPIO_Port, steer_rr_ChannelA_Pin) == 1)
		{
			if(HAL_GPIO_ReadPin(steer_rr_ChannelB_GPIO_Port, steer_rr_ChannelB_Pin) == 0) rr++;
			else if(HAL_GPIO_ReadPin(steer_rr_ChannelB_GPIO_Port, steer_rr_ChannelB_Pin) == 1) rr--;
		}
		else if(HAL_GPIO_ReadPin(steer_rr_ChannelA_GPIO_Port, steer_rr_ChannelA_Pin) == 0)
		{
			if(HAL_GPIO_ReadPin(steer_rr_ChannelB_GPIO_Port, steer_rr_ChannelB_Pin) == 1) rr++;
			else if(HAL_GPIO_ReadPin(steer_rr_ChannelB_GPIO_Port, steer_rr_ChannelB_Pin) == 0) rr--;
		}
	}
}

void cmd_vel_cb(const geometry_msgs::Twist& msg)
{

	float x = msg.linear.x;
	float y = msg.linear.y;
	float a = sqrtf(x*x + y*y);
	int16_t sign;
	if (a == 0)
	{
		for(int i = 0; i < 4; i++)
		{
			vels[i] = 0;
			angs[i] = 0;
		}
	}

	else if ((x == 0))
	{

		sign = y > 0 ? 1 : -1;
		for(int i = 0; i < 4; i++)
		{
			vels[i] = a;
			angs[i] = sign * 250 * 0.4; //0.4 Maps Ticks to PWM
		}

	}
	else
	{
		sign = x > 0 ? 1 : -1;
		int ang = (159.16) * atan(y/x);
		for(int i = 0; i < 4; i++)
		{
			vels[i] = sign * a;
			angs[i] = 0.4 * ang; //0.4 Maps Ticks to PWM
		}
	}
	nh.loginfo("Message Received");
}



ros::Subscriber<geometry_msgs::Twist> sub("cmd_vel", cmd_vel_cb );



void setup()
{
	nh.initNode();
	nh.subscribe(sub);

}


void loop()
{
	nh.spinOnce();
	//FR
	TIM1->CCR1 = vels[0] >= 0 ? vels[0] * 100  : 0;
	TIM1->CCR2 = vels[0] < 0 ? -vels[0] * 100  : 0;
	//FL
	TIM1->CCR3 = vels[1] >= 0 ? vels[1] * 100  : 0;
	TIM1->CCR4 = vels[1] < 0 ? -vels[0] * 100  : 0;
	//RL
	TIM3->CCR1 = vels[2] >= 0 ? vels[2] * 100  : 0;
	TIM3->CCR2 = vels[2] < 0 ? -vels[0] * 100  : 0;
	//RR
	TIM3->CCR3 = vels[3] >= 0 ? vels[3] * 100  : 0;
	TIM3->CCR4 = vels[3] < 0 ? -vels[0] * 100  : 0;

	fr_s = angs[0] - fr;
	fl_s = angs[1] - fl;
	rl_s = angs[2] - rl;
	rr_s = angs[3] - rr;

	//FR
	TIM4->CCR1 = fr_s >= 0 ? fr_s : 0;
	TIM4->CCR2 = fr_s < 0 ? -fr_s : 0;
	//FL
	TIM4->CCR3 = fl_s >= 0 ? fl_s : 0;
	TIM4->CCR4 = fl_s < 0 ? -fl_s : 0;
	//RL
	TIM8->CCR1 = rl_s >= 0 ? rl_s : 0;
	TIM8->CCR2 = rl_s < 0 ? -rl_s : 0;
	//RR
	TIM8->CCR3 = rr_s >= 0 ? rr_s : 0;
	TIM8->CCR4 = rr_s < 0 ? -rr_s : 0;

}
