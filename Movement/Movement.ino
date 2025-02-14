#include <ezButton.h>

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

// Function Declarations
void forward(int, int);
void back(int, int);
void stop();

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
  stop();
}

void loop(){
  y = analogRead(VRY);

  if (y - CENTER > DEADZONE){
    forward(forB, bacB);
  } else if (y - CENTER < -DEADZONE) {
    back(forB, bacB);
  } else{
    stop();
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

void stop() {
  digitalWrite(bacA, LOW);
  digitalWrite(bacA, LOW);
  digitalWrite(forB, LOW);
  digitalWrite(bacB, LOW);
}
