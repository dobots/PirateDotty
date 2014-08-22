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
#include "Looper.h"

unsigned int IR_GUN_SHOT_SEND[] = {1000, 1000, 1000, 1000, 1000};

bool shoot = false;
bool continuous = false;
int lastShotDetect = 0;
int shotCount = 0;
int nextShot = 0;

bool detectShot();
void hitDetected();

void gunner_init() {
	Looper::registerLoopFunc(gunner_loop);
}

int gunner_loop() {

	// shoot
	if (continuous) {
		shoot = true;
	}

	if (shoot && Looper::now() > nextShot) {
		LOGd(1, "SHOOT");
		IRHandler::getInstance()->send(IR_GUN_SHOT_SEND, 5);
		shoot = false;
	}

	// check if shot
	if (detectShot()) {
		lastShotDetect = Looper::now();
	}

	if (shotCount == 3) {
		hitDetected();
		shotCount = 0;
	}

	if (Looper::now() > lastShotDetect + HIT_TIMEOUT) {
		shotCount = 0;
	}

	return 1000 / GUNNER_FREQ;
}

void shootGuns() {
	if (shoot == false) {
		nextShot += SHOOT_DELAY;
		shoot = true;
	}
}

void setContinuous(bool value) {
	continuous = value;
}

bool detectShot() {

	bool shotDetected = false;
	if (IRHandler::getInstance()->hasNewResult()) {

		unsigned long lastResult = IRHandler::getInstance()->getResult();

		if (lastResult == IR_GUN_SHOT) {
			// clear the result so that in the next iteration we don't try to read the same result again
			IRHandler::getInstance()->clearResult();

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
