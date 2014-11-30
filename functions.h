//-----------------------------------------------------------------
// Name: Jaksha, Clayton, B.
// File: functions.h
// Date: 30 NOV 2014
// Purp: header file for functions that make Robert the robot move in a certain directions
//-----------------------------------------------------------------

#ifndef START5_H_
#define START5_H_
#define FULL_SPEED_LEFT 0x0070
#define FULL_SPEED_RIGHT 0x0060
#define HALF_SPEED_LEFT 0x0090
#define HALF_SPEED_RIGHT 0x0090
void moveRobotForward(void);
void moveRobotBackwards(void);
void moveRobotLeft(void);
void moveRobotRight(void);
void moveRobotLeftSlow(void);
void moveRobotRightSlow(void);
void stopRobot(void);


#endif
