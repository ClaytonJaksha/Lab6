Lab6
====

ECE 382 Lab 6: Robot Motion


## Prelab
In this lab, we will use `TA0` to measure incoming IR signals from our remote control, `TA1` to control left motor PWM outputs and right motor outputs.

##### Directionality Matrix
| Directionality | Left Motor <br></br> + Lead | Left Motor <br></br> - Lead | Right Motor <br></br> + Lead | Right Motor <br></br> - Lead |
|----------------|:-----------------:|:-----------------:|:------------------:|:------------------:|
| Forward        |        PWM        |         0         |         PWM        |          0         |
| Left           |         0         |        PWM        |         PWM        |          0         |
| Right          |        PWM        |         0         |          0         |         PWM        |
| Reverse        |         0         |        PWM        |          0         |         PWM        |

The positive lead of the left motor will be attached to `P1.2`

The negative lead of the left motor will be attached to `P1.3`

The positive lead of the right motor will be attached to `P1.4`

The negative lead of the right motor will be attached to `P1.5`

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
