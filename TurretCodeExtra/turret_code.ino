#include <Servo.h>
#define SERVO_PIN 9
#define LEFT_BUTTON 2
#define RIGHT_BUTTON 3

Servo turretServo;
int pos = 90; //start at 90°
void setup() {
  turretServo.attach(SERVO_PIN);
  //pending commands for joystick
  turretServo.write(pos);
  delay(500); //adjust later!
}

void turnLeft() {
  pos = max(0, pos - 5);
  turretServo.write(pos);
  delay(15);
}

void turnRight() {
  pos = min(180, pos + 5);
  turretServo.write(pos);
  delay(15);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (digitalRead(LEFT_BUTTON) == LOW) {
    turnLeft(); 
  }
  if (digitalRead(RIGHT_BUTTON) == LOW) {
    turnRight();
  }
  delay(100);

}
