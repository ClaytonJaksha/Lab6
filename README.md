Lab 6
====
#### Clayton Jaksha | ECE 382 | Dr. York | M2A
***Note: I use remote control DFEC #6 throughout the course of this lab***
## Objective and Purpose
### Objective

The objective of this lab is to use pulse-width modulation to drive our robot's (hereafter referred to as "Robert") main wheels.

### Purpose

To begin incorporating course concepts on the final course project.


## Preliminary Design
In this lab, we will use `TA0` to measure incoming IR signals from our remote control, `TA1` to control left motor PWM outputs and right motor outputs.

#### Directionality Matrix
| Directionality | Left Motor <br></br> Red Lead <br></br> PWM | Left Motor <br></br> Black Lead <br></br> GPIO | Right Motor <br></br> Red Lead <br></br> PWM | Right Motor <br></br> Black Lead <br></br> GPIO |
|----------------|:-----------------:|:-----------------:|:------------------:|:------------------:|
| Forward        |        OUTMOD_3        |         0         |         OUTMOD_3        |          0         |
| Left           |        OUTMOD_7         |        1       |         OUTMOD_3        |          0         |
| Right          |        OUTMOD_3        |         0         |          OUTMOD_7         |         1        |
| Reverse        |        OUTMOD_7         |        1        |          OUTMOD_7         |         1        |

The red lead of the left motor will be driven by `P2.1`

The black lead of the left motor will be driven by `P2.3`

The red lead of the right motor will be attached to `P1.5`

