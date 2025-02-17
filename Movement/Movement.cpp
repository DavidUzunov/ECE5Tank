// Code for Movement Functions
// Written by Anthony Ma
#include"Movement.h"

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