/*
 * contador de tiempo. en un minuto termina el juego.
 */
const int lowestPin = 3;
const int highestPin = 8;


void setup() {
  for (int thisPin =lowestPin; thisPin <= highestPin; thisPin++) {
    pinMode(thisPin, OUTPUT);
  }
}

void loop() {

  for (int thisPin = lowestPin; thisPin <= highestPin; thisPin++) {
    // fade the LED on thisPin from brithstest to off:
    analogWrite(thisPin, 254);
  }

  // de a uno voy apagándolo
  for (int thisPin = lowestPin; thisPin <= highestPin; thisPin++) {
    // fade the LED on thisPin from brithstest to off:
    for (int brightness = 254; brightness >= 0; brightness--) {
      analogWrite(thisPin, brightness);
      delay(10);
    }
  }
  
  for (int fin = 0; fin <= 20; fin++) {
    for (int thisPin = lowestPin; thisPin <= highestPin; thisPin++) {
      analogWrite(thisPin, 254);
      delay(10);
      analogWrite(thisPin, 0);
    }    
  }



  
}
