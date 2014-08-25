/*
 * Bluetooth.h
 *
 *  Created on: Nov 7, 2013
 *      Author: dominik
 */

#ifndef BLUETOOTH_H_
#define BLUETOOTH_H_

#include "aJSON.h"

void initBluetooth(Stream *stream);

int receiveCommands();

void onControl(boolean enabled);
void onDisconnect(aJsonObject* json);
void onSensorRequest(aJsonObject* json);
void onDrive(int left, int right);
void onCustom(aJsonObject* json);

//void handleMotorCommand(aJsonObject* json);

#endif /* BLUETOOTH_H_ */
