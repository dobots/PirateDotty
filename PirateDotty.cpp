#include "PirateDotty.h"

#include "Actuator.h"
#include "Bluetooth.h"
#include "IRHoming.h"
#include "Log.h"
#include "Pinout.h"
#include "RandomWalk.h"
#include "Sensor.h"
#include "IRHandler.h"
#include "Gunner.h"
#include "Looper.h"

bool isRemoteControl = true;
long lastActivity = 0;

bool homing=true;
bool randoming=false;
bool dismount = false;

//The setup function is called once at startup of the sketch
void setup()
{
	Serial.begin(115200); // USB
//	Serial1.begin(115200);
	Serial2.begin(115200);	// Bluetooth

#ifdef BT_SERIAL
	initLogging(&Serial2);
#else
	initLogging(&Serial);
#endif

	initBluetooth(&Serial2);

	initSensors();
	initActuators();
	initRandomWalk();

	IRHandler::getInstance()->initialize();

	initIRHoming();
	gunner_init();

	ledON(STATE_LED);

//	pinMode(A14,INPUT);

//	for(int i=0;i<23;i++){
//		pinMode(UNUSED[i],OUTPUT);
//	}

	LOGi(0, "\n\n\n\n\ninitialisation done ...");
}

// The loop function is called in an endless loop
void loop()
{
	// don't disable this, currently handles:
	// - receiveCommands()
	// - IRHandler::loop()
	// - gunner_loop();
	Looper::loop();

//	readBatteryState();


//	IRHandler::loop();
//	gunner_loop();


//	IRhomeWalk();
//	drive(255,255);
//	int spd = 20;
//	drive(spd,spd);



	/*
	int value = analogRead(A14);
	if(homing && value>800){
		homing=false;
		dostop();
		lastActivity = millis();
	}
//	if(value<100){
//		homing=true;
//	}
//	Serial.println(value);

	if(homing){
		IRhomeWalk();
	} else if(randoming){
		randomWalk();
	} else if(dismount){
		drive(-100,-100);
		delay(4000);
		dostop();
		dismount=false;
		homing=false;
		randoming=true;
		lastActivity=millis();
	}

	if(!homing && millis()>(lastActivity + INACTIVITY_TIMEOUT)){ //1 minute on charger
		dismount=true;
		homing=false;
		randoming=false;
	} else if(randoming && millis()>(lastActivity + INACTIVITY_TIMEOUT2)){ // 5 minutes driving
		randoming=false;
		dismount=false;
		homing=true;
	}

//	receiveCommands();

//	if (millis() > (lastActivity + INACTIVITY_TIMEOUT)) {
//		randomWalk();
////		IRhomeWalk();
//	}

//	readSensors();
	*/
//	receiveCommands();
}
