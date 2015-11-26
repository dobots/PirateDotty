/**
 * 456789------------------------------------------------------------------------------------------------------------120
 *
 * @brief
 * @file IRHoming.cpp
 *
 * This file is created at Almende B.V. and Distributed Organisms B.V. It is open-source software and belongs to a
 * larger suite of software that is meant for research on self-organization principles and multi-agent systems where
 * learning algorithms are an important aspect.
 *
 * This software is published under the GNU Lesser General Public license (LGPL).
 *
 * It is not possible to add usage restrictions to an open-source license. Nevertheless, we personally strongly object
 * against this software being used for military purposes, factory farming, animal experimentation, and "Universal
 * Declaration of Human Rights" violations.
 *
 * Copyright (c) 2013 Marc J. Hulscher <dominik@dobots.nl>
 *
 * @author    dominik
 * @date      Jan 22, 2014
 * @project
 * @company   Almende B.V.
 * @company   Distributed Organisms B.V.
 * @case
 */

#include "IRHoming.h"

#include "Actuator.h"
#include "IRremote.h"
#include "messenger.h"
#include "Pinout.h"
#include "PirateDotty.h"
#include "Sensor.h"
#include "IRHandler.h"
#include "Looper.h"
#include "DriveControl.h"

bool GOHOME;
bool CHARGING;
unsigned long correctValue = 543819690;
unsigned long lastValue;
unsigned long currValue;

//int ROTATE_HOMING_SPEED = 20;
//int DEFAULT_HOMING_SPEED = 120;
int ROTATE_HOMING_SPEED = 40;
//int DEFAULT_HOMING_SPEED = 90;	//this speed works on samsGalaxy & nexus7....NOT xperia's
int DEFAULT_HOMING_SPEED = 40;

int lastDirection = -1;		// toggles between 1 and -1 for direction left & right
int lastCheck = millis();
int lastControl = millis();
int lastSwitch = millis();
int waitPeriod = 200;
int recvTimeout = 300;
int searchTimeout = 20000;

void initIRHoming(){
	GOHOME = false;
	CHARGING = false;

//	Looper::registerLoopFunc(IRhomeWalk);
}

void sendLog(char* log){
	aJsonObject * Log = createSensorData();
    addSensorValue(Log, "Log", log);
    sendMessage(Log);
}

void doDrive(int left, int right) {
	if (GOHOME) {
		setDriveSpeeds(left, right);
	}
}

int lastHoming = 0;
int errorCount = 0;
int IRhomeWalk(){
	if (!GOHOME) {
		lastHoming = 1;
		return waitPeriod;
	}

	// TODO: identify under which decoder the values are found!
	// preferably apply that decoder directly for more speed?

//	if(millis() >= lastSignal + waitPeriod){
//
//		int irReceived = irrecv_digi.decode(&IRresults);
//		if (irReceived) {
//
//			lastSignal = millis();
//			LOGd(1, "\tsignal recvd: %d", IRresults.value);
//			irrecv_digi.resume();
//		}
//	}
//
//	return;

	if(millis() >= lastCheck + waitPeriod){

		if (IRHandler::getInstance()->hasNewResult()) {
			currValue = IRHandler::getInstance()->getResult();
			lastCheck = millis();

//			sendIRData();

//			LOGd(1, "\tsignal recvd: %d", IRresults.value);
//			irrecv_digi.resume();
		} else if (millis() >= lastCheck + recvTimeout) {
			lastCheck = millis();
//			sendNull();
			errorCount = 5;
//			sendLog("2");
			LOGd(1, "\trecv timeout");
		}

		if(GOHOME){
			if(IRHandler::getInstance()->hasNewResult()){
				if(currValue==correctValue){
					LOGd(2, "  homing fwd");
					errorCount = 0;

					lastControl = millis();
					doDrive(DEFAULT_HOMING_SPEED,DEFAULT_HOMING_SPEED);
					lastHoming = 0;
//					lastValue = IRresults.value;
//					lastDirection = 1;
//					sendLog("3");
				} else {
					if ((lastValue == correctValue && errorCount < 4) || lastHoming == 4) {

						LOGd(2, "  homing fwd try");
						lastControl = millis();
						doDrive(DEFAULT_HOMING_SPEED,DEFAULT_HOMING_SPEED);
						lastHoming = 5;
						++errorCount;
					} else {
//					if (lastValue == correctValue && errorCount == 0) {
//						LOGd(1, "  homing change rotation");
//
//						lastControl = millis();
//						lastSwitch = millis();
//						lastDirection *= -1;
//						drive(lastDirection*ROTATE_HOMING_SPEED,-1*lastDirection*ROTATE_HOMING_SPEED);
//	//					sendLog("5");
//					} else {
						LOGd(2, "  homing rotate");

						lastControl = millis();
						doDrive(lastDirection*ROTATE_HOMING_SPEED,-1*lastDirection*ROTATE_HOMING_SPEED);
						lastHoming = 1;
//						lastValue = IRresults.value;
					}
//					++errorCount;
//					sendLog("4");
				}
			} else if (millis() >= lastControl + recvTimeout) {
//				if (lastHoming == 1 && errorCount < 4) {
////					if (lastValue == correctValue && errorCount < 4) {
//					LOGd(2, "  homing change rotation");
//
//					lastControl = millis();
//					lastDirection *= -1;
//					++errorCount;
//					doDrive(lastDirection*ROTATE_HOMING_SPEED,-1*lastDirection*ROTATE_HOMING_SPEED);
//					lastHoming = 2;
////					sendLog("5");
//				} else
					if (lastHoming == 0 || lastHoming == 5) {
					LOGd(2, "  homing bwd");

					lastControl = millis() + recvTimeout / 2;
					lastValue = -1;
					errorCount = 0;
					doDrive(-1*DEFAULT_HOMING_SPEED, -0.6*DEFAULT_HOMING_SPEED);
					lastHoming = 3;
//					sendLog("6");
				} else {
					LOGd(2, "  homing search");

					lastControl = millis();
					doDrive(lastDirection*ROTATE_HOMING_SPEED,-1*lastDirection*ROTATE_HOMING_SPEED);
					lastHoming = 4;
//					sendLog("7");

				}

//					lastValue = 0;
//				} else if ((lastValue != 0)) {
//	//				lastDirection *= -1;
//					drive(lastDirection*ROTATE_HOMING_SPEED,-1*lastDirection*ROTATE_HOMING_SPEED);
//					lastValue = 0;
				}
//			} else if (millis() >= lastSignal + searchTimeout) {
//				dostop();
//			}

			lastValue = currValue;
		}

	}

	return waitPeriod;

	/* 17:19, 14.08.14
	void IRhomeWalk(){

		// TODO: identify under which decoder the values are found!
		// preferably apply that decoder directly for more speed?


		if(millis() >= lastSignal + waitPeriod){

			if(GOHOME){
			int irReceived = irrecv_digi.decode(&IRresults);
			if (irReceived) {
				lastSignal = millis();
				sendIRData();
				irrecv_digi.resume();
	//			sendLog("1");
				LOGd(1, "\tsignal recvd: %d", IRresults.value);
			} else if (millis() >= lastSignal + recvTimeout) {
				lastSignal = millis();
				sendNull();
				errorCount = 5;
	//			sendLog("2");
				LOGd(1, "\trecv timeout");
			}

				if(irReceived){
					errorCount = 0;
					if(IRresults.value==correctValue){
						LOGd(1, "  homing fwd");

						lastControl = millis();
						drive(DEFAULT_HOMING_SPEED,DEFAULT_HOMING_SPEED);
						lastValue = IRresults.value;
	//					sendLog("3");
					} else {
						LOGd(1, "  homing rotate");

						lastControl = millis();
						drive(lastDirection*ROTATE_HOMING_SPEED,-1*lastDirection*ROTATE_HOMING_SPEED);
						lastValue = IRresults.value;
	//					sendLog("4");
					}
				} else if (millis() >= lastControl + recvTimeout) {
					if (lastValue == correctValue && errorCount < 4) {
						LOGd(1, "  homing change rotation");

						lastControl = millis();
						lastDirection *= -1;
						++errorCount;
						drive(lastDirection*ROTATE_HOMING_SPEED,-1*lastDirection*ROTATE_HOMING_SPEED);
	//					sendLog("5");
					} else if (lastValue == correctValue) {
						LOGd(1, "  homing bwd");

						lastControl = millis() - recvTimeout;
						errorCount = 0;
						drive(-1*DEFAULT_HOMING_SPEED, -1*DEFAULT_HOMING_SPEED);
	//					sendLog("6");
					} else {
						LOGd(1, "  homing search");

						lastControl = millis();
						drive(lastDirection*ROTATE_HOMING_SPEED,-1*lastDirection*ROTATE_HOMING_SPEED);
	//					sendLog("7");

					}

	//					lastValue = 0;
	//				} else if ((lastValue != 0)) {
	//	//				lastDirection *= -1;
	//					drive(lastDirection*ROTATE_HOMING_SPEED,-1*lastDirection*ROTATE_HOMING_SPEED);
	//					lastValue = 0;
					}
	//			} else if (millis() >= lastSignal + searchTimeout) {
	//				dostop();
	//			}
			}

		}
	*/


//	if(HOME==true && irrecv_digi.decode(&IRresults)){
//		if(IRresults.value == correctValue){
//			irrecv_digi.resume();
//			moveForward(duration);
//		} else if(lastValue==correctValue && lastDirection == RIGHT) {
//			rotateCounterClockwise();
//		} else if(lastValue==correctValue && lastDirection == LEFT) {
//			rotateClockwise();
//		}
//		lastValue = IRresults.value;
//		lastActivity = millis();
//	} else if(irrecv_digi.decode(&IRresults)) {
//		sendIRData();
//		irrecv_digi.resume();
//	}
//	return;
}


void switchHoming() {
	if (GOHOME) {
		disableHoming();
	} else {
		enableHoming();
	}
}

void enableHoming(){
	LOGd(1, "  start homing");
	lastValue = -1;
	GOHOME = true;
}

void disableHoming(){
	LOGd(1, "  stop homing");
	lastValue = 0;
	GOHOME = false;
	dostop();
}

void sendNull(){
	aJsonObject * IRData;
    IRData = createSensorData();
    addSensorValue(IRData, "IR command received", 0);
    sendMessage(IRData);
}
