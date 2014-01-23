/*
 * RandomWalk.cpp
 *
 *  Created on: Nov 7, 2013
 *      Author: dominik
 */

#include "PirateDotty.h"
#include "RandomWalk.h"
#include "Actuator.h"

unsigned long lastMove;

int DEFAULT_SPEED = 255;
int RADIUS_OFFSET = 55;

void initRandomWalk() {
	randomSeed(1);
//	randomSeed(analogRead(0));
}

int nextMoveTime = 0;

void randomWalk() {

	if (millis() > nextMoveTime) {
		LOGd(1, "randomWalk..");

		int move = random(1, 8);
		int duration = random(1, 4);

		LOGd(3, "move: %d, duration: %d", move, duration);

		switch(move) {
		case 1:
			moveForward(duration);
			break;
		case 2:
			moveLeftForward(duration);
			break;
		case 3:
			moveRightForward(duration);
			break;
		case 4:
			moveBackward(duration);
			break;
		case 5:
			moveLeftBackward(duration);
			break;
		case 6:
			moveRightBackward(duration);
			break;
		case 7:
			rotateClockwise(duration);
			break;
		case 8:
			rotateCounterClockwise(duration);
			break;
		}

		nextMoveTime = millis() + duration * 1000;
	}
}


void moveForward(long duration) {
	LOGd(1, "moveForward, %d s", duration);
	drive(DEFAULT_SPEED, DEFAULT_SPEED);
}

void moveLeftForward(long duration) {
	LOGd(1, "moveLeftForward, %d s", duration);
	drive(DEFAULT_SPEED - RADIUS_OFFSET, DEFAULT_SPEED);
}

void moveRightForward(long duration) {
	LOGd(1, "moveRightForward, %d s", duration);
	drive(DEFAULT_SPEED, DEFAULT_SPEED - RADIUS_OFFSET);
}


void moveBackward(long duration) {
	LOGd(1, "moveBackward, %d s", duration);
	drive(-DEFAULT_SPEED, -DEFAULT_SPEED);
}

void moveLeftBackward(long duration) {
	LOGd(1, "moveLeftBackward, %d s", duration);
	drive(-(DEFAULT_SPEED - RADIUS_OFFSET), -DEFAULT_SPEED);
}

void moveRightBackward(long duration) {
	LOGd(1, "moveRightBackward, %d s", duration);
	drive(-DEFAULT_SPEED, -(DEFAULT_SPEED - RADIUS_OFFSET));
}


void rotateClockwise(long duration) {
	LOGd(1, "rotateClockwise, %d s", duration);
	drive(DEFAULT_SPEED, -DEFAULT_SPEED);
}

void rotateCounterClockwise(long duration) {
	LOGd(1, "rotateCounterClockwise, %d s", duration);
	drive(-DEFAULT_SPEED, DEFAULT_SPEED);
}
