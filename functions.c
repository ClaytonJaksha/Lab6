//-----------------------------------------------------------------
// Name: Jaksha, Clayton, B.
// File: functions.c
// Date: 30 NOV 2014
// Purp: functions that make Robert the robot move in a certain directions
//-----------------------------------------------------------------
#include <msp430g2553.h>
#include "functions.h"
void moveRobotForward(void)
{
	TA1CCR1 = FULL_SPEED_LEFT;
	TA1CCR2 = FULL_SPEED_RIGHT;
	TA1CCTL1 = OUTMOD_3;
	TA1CCTL2 = OUTMOD_3;
	P2SEL |= (BIT1|BIT5);
	P2OUT &=~(BIT3|BIT4);
}
void moveRobotBackwards(void)
{
	TA1CCR1 = FULL_SPEED_LEFT;
	TA1CCR2 = FULL_SPEED_RIGHT;
	TA1CCTL1 = OUTMOD_7;
	TA1CCTL2 = OUTMOD_7;
	P2SEL |= BIT1|BIT5;
	P2OUT |= (BIT3|BIT4);
}
void moveRobotLeft(void)
{
	TA1CCR1 = FULL_SPEED_LEFT;
	TA1CCR2 = FULL_SPEED_RIGHT;
	TA1CCTL1 = OUTMOD_7;
	TA1CCTL2 = OUTMOD_3;
	P2SEL |= BIT1|BIT5;
	P2OUT |= BIT3;
	P2OUT &=~BIT4;
}
void moveRobotRight(void)
{
	TA1CCR1 = FULL_SPEED_LEFT;
	TA1CCR2 = FULL_SPEED_RIGHT;
	TA1CCTL1 = OUTMOD_3;
	TA1CCTL2 = OUTMOD_7;
	P2SEL |= BIT1|BIT5;
	P2OUT |= BIT4;
	P2OUT &=~BIT3;
}
void moveRobotLeftSlow(void)
{
	TA1CCR1 = HALF_SPEED_LEFT;
	TA1CCR2 = FULL_SPEED_RIGHT;
	TA1CCTL1 = OUTMOD_3;
	TA1CCTL2 = OUTMOD_3;
	P2SEL |= BIT1|BIT5;
	P2OUT &=~BIT4;
	P2OUT &=~BIT3;
}
void moveRobotRightSlow(void)
{
	TA1CCR1 = FULL_SPEED_LEFT;
	TA1CCR2 = HALF_SPEED_RIGHT;
	TA1CCTL1 = OUTMOD_3;
	TA1CCTL2 = OUTMOD_3;
	P2SEL |= BIT1|BIT5;
	P2OUT &=~BIT4;
	P2OUT &=~BIT3;
}
void stopRobot(void)
{
	TA1CCR1 = FULL_SPEED_LEFT;
	TA1CCR2 = FULL_SPEED_RIGHT;
	P2OUT &=~(BIT1|BIT3|BIT4|BIT5);
}
