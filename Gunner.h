/**
 * 456789------------------------------------------------------------------------------------------------------------120
 *
 * @brief:
 * @file: Gun.h
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
 * @date:        Aug 21, 2014
 * @project:    PirateDotty
 * @company:     Distributed Organisms B.V.
 */

#ifndef GUNNER_H_
#define GUNNER_H_

#define IR_GUN_SHOT 632192736

// for a hit to be detected, 3 shots signals need to be detected within HIT_TIMOUT
// shot count will be reset HIT_TIMEOUT seconds after the last detected shot
#define HIT_TIMEOUT 1000 // ms

// delay next gun shot. guns can only be shot every ... seconds (need time to reload!)
//#define SHOOT_DELAY 2000 //ms
#define RAGE_DURATION 10000 // ms
#define MIN_SPEED 100
#define MAX_SPEED 255
#define MIN_SPEED_RANGE -MAX_SPEED+MIN_SPEED
#define MAX_SPEED_RANGE MAX_SPEED-MIN_SPEED
#define MAX_SPEED_CHANGE 10

// detect shots every ... seconds
#define GUNNER_FREQ 5 // HZ

extern bool continuous;

void gunner_init();

int gunner_loop();

void shootGuns();
void setContinuous(bool value);
void fireVolley();

void sendHitDetected();

#endif /* GUN_H_ */
