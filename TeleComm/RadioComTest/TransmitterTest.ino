#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(7, 8); // CE, CSN pins
//creates the radio object

const byte address[6] = "00001";//same address as the receiver so they can communicate

void setup() {
  radio.begin();
  radio.openWritingPipe(address);//designates this as a transmitter
  radio.setPALevel(RF24_PA_MIN);//power amplifier level - set based on distance between Tx and Rx components
  //change above min for sure in our case
  radio.stopListening();//stops it from listening which designates it as transmitter
}

void loop() {
  const char text[] = "Hello World";//test transmission
  radio.write(&text, sizeof(text));//sends the transmission up to 32 bytes at a time
  delay(1000);
}
