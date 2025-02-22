//Essential libraries
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include "Movement.h"
#include <Servo.h>  //used for turret servo motors

RF24 radio(7, 8);  // CE, CSN pins

Servo Turret1;  //Turret1 is the updown turret. If we Manage to get a second one setup, we'll add Turret2 for the second turret.
int LPin = 14;//digitizes analog pin A0

const byte address[6] = "00001";  //match address byte on transmitter and receiver

motorPin rightMot = { 5, 4, 2 }, leftMot = { 3, 10, 9 };

struct JoystickInput{
int Y1;
int Y2;
int button1;
int button2;
};

void setup() {
  Serial.begin(9600);

  // Initializes the radio
  if (radio.begin()) {
    Serial.println("CONNECTED!");
  } else {
    Serial.println("Failed to connect to radio (sad face)");
  };

  // Initializes the motor pins
  init(rightMot);
  init(leftMot);

  //initialize servo pin(s)
  Turret1.attach(6);  //6 is the final free pin I could see on the Rx side
  // Opens pipes for reading in transmissions
  radio.openReadingPipe(1, address);  //the receiver gets designated as a receiver on the same address
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
};

void loop() {
  JoystickInput Testing;
  if (Testing.button1 == 0) {//Concept: two modes - mode 0 is tank controls, mode 1 is turret controls, pushing the button toggles between it
    if (radio.available()) {  //checks if there is data that can be read
      //Reads in the joystick positions
      radio.read(&Testing, sizeof(Testing));

      // Moves the tracks
      move(Testing.Y1, leftMot);   // Left
      move(Testing.Y2, rightMot);  // Right
    }
  } else {
    if (radio.available()) {  //checks if there is data that can be read
      //Reads in the joystick positions
      radio.read(&Testing, sizeof(Testing));

      // Moves the servo
      Turret1.write(Testing.Y1);
      //Turret2.write(Testing.Y2);//This line only exists if we have the pins for a second servo
      if(Testing.button2 == 1){
        digitalWrite(LPin, HIGH);
        delay(50);
        digitalWrite(LPin, LOW);
      }
    }
  }
  delay(10);
}