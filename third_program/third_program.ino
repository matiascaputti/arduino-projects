#include <limits.h>

int sensor1Pin = A0;    // select the input pin for the potentiometer
int led1Pin = 13;      // select the pin for the LED
int sensor1Value = 0;  // variable to store the value coming from the sensor

int sensor2Pin = A5;
int led2Pin = 7;
int sensor2Value = 0;

int sensor3Pin = A5;
int led3Pin = 7;
int sensor3Value = 0;

int sensor4Pin = A5;
int led4Pin = 7;
int sensor4Value = 0;

int sensor5Pin = A5;
int led4Pin = 7;
int sensor5Value = 0;

int sensor6Pin = A5;
int led4Pin = 7;
int sensor6Value = 0;

int sensor7Pin = A5;
int led4Pin = 7;
int sensor7Value = 0;

int cont = 1;
int puntaje = 0;
double values[7];

int i, iMax;
int maxValue=INT_MIN;

void setup() {
  // declare the ledPin as an OUTPUT:
  Serial.begin(115200);
  pinMode(led1Pin, OUTPUT);
  pinMode(led2Pin, OUTPUT);
  pinMode(led3Pin, OUTPUT);
  pinMode(led4Pin, OUTPUT);
  pinMode(led5Pin, OUTPUT);
  pinMode(led6Pin, OUTPUT);
  pinMode(led7Pin, OUTPUT);
  Serial.println("Insert coin...");
  Serial.println("Play!");
}

void action(int ledPin, int sensorValue) {
  //Serial.println(sensorValue);
  // turn the ledPin on
  if (sensorValue > 800) {
    Serial.println(sensorValue);
    //if (cont <= 3) {

      digitalWrite(ledPin, 1);
    //  Serial.print("Tiro: ");
    //  Serial.print(cont);
    //  Serial.print("... ");

      // que se vea el puntaje
    //  Serial.println(sensorValue);

      delay(500);
      digitalWrite(ledPin, LOW);
    //  cont++;
    //  puntaje = puntaje + sensorValue;
    //}
  }

   //if (cont == 4 ) {
   //   Serial.println();
   //   Serial.println("FIN DEL JUEGO....... tu puntaje fue.....");
   //   Serial.println(puntaje);

   //   Serial.println();
   //   cont = 1;
   //   puntaje = 0;

   //   Serial.println("Insert coin...");
   //   Serial.println("Play!");

   // }
}

void loop() {
  // read the value from each sensor:
  values[0] = analogRead(sensor1Pin);
  values[1] = analogRead(sensor2Pin);
  values[2] = analogRead(sensor3Pin);
  values[3] = analogRead(sensor4Pin);
  values[4] = analogRead(sensor5Pin);
  values[5] = analogRead(sensor6Pin);
  values[6] = analogRead(sensor7Pin);

  maxValue = -1;
  //Serial.print(sensor1Value);
  //Serial.print(sensor2Value);

  for (i = 0; i < 7; i++) {
    if ( values[i] > maxValue ) {
      maxValue = values[i];
      iMax = i;
    }
  }

  switch (iMax) {
    case 0:
      action(led1Pin, sensor1Value);
      //break;
    case 1:
      action(led2Pin, sensor2Value);
      //break;
    case 2:
      action(led3Pin, sensor3Value);
      //break;
    case 3:
      action(led4Pin, sensor4Value);
      //break;
    case 4:
      action(led5Pin, sensor5Value);
      //break;
    case 5:
      action(led6Pin, sensor6Value);
      //break;
    case 6:
      action(led7Pin, sensor7Value);
      //break;
    default:
      // if nothing else matches, do the default
      // default is optional
      break;
  }



  //if (sensor1Value >= sensor2Value) {
  //  action(led1Pin, sensor1Value);
  //} else {
  //  action(led2Pin, sensor2Value);
  //}
}
