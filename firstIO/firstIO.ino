void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

String a;

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("ARDUINO > Testing");
  Serial.println(a);
  if (Serial.read() != -1) {
    a = Serial.readStringUntil('\n');;
    Serial.println(a);
  }
  delay(1000);
}
