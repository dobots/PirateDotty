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

//int shots = 0;
bool continuous = false; // not used, but too lazy to remove in all code
int lastShotDetect = 0;
int shotCount = 0;
//int gunsReloaded = 0;
//int reloadTime = 0;
//bool readyToShoot = true;
bool raging = false;
int shotTime = 0;
int speedLeft = 0;
int speedRight = 0;

bool detectShot();
void hitDetected();
int capRageSpeed(int speed);
int offsetSpeed(int speed);
void unrage();

void gunner_init() {
	Looper::registerLoopFunc(gunner_loop);
}

int gunner_loop() {
//	LOGd(1, "min=%i max=%i range=%i - %i", MIN_SPEED, MAX_SPEED, MIN_SPEED_RANGE, MAX_SPEED_RANGE);
//	LOGd(1, "2 * max range: %i", 2*MAX_SPEED_RANGE);
//	LOGd(1, "rand: %i", rand() % (2*MAX_SPEED_RANGE));
/*
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
*/

	if (raging) {
		IRHandler::getInstance()->send(IR_GUN_SHOT_SEND, 5);

		speedLeft = capRageSpeed(speedLeft + rand() % (2*MAX_SPEED_CHANGE) - MAX_SPEED_CHANGE);
		speedRight = capRageSpeed(speedRight + rand() % (2*MAX_SPEED_CHANGE) - MAX_SPEED_CHANGE);
		drive(offsetSpeed(speedLeft), offsetSpeed(speedRight));
//		delay(GUNNER_DRIVE_DELAY);

//		LOGd(1, "now=%i", Looper::now());
		if (shotTime + RAGE_DURATION < Looper::now()) {
			unrage();
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

int capRageSpeed(int speed) {
	int cappedSpeed = speed;
	if (cappedSpeed > MAX_SPEED_RANGE) {
		cappedSpeed = MAX_SPEED_RANGE;
	}
	if (cappedSpeed < MIN_SPEED_RANGE) {
		cappedSpeed = MIN_SPEED_RANGE;
	}
	return cappedSpeed;
}

// given speed goes from MIN_SPEED_RANGE to MAX_SPEED_RANGE
// outputs it in the range -MAX_SPEED to -MIN_SPEED or MIN_SPEED to MAX_SPEED
int offsetSpeed(int speed) {
//	LOGd(1, "offsetSpeed: %i", speed);
	int offsetSpeed = speed;


	if (offsetSpeed > 0) {
		offsetSpeed += MIN_SPEED;
	}
	else {
		offsetSpeed -= MIN_SPEED;
	}
	return offsetSpeed;
}

void rage() {
	LOGd(1, "rrrRRRRAAAAAAGGGEEE!!!!");
	raging = true;
	shotTime = Looper::now();
//	LOGd(1, "shotTime=%i", shotTime);

	// Init speeds with a random value
	speedLeft = capRageSpeed(rand() % (2*(MAX_SPEED_RANGE)) - MAX_SPEED_RANGE);
	speedRight = capRageSpeed(rand() % (2*(MAX_SPEED_RANGE)) - MAX_SPEED_RANGE);
//	LOGd(1, "speeds: %i %i", speedLeft, speedRight);
	// TODO: Enable leds
	drive(offsetSpeed(speedLeft), offsetSpeed(speedRight));
//	delay(GUNNER_DRIVE_DELAY);
}

void unrage() {
	LOGd(1, "I'm ok again");
	raging = false;
	drive(0,0);
	// Disable leds
}


void shootGuns() {

}

void fireVolley() {

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
	sendHitDetected();
	rage();

/*
	for (int i = 0; i < 5; ++i) {
		drive(-100, 100);
		delay(100);
		drive(100,-100);
		delay(100);
	}
	drive(0,0);
*/
}

void sendHitDetected() {
#ifdef BT_APP
	LOGd(1, "sendHItDetected()");
	aJsonObject* json = createJsonBase(HIT_DETECTED);
    sendMessage(json);
#endif
}
