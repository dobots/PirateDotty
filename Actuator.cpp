/*
 * Actuator.cpp
 *
 *  Created on: Nov 7, 2013
 *      Author: dominik
 */

#include "PirateDotty.h"
#include "Actuator.h"
#include "Pinout.h"

typedef enum directions {
	FORWARD, BACKWARD, LEFT, RIGHT
};

void initActuators() {
	pinMode(MOTORAIN1, OUTPUT);
	pinMode(MOTORAIN2, OUTPUT);
	pinMode(MOTORBIN1, OUTPUT);
	pinMode(MOTORBIN2, OUTPUT);
	pinMode(MOTORSTDBY, OUTPUT);
	pinMode(MOTORAPWM, OUTPUT);
	pinMode(MOTORBPWM, OUTPUT);
	pinMode(STATE_LED,  OUTPUT);
}

// --------------------------------------------------------------------
// Motor Utility Functions
void setmotors(int AIN1,int AIN2,int BIN1,int BIN2) {
	digitalWrite(MOTORAIN1,AIN1);
	digitalWrite(MOTORAIN2,AIN2);
	digitalWrite(MOTORBIN1,BIN1);
	digitalWrite(MOTORBIN2,BIN2);
}

// --------------------------------------------------------------------
void moveBot(int straightpow, int powdiff)
{
	// uses 2 component speed decomposition
	// int straightpow describes the forward (or backward) power
	// -255 = backward full power, 255 = forward full power
	// int powdiff describes the difference in power between wheels
	// powdiff e [-255,255]
	digitalWrite(MOTORSTDBY,LOW);  // Disable Motors
	int L = capSpeed(straightpow+powdiff);
	int R = capSpeed(straightpow-powdiff);

	setDirection(&L, &R);

	analogWrite(MOTORBPWM,R);
	analogWrite(MOTORAPWM,L);
	digitalWrite(MOTORSTDBY,HIGH);  // Enable Motors
}

void setDirection(int* leftSpeed, int* RightSpeed)
{
	if (*leftSpeed>0)
	{
		if (*RightSpeed>0)
			setmotors(HIGH, LOW, HIGH, LOW); /*Forward*/
		else
		{
			setmotors(HIGH, LOW, LOW, HIGH); /*Left forw, Right back*/
			*RightSpeed *= -1;
		}
	}
	else
	{
		*leftSpeed *= -1;
		if (*RightSpeed>0)
			setmotors(LOW, HIGH, HIGH, LOW); /*Right forw, Left back*/
		else
		{
			setmotors(LOW, HIGH, LOW, HIGH); /*Backward*/
			*RightSpeed *= -1;
		}
	}
}

// --------------------------------------------------------------------
int capSpeed(int value)
{
	return max(min(value,255),-255);
}

// --------------------------------------------------------------------
void drive(int leftSpeed, int rightSpeed)
{
	int left = capSpeed(leftSpeed);
	int right = capSpeed(rightSpeed);

	LOGd(3, "drive(%d, %d)", leftSpeed, rightSpeed);

	setDirection(&left, &right);

	analogWrite(MOTORAPWM, left);
	analogWrite(MOTORBPWM, right);
	digitalWrite(MOTORSTDBY,HIGH); // enable motors
}

// --------------------------------------------------------------------
void domove(int drivespeed) {
	digitalWrite(MOTORSTDBY,HIGH); // enable motors

	analogWrite(MOTORAPWM, drivespeed);
	analogWrite(MOTORBPWM, drivespeed);
}

// --------------------------------------------------------------------
void dostop() {
	//  LOGd("\tmotor stop");
	digitalWrite(MOTORSTDBY,LOW); // disnable motors
}

// --------------------------------------------------------------------
void ledON(int ledPin)
{
	digitalWrite(ledPin, HIGH);   // sets the LED on
}

// --------------------------------------------------------------------
void ledOFF(int ledPin)
{
	digitalWrite(ledPin, LOW);   // sets the LED off
}
