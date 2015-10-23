#include <SevSeg.h>

SevSeg sevseg; //Initiate a seven segment controller object

void setup() {
  byte numDigits = 4;
  byte digitPins[] = {42, 43, 44, 45};
  byte segmentPins[] = {46, 47, 48, 49, 50, 51, 52, 53};

  Serial.begin(9600);
  sevseg.begin(COMMON_ANODE, numDigits, digitPins, segmentPins);
  sevseg.setBrightness(90);
}

void loop() {
  static unsigned long timer = millis();
  static int deciSeconds = 0;

  
  if (millis() >= timer) {
    deciSeconds++; // 100 milliSeconds is equal to 1 deciSecond
    timer += 100; 
    if (deciSeconds == 10000) { // Reset to 0 after counting for 1000 seconds.
      deciSeconds=0;
    }
    sevseg.setNumber(deciSeconds, 1);
    //Serial.println(deciSeconds);
  }
  

 // sevseg.setNumber(1111, 1);

  sevseg.refreshDisplay(); // Must run repeatedly
}
