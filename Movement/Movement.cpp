// Code for Movement Functions
// Written by Anthony Ma
#include"Movement.h"

void move(int value, motorPin mp){
  if (value > CENTER + DEADZONE){
      forward(mp);
      int speed = map(value, CENTER + DEADZONE, 1023, MIN_SPEED, MAX_SPEED);
      analogWrite(mp.enPin, speed);
  } else if (value < CENTER - DEADZONE){
      back(mp);
      int speed = map(value, CENTER - DEADZONE, 0, MIN_SPEED, MAX_SPEED);
      analogWrite(mp.enPin, speed);
    } else{
      stop(mp);
    }
}

void init(motorPin mp){
  pinMode(mp.enPin, OUTPUT);
  pinMode(mp.in1, OUTPUT);
  pinMode(mp.in2, OUTPUT);
}

void forward(motorPin mp) {
    digitalWrite(mp.in1, HIGH);
    digitalWrite(mp.in2, LOW);
  }
  
  void back(motorPin mp) {
    digitalWrite(mp.in1, LOW);
    digitalWrite(mp.in2, HIGH);
  }
  
  void stop(motorPin mp) {
    digitalWrite(mp.in1, LOW);
    digitalWrite(mp.in2, LOW);
  }