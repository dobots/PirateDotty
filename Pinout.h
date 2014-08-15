/*
 * Pinout.h
 *
 *  Created on: Nov 7, 2013
 *      Author: dominik
 */

#ifndef PINOUT_H_
#define PINOUT_H_

#define MOTORAIN1 19 // AIN1
#define MOTORAIN2 18 // AIN2
#define MOTORBIN1 20 // BIN1
#define MOTORBIN2 21// BIN2
#define MOTORAPWM 22 // PWMA
#define MOTORBPWM 23 // PWMB
#define MOTORSTDBY 17

#define IRRECEIVER 3 // Infrared Receiver
#define IRLEDRIGHT 6 // Not locked down, can change the pin #

#define BATTERYSENSOR 16 // A2
//#define IRLEDLEFT ..

#define ID_SWITCH 7
#define POWER_SWITCH 8


//int UNUSED[23] = {0,1,2,4,5,7,8,9,10,11,12,14,15,24,25,26,27,28,29,30,31,32,33};


#define STATE_LED 13

#define CAPSPEED 100 // this cap should be low enough for all phones (give ppl option to up it for better phones)
//#define CAPSPEED 50

#endif /* PINOUT_H_ */
