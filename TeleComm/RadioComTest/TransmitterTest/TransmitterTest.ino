//essential libraries
#include <ezButton.h>//used for the joystick button(used for toggling joystick modes)
//these 3 used for radio transmission
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>


// Joystick Pins
int VRY=A1; //analog output in the y direction from the joystick
int SW=9;  //joystick button output
//pins: A1,2
int y;//y data var
ezButton button(SW);


RF24 radio(8, 7); // CE, CSN pins
//creates the radio object

const byte address[6] = "00001";//same 5 char address as the receiver so they can communicate

void setup() {
  Serial.begin(9600);

  if(radio.begin()){
    Serial.println("Radio.begin Succeeded!");
  }
  else{
    Serial.println("not able to begin radio");
  }
  radio.openWritingPipe(address);//designates this as a transmitter
  radio.setPALevel(RF24_PA_MIN);//power amplifier level - set based on distance between Tx and Rx components
  //change above min for sure in our case
  radio.stopListening();//stops it from listening which designates it as transmitter
}

void loop() {//code for test
  int transmission;//test transmission with joystick data class
  y = analogRead(VRY);//only Y input is needed
  transmission = y;
  radio.write(&transmission, sizeof(transmission));//sends the transmission up to 32 bytes at a time
  if(digitalRead(SW)!=HIGH){//if the button is pressed, send a transmission for the button
    transmission = digitalRead(SW);
    Serial.println("Button Pressed!");
    radio.write(&transmission, sizeof(transmission));//sends the transmission up to 32 bytes at a time
  }
  delay(1000);
}


//real code
/*




//Motor stuff is for Rx code

// Motor A pins
int enA = 9;
int bacA = 8;
int forA = 7;

// Motor B pins
int enB = 3;
int bacB = 4;
int forB = 5;




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

  //set up RF transmission
  radio.begin();
  radio.openWritingPipe(address);//designates this as a transmitter
  radio.setPALevel(RF24_PA_MIN);//power amplifier level - set based on distance between Tx and Rx components
  //change above min for sure in our case
  radio.stopListening();//stops it from listening which designates it as transmitter

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

  radio.write(&joyPos, sizeof(joyPos));
}



//functions for Rx

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


*/