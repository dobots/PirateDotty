/*
 * Bluetooth.h
 *
 *  Created on: Nov 7, 2013
 *      Author: dominik
 */

#ifndef BLUETOOTH_H_
#define BLUETOOTH_H_

#include "aJSON.h"

#define HOMING USER+1
#define SHOOT_GUNS USER+2
#define FIRE_VOLLEY USER+3
#define HIT_DETECTED USER+4

void initBluetooth(Stream *stream);

int receiveCommands();

void onControl(boolean enabled);
void onDisconnect(aJsonObject* json);
void onSensorRequest(aJsonObject* json);
void onDrive(int left, int right);
void onCustom(aJsonObject* json);

//void handleMotorCommand(aJsonObject* json);

#endif /* BLUETOOTH_H_ */
