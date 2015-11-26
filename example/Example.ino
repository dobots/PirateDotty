#include <Sensor.h>
#include <ObstacleDetection.h>
#include <Actuator.h>
#include <DriveControl.h>
#include <Pinout.h>
#include <Log.h>

void setup() {
//  Serial.begin(115200); // USB
  Serial2.begin(115200); // Bluetooth
  
  // change to Serial for logging over USB
  initLogging(&Serial2);
  
  // put your setup code here, to run once:
  initActuators();
  initSensors();
}

void loop() {
  // put your main code here, to run repeatedly:

  int distance = getDistance();
  LOGi(0, "distance: %4d", distance);

  if (distance < 800) {
//    drive(0, 0);
//    setDriveSpeeds(0, 0);
  } else {
//    drive(100, 100);
//    setDriveSpeeds(100, 100);
  }

//  driveControl();

  delay(100);
}
