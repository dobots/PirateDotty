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

int lightMeasurements[LIGHT_SENSOR_HIST_SIZE] = {0};
unsigned long lightMeasurementTimestamps[LIGHT_SENSOR_HIST_SIZE] = {0};

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

int readLightSensor() {
	int value = analogRead(LIGHT_SENSOR);
	unsigned long timestamp = millis();
	
	// Shift history
	for (int i=0; i<LIGHT_SENSOR_HIST_SIZE-1; i++) {
		lightMeasurements[i] = lightMeasurements[i+1];
		lightMeasurementTimestamps[i] = lightMeasurementTimestamps[i+1];
	}
	// Store last measurement at the back
	lightMeasurements[LIGHT_SENSOR_HIST_SIZE-1] = value;
	lightMeasurementTimestamps[LIGHT_SENSOR_HIST_SIZE-1] = timestamp;
	return value;
}

int getFilteredLightLevel() {
	unsigned long now = millis();
	
	// If the last measurement was too long ago, just return last measurement
	if (now - lightMeasurementTimestamps[LIGHT_SENSOR_HIST_SIZE-1] > LIGHT_SENSOR_HIST_MAX_DT) {
		return lightMeasurements[LIGHT_SENSOR_HIST_SIZE-1];
	}
	
	unsigned long sum = 0;
	unsigned long sumWeights = 0;
	// Weighted sum: measurements longer ago have a lower weight
	for (int i=LIGHT_SENSOR_HIST_SIZE-1; i>=0; i--) {
		unsigned long timediff = (now - lightMeasurementTimestamps[i]);
		if (timediff > LIGHT_SENSOR_HIST_MAX_DT) {
			break;
		}
		// Weight is based on squared time difference
		// Make sure this doesn't overflow the sum!
		unsigned long weight = (LIGHT_SENSOR_HIST_MAX_DT - timediff)/100;
		weight *= weight;
		sum += weight*lightMeasurements[i];
		sumWeights += weight;
//		LOGi(0, "timediff=%4d  weight=%6d  sum=%6d  sumWeights=%6d", timediff, weight, sum, sumWeights);
	}
	// Normalize: divide weighted sum by sum of weights
//	return sum / (LIGHT_SENSOR_HIST_SIZE * (LIGHT_SENSOR_HIST_SIZE+1) * (2*LIGHT_SENSOR_HIST_SIZE+1) / 6);
//	LOGi(0, "sum=%6d sumWeights=%6d", sum, sumWeights);
	return sum / sumWeights;
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
