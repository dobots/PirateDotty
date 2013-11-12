/*
 * RandomWalk.h
 *
 *  Created on: Nov 7, 2013
 *      Author: dominik
 */

#ifndef RANDOMWALK_H_
#define RANDOMWALK_H_

void initRandomWalk();
void randomWalk();

void moveForward(long duration);
void moveLeftForward(long duration);
void moveRightForward(long duration);

void moveBackward(long duration);
void moveLeftBackward(long duration);
void moveRightBackward(long duration);

void rotateClockwise(long duration);
void rotateCounterClockwise(long duration);

#endif /* RANDOMWALK_H_ */
