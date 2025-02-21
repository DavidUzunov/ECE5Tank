// Code for Movement Functions
// Written by Anthony Ma
#include"Movement.h"

void move(int value, int pin1, int pin2, int enablePin){
  if (value > CENTER + DEADZONE){
      forward(pin1, pin2);
      int speed = map(value, CENTER + DEADZONE, 1023, MIN_SPEED, MAX_SPEED);
      analogWrite(enablePin, speed);
  } else if (value < CENTER - DEADZONE){
      back(pin1, pin2);
      int speed = map(value, CENTER - DEADZONE, 0, MIN_SPEED, MAX_SPEED);
      analogWrite(enablePin, speed);
    } else{
      stop(pin1, pin2);
    }
}

void forward(int pin1, int pin2) {
    digitalWrite(pin1, HIGH);
    digitalWrite(pin2, LOW);
  }
  
  void back(int pin1, int pin2) {
    digitalWrite(pin1, LOW);
    digitalWrite(pin2, HIGH);
  }
  
  void stop(int pin1, int pin2) {
    digitalWrite(pin1, LOW);
    digitalWrite(pin2, LOW);
  }