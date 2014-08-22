/**
 * 456789------------------------------------------------------------------------------------------------------------120
 *
 * @brief:
 * @file: Gun.cpp
 *
 * @desc: 
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
 * Copyright (c) 2013 Dominik Egger <dominik@dobots.nl>
 *
 * @author:        Dominik Egger
 * @date:        Aug 21, 2014
 * @project:    PirateDotty
 * @company:     Distributed Organisms B.V.
 */

#include "Gunner.h"
#include "IRHandler.h"
#include "Log.h"
#include "Actuator.h"

unsigned int IR_GUN_SHOT_SEND[] = {1000, 1000, 1000, 1000, 1000};

bool shoot = false;
bool continuous = false;
int lastShot = millis();
int lastDetect = millis();
int lastShotDetect = millis();
int timeout = 200;
int shotCount = 0;

void gunner_loop() {

//	if (continuous) {
//		shoot = true;
//	}

	if (shoot && (millis() > lastShot + timeout)) {
		shootGuns();
		shoot = false;
		lastShot = millis();
	}

	if (millis() > lastDetect + timeout) {
		if (detectShot()) {
			lastShotDetect = millis();
		}
		if (shotCount == 3) {
			hitDetected();
		}
		lastDetect = millis();
	}

	if (millis() > lastShotDetect + 1000) {
		shotCount = 0;
	}

}

void shootGuns() {

	LOGd(1, "SHOOT");
	IR_HANDLER.send(IR_GUN_SHOT_SEND, 5);

}

bool detectShot() {

	bool shotDetected = false;
	if (IR_HANDLER.hasNewResult()) {

		unsigned long lastResult = IR_HANDLER.getResult();

		if (lastResult == IR_GUN_SHOT) {
			shotDetected = true;
			++shotCount;
			LOGd(1, "shot %d detected", shotCount);
		}

	}

	return shotDetected;

}

void hitDetected() {

	LOGd(1, "yarrrgh!! we was hit");

	for (int i = 0; i < 5; ++i) {
		drive(-100, 100);
		delay(100);
		drive(100,-100);
		delay(100);
	}
	drive(0,0);
}
