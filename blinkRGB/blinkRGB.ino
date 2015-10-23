/*
Led RGB
Function to turn on an RGB led and set it's on/off time
*/
 
int RGB_1_redPin  =  9;
int RGB_1_greenPin = 10;
int RGB_1_bluePin  = 11;
char RGB_1_type = 'A';
String RGB_1_name = "RGB_1";
 
void setup() {
  pinMode(RGB_1_redPin, OUTPUT);
  pinMode(RGB_1_greenPin, OUTPUT);
  pinMode(RGB_1_bluePin, OUTPUT);
}

void blinkRGB(int pinRed, int pinGreen, int pinBlue,
              int red, int green, int blue,
              int timeOn, int timeOff, char type, String RGBname) {
  int off = 0;
  if (type == 'A') { red = 255 - red; green = 255 - green; blue = 255 - blue; off = 255 - off; }
  analogWrite(pinRed, red); analogWrite(pinGreen, green); analogWrite(pinBlue, blue);

  delay(timeOn);
  analogWrite(pinRed, off); analogWrite(pinGreen, off); analogWrite(pinBlue, off);
  delay(timeOff);
}

void loop() {
    blinkRGB(RGB_1_redPin, RGB_1_greenPin, RGB_1_bluePin, 50, 0, 150, 500, 500, RGB_1_type, RGB_1_name);
    blinkRGB(RGB_1_redPin, RGB_1_greenPin, RGB_1_bluePin, 0, 150, 50, 500, 500, RGB_1_type, RGB_1_name);
    blinkRGB(RGB_1_redPin, RGB_1_greenPin, RGB_1_bluePin, 255, 255, 0, 500, 500, RGB_1_type, RGB_1_name);
    blinkRGB(RGB_1_redPin, RGB_1_greenPin, RGB_1_bluePin, 0, 255, 255, 500, 500, RGB_1_type, RGB_1_name);
}
