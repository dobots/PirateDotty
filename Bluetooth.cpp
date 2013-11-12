/*
 * Bluetooth.cpp
 *
 *  Created on: Nov 7, 2013
 *      Author: dominik
 */

#include "PirateDotty.h"
#include "Bluetooth.h"
#include "Actuator.h"

aJsonStream *serial_stream;
aJsonStream debug_stream(&Serial);
//HardwareSerial *bt_serial;

unsigned long lastCommandReceived = 0;

//jsmn_parser parser;
//#define NUM_TOKENS 100
//jsmntok_t tokens[NUM_TOKENS];

void initBluetooth(Stream *stream) {
	serial_stream = new aJsonStream(stream);
//	jsmn_init(&parser);
}

//void checkRemoteControlTimeout() {
//	if ((millis() - lastCommandReceived) > INACTIVITY_TIMEOUT) {
//		isRemoteControl = false;
//	}
//}

void receiveCommands() {

//#ifdef DEBUG
//	if (Serial.available()) {
//		int incoming = Serial.read();
//		handleInput(incoming);
//	}
//	return;
//#endif
//
//#ifdef DEBUG_BT
//	if (Serial3.available()) {
//		int incoming = Serial3.read();
//		// LOGd(1, "serial3: %d", incoming);
//		handleInput(incoming);
//	}
//#endif

//	LOGd(1, "receiveCommands ...");

	aJsonObject* item;
	if (serial_stream->available()) {
		LOGd(1, "incoming data ...");
		item = aJson.parse(serial_stream);
		aJson.print(item, &debug_stream);
		Serial.println(" ");

		if (item == NULL) {
			LOGd(0, "not a json object!");
			// while(Serial.available()) {
			// 	Serial3.print(Serial.read());
			// }
			// Serial3.println("");
			serial_stream->flush();
			return;
		}
	} else {
//		LOGd(1, "nothing received ...");
		return;
	}

	LOGd(1, "command received ...");
	lastActivity = millis();

	switch(getID(item)) {
		// switch(getType(item)) {
		case DRIVE_COMMAND:
			handleDriveCommand(item);
			isRemoteControl = true;
			break;
//		case MOTOR_COMMAND:
//			handleMotorCommand(item);
//			break;
		case CONTROL_COMMAND:
			handleControlCommand(item);
			break;
		case DISCONNECT:
			handleDisconnect(item);
			break;
		case SENSOR_REQUEST:
			handleSensorRequest(item);
			break;
		default:
			break;
	}
	aJson.deleteItem(item);

}

void handleControlCommand(aJsonObject* json) {
	///TODO: remove?
	// is not necessary for now
}

void handleDisconnect(aJsonObject* json) {
	// is sent when the phone disconnects from the robot, best to turn off all motors here
	LOGd(3, "handleSensorRequest");
}

void handleSensorRequest(aJsonObject* json) {
	LOGd(3, "handleSensorRequest");
//	sendData();
}

//void handleMotorCommand(aJsonObject* json) {
//	int id = -1, value = -1;
//	decodeMotorCommand(json, &id, &value); //  motor id, speed value between -255 and 255
//	LOGd(3, "handleMotorCommand (%d, %d)", id, value);
//	desiredSpeedMotor[id] = capSpeed(value);
//}

void handleDriveCommand(aJsonObject* json) {
	int leftSpeed = 0, rightSpeed = 0;

	decodeDriveCommand(json, &leftSpeed, &rightSpeed);

	rightSpeed = capSpeed(rightSpeed);
	leftSpeed = capSpeed(leftSpeed);

	LOGd(3, "hanldeDriveCommand (%d, %d)", leftSpeed, rightSpeed);
	drive(leftSpeed, rightSpeed);
}

int getID(aJsonObject* json) {
	aJsonObject *id, *header;
	header = aJson.getObjectItem(json, "header");
	if (header == NULL) {
		LOGd(1, "wrong json message!");
		return -1;
	}

	id = aJson.getObjectItem(header, "type");
	if (id == NULL) {
		LOGd(1, "wrong json message!");
		return -1;
	}
	return id->valueint;
}

//void decodeMotorCommand(aJsonObject* json, int* motor_id, int* speed) {
//	aJsonObject* data = aJson.getObjectItem(json, "data");
//
//	aJsonObject* motor_id_j = aJson.getArrayItem(data, 0);
//	*motor_id = motor_id_j->valueint;
//
//	aJsonObject* speed_j = aJson.getArrayItem(data, 1);
//	*speed = speed_j->valueint;
//}

void decodeDriveCommand(aJsonObject* json, int* left, int* right) {
	aJsonObject* data = aJson.getObjectItem(json, "data");

	if (data == NULL) {
		LOGd(0, "DATA NOT FOUND");
	}

	aJsonObject* right_j = aJson.getObjectItem(data, "right");
	*right = right_j->valueint;

	aJsonObject* left_j = aJson.getObjectItem(data, "left");
	*left = left_j->valueint;
}


