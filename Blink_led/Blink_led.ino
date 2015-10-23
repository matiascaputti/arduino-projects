int led1 = 31;
int led2 = 32;
int led3 = 33;

void setup(){
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
}

void loop(){
  analogWrite(led1, 255);
  analogWrite(led2, 255);
  analogWrite(led3, 255);
}
