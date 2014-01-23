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

Messenger messenger(onControl, onDisconnect, onSensorRequest, onDrive);

void initBluetooth(Stream *stream) {
	setSerialLine(stream);
}

void handleInput(int incoming) {
	switch(incoming) {
	case '8':
		drive(255, 255);
		break;
	case '2':
		drive(-255, -255);
		break;
	case '4':
		drive(-255, 255);
		break;
	case '6':
		drive(255, -255);
		break;
	case '5':
		drive(0, 0);
		break;
	default:
		LOGd(1, "incoming: %c (%d)", incoming, incoming);
		break;
	}
}

void receiveCommands() {

#ifdef DEBUG
	if (Serial.available()) {
		int incoming = Serial.read();
		handleInput(incoming);

		lastActivity = millis();
	}
#endif

	if (messenger.handleMessages()) {
		lastActivity = millis();
	}
}

void onControl(boolean enabled) {
	LOGd(3, "onControl: %s", (enabled ? "true" : "false"));
}

void onDisconnect(aJsonObject* json) {
	LOGd(3, "onDisconnect");
}

void onSensorRequest(aJsonObject* json) {
	LOGd(3, "onSensorRequest");
//	sendData();
}

void onDrive(int left, int right) {
	right = capSpeed(right);
	left = capSpeed(left);

	LOGd(3, "hanldeDriveCommand (%d, %d)", leftSpeed, rightSpeed);
	drive(left, right);
}

//void handleMotorCommand(aJsonObject* json) {
//	int id = -1, value = -1;
//	decodeMotorCommand(json, &id, &value); //  motor id, speed value between -255 and 255
//	LOGd(3, "handleMotorCommand (%d, %d)", id, value);
//	desiredSpeedMotor[id] = capSpeed(value);
//}
