int led1 = 9;
int led2 = 10;
int led3 = 3;

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
