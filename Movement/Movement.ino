//Essential libraries
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include "Movement.h"
#include <Servo.h>  //used for turret servo motors

// Struct of Joystick data
struct JoystickInput{
  // Y levels
  int yLeft;
  int yRight;

  // Button states
  bool buttonLeft;
  bool buttonRight;
} testing;

// Transceiver Variables
RF24 radio(10, 9);  // CE, CSN pins
const byte address[6] = "00001";  //match address byte on transmitter and receiver

// Motor Objects
motorPin rightMot = { 5, 4, 2 }, leftMot = { 3, 10, 9 }; //Motor control pins

// Turrent Variables
bool turretMode;
Servo Turret1; //Turret1 is the updown turret. If we Manage to get a second one setup, we'll add Turret2 for the second turret.
int LPin = 14; //digitizes analog pin A0

void setup() {
  Serial.begin(9600);

  delay(100);
  // Initializes the radio
  if (radio.begin()) {
    Serial.println("Radio Connected");
  } else {
    Serial.println("Failed to connect to radio :(");
  };

  // Opens pipes for reading in transmissions
  radio.openReadingPipe(1, address);  //the receiver gets designated as a receiver on the same address
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();

  // Initialize motor pins
  init(rightMot);
  init(leftMot);

  // Initialize servo pin(s)
  turretMode = false;
  Turret1.attach(6);  //6 is the final free pin I could see on the digital side of the tank arduino
};

void loop() {

  if (radio.available()) {  //Checks if there is data that can be read
      radio.read(&testing, sizeof(testing)); //Reads in the joystick data
  }

  if (testing.buttonLeft){
    turretMode = !turretMode; // Toggles betweens the modes of the turret
  }

  if (!turretMode) {//Concept: two modes - mode 0 is tank controls, mode 1 is turret controls, pushing the button toggles between it
      // Moves the tracks
      move(testing.yLeft, leftMot);   // Left
      move(testing.yRight, rightMot);  // Right

  } else {
    // Moves the servo
    Turret1.write(testing.yLeft);

    //Turret2.write(Testing.Y2);//This line only exists if we have the pins for a second servo
/*    if(testing.buttonRight == 1){
      digitalWrite(LPin, HIGH);
      delay(50);
      digitalWrite(LPin, LOW);
    }*/
  }
  delay(10);
}