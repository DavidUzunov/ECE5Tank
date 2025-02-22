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
motorPin rightMot = { 6, 7, 8 }, leftMot = { 5, 4, 3 }; //Motor control pins

// Turrent Variables
bool turretMode;
// TurretZ for controlling the z direction
Servo turretZ; 
int zPin = 2; 
int turretZPos;
// TurretXY for controlling horizontal direction
Servo turretXY; 
int xyPin = 14; // Analog pin 0
int turretXYPos;


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
  turretZ.attach(zPin); // Attach servo motor to pin 2
  turretZPos = 0; // Start at pos 0
  turretZ.write(turretZPos); // Reset Turret Position
  turretXY.attach(xyPin); // Attach servo motor to pin A0
  turretXYPos = 0; // Start at pos 0
  turretXY.write(turretXYPos); // 
};

void loop() {

  if (radio.available()) {  //Checks if there is data that can be read
      radio.read(&testing, sizeof(testing)); //Reads in the joystick data
  }

  Serial.print("Button Left: ");
  Serial.print(testing.buttonLeft);
  Serial.print("\tButton Right: ");
  Serial.print(testing.buttonRight);
  Serial.print("\tTurret Mode: ");
  Serial.println(turretMode);


  if (testing.buttonRight){
    turretMode = !turretMode; // Toggles betweens the modes of the turret
  }

  if (!turretMode) {//Concept: two modes - mode 0 is tank controls, mode 1 is turret controls, pushing the button toggles between it
      // Moves the tracks
      move(testing.yLeft, leftMot);   // Left
      move(testing.yRight, rightMot);  // Right

  } else {
    // Moves the servo up
    if (testing.yRight > CENTER + DEADZONE){
      // Increments turret if you push the joystick up
      if (turretZPos < 180){
        turretZPos += 3;
      }
    } else if (testing.yRight < CENTER - DEADZONE){
      // Decrements turret pos if you push the joystick down
      if (turretZPos > 0){
        turretZPos -= 3;
      }
    }

    turretZ.write(turretZPos);

    /*//if (testing.buttonRight > CENTER + DEADZONE){
      // Moves to the right when right joystick pushed up
      if (turretXYPos < 180){}
        turretXYPos++;
      }
    } else (testing.buttonRight < CENTER - DEADZONE){
      // Moves to the left when left joystick down
      if (turretXYPos > 0){
        turretXYPos--;
      }
    }

    turretXY.write(turretXYPos;
    }*/
  }
  
  delay(10);
}