int led = 3;
int brightness = 50;
int fadeAmount = 10;

void setup(){
  pinMode(led, OUTPUT);
}

void loop(){
  analogWrite(led, brightness);
  brightness = brightness + fadeAmount;

  delay(300);
}
