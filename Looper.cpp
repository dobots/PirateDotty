/**
 * 456789------------------------------------------------------------------------------------------------------------120
 *
 * @brief:
 * @file: ExecutionHandler.cpp
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
 * @date:        Aug 22, 2014
 * @project:    PirateDotty
 * @company:     Distributed Organisms B.V.
 */

#include "Looper.h"
#include "Arduino.h"
#include "Log.h"

Looper* INSTANCE;

Looper::Looper() :
		mTimeNow(0),
		last(NULL),
		first(NULL)
{}

Looper* Looper::getInstance() {
	if (INSTANCE == NULL) {
		INSTANCE = new Looper();
	}

	return INSTANCE;
}

void Looper::loop() {
	getInstance()->mTimeNow = millis();
	getInstance()->run();
}

void Looper::run() {

	// loop through all registered functions
	loopFunc* loop = first;
	while (loop != NULL) {
		// if next execution time
		if (loop->nextExecution < mTimeNow) {
			// call function, which returns the delay
			int delay = loop->cb();
			// update the next execution time
			loop->nextExecution = mTimeNow + delay;
		}
		loop = loop->nextLoopFunc;
	}
}

int Looper::now() {
	return getInstance()->mTimeNow;
}

void Looper::registerLoopFunc(loopFunc_t func, int delay) {

	loopFunc* loop = new loopFunc();
	loop->cb = func;
	loop->nextExecution = Looper::now();
	loop->nextLoopFunc = NULL;

	// if it's the first entry, set the first pointer to this entry
	if (getInstance()->first == NULL) {
		getInstance()->first = loop;
	}

	// if there was already an entry, update the next pointer of that
	// entry to this entry
	if (getInstance()->last != NULL) {
		getInstance()->last->nextLoopFunc = loop;
	}

	// update the last pointer to this entry
	getInstance()->last = loop;

}