The black lead of the right motor will be attached to `P1.4`
#### Hardware Schematic
![alt text](https://fbcdn-sphotos-h-a.akamaihd.net/hphotos-ak-xpa1/v/t34.0-12/10836211_1001492989864963_1971890665_n.jpg?oh=77c8c6f40db9cd797dcc3c54f3648a04&oe=547E3D40&__gda__=1417478673_3e5f336960c24b2c4275500b1e7637e1 "dat hardware")
#### Pseudocode
##### `moveRobotForward()`
```
void moveRobotForward(void);
  _disable_interrupts();
  P1SEL |= BIT2|BIT4;
  P1OUT &=~(BIT3|BIT5);
  _enable_interrupts();
```
##### `moveRobotLeft()`
```
void moveRobotForward(void);
  _disable_interrupts();
  P1SEL |= BIT3|BIT4;
  P1OUT &=~(BIT2|BIT5);
  _enable_interrupts();
```
##### `moveRobotRight()`
```
void moveRobotForward(void);
  _disable_interrupts();
  P1SEL |= BIT2|BIT5;
  P1OUT &=~(BIT3|BIT4);
  _enable_interrupts();
```
##### `moveRobotBackwards()`
```
void moveRobotForward(void);
  _disable_interrupts();
  P1SEL |= BIT3|BIT5;
  P1OUT &=~(BIT2|BIT4);
  _enable_interrupts();
```

#### Basic Functionality

Once I program basic functions that will make the wheels spin in the desired direction and speed, I will program them in to a script. I will call those functions followed by some amount of delay in the form of `__delay_cycles(###)`.

#### Remote-Control Robert

For this part, I will affix my IR sensor (seen in hardware schematic) and then reuse my code from Lab 5. Instead of using script to control the robot for this portion, I will use `if` statements that change Robert's movement based on the signal it takes in from the remote control.

## Code Walkthrough
### Basic Functionality
###### Taken from `main_basic.c`
This is the basic initialization for functionality of the code. It includes all the necessary header files and that's basically it. The basic functionality code is pretty simple.
```
#include <msp430g2553.h>
#include "start5.h"
#include "functions.h"
```
This is the main loop script. It changes the settings for the outputs, delays, changes again, delays again, etc.
```
void main(void) {

	initMSP430();
	P2OUT&=~(BIT4|BIT2|BIT1|BIT5); // ensure everything is stopped before we begin.
	stopRobot();
	while(1){
	moveRobotForward();
	__delay_cycles(10000000);
	moveRobotLeft();
	__delay_cycles(3500000);
	moveRobotForward();
	__delay_cycles(10000000);
	moveRobotRight();
	__delay_cycles(3500000);
	moveRobotBackwards();
	__delay_cycles(10000000);
	moveRobotLeftSlow();
	__delay_cycles(20000000);
	moveRobotForward();
	__delay_cycles(5000000);
	moveRobotRightSlow();
	__delay_cycles(20000000);
	moveRobotLeftSlow();
	}
} // end main
```
This is the initialization for the MSP430 with its outputting.
```
void initMSP430() {

	IFG1=0; 					// clear interrupt flag1
	WDTCTL=WDTPW+WDTHOLD; 		// stop WD

	BCSCTL1 = CALBC1_8MHZ;
	DCOCTL = CALDCO_8MHZ;

	P1DIR |= BIT0|BIT6;                     // set LEDs to output

	P2SEL  &= ~BIT6;						// Setup P2.6 as GPIO not XIN
	P2SEL2 &= ~BIT6;
	P2DIR &= ~BIT6;
	P2IFG &= ~BIT6;						// Clear any interrupt flag
	P2IE  |= BIT6;						// Enable PORT 2 interrupt on pin change

	HIGH_2_LOW;
	P1DIR |= BIT0 | BIT6;				// Enable updates to the LED
	P1OUT &= ~(BIT0 | BIT6);			// An turn the LED off

	TA0CCR0 = 0x8000;					// create a 16mS roll-over period
	TACTL &= ~TAIFG;					// clear flag before enabling interrupts = good practice
	TACTL = ID_3 | TASSEL_2 | MC_1;		// Use 1:1 presclar off MCLK and enable interrupts


	//set up left wheel PWM
	P2DIR |= (BIT1|BIT3|BIT4|BIT5);
	P2OUT &= ~(BIT3|BIT4);
	TA1CTL = ID_3 | TASSEL_2 | MC_1;		// Use 1:8 presclar off MCLK
    TA1CCR0 = 0x0100;						// set signal period
    TA1CCR1 = 0x0080;
    TA1CCTL1 = OUTMOD_3;					// set TACCTL1 to Reset / Set mode
    TA1CCR2 = 0x0080;
    TA1CCTL2 = OUTMOD_3;
}

```

### A Functionality
###### Taken from `main.c`
This is the initialization. It does pretty much the same thing as basic functionality, with the added pieces like `packetData[]` and `packetIndex` that make the IR sensor reading work.
```
#include <msp430g2553.h>
#include "start5.h"
#include "functions.h"
int8	newIrPacket = FALSE;
int32	packetData[48];
int8	packetIndex = 0;
unsigned char get_some=FALSE;
```
This is the main loop for A Functionality.
```
void main(void) {

	initMSP430();				// Setup MSP to process IR and buttons
	int32 bitstring=0x00000000;
	int32	i;
	int8	packetIndex2=0;
	stopRobot();
	_enable_interrupt();
	while(1)  {
		if (get_some) {
			_disable_interrupt();
			packetIndex2=0;
			while (packetData[packetIndex2]!=2)
			{
				packetIndex2++;
			}
			packetIndex2++;
			while (packetIndex2<33)
			{
				bitstring+=packetData[packetIndex2];
				bitstring<<=1;
				packetIndex2++;
			}
			if (bitstring==BUTTON_FIVE)
			{
				stopRobot();
			} else if (bitstring==BUTTON_TWO)
			{
				moveRobotForward();
			} else if (bitstring==BUTTON_FOUR)
			{
				moveRobotLeft();
			} else if (bitstring==BUTTON_SIX)
			{
				moveRobotRight();
			} else if (bitstring==BUTTON_EIGHT)
			{
				moveRobotBackwards();
			} else if (bitstring==BUTTON_ONE)
			{
				moveRobotLeftSlow();
			} else if (bitstring==BUTTON_THREE)
			{
				moveRobotRightSlow();
			} else
			{
				stopRobot();
			}
			for (i=0;i<0xFFFFF;i++);
			bitstring=0x00000000;
			packetIndex=0;
			_enable_interrupt();
			get_some=0;
		} else
		{
			bitstring=0x00000000;
		}
	} // end infinite loop
} // end main
```
Here we define our ISR. It is meant to trigger of P2.6, so we use `PORT2_VECTOR`. Basically, what the interrupt does is interrupt each time P2.6 (which is connected to the IR sensor) edge triggers, counts how long it stays at `1`, decides whether it's a `0` or `1`, then stores that value into `packetData`. Once we've triggered 34 times (which is enough to get a unique message from the remote), we flag and our main loop takes care of the rest.

```
#pragma vector = PORT2_VECTOR			// This is from the MSP430G2553.h file

__interrupt void pinChange (void) {

	int8	pin;
	int16	pulseDuration;

	P2IFG &= ~BIT6;
	if (IR_PIN)		pin=1;	else pin=0;

	switch (pin) {					// read the current pin level
		case 0:						// !!!!!!!!!NEGATIVE EDGE!!!!!!!!!!
			pulseDuration = TAR;
			if ((pulseDuration>minStartPulse)&&(pulseDuration<maxStartPulse))
			{
				pulseDuration=2;
			} else if ((pulseDuration>minLogic0Pulse)&&(pulseDuration<maxLogic0Pulse))
			{
				pulseDuration=0;
			} else if ((pulseDuration>minLogic1Pulse)&&(pulseDuration<maxLogic1Pulse))
			{
				pulseDuration=1;
			}
			packetData[packetIndex++] = pulseDuration;
			LOW_2_HIGH; 				// Setup pin interrupr on positive edge
			break;

		case 1:							// !!!!!!!!POSITIVE EDGE!!!!!!!!!!!
			TAR = 0x0000;						// time measurements are based at time 0
			HIGH_2_LOW; 						// Setup pin interrupr on positive edge
			break;
	} // end switch
	if (packetIndex>33)
	{
		get_some=1;
	}
} // end pinChange ISR
```

Initialization remained exactly the same from basic functionality, so I will not re-explain them.

## Debugging

Debugging was primarily done by looking at the Nokia 1202 display and the stored register and expression values within CCS-6.0's debugging feature. Also, for A functionality, I left my LED stuff from basic functionality too to make sure everything up until the if statements were working.

## Testing Methodology/Results

#### Testing Methodology
To test the funcionality of my program, I attached the hardware IAW the diagram in my deisgn section, loaded the program, ran the program, and pressed buttons on my remote. If it did what I wanted, then it passed the test.
#### Results
The code works!
##### Basic Functionality
By pressing the "4" button on my remote, the red LED would toggle. Then, by pressing the "6" button, the green LED would toggle. Fairly straightforward to test and everything worked as expected.
##### A Functionality
For this one, I made the etch-a-sketch function through my remote control. In my implementation, I made the "2" button move the cursor up, the "4" button move left, the "6" button move right, the "8" button move down, and the "5" button toggle color. The solution mostly worked. The basic idea of moving a block and then erasing blocks works fine, but the command `initNokia()` leaves a couple of weird ghost bits drawn on the screen with every button press.

However, I would say that the goal of the lab has been accomplished.

## Observations and Conclusion
#### Observations

* Reusing previous .c and .h files can make coding faster and modular.
* ISRs and Nokia displays may not work together easily. Be careful for future projects.
* Structures and fun and easy to use. They enable a group of information to be stored in an organized manner.

#### Conclusion

The etch-a-sketch worked according to specs (well, mostly). The Army team is fully prepared to beat everyone ever.

## Documentation

None


# SONS OF SLUM AND GRAVY TAKE NO QUARTER
![alt text](http://farm7.static.flickr.com/6120/6300471005_c44f5ef019.jpg "GO ARMY, BEAT NAVY")
