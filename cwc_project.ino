#include <ArduinoJson.h>
#include <ArduinoJson.hpp>

#include <TScheduler.hpp>
#include <TSchedulerDeclarations.hpp>
#include <TaskScheduler.h>
#include <TaskSchedulerDeclarations.h>
#include <TaskSchedulerSleepMethods.h>

#include <painlessMesh.h>
#define   MESH_PREFIX     "whateverYouLike"
#define   MESH_PASSWORD   "somethingSneaky"
#define   MESH_PORT       5555

#include <HCSR04.h>
const int triggerPin = 33;
const int echoPin = 34; 

#include <Adafruit_NeoPixel.h>
#define onboardLED 18
Adafruit_NeoPixel pixels(1, onboardLED, NEO_GRB + NEO_KHZ800);

#include <DRV8833.h>
DRV8833 driver = DRV8833();
const int FLT = 12; 
const int BIN1 = 13;
const int BIN2 = 14; 
const int nSleep = 15; 
const int AIN1 = 17; 
const int AIN2 = 16; 

// The speed of the motors:
const int motorSpeed = 128; // Half speed (255 / 2).

//Demo Joystick
const int joystick_Switch_pin = 3; 
const int joystick_X_pin = 5;
const int joystick_Y_pin = 4;


void setup() {
  
  Serial.begin(9600);
  HCSR04.begin(triggerPin, echoPin);
  pixels.setPixelColor(0, 130);
  pixels.show();   
  delay(1000);
  
  Serial.println("Hello World");
  pixels.setPixelColor(255, 255);
  pixels.show();   
  Serial.println("Setting pin modes");
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT);
  pinMode(nSleep, OUTPUT); //nSleep Mode = On when logic HIGH, logic LOW to sleep
  pinMode(FLT, INPUT);

  digitalWrite(AIN1, LOW);
  digitalWrite(AIN2, LOW);
  digitalWrite(BIN1, LOW);
  digitalWrite(BIN2, LOW);
  
  pinMode(joystick_Switch_pin, INPUT);
  pinMode(joystick_X_pin, INPUT);
  pinMode(joystick_Y_pin, INPUT);
  
  Serial.println("Almost done");
  pixels.setBrightness(10);
  pixels.begin(); 
  Serial.println("Ready!");
  pixels.setPixelColor(0, 255);
  pixels.show();   
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

void motorsForward() {

}

void loop() {
  double* distances = HCSR04.measureDistanceCm();

  //Test distance, gets pulled from distances array
  //Determine proxemics in conditionals below
  int testDistance = distances[0];  
    if (testDistance < 10 {
      Serial.println("Proxemic 1");
      pixels.setPixelColor(0, 20);
      pixels.show();  
    } else if (#CONDITION2) {
      Serial.println("Proxemic 2");
      pixels.setPixelColor(0, 100);
      pixels.show();  
    } else if (#CONDITION3) {
      Serial.println("Proxemic 3");
      pixels.setPixelColor(0, 200);
      pixels.show();        
    }

  //Running pixel setting
  pixels.setPixelColor(0, 170);
  pixels.show();   
    
  delay(1000);
  
  //Print distances array, label correct unit (centimeter)
  Serial.print(distances[0]);
  Serial.println(" cm");
  Serial.println("---");
  delay(500);

  //For testing
  //read values from joystick, assign to temp int, print to serial
  int joystick_X = analogRead(joystick_X_pin);
  int joystick_Y = analogRead(joystick_Y_pin);
  Serial.print("Joystick X: ");
  Serial.println(joystick_X);
  Serial.print("Joystick Y: ");
  Serial.println(joystick_Y);

  // digitalWrite(AIN1, HIGH);
  // digitalWrite(BIN1, HIGH);
  // digitalWrite(AIN2, LOW);
  // analogWrite(AIN1, motorSpeed);
  // analogWrite(BIN1, motorSpeed);  
  // delay(1000);
  // digitalWrite(AIN1, LOW);
  // digitalWrite(BIN1, LOW);
  // analogWrite(AIN1, 0);
  // analogWrite(BIN1, 0);
  // delay(1000);
  return;
}
