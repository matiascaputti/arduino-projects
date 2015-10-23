#include <limits.h>

// Config Sensor 1
int sensor1Pin = A5;    // select the input pin for the potentiometer
double sensor1Value = 0.0;  // variable to store the value coming from the sensor
int RGB_1_redPin  =  15;
int RGB_1_greenPin = 14;
int RGB_1_bluePin  = 13;
char RGB_1_type = 'A';
String RGB_1_name = "RGB_1";

// Config Sensor 2
int sensor2Pin = A0;
int sensor2Value = 0;
int RGB_2_redPin  =  30;
int RGB_2_greenPin = 29;
int RGB_2_bluePin  = 28;
char RGB_2_type = 'A';
String RGB_2_name = "RGB_2";

// Config Sensor 3
int sensor3Pin = A6;
int sensor3Value = 0;
int RGB_3_redPin  =  12;
int RGB_3_greenPin = 11;
int RGB_3_bluePin  = 10;
char RGB_3_type = 'A';
String RGB_3_name = "RGB_3";

// Config Sensor 4
int sensor4Pin = A4;
int sensor4Value = 0;
int RGB_4_redPin  =  18;
int RGB_4_greenPin = 17;
int RGB_4_bluePin  = 16;
char RGB_4_type = 'A';
String RGB_4_name = "RGB_4";

// Config Sensor 5
int sensor5Pin = A1;
int sensor5Value = 0;
int RGB_5_redPin  =  27;
int RGB_5_greenPin = 26;
int RGB_5_bluePin  = 25;
char RGB_5_type = 'A';
String RGB_5_name = "RGB_5";

// Config Sensor 6
int sensor6Pin = A3;
int sensor6Value = 0;
int RGB_6_redPin  =  21;
int RGB_6_greenPin = 20;
int RGB_6_bluePin  = 19;
char RGB_6_type = 'A';
String RGB_6_name = "RGB_6";

// Config Sensor 7
int sensor7Pin = A2;
int sensor7Value = 0;
int RGB_7_redPin  =  24;
int RGB_7_greenPin = 23;
int RGB_7_bluePin  = 22;
char RGB_7_type = 'A';
String RGB_7_name = "RGB_7";


int cont = 1;
int puntaje = 0;
int values[7];

int i, iMax;
int maxValue=INT_MIN;

void setup() {
  // declare the ledPin as an OUTPUT:
  Serial.begin(115200);
  /*
  pinMode(RGB_1_redPin, OUTPUT);
  pinMode(RGB_1_greenPin, OUTPUT);
  pinMode(RGB_1_bluePin, OUTPUT);
  */
  Serial.println("Insert coin...");
  Serial.println("Play!");
}

void blinkRGB(int pinRed, int pinGreen, int pinBlue,
              int red, int green, int blue,
              int timeOn, int timeOff, char type, String RGBname) {
  int off = 0;
  if (type == 'A') { red = 255 - red; green = 255 - green; blue = 255 - blue; off = 255 - off; }
  analogWrite(pinRed, red); analogWrite(pinGreen, green); analogWrite(pinBlue, blue);

  //delay(timeOn);
  //analogWrite(pinRed, off); analogWrite(pinGreen, off); analogWrite(pinBlue, off);
  //delay(timeOff);
}

void action(int sensorValue, int RGB_redPin, int RGB_greenPin,
            int RGB_bluePin, char RGB_type, String RGB_name) {

  Serial.println(sensorValue);
  if (sensorValue > 50) {
      blinkRGB(RGB_redPin, RGB_greenPin, RGB_bluePin, 0, 0, 255, 500, 0, RGB_type, RGB_name);
      delay(500);
      blinkRGB(RGB_redPin, RGB_greenPin, RGB_bluePin, 0, 0, 0, 500, 0, RGB_type, RGB_name);

  }

}

void loop() {


  // TEST 1 LED A LA VEZ
  /*
  sensor1Value = analogRead(sensor1Pin) / 20;
  sensor2Value = analogRead(sensor2Pin) / 20;
  sensor3Value = analogRead(sensor3Pin) / 20;
  sensor4Value = analogRead(sensor4Pin) / 20;
  sensor5Value = analogRead(sensor5Pin) / 20;
  sensor6Value = analogRead(sensor6Pin) / 20;
  sensor7Value = analogRead(sensor7Pin) / 20;
  */

  /*
  action(sensor1Value, RGB_1_redPin, RGB_1_greenPin, RGB_1_bluePin, RGB_1_type, RGB_1_name);
  action(sensor2Value, RGB_2_redPin, RGB_2_greenPin, RGB_2_bluePin, RGB_2_type, RGB_2_name);
  action(sensor3Value, RGB_3_redPin, RGB_3_greenPin, RGB_3_bluePin, RGB_3_type, RGB_3_name);
  action(sensor4Value, RGB_4_redPin, RGB_4_greenPin, RGB_4_bluePin, RGB_4_type, RGB_4_name);
  action(sensor5Value, RGB_5_redPin, RGB_5_greenPin, RGB_5_bluePin, RGB_5_type, RGB_5_name);
  action(sensor6Value, RGB_6_redPin, RGB_6_greenPin, RGB_6_bluePin, RGB_6_type, RGB_6_name);
  action(sensor7Value, RGB_7_redPin, RGB_7_greenPin, RGB_7_bluePin, RGB_7_type, RGB_7_name);
  */



  // JUEGO PARA 7 SENSORES

  values[0] = analogRead(sensor1Pin) / 20;
  values[1] = analogRead(sensor2Pin) / 20;
  values[2] = analogRead(sensor3Pin) / 20;
  values[3] = analogRead(sensor4Pin) / 20;
  values[4] = analogRead(sensor5Pin) / 20;
  values[5] = analogRead(sensor6Pin) / 20;
  values[6] = analogRead(sensor7Pin) / 20;

  maxValue = -1;


  for (i = 0; i < 7; i++) {
    if ( values[i] > maxValue ) {
      maxValue = values[i];
      iMax = i;
    }
  }

  /*
  for (i = 0; i < 7; i++) {
    if (values[i] > 50) {
      for (i = 1; i <= 7; i++){
        String string_one = "Sensor: ";
        String string_two = string_one + i;
        Serial.println(string_two);
        Serial.println(values[i]);
      }
      delay(1000000000000);
    }
  }
  */

  switch (iMax) {
    case 0:
      action(values[0], RGB_1_redPin, RGB_1_greenPin, RGB_1_bluePin, RGB_1_type, RGB_1_name);
      break;
    case 1:
      action(values[1], RGB_2_redPin, RGB_2_greenPin, RGB_2_bluePin, RGB_2_type, RGB_2_name);
      break;
    case 2:
      action(values[2], RGB_3_redPin, RGB_3_greenPin, RGB_3_bluePin, RGB_3_type, RGB_3_name);
      break;
    case 3:
      action(values[3], RGB_4_redPin, RGB_4_greenPin, RGB_4_bluePin, RGB_4_type, RGB_4_name);
      break;
    case 4:
      action(values[4], RGB_5_redPin, RGB_5_greenPin, RGB_5_bluePin, RGB_5_type, RGB_5_name);
      break;
    case 5:
      action(values[5], RGB_6_redPin, RGB_6_greenPin, RGB_6_bluePin, RGB_6_type, RGB_6_name);
      break;
    case 6:
      action(values[6], RGB_7_redPin, RGB_7_greenPin, RGB_7_bluePin, RGB_7_type, RGB_7_name);
      break;
  }

}



