#include <Sensor.h>
#include <ObstacleDetection.h>
#include <Actuator.h>
#include <DriveControl.h>
#include <Pinout.h>
#include <Log.h>

void setup() {
  Serial2.begin(115200); // USB
  
  initLogging(&Serial2);
  
  // put your setup code here, to run once:
  initActuators();
  initSensors();
}

void loop() {
  // put your main code here, to run repeatedly:
  
  LOGi(0, "distance: %4d", getDistance());

  if (obstacleDetected()) {
//    drive(-100, -100);
    setDriveSpeeds(-100, -100);
  } else {
    setDriveSpeeds(100, 100);
//    drive(100, 100);
  }

//  driveControl();

  delay(100);
}
