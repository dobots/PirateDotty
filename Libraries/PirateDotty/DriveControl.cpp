/**
 * 456789------------------------------------------------------------------------------------------------------------120
 *
 * @brief:
 * @file: DriveControl.cpp
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

#include "DriveControl.h"
#include "Actuator.h"

//-------------------------------------------------------------------
// CONFIG
//-------------------------------------------------------------------

int leftSpeedSetpoint;
int rightSpeedSetpoint;

int curLeftSpeed = 0;
int curRightSpeed = 0;

//-------------------------------------------------------------------
// FUNCTIONS
//-------------------------------------------------------------------

// PRIVATE

#define sgn(x) ((x < 0 )? (-1) : (1))

void setDriveSpeeds(int leftSpeed, int rightSpeed) {
	leftSpeedSetpoint = leftSpeed;
	rightSpeedSetpoint = rightSpeed;
	if (leftSpeed == 0 && rightSpeed == 0) {
		curLeftSpeed = 0;
		curRightSpeed = 0;
	}
}

// PUBLIC

int driveControl() {

	// So far so good, move proportionally closer to desired speed
#ifdef RAMPING
	int diffRightSpeed = rightSpeedSetpoint - curRightSpeed;
	curRightSpeed += sgn(diffRightSpeed) * min(abs(diffRightSpeed), RAMPING_STEP);
#else
	// [19.11.14] no more ramping necessary with new hardware
	curRightSpeed = rightSpeedSetpoint;
#endif

#ifdef RAMPING
	int diffLeftSpeed = leftSpeedSetpoint - curLeftSpeed;
	curLeftSpeed += sgn(diffLeftSpeed) * min(abs(diffLeftSpeed), RAMPING_STEP);
#else
	// [19.11.14] no more ramping necessary with new hardware
	curLeftSpeed = leftSpeedSetpoint;
#endif

	drive(curLeftSpeed, curRightSpeed);

	return 100;
}

