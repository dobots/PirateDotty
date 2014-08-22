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

Messenger messenger(onControl, onDisconnect, onSensorRequest, onDrive);

void initBluetooth(Stream *stream) {
	setSerialLine(stream);
}

void handleInput(int incoming) {

	switch(incoming) {
	case 'w':
		drive(55, 55);
		break;
	case 's':
		drive(-55, -55);
		break;
	case 'a':
		drive(-55, 55);
		break;
	case 'd':
		drive(55, -55);
		break;
	case 'q':
	case 'e':
		drive(0, 0);
		break;
	case 'h':
		switchHoming();
		break;
	case 32:
		shoot = true;
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

void receiveCommands() {

#ifdef DEBUG
	if (Serial2.available()) {
		int incoming = Serial2.read();
		handleInput(incoming);

		lastActivity = millis();
	}
#else
	if (messenger.handleMessages()) {
		lastActivity = millis();
	}
#endif

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
//	sendIRData();
	switchHoming();
//	switchPower();
}

void onDrive(int left, int right) {
	right = capSpeed(right);
	left = capSpeed(left);

	LOGd(3, "handleDriveCommand (%d, %d)", left, right);
	drive(left, right);
}

//void handleMotorCommand(aJsonObject* json) {
//	int id = -1, value = -1;
//	decodeMotorCommand(json, &id, &value); //  motor id, speed value between -255 and 255
//	LOGd(3, "handleMotorCommand (%d, %d)", id, value);
//	desiredSpeedMotor[id] = capSpeed(value);
//}
