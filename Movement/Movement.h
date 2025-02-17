// Movement Header File
// Written by Anthony Ma

#include<Arduino.h>
// Takes in 2 integers representing the control pins of motor
// Sets the pins to make the motor turn forward
void forward(int, int);

// Takes in 2 integers representing the control pins of motor
// Sets the pins to make the motor turn backward
void back(int, int);

// Takes in 2 integers representing the control pins of motor
// Sets the pins to make the motor stop
void stop(int , int);