/**
 * 456789------------------------------------------------------------------------------------------------------------120
 *
 * @brief 
 * @file Sensor.h
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

#ifndef SENSOR_H_
#define SENSOR_H_

void initSensors();
void readSensors();
int readBatteryState();

void sendSensorData();

#endif /* SENSOR_H_ */
