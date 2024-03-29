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
int16_t angs[4];

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
			angs[i] = sign * 250;
		}

	}
	else
	{
		sign = x > 0 ? 1 : -1;
		int ang = (159.16) * atan(y/x);
		for(int i = 0; i < 4; i++)
		{
			vels[i] = sign * a;
			angs[i] = ang;
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

}
