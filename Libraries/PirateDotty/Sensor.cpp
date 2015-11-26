/**
 * 456789------------------------------------------------------------------------------------------------------------120
 *
 * @brief 
 * @file Sensor.cpp
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
 * Copyright (c) 2013 Marc J. Hulscher <dominik@dobots.nl>
 *
 * @author    dominik
 * @date      Apr 25, 2014
 * @project   
 * @company   Almende B.V.
 * @company   Distributed Organisms B.V.
 * @case      
 */

#include "Sensor.h"

#include "Pinout.h"
#include "PirateDotty.h"
#include "protocol.h"
#include "IRHandler.h"

void initSensors(){
	pinMode(BATTERY_SENSOR,INPUT);
	pinMode(DISTANCE_SENSOR, INPUT);
	pinMode(LIGHT_SENSOR, INPUT);
}

void readSensors(){
	readBatteryState();
}

int getDistance() {
	int value = analogRead(DISTANCE_SENSOR);
	value = 1024-value;
//	LOGd(3, "distance: %4d", value);
	return value;
}

int readBatteryState(){
	int value = analogRead(BATTERY_SENSOR);
//	LOGd(3, "batteryState: %4d", value);
	return value;
}

void sendBattery() {
	aJsonObject * battery = createSensorData();
	int batterystate = readBatteryState();
	addSensorValue(battery, "Battery", batterystate);
	sendMessage(battery);
}

void sendSensorData() {
	// taking the easy way now, by just calling each individual function
	// but better would be to gather the data here and pack it all in one
	// message to send
	IRHandler::getInstance()->sendIRData();
}
