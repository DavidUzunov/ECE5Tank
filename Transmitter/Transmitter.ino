//essential libraries
#include <ezButton.h>  //used for the joystick button(used for toggling joystick modes)
//these 3 used for radio transmission
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>


// Joystick Pins
int VRY1 = A0;  //analog output in the y direction from the joystick for left track
int VRY2 = A1;  //analog output in the y direction from the joystick for the right track
int SW = 8;     //joystick button output
int SW2 = 7;

ezButton button(SW);
ezButton button2(SW2);
//bool press = true;  //button state tracking

//creates the radio object
RF24 radio(9, 10);  // CE, CSN pins
const byte address[6] = "00001";  //same 5 char address as the receiver so they can communicate
//int prevState;                    //used for button 1, checks if the previous state matches current state to toggle controller modes

struct SendData {
  int Y1;
  int Y2;
  bool Button1 = false;
  bool Button2 = false;
};

SendData Transmission;

void setup() {
  Serial.begin(9600);
  delay(100);
  if (radio.begin()) {
    Serial.println("Radio.begin Succeeded!");
  } else {
    Serial.println("not able to begin radio");
  }
  radio.openWritingPipe(address);  //designates this as a transmitter
  radio.setChannel(100);
  radio.setPALevel(RF24_PA_MIN);   //power amplifier level - set based on distance between Tx and Rx components
  //change above min for sure in our case
  radio.stopListening();  //stops it from listening which designates it as transmitter

  button.setDebounceTime(50);  // set debounce time to 50 milliseconds
  button2.setDebounceTime(50);
}

void loop() {                          //code for test
  button.loop();                       // MUST call the loop() function first
  button2.loop();                    
  
  // Takes in Y positions of joysticks
  Transmission.Y1 = analogRead(VRY1);  //only Y input is needed, takes in left track
  Transmission.Y2 = analogRead(VRY2);  //only Y input is needed, takes in for right track

  // Check button states
  if (!digitalRead(SW)) {
    //TODO: One issue with this line is that the button doesn't want to switch to 0 unless you briefly hold it
    Serial.println("Button Pressed");
    Transmission.Button1 = true;
  }
  if (button2.isPressed()){
    Serial.println("Button2 Pressed");
    Transmission.Button2 = true;           //right switch - shoot button
  }

  radio.write(&Transmission, sizeof(Transmission));  //sends the transmission up to 32 bytes at a time
  /*Serial.print("Y1: ");
  Serial.print(Transmission.Y1);
  Serial.print("\tY2: ");
  Serial.println(Transmission.Y2);*/
  
  Transmission.Button1 = false;
  Transmission.Button2 = false;
  delay(10);
}
