Lab6
====

ECE 382 Lab 6: Robot Motion


## Prelab
In this lab, we will use `TA0` to measure incoming IR signals from our remote control, `TA1` to control left motor PWM outputs, and `TA2` to control right motor outputs.

##### Directionality Matrix
| Directionality | Left Motor <br></br> + Lead | Left Motor <br></br> - Lead | Right Motor <br></br> + Lead | Right Motor <br></br> - Lead |
|----------------|:-----------------:|:-----------------:|:------------------:|:------------------:|
| Forward        |        PWM        |         0         |         PWM        |          0         |
| Left           |         0         |        PWM        |         PWM        |          0         |
| Right          |        PWM        |         0         |          0         |         PWM        |
| Reverse        |         0         |        PWM        |          0         |         PWM        |
