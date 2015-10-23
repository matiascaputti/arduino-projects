
int red = 13;

void setup() {
  // put your setup code here, to run once:
  pinMode(red, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  analogWrite(red, 0);
  delay(500);
  analogWrite(red, 255);
  delay(500);
}
