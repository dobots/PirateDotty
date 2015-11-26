#include "PirateDotty.h"

#include "Actuator.h"
#include "Bluetooth.h"
#include "Sensor.h"
#include "Looper.h"
#include "ObstacleDetection.h"
#include "DriveControl.h"
#include "RandomWalk.h"

bool isRemoteControl = true;
long lastActivity = 0;

bool homing=true;
bool randoming=false;
bool dismount = false;

int readLight() {

	int valueLightSensor2 = analogRead(LIGHT_SENSOR);

	LOGi(0, "light: %4d", valueLightSensor2);

	return 500;
}

bool close = false;
bool far = false;
bool midrange = false;

int checkDistance() {

	LOGi(0, "distance: %4d", getDistance());

	if (obstacleDetected()) {
		if (isClose() && !close) {
			close = true;
			far = false;
			midrange = false;
			LOGd(0, "CLOSE!!!");
		} else if (isFar() && !far) {
			far = true;
			close = false;
			midrange = false;
			LOGd(0, "FAR AWAY");
		} else if (isMidrange() && !midrange) {
			far = false;
			close = false;
			midrange = true;
			LOGd(0, "GOING MIDRANGE");
		}
	} else if (close || far || midrange) {
		close = far = midrange = false;
		LOGd(0, "GONE");
	}

	return 500;
}

void initLoopers() {
	// read bluetooth
	Looper::registerLoopFunc(receiveCommands);
	// handle drive commands
	Looper::registerLoopFunc(driveControl);

	Looper::registerLoopFunc(readLight);
	Looper::registerLoopFunc(checkDistance);

//	// gunner
//	Looper::registerLoopFunc(gunner_loop);
//	// ir handler
//	Looper::registerLoopFunc(IRHandler::loop);
}

//The setup function is called once at startup of the sketch
void initDotty()
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

	ledON(STATE_LED);

//	pinMode(A14,INPUT);

//	for(int i=0;i<23;i++){
//		pinMode(UNUSED[i],OUTPUT);
//	}

	initLoopers();

	LOGi(0, "\n\n\n\n\ninitialisation done ...");
	LOGi(0, "hello");
}

// The loop function is called in an endless loop
void loopDotty()
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
