// Movement Header File
// Written by Anthony Ma

#include<Arduino.h>

// Speed Variables
#define MIN_SPEED 100
#define MAX_SPEED 255
#define CENTER 512
#define DEADZONE 50


void move(int value, int pin1, int pin2, int enablePin);

// Takes in 2 integers representing the control pins of motor
// Sets the pins to make the motor turn forward
void forward(int, int);

// Takes in 2 integers representing the control pins of motor
// Sets the pins to make the motor turn backward
void back(int, int);

// Takes in 2 integers representing the control pins of motor
// Sets the pins to make the motor stop
void stop(int , int);