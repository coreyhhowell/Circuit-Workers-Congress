#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>

#define TFT_CS 10
#define TFT_DC 9
#define TFT_MOSI 11
#define TFT_SCK 13
#define TFT_RST 7 // RST can be connected to any digital pin

Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_MOSI, TFT_SCK, TFT_RST);

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

//  Motor speed 50% Duty Cycle 
const int motorSpeed = 128; 

void setup() {
  
  Serial.begin(9600);
  
  tft.begin();
  tft.setRotation(2); // adjust the rotation as needed
  tft.fillScreen(ILI9341_WHITE);
  
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
  //  Motors forward
  digitalWrite(AIN1, HIGH);
  digitalWrite(BIN1, HIGH);
  analogWrite(AIN2, motorSpeed);
  analogWrite(BIN2, motorSpeed);
}
void motorsBackward() {
  //  Motors forward
  // Just reverse polarity 
  digitalWrite(AIN2, HIGH);
  digitalWrite(BIN2, HIGH);
  analogWrite(AIN1, motorSpeed);
  analogWrite(BIN1, motorSpeed);
}

void motorsRight() {
  //  Motors right
  // A on, B off
  digitalWrite(AIN1, HIGH);
  digitalWrite(BIN1, LOW);
  analogWrite(AIN2, motorSpeed);
}

void motorsLeft() {
  //  Motors right
  // A off, B on
  digitalWrite(AIN1, LOW);
  digitalWrite(BIN1, HIGH);
  analogWrite(BIN2, motorSpeed);
}

void loop() {
   tft.fillScreen(ILI9341_WHITE);
  char binarySequence[] = "00010000001110100011011110010000001100010011100100110010101100001011010110010000001110100011010000110010100100000011000110110100001100001011010010110111001110011001000000110111101100110001000000111001101100101011100100111011001101001011101000111010101100100011001010010000001100001011011100110010000100000011001000110010101101101011000010110111001100100001000000110111101110101011100100010000001110010011010010110011101101000"; // your binary sequence here
  int sequenceLength = strlen(binarySequence);
  int squareSize = 14; // size of each square in pixels
  int x = 0; // starting x position
  int y = 0; // starting y position

  for (int i = 0; i < sequenceLength; i++) {
    char digit = binarySequence[i];

    if (digit == '1') {
      tft.fillRect(x, y, squareSize, squareSize, ILI9341_YELLOW);
    } else {
      tft.fillRect(x, y, squareSize, squareSize, ILI9341_BLUE);
    }

    x += squareSize;

    if (x >= tft.width()) {
      x = 0;
      y += squareSize;
    } 
    delay(10);
  }
  
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

  
  //Cycle motors test
  digitalWrite(AIN1, HIGH);
  digitalWrite(BIN1, HIGH);
  digitalWrite(AIN2, LOW);
  analogWrite(AIN1, motorSpeed);
  analogWrite(BIN1, motorSpeed);  
  delay(1000);
  digitalWrite(AIN1, LOW);
  digitalWrite(BIN1, LOW);
  analogWrite(AIN1, 0);
  analogWrite(BIN1, 0);
  delay(1000);
  return;
}
