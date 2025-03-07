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
} inputs;

// Transceiver Variables
RF24 radio(10, 9);  // CE, CSN pins
const byte address[6] = "00001";  //match address byte on transmitter and receiver

// Motor Objects
motorPin rightMot = { 6, 7, 8 }, leftMot = { 5, 4, 3 }; //Motor control pins

// Turrent Variables
bool turretMode;

// TurretZ for controlling the z direction
Servo turretZ; 
const int zPin = 2; 
int turretZPos;

// TurretXY for controlling horizontal direction
Servo turretXY; 
const int xyPin = 14; // Analog pin 0
int turretXYPos;

const int laserPin = 16;
int timeTurretMove = 0;


void setup() {
  Serial.begin(9600);

  delay(100);

  // Initializes the radio
  if (radio.begin()) {
    Serial.println("Radio Connected");
  } else {
    Serial.println("Failed to connect to radio :(");
  };

  // 

  // Opens pipes for reading in transmissions
  radio.openReadingPipe(1, address);  //the receiver gets designated as a receiver on the same address
  radio.setChannel(100);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();

  // Initialize motor pins
  init(rightMot);
  init(leftMot);

  // Initialize servo pin(s)
  turretMode = false;
  turretZ.attach(zPin); // Attach servo motor to pin 2
  turretZPos = 90; // Start at pos 90
  turretZ.write(turretZPos); // Reset Turret Position
  turretXY.attach(xyPin); // Attach servo motor to pin A0
  turretXYPos = 90; // Start at pos 0
  turretXY.write(turretXYPos); // 

  pinMode(laserPin, OUTPUT);
};

void loop() {

  if (radio.available()) {  //Checks if there is data that can be read
      radio.read(&inputs, sizeof(inputs)); //Reads in the joystick data
  }

  /*Serial.print("yRight: ");
  Serial.print(inputs.yRight);
  Serial.print("\tyLeft: ");
  Serial.println(inputs.yLeft);
  Serial.print("Turret Mode: ");
  Serial.println(turretMode);*/

  if (inputs.buttonRight){
    turretMode = !turretMode; // Toggles betweens the modes of the turret
  }

  if (inputs.buttonLeft){
    digitalWrite(laserPin, HIGH);
  } else{
    digitalWrite(laserPin, LOW);
  }

  if (!turretMode) {//Concept: two modes - mode 0 is tank controls, mode 1 is turret controls, pushing the button toggles between it
      // Moves the tracks
      move(inputs.yLeft, leftMot);   // Left
      move(inputs.yRight, rightMot);  // Right

  } else {
    // Create delay for the turret
    int currentTime = millis();
    if (currentTime - timeTurretMove > 100){
      timeTurretMove = currentTime;

      // Moves the servo up
      if (inputs.yRight > CENTER + DEADZONE){
        // Increments turret if you push the joystick up
        if (turretZPos < 160){
          turretZPos += 3;
        }
      } else if (inputs.yRight < CENTER - DEADZONE){
        // Decrements turret pos if you push the joystick down
        if (turretZPos > 45){
          turretZPos -= 3;
        }
      }

      if (inputs.yLeft > CENTER + DEADZONE){
        // Moves to the right when right joystick pushed up
        if (turretXYPos < 180){
          turretXYPos += 2;
        }
      } else if (inputs.yLeft < CENTER - DEADZONE){
        // Moves to the left when left joystick down
        if (turretXYPos > 0){
          turretXYPos -= 2;
        }
      }

      turretXY.write(turretXYPos);
      turretZ.write(turretZPos);
    }

  }
  
  delay(10);
}