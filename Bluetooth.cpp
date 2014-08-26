/*
 * Bluetooth.cpp
 *
 *  Created on: Nov 7, 2013
 *      Author: dominik
 */

#include "PirateDotty.h"
#include "Bluetooth.h"
#include "Actuator.h"
#include "messenger.h"
#include "IRHoming.h"
#include "Gunner.h"
#include "IRHandler.h"
#include "Sensor.h"
#include "protocol.h"
#include "Looper.h"

#ifdef BT_APP
	Messenger messenger(onControl, onDisconnect, onSensorRequest, onDrive, onCustom);
#endif

Stream* btSerialLine = NULL;

void initBluetooth(Stream *stream) {
	btSerialLine = stream;
	setSerialLine(stream);

	Looper::registerLoopFunc(receiveCommands);
}

void onControl(boolean enabled) {
	LOGd(3, "onControl: %s", (enabled ? "true" : "false"));
}

void onDisconnect(aJsonObject* json) {
	LOGd(3, "onDisconnect");
}

void onSensorRequest(aJsonObject* json) {
	LOGd(3, "onSensorRequest");
	sendSensorData();
}

void onDrive(int left, int right) {
	right = capSpeed(right);
	left = capSpeed(left);

	LOGd(3, "handleDriveCommand (%d, %d)", left, right);
	drive(left, right);
}

void onCustom(aJsonObject* json) {
	switch(getType(json)) {
	case HOMING:
		switchHoming();
		break;
	case SHOOT_GUNS:
		shootGuns();
		break;
	case FIRE_VOLLEY:
		fireVolley();
		break;
	}
}

int lastDrive = 0;
#define DRIVE_TIMEOUT 1000

void handleInput(int incoming) {

	switch(incoming) {
	case 'w':
		drive(55, 55);
		lastDrive = millis();
		break;
	case 's':
		drive(-55, -55);
		lastDrive = millis();
		break;
	case 'a':
		drive(-55, 55);
		lastDrive = millis();
		break;
	case 'd':
		drive(55, -55);
		lastDrive = millis();
		break;
	case 'q':
	case 'e':
		drive(0, 0);
		break;
	case 'h':
		switchHoming();
		break;
	case 32:
		shootGuns();
		break;
	case 'v':
		fireVolley();
		break;
	case 'c':
		continuous = !continuous;
		LOGd(1, "shoot continuous: %s", continuous ? "true" : "false");
		break;
	default:
		LOGd(1, "incoming: %c (%d)", incoming, incoming);
		break;
	}

}

int receiveCommands() {

#ifdef USB_SERIAL
	if (Serial.available()) {
		int incoming = Serial.read();
		handleInput(incoming);

		lastActivity = millis();
	}

	if (lastDrive && (millis() > lastDrive + DRIVE_TIMEOUT)) {
		drive(0,0);
		lastDrive = 0;
	}
#endif
#ifdef BT_SERIAL
	if (btSerialLine->available()) {
		int incoming = btSerialLine->read();
		handleInput(incoming);

		lastActivity = millis();
	}
#endif
#ifdef BT_APP
	if (messenger.handleMessages()) {
		lastActivity = millis();
	}
#endif

	return 0; // no delay, call as much as possible
}

//void handleMotorCommand(aJsonObject* json) {
//	int id = -1, value = -1;
//	decodeMotorCommand(json, &id, &value); //  motor id, speed value between -255 and 255
//	LOGd(3, "handleMotorCommand (%d, %d)", id, value);
//	desiredSpeedMotor[id] = capSpeed(value);
//}
