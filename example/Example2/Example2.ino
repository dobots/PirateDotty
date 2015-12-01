#include <Sensor.h>
#include <ObstacleDetection.h>
#include <Actuator.h>
#include <Pinout.h>
#include <Log.h>

// The maximum speed of the motors
#define SPEED_MAX 70

// Choose which serial port we will use
//#define SERIAL Serial // USB
#define SERIAL Serial2 // Bluetooth

// This variable will be the current maximum speed.
// Setting this to 0 will make the robot stop driving.
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
    // No obstable, so let's search for the light
    searchLight();
  }

  // Set speed to 0 and pause the program for 1000ms (1 second), so we can better see what happens
  setMotorSpeed(0, 0);
  delay(1000);

  // This part checks if data was sent and reads it if so.
  readSerial();

  // Remember the light value, so we can compare it
  previousLightVal = lightVal;

  // Pause the program for a short while, so that the loop doesn't go too fast
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
  // Left motor and right moter speed should be 0
  setMotorSpeed(0, 0);
}


// Should drive towards the light
void searchLight() {
    // Example: we simply turn randomly and drive straight afterwards
    int leftSpeed;
    int rightSpeed;

    // Get a 1 or 0 at random:
    int direction = random(0, 1);

    // The random variable "direction" determines if we turn left or right
    if (direction == 1) {
      // Turn right
      leftSpeed  = SPEED_MAX;
      rightSpeed = -SPEED_MAX;
    }
    else {
      // Turn left
      leftSpeed  = -SPEED_MAX;
      rightSpeed = SPEED_MAX;
    }

    // Actually set the motor speeds
    setMotorSpeed(leftSpeed, rightSpeed);
    
    // Pause the program for 250 ms to 500 ms to let the robot turn for some time
    int driveTime = random(250, 500);
    delay(driveTime);

    // Read and print sensors again
    LOGi(0, "After turning");
    readAndPrintSensors();
    
    // Set speed to 0 and pause the program for 1000ms (1 second), so we can better see what happens
    setMotorSpeed(0, 0);
    delay(1000);
    
    // After turning: drive straight for 300ms
    if (lightVal < previousLightVal) {
      // If the current light value is lower than the previous: drive backwards
      setMotorSpeed(-SPEED_MAX, -SPEED_MAX);
    }
    else {
      // If the current light value is larger or equal: drive forwards
      setMotorSpeed(SPEED_MAX, SPEED_MAX);
    }
    // Pause the program for 300ms (0.3 seconds) to let the robot drive for some time
    delay(300);
}


////////////////////////////////////////////////
// You don't have to read the functions below //
////////////////////////////////////////////////

// Set the speed of the motors, while making sure they don't go faster than maxSpeed
void setMotorSpeed(int leftSpeed, int rightSpeed) {
  if (leftSpeed > 0) {
    leftSpeed = min(leftSpeed, maxSpeed);
  }
  else {
    leftSpeed = max(leftSpeed, -maxSpeed);
  }
  if (rightSpeed > 0) {
    rightSpeed = min(rightSpeed, maxSpeed);
  }
  else {
    rightSpeed = max(rightSpeed, -maxSpeed);
  }
  drive(leftSpeed, rightSpeed);
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

