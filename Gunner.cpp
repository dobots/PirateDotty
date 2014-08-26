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
#include "protocol.h"
#include "Bluetooth.h"

unsigned int IR_GUN_SHOT_SEND[] = {1000, 1000, 1000, 1000, 1000};

//bool shoot = false;
int shots = 0;
bool continuous = false;
int lastShotDetect = 0;
int shotCount = 0;
int gunsReloaded = 0;
int reloadTime = 0;
bool readyToShoot = true;

bool detectShot();
void hitDetected();

void gunner_init() {
	Looper::registerLoopFunc(gunner_loop);
}

int gunner_loop() {

	// shoot
	if (continuous) {
		shots = 1;
	}

	if (!readyToShoot && Looper::now() > gunsReloaded) {
		LOGd(1, "guns reloaded ...");
		readyToShoot = true;
	}

	if (shots && readyToShoot) {
		LOGd(1, "SHOOT %d", shots);
		IRHandler::getInstance()->send(IR_GUN_SHOT_SEND, 5);
		--shots;

		if (!shots) {
			gunsReloaded = Looper::now() + reloadTime;
			readyToShoot = false;
			LOGd(1, "reloading ... (%d s)", reloadTime / 1000);
		} else {
			gunsReloaded = Looper::now() + 500;
			readyToShoot = false;
		}
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
	if (readyToShoot) {
		reloadTime = SHOOT_DELAY;
		shots = 1;
	}
}

void fireVolley() {
	if (readyToShoot) {
		reloadTime = 3 * SHOOT_DELAY;
		shots = 3;
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

	sendHitDetected();

	for (int i = 0; i < 5; ++i) {
		drive(-100, 100);
		delay(100);
		drive(100,-100);
		delay(100);
	}
	drive(0,0);

}

void sendHitDetected() {
#ifdef BT_APP
	LOGd(1, "sendHItDetected()");
	aJsonObject* json = createJsonBase(HIT_DETECTED);
    sendMessage(json);
#endif
}
