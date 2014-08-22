/**
 * 456789------------------------------------------------------------------------------------------------------------120
 *
 * @brief:
 * @file: IRHandler.cpp
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

#include "IRHandler.h"
#include "Log.h"

IRHandler IR_HANDLER;

IRHandler IRHandler::getInstance() {
	return IR_HANDLER;
}

void IRHandler::loop() {

	if (millis() >= IR_HANDLER.mLastSignal + WAIT_PERIOD) {
		IR_HANDLER.receive();
	}
}

bool IRHandler::receive() {
	if (!mInitialized) {
		return false;
	}

	decode_results irResult;
	mNewResult = mIRReceiver.decode(&irResult);

	if (mNewResult) {
		mLastResult = irResult;
		LOGd(1, "\t[%d] signal recvd: %d", millis(), irResult.value);
		mIRReceiver.resume();
		mLastSignal = millis();
	} else {
//		LOGd(1, "\t[%d] no signal", millis());
	}
	return mNewResult;
}

unsigned long IRHandler::getResult() {
	if (!mInitialized) {
		return 0;
	}

	return mLastResult.value;
}

bool IRHandler::hasNewResult() {
	return mNewResult;
}

void IRHandler::initialize() {
	mIRReceiver.enableIRIn(); // Start the receiver
	mInitialized = true;
}

void IRHandler::send(unsigned int *code, int length) {

	for (int i = 0; i < 10; i++) {
		mIRSender.sendRaw(code, length, 38);
		delay(40);
	}

	// enable receiver again
	mIRReceiver.enableIRIn();
}


