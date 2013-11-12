/*
 * Bluetooth.h
 *
 *  Created on: Nov 7, 2013
 *      Author: dominik
 */

#ifndef BLUETOOTH_H_
#define BLUETOOTH_H_

#include "aJSON.h"

#define SENSOR_DATA 0
#define DRIVE_COMMAND 1
#define MOTOR_COMMAND 2
#define CONTROL_COMMAND 3
#define DISCONNECT 4
#define SENSOR_REQUEST 5

#define INT_T 0
#define DOUBLE_T 1
#define STRING_T 2
#define BOOL_T 3

void initBluetooth(Stream *stream);

void checkRemoteControlTimeout();

void receiveCommands();

void handleControlCommand(aJsonObject* json);

void handleDisconnect(aJsonObject* json);

void handleSensorRequest(aJsonObject* json);

//void handleMotorCommand(aJsonObject* json);

void handleDriveCommand(aJsonObject* json);

//void decodeMotorCommand(aJsonObject* json, int* motor_id, int* speed);

int getID(aJsonObject* json);
void decodeDriveCommand(aJsonObject* json, int* left, int* right);

#endif /* BLUETOOTH_H_ */
