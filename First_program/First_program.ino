

int sensorPin = A0;    // select the input pin for the potentiometer
int ledPin = 13;      // select the pin for the LED
int sensorValue = 0;  // variable to store the value coming from the sensor
int cont = 1;
int puntaje = 0;

void setup() {
  // declare the ledPin as an OUTPUT:
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);
  Serial.println("Insert coin...");
  Serial.println("play!");
}

void loop() {
  // read the value from the sensor:
  sensorValue = analogRead(sensorPin);

  
  //Serial.println(sensorValue);
  // turn the ledPin on
  if (sensorValue > 800) {
    if (cont <= 3) {
     
      digitalWrite(ledPin, HIGH);
      Serial.print("tiro: ");
      Serial.print(cont);
      Serial.print("... ");

      // que se vea el puntaje
      Serial.println(sensorValue);
      
      delay(1000);
      digitalWrite(ledPin, LOW);
      cont++;
      puntaje = puntaje + sensorValue;
    }
  }

   if (cont == 4 ) {
      Serial.println();
      Serial.println("FIN DEL JUEGO....... tu puntaje fue.....");
      Serial.println(puntaje);

     Serial.println();
     cont = 1;
     puntaje = 0; 

       Serial.println("Insert coin...");
  Serial.println("play!"); 

    }

}
