#include <ezButton.h>
#include "Movement.h"

// Motor A
int enA = 9;
int bacA = 8;
int forA = 7;

// Motor B
int enB = 3;
int bacB = 4;
int forB = 5;

// Joystick Pins
int VRY; //analog output in the y direction from the joystick
int SW=2;     //joystick button output
int CENTER = 512;
int DEADZONE = 50;
//pins: A1,A2,12
int y,s;
ezButton button(SW);

// Speed Variables
#define MIN_SPEED 100
#define MAX_SPEED 255

void setup(){
  // Set Up Motor Pins
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(forA, OUTPUT);
  pinMode(bacA, OUTPUT);
  pinMode(bacB, OUTPUT);
  pinMode(forB, OUTPUT);

  // Set up Joystick Pins
  button.setDebounceTime(50);
  VRY=A1;//analog pins
  pinMode(VRY, INPUT);
  pinMode(SW, INPUT);

  // Turn Motors Off
  stop(forA, bacA);
}

void loop(){
  y = analogRead(VRY);
  if (y > CENTER + DEADZONE){
    forward(forB, bacB);
    int speed = map(y, CENTER + DEADZONE, 1023, MIN_SPEED, MAX_SPEED);
    analogWrite(enB, speed);

  } else if (y < CENTER - DEADZONE) {
    back(forB, bacB);
    int speed = map(y, CENTER - DEADZONE, 0, MIN_SPEED, MAX_SPEED);
    analogWrite(enB, speed);

  } else{
    stop(forB, bacB);
  } 
}
