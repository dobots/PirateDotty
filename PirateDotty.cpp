// Do not remove the include below
#include "PirateDotty.h"
#include "Actuator.h"
#include "Bluetooth.h"
#include "Log.h"
#include "RandomWalk.h"

bool isRemoteControl = false;
long lastActivity = 0;

//The setup function is called once at startup of the sketch
void setup()
{
	Serial1.begin(115200);
	Serial2.begin(115200);

	initActuators();
	initBluetooth(&Serial2);

	initRandomWalk();

	ledON(STATE_LED);

	LOGi(0, "initialisation done ...");
}

// The loop function is called in an endless loop
void loop()
{
	receiveCommands();

	if (millis() > (lastActivity + INACTIVITY_TIMEOUT)) {
		randomWalk();
	}

}
