
int sensor1Pin = A0;    // select the input pin for the potentiometer
int led1Pin = 13;      // select the pin for the LED
int sensor1Value = 0;  // variable to store the value coming from the sensor

int sensor2Pin = A5;
int led2Pin = 7;
int sensor2Value = 0;

int cont = 1;
int puntaje = 0;

void setup() {
  // declare the ledPin as an OUTPUT:
  Serial.begin(115200);
  pinMode(led1Pin, OUTPUT);
  pinMode(led2Pin, OUTPUT);
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
  sensor1Value = analogRead(sensor1Pin);
  sensor2Value = analogRead(sensor2Pin);

  //Serial.print(sensor1Value);
  //Serial.print(sensor2Value);

  if (sensor1Value >= sensor2Value) {
    action(led1Pin, sensor1Value);
  } else {
    action(led2Pin, sensor2Value);
  }
}
