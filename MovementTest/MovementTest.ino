int Left1; // left motor forward pin
int Left2; // left motor backward pin
int Right1; // right motor forward pin
int Right2; // right motor backward pin

void setup(){

}

void ForwardRight() {
  digitalWrite(Right1, HIGH);
  digitalWrite(Right2, LOW);
}

void BackwardRight() {
  digitalWrite(Right1, LOW);
  digitalWrite(Right2, HIGH);
}

void ForwardLeft() {
  digitalWrite(Left1, LOW);
  digitalWrite(Left2, HIGH);
}

void BackwardLeft() {
  digitalWrite(Left1, HIGH);
  digitalWrite(Left2, LOW);
}

void stopMotors() {
  digitalWrite(Left1, LOW);
  digitalWrite(Left2, LOW);
  digitalWrite(Right1, LOW);
  digitalWrite(Right2, LOW);
}

void loop(){

}
