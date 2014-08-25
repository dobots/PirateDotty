/**
 * 456789------------------------------------------------------------------------------------------------------------120
 *
 * @brief:
 * @file: IRHandler.h
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

#ifndef IRHANDLER_H_
#define IRHANDLER_H_

#include "PirateDotty.h"
#include "Pinout.h"
#include "IRremote.h"
#include "Log.h"

// how often the ir recevier is checked per second
#define IR_FREQ 5 // hz

class IRHandler {
public:

	static int loop();
	static IRHandler* getInstance();

	unsigned long getResult();
	bool hasNewResult();
	void clearResult();

	void initialize();

	void send(unsigned int* code, int length);

#ifdef BT_APP
	void sendIRData();
#endif

	int mLastSignal;

private:
	IRHandler();

	bool receive();

	IRsend mIRSender;
	IRrecv mIRReceiver;
	decode_results mLastResult;
	bool mNewResult;

	bool mInitialized;

};

extern IRHandler IR_HANDLER;

#endif /* IRHANDLER_H_ */
