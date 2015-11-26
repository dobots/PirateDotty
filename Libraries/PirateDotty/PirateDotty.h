// Only modify this file to include
// - function definitions (prototypes)
// - include files
// - extern variable definitions
// In the appropriate section

#ifndef PirateDotty_H_
#define PirateDotty_H_
#include "Arduino.h"
//add your includes for the project PirateDotty here

#include "Debug.h"
#include "Pinout.h"
#include "Log.h"

//add your function definitions for the project PirateDotty here

#define INACTIVITY_TIMEOUT 60000 // 60 seconds
#define INACTIVITY_TIMEOUT2 300000 // 300 seconds

extern bool isRemoteControl;
extern long lastActivity;

void initDotty();
void loopDotty();


//Do not add code below this line
#endif /* PirateDotty_H_ */
