/**
 * 456789------------------------------------------------------------------------------------------------------------120
 *
 * @brief:
 * @file: ObstacleDetection.h
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

#pragma once

//-------------------------------------------------------------------
// INCLUDES
//-------------------------------------------------------------------

//-------------------------------------------------------------------
// CONFIG
//-------------------------------------------------------------------

#define CLOSE_THRESHOLD 300
#define FAR_THRESHOLD 800
#define OBSTACLE_DETECTION_THRESHOLD 900

//-------------------------------------------------------------------
// FUNCTIONS
//-------------------------------------------------------------------

bool isClose();
bool isMidrange();
bool isFar();
bool obstacleDetected();
