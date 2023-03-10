#include <Adafruit_NeoPixel.h>
Adafruit_NeoPixel pixels(1, onboardLED, NEO_GRB + NEO_KHZ800);
#define onboardLED 18

#include <DRV8833.h>
DRV8833 driver = DRV8833();
const int AIN1 = 17; 
const int AIN2 = 16; 
const int nSleep = 15; 
const int BIN1 = 12;
const int BIN2 = 13; 

// The speed of the motors:
const int motorSpeed = 128; // Half speed (255 / 2).

#define LED_PIN 19


void setup() {
  Serial.begin(9600);
  delay(1000);
  Serial.println("Hello World");
  
  pinMode(LED_PIN, OUTPUT);
  
  
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT);
  pinMode(nSleep, OUTPUT); //nSleep Mode = On when logic HIGH, logic LOW to sleep
  digitalWrite(nSleep, HIGH);

  digitalWrite(AIN1, LOW);
  digitalWrite(AIN2, LOW);
   digitalWrite(BIN1, LOW);
  digitalWrite(BIN2, LOW);
  
  pixels.setBrightness(10);
  pixels.begin(); 
  Serial.println("Ready!");
}
// Input a value 0 to 255 to get a color value.
uint32_t Wheel(byte WheelPos)
{
    //Assume the wheel value is less than 85, if so Green value is 0
    uint32_t returnColor = Adafruit_NeoPixel::Color((byte)(255 - (WheelPos * 3)), 0, (byte)(WheelPos * 3));

    //If we are greater than 170 Red value is 0
    if (WheelPos > 84 && WheelPos < 170)
    {
        WheelPos -= 85;
        returnColor = Adafruit_NeoPixel::Color(0, (byte)(WheelPos * 3), (byte)(255 - WheelPos * 3));
    }
    //Finally above 170 and Blue value is 0
    else if (WheelPos >= 170)
    {
        WheelPos -= 170;
        returnColor = Adafruit_NeoPixel::Color((byte)(WheelPos * 3), (byte)(255 - WheelPos * 3), 0);
    }

    return returnColor;
}

//Counter to run from 0-255 to cycle the colors of the rainbow.
int colorCount = 0;

void loop() {
  
  pixels.setPixelColor(0, Wheel(colorCount++));
  pixels.show();   
    if (colorCount > 255)
        colorCount = 0;

  digitalWrite(LED_PIN, HIGH);
  digitalWrite(AIN1, HIGH);
  digitalWrite(BIN1, HIGH);
  //digitalWrite(AIN2, LOW);
  analogWrite(AIN1, motorSpeed);
  analogWrite(BIN1, motorSpeed);  
  Serial.println("LED on");
  delay(1000);
  digitalWrite(LED_PIN, LOW);
  digitalWrite(AIN1, LOW);
  digitalWrite(BIN1, LOW);
  analogWrite(AIN1, 0);
  analogWrite(BIN1, 0);
  Serial.println("LED off");
  delay(1000);
}
