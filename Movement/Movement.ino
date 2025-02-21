//Essential libraries
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include "Movement.h"


RF24 radio(7, 8); // CE, CSN pins

const byte address[6] = "00001";//match address byte on transmitter and receiver

struct JoystickData { //same construction for joystick as receiver
  int x;
  int y;
};

motorPin rightMot = {5, 4, 2}, leftMot = {3, 10, 9};

void setup() {
  Serial.begin(9600);

  // Initializes the radio
  if(radio.begin()) {
    Serial.println("CONNECTED!");
  } else {
    Serial.println("Not connect Radio");
  };

  // Initializes the motor pins
  init(rightMot);
  init(leftMot);

  // Opens pipes for reading in transmissions
  radio.openReadingPipe(1, address);//the receiver gets designated as a receiver on the same address
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
};

void loop() {

  if (radio.available()) {//checks if there is data that can be read
    //Reads in the joystick positions
    int values[2];
    radio.read(&values, sizeof(values));
    
    // Moves the tracks
    move(values[0], leftMot); // Left
    move(values[1], rightMot); // Right
    
  }

  delay(10);

}