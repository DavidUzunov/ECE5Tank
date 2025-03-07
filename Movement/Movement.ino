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
  int buttonRight;
} inputs;

// State Machine
int carState; // State of Car
unsigned int timeButtonPressed;
int timeElapsed;


// Transceiver Variables
RF24 radio(10, 9);  // CE, CSN pins
const byte address[6] = "00001";  //match address byte on transmitter and receiver

// Motor Objects
motorPin rightMot = { 6, 7, 8 }, leftMot = { 5, 4, 3 }; //Motor control pins

// Turrent Variables
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
  while(!Serial);

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
  turretZ.attach(zPin); // Attach servo motor to pin 2
  turretZPos = 90; // Start at pos 90
  turretZ.write(turretZPos); // Reset Turret Position
  turretXY.attach(xyPin); // Attach servo motor to pin A0
  turretXYPos = 90; // Start at pos 0
  turretXY.write(turretXYPos);

  // State of Car
  carState = OFF;
};

void loop() {

  if (radio.available()) {  //Checks if there is data that can be read
      radio.read(&inputs, sizeof(inputs)); //Reads in the joystick data
  }

  /*Serial.print("Y Right: ");
  Serial.print(testing.yRight);
  Serial.print("\tY Left: ");
  Serial.print(testing.yLeft);
  Serial.print("\tButton Right: ");
  Serial.print(testing.buttonRight);
  Serial.print("\tTurret Mode: ");
  Serial.println(turretMode);*/

  // The button switched state
  if (inputs.buttonRight == 1){
    timeButtonPressed = millis(); // Start Recording time
  } else if (inputs.buttonRight == 2) { // Button is already pressed

      // Record the time elapsed
      timeElapsed = millis() - timeButtonPressed;

      // Different actions depending on state of the machine
    switch (carState){

      case OFF: // Off mode
        if (timeElapsed > 2000){ // If more than 2 secs passed, turn car on
          carState = TANK_MODE;
        }
        break;
    
      case TANK_MODE:
        if (timeElapsed > 5000){
          carState = OFF;
        } else{
          carState = TURRET_MODE;
        }
        break;

      case TURRET_MODE:
        if (timeElapsed > 5000){
          carState = OFF;
        } else{
          carState = TANK_MODE;
        }
        break;
    }

    
  }

  switch (carState){
    
    case TANK_MODE:
      // Moves the tracks
      move(inputs.yLeft, leftMot);   // Left
      move(inputs.yRight, rightMot);  // Right
      break;

    case TURRET_MODE:
      // Moves the servo up
      if (inputs.yRight > CENTER + DEADZONE){
        // Increments turret if you push the joystick up
        if (turretZPos < 160){
          turretZPos += 3;
        }
      } else if (inputs.yRight < CENTER - DEADZONE){
        // Decrements turret pos if you push the joystick down
        if (turretZPos > 70){
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

      break;

  }

  /*Serial.print("State: ");
  Serial.print(carState);
  Serial.print("\t Right Button: ");
  Serial.println(inputs.buttonRight);*/
  delay(10);

}