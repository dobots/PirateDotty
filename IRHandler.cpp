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

#include "protocol.h"
#include "IRHandler.h"
#include "Log.h"
#include "Looper.h"

IRHandler* IR_HANDLER_INSTANCE = NULL;

IRHandler::IRHandler() :
		mIRReceiver(IRRECEIVER), mInitialized(false), mNewResult(false), mLastSignal(0)
{
};

IRHandler* IRHandler::getInstance() {
	if (IR_HANDLER_INSTANCE == NULL) {
		IR_HANDLER_INSTANCE = new IRHandler();
	}

	return IR_HANDLER_INSTANCE;
}

int IRHandler::loop() {

	IRHandler::getInstance()->receive();

	return 1000 / IR_FREQ;
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
		// resume receiver, has to be done after every successful reception
		mIRReceiver.resume();
		mLastSignal = millis();

	} else {
		mLastResult.value = 0;
//		LOGd(1, "\t[%d] no signal", millis());
	}

#ifdef BT_APP
//	if (mNewResult) {
	sendIRData();
//	} else {
//		sendIRData(0);
//	}
#endif

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

void IRHandler::clearResult() {
	mNewResult = false;
}

void IRHandler::initialize() {
	Looper::registerLoopFunc(IRHandler::loop);
	mIRReceiver.enableIRIn(); // Start the receiver
	mInitialized = true;
}

void IRHandler::send(unsigned int *code, int length) {

	for (int i = 0; i < 10; i++) {
		mIRSender.sendRaw(code, length, 38);
		delay(40);
	}

	// enable receiver again, has to be done after every send
	mIRReceiver.enableIRIn();
}

#ifdef BT_APP
void IRHandler::sendIRData() {
	aJsonObject * IRData;
    IRData = createSensorData();
    addSensorValue(IRData, "IR command received", (long int)mLastResult.value);
    sendMessage(IRData);
}
#endif


