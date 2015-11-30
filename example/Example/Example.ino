#include <Sensor.h>
#include <ObstacleDetection.h>
#include <Actuator.h>
#include <DriveControl.h>
#include <Pinout.h>
#include <Log.h>

// The maximum speed
#define SPEED_MAX 50

// Choose which serial port we will use
//#define SERIAL Serial // USB
#define SERIAL Serial2 // Bluetooth

// This variable will be the current maximum speed.
// Setting this to 0 will disable driving.
int maxSpeed = 0;

// This variable is used to store the current measurment of the raw light level value.
int rawLightVal;

// This variable is used to store a filtered light level value.
int lightVal;

// This variable is used to store the measured distance to an obstacle.
int distance;

// This variable will be used to remember the previously measured light level.
int previousLightVal = 0;




// Code to initialize everything
void setup() {
  // Initialize the debug logger
  SERIAL.begin(115200);
  initLogging(&SERIAL);
  
  // Initialize the motors
  initActuators();
  
  // Initialize the sensors
  initSensors();

  LOGi(0, "Initialized!");
}


// This is the main loop
// Code in the loop runs over and over again
void loop() {
  LOGi(0, "Start of loop");
  // Read out light and distance sensors, and print the result.
  // You can see what this function does at the bottom of this file.
  readAndPrintSensors();

  if (distance < 400) {
    // If the distance is low, there is an obstacle close
    LOGi(0, "Obstacle detected!");

    dealWithObstacle();
  }
  else {
    // No obstable, so let's drive
    randomDrive();
  }

  // Stop and wait some time, so we can better see what happens
  drive(0, 0);
  delay(1000);

  // This part checks if data was sent and reads it if so.
  readSerial();

  // Remember the light value, so we can compare it
  previousLightVal = lightVal;

  // Wait a little bit, so that the loop doesn't go too fast
  delay(100);
}


// Read out light and distance sensors, and print the result.
void readAndPrintSensors() {
  // Read out the raw value of the light sensor
  rawLightVal = readLightSensor();

  // Get a filtered value of the light sensor
  lightVal = getFilteredLightLevel();

  // Read out the distance sensor
  distance = getDistance();

  // Log (or print) all the sensor values
  LOGi(0, "distance: %4d    raw lightVal: %4d   filtered lightVal: %4d    previous lightVal: %4d", distance, rawLightVal, lightVal, previousLightVal);
}


// What to do when something is in front of the robot
void dealWithObstacle() {
  // Example: simly stop the robot.
  // Left motor and right moter should drive with speed 0
  drive(0, 0);
}


// Drive forward randomly
void randomDrive() {
  // Drive forward with a random turn

  // Left speed is randomly chosen between 0 and maxSpeed
  int leftSpeed = random(0, maxSpeed);
  int rightSpeed = maxSpeed - leftSpeed;
  LOGi(0, "drive %3d %3d", leftSpeed, rightSpeed);

  // Actually make the motors drive this speed for some time
  drive(leftSpeed, rightSpeed);
  delay(300);
}


// Reads serial and handles the data
void readSerial() {
  while (SERIAL.available() > 0) {
    // If so, we check what data was sent:
    // a "h" sets maxSpeed to 0, so that the robot stops driving
    // a "g" sets maxSpeed to SPEED_MAX, so that the robot starts driving
    int readByte = SERIAL.read();
    switch(readByte) {
      case 104: // h
      case 72:  // H
        maxSpeed = 0;
        LOGi(0, "Halting motors");
        break;
      case 103: // g
      case 71:  // G
        maxSpeed = SPEED_MAX;
        LOGi(0, "GO!");
        break;
    }
  }
}

