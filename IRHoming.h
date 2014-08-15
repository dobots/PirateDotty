/**
 * 456789------------------------------------------------------------------------------------------------------------120
 *
 * @brief 
 * @file IRHoming.h
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
 * @date      Jan 22, 2014
 * @project   
 * @company   Almende B.V.
 * @company   Distributed Organisms B.V.
 * @case      
 */

#ifndef IRHOMING_H_
#define IRHOMING_H_

void initIRHoming();
void IRhomeWalk();
void enableHoming();
void disableHoming();
void moveForward(long duration);
void rotateCounterClockwise();
void rotateClockwise();

void sendIRData();
void sendNull();

void switchHoming();

#endif /* IRHOMING_H_ */