int led = 9;
int brightness = 50;
int fadeAmount = 1;

void setup(){
  pinMode(led, OUTPUT);
}

void loop(){
  analogWrite(led, brightness);
  brightness = brightness + fadeAmount;

  delay(10);
}
