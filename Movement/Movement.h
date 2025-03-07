// Movement Header File
// Written by Anthony Ma

#include<Arduino.h>

// Speed Variables
#define MIN_SPEED 100
#define MAX_SPEED 255
#define CENTER 512
#define DEADZONE 100

// State Variables
#define OFF 0
#define TANK_MODE 1
#define TURRET_MODE 2

struct motorPin {
  int enPin;
  int in1;
  int in2;
};

// Controls the movement of the tracks
void move(int, motorPin);

// Initializes the pins
void init(motorPin);

// Takes in 2 integers representing the control pins of motor
// Sets the pins to make the motor turn forward
void forward(motorPin);

// Takes in 2 integers representing the control pins of motor
// Sets the pins to make the motor turn backward
void back(motorPin);

// Takes in 2 integers representing the control pins of motor
// Sets the pins to make the motor stop
void stop(motorPin);