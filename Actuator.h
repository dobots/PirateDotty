/*
 * Actuator.h
 *
 *  Created on: Nov 7, 2013
 *      Author: dominik
 */

#ifndef ACTUATOR_H_
#define ACTUATOR_H_

void initActuators();
void setup();
void moveBot(int straightpow, int powdiff);
void setDirection(int* leftSpeed, int* RightSpeed);
int capSpeed(int value);
void drive(int leftSpeed, int rightSpeed);
void domove(int drivespeed);
void dostop();
void ledON(int ledPin);
void ledOFF(int ledPin);

#endif /* ACTUATOR_H_ */
