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

int enA = 5;
int in1 = 4;
int in2 = 2;

int enB = 3;
int in3 = 10;
int in4 = 9;

void setup() {
  Serial.begin(9600);
  delay(100);
  
  if(radio.begin()) {
    Serial.println("CONNECTED!");
  } else {
    Serial.println("Not connect Radio");
  };

  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

  radio.openReadingPipe(1, address);//the receiver gets designated as a receiver on the same address
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
};

void loop() {
  //Serial.println("Printing Works");
  //Serial.println(radio.available());
  if (radio.available()) {//checks if there is data that can be read
    int values[2];//can read up to 32 bytes
    radio.read(&values, sizeof(values));//takes the transmission and pastes into the variable
    Serial.print("L: ");
    Serial.print(values[0]);
    Serial.print("R: ");
    Serial.println(values[1]);
    
    move(values[0], in1, in2, enA); // Left
    move(values[1], in3, in4, enB); // Right
    
    } 
    delay(10);
  }