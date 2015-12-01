/**
 * 456789------------------------------------------------------------------------------------------------------------120
 *
 * @brief:
 * @file: ObstacleDetection.cpp
 *
 * @desc: 
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
 * Copyright (c) 2013 Dominik Egger <dominik@dobots.nl>
 *
 * @author:        Dominik Egger
 * @date:        Nov 20, 2015
 * @project:    PirateDotty
 * @company:     Distributed Organisms B.V.
 */

//-------------------------------------------------------------------
// INCLUDES
//-------------------------------------------------------------------
#include "ObstacleDetection.h"
#include "Sensor.h"

//-------------------------------------------------------------------
// CONFIG
//-------------------------------------------------------------------

//-------------------------------------------------------------------
// FUNCTIONS
//-------------------------------------------------------------------

// PUBLIC

bool isClose() {
	return getDistance() <= CLOSE_THRESHOLD;
}

bool isMidrange() {
	int distance = getDistance();
	return distance > CLOSE_THRESHOLD && distance <= FAR_THRESHOLD;
}

bool isFar() {
	return getDistance() > FAR_THRESHOLD;
}

bool obstacleDetected() {
	return getDistance() < OBSTACLE_DETECTION_THRESHOLD;
}

// PRIVATE

