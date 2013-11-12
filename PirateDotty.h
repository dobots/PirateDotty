// Only modify this file to include
// - function definitions (prototypes)
// - include files
// - extern variable definitions
// In the appropriate section

#ifndef PirateDotty_H_
#define PirateDotty_H_
#include "Arduino.h"
//add your includes for the project PirateDotty here

#include "Pinout.h"
//#include "aJSON.h"
#include "Log.h"

//end of add your includes here
#ifdef __cplusplus
extern "C" {
#endif
void loop();
void setup();
#ifdef __cplusplus
} // extern "C"
#endif

//add your function definitions for the project PirateDotty here

#define INACTIVITY_TIMEOUT 60000 // 60 seconds

extern bool isRemoteControl;
extern long lastActivity;

//Do not add code below this line
#endif /* PirateDotty_H_ */
