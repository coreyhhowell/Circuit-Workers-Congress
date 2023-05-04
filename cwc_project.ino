#include <PNGdec.h>          // PNG decoder library ( PNG converted to hex array https://notisrac.github.io/FileToCArray/ )
#include "panda.h"           // Image is stored in hex array
#define MAX_IMAGE_WDITH 240  // Width of 2.2" display being used
PNG png;                     // PNG decoder instance

//Mesh Networking, Painless Mesh + dependencies
#include <AsyncTCP.h>
#include <ArduinoJson.h>
#include <ArduinoJson.hpp>
#include <painlessMesh.h>
Scheduler userScheduler;  // to control your personal task
painlessMesh mesh;

#define MESH_PREFIX "circuitworkerscongress"
#define MESH_PASSWORD "cwcMeshPass"
#define MESH_PORT 5555

// map ChipIDs to narrative names
std::map<uint64_t, String> macToName = {
  { 9581130030801662794, "Mimosa" },
  { 9581130030801646332, "Acacia" },
  { 9581130030801631442, "Phaseolus" },
};

void sendMessage();  // Prototype so PlatformIO doesn't complain
Task taskSendMessage(TASK_SECOND * 1, TASK_FOREVER, &sendMessage);

#include <Adafruit_BusIO_Register.h>
#include <Adafruit_I2CDevice.h>
#include <Adafruit_I2CRegister.h>
#include <Adafruit_SPIDevice.h>

#include <Adafruit_PM25AQI.h>
#include <SoftwareSerial.h>
SoftwareSerial pmSerial(2, 3);
Adafruit_PM25AQI aqi = Adafruit_PM25AQI();
PM25_AQI_Data data;


#include <SPI.h>               // Default SPI library
#include <TFT_eSPI.h>          // Hardware-specific library
TFT_eSPI tft = TFT_eSPI();     // Invoke custom library
#include <Adafruit_GFX.h>      // GFX library for displays
#include <Adafruit_ILI9341.h>  // Display library for ILI9341 displays

//Initial X and Y values for printing to ILI9341 display
int16_t xpos = 0;
int16_t ypos = 0;


#include <pwmWrite.h>  //PWM management library for ESP32 based devices
Pwm pwm = Pwm();       //PWM object
const uint32_t frequency = 10000;
const byte resolution = 10;
const uint16_t duty = 341;

// Servo speeds, degrees/second
float speed1 = 40.0;
float speed2 = 65.0;

// Servo Easing Constant, ke
float ke1 = 0.5;        // Easing
float ke2 = 0.2;        // Easing, nearly linear
uint8_t position = 90;  // Servo initially go to position (degrees)
float ye1;              // Servo floating value for printing writeServo values to serial

#include <Adafruit_NeoPixel.h>                                  // NeoPixel library, used to access GPIO-18 LED on-board ESP
#define onboardLED 18                                           // GPIO-18, onboard LED
Adafruit_NeoPixel pixels(1, onboardLED, NEO_GRB + NEO_KHZ800);  //pixels object

// Motors
#include <DRV8833.h>         // library for controlling motors via DRV8833 H-bridge driver
DRV8833 driver = DRV8833();  // Driver object
const int FLT = 12;          // Fault pin, runs LOW, returns HIGH if fault detected
const int BIN1 = 13;         // Terminal 1 of 2, Motor B
const int BIN2 = 14;         // Terminal 2 of 2, Motor B
const int nSleep = 15;       // Sleep pin, low by default, to become active -> logic = HIGH
const int AIN1 = 16;         // Terminal 1 of 2, Motor A
const int AIN2 = 17;         // Terminal 2 of 2, Motor A
const int motorSpeed = 128;  // Motor Speed, 50% Duty Cycle, 0-255

#include <HCSR04.h>
byte triggerPin = 7;
byte echoPin = 8;
bool IsCloseToHuman = false;  // boolean to be used for state change IF robot is in proximity to person, initially false

const int piezoPin = 4;  // Medium buzzer for beeping

void setup() {

  Serial.begin(9600);
  pmSerial.begin(9600);

  pixels.begin();
  pixels.setBrightness(10);
  pixels.setPixelColor(0, 255);
  pixels.show();
  if (!aqi.begin_UART(&pmSerial)) {  // connect to the sensor over software serial
    Serial.println("Could not find PM 2.5 sensor!");
    while (1) delay(10);
  }
  pixels.setBrightness(15);
  pixels.setPixelColor(65, 255);
  pixels.show();

  mesh.setDebugMsgTypes(ERROR | STARTUP);  // set before init() so that you can see startup messages
  mesh.init(MESH_PREFIX, MESH_PASSWORD, &userScheduler, MESH_PORT);
  mesh.onReceive(&receivedCallback);
  mesh.onNewConnection(&newConnectionCallback);
  mesh.onChangedConnections(&changedConnectionCallback);
  mesh.onNodeTimeAdjusted(&nodeTimeAdjustedCallback);

  userScheduler.addTask(taskSendMessage);
  taskSendMessage.enable();

  pixels.setBrightness(20);
  pixels.setPixelColor(65, 255);
  pixels.show();

  HCSR04.begin(triggerPin, echoPin);

  pinMode(piezoPin, OUTPUT);  //Config piezoPin

  tft.init();          // Initialise the TFT
  tft.setTextFont(4);  //set font size fr ILI9341
  tft.setRotation(2);  // Rotates to portrait mode, pinouts at top [1 or 3 are landscape mode]

  pixels.setBrightness(15);
  pixels.setPixelColor(65, 255);
  pixels.show();

  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT);
  pinMode(nSleep, OUTPUT);     //nSleep Mode pinmode
  digitalWrite(nSleep, HIGH);  // Mode = On when logic HIGH, logic LOW to sleep
  pinMode(FLT, INPUT);         //Fault pin runs high defualt, when returns low = fault detected

  pixels.setBrightness(10);
  pixels.setPixelColor(255, 255);
  pixels.show();
}

void loop() {
  mesh.update();
  double *distances = HCSR04.measureDistanceCm();
  Serial.println("Looping");
  if (distances[0] > 100) {
    Serial.print(distances[0]);
    Serial.println("Longer than 100 cm away");
    motorsForward();
    Serial.println("Motors forward");
    delay(2000);

  } else {
    Serial.print(distances[0]);
    Serial.println("Less than 100 cm away");
    digitalWrite(AIN1, LOW);
    analogWrite(AIN2, 0);
    digitalWrite(BIN1, LOW);
    analogWrite(BIN2, 0);
    Serial.println("Motors off");
    return;
  }


  // if (!aqi.read(&data)) {
  //   Serial.println("Could not read from AQI");
  //   delay(500);  // try again in a bit!
  //   return;
  // }


  // if (data.pm10_env > 500) {
  //   Serial.print(F("PM 1.0: "));
  //   Serial.print(data.pm10_env);
  // } else if (data.pm25_env > 1000) {
  //   Serial.print(F("\t\tPM 2.5: "));
  //   Serial.print(data.pm25_env);
  // } else if (data.pm100_env > 2500) {
  //   Serial.print(F("\t\tPM 10: "));
  //   Serial.println(data.pm100_env);
  // }


  // while (1) {
  //   robotVisualMessage();
  //   break;
  // }
}
void motorsForward() {
  digitalWrite(AIN1, HIGH);
  analogWrite(AIN2, motorSpeed);
  digitalWrite(BIN1, HIGH);
  analogWrite(BIN2, motorSpeed);
}
void motorsReverse() {
  digitalWrite(AIN2, HIGH);
  analogWrite(AIN1, motorSpeed);
  digitalWrite(BIN2, HIGH);
  analogWrite(BIN1, motorSpeed);
}
void motorsTurn() {
  digitalWrite(BIN2, HIGH);
  analogWrite(BIN1, motorSpeed);
}
void motorsStop() {
  digitalWrite(AIN1, LOW);
  analogWrite(AIN2, 0);
  digitalWrite(BIN1, LOW);
  analogWrite(BIN2, 0);
}

void pngDraw(PNGDRAW *pDraw) {  // Callback function called to process the hex array and generate an image
  uint16_t lineBuffer[MAX_IMAGE_WDITH];
  png.getLineAsRGB565(pDraw, lineBuffer, PNG_RGB565_BIG_ENDIAN, 0xffffffff);
  tft.pushImage(xpos, ypos + pDraw->y, pDraw->iWidth, 1, lineBuffer);
}

void robotVisualMessage() {
  int16_t rc = png.openFLASH((uint8_t *)panda, sizeof(panda), pngDraw);  // rc used for buffer
  if (rc == PNG_SUCCESS) {
    Serial.println("Successfully png file");
    Serial.printf("image specs: (%d x %d), %d bpp, pixel type: %d\n", png.getWidth(), png.getHeight(), png.getBpp(), png.getPixelType());
    tft.startWrite();
    uint32_t dt = millis();  // delta time
    rc = png.decode(NULL, 0);
    Serial.print(millis() - dt);
    Serial.println("ms");
    tft.endWrite();
  }

  delay(5000);  // Hold rendered QR code for 5 seconds, wipe white
  tft.fillScreen(ILI9341_WHITE);

  tft.fillRectVGradient(0, 0, 240, 320, TFT_WHITE, TFT_YELLOW);     //White yellow gradient
  tft.setCursor(0, 0);                                              // Start text in upper left corner
  tft.print("CIRCUIT WORKERS CONGRESS 110000101 NOT1101 IGNORED");  // CWC message
  delay(3000);

  //CWC messages in binary string
  char binarySequence[] = "000101001000000111010001101001100110000110000110000101101001011011100111001100100000011011110110011000100000011100110110010101110010011101100110100101110100011101010110010001100101001000001001010110110101100001011011100110010000100000011011110111010101110010001000000111001001101001011001100100100110 ";

  int sequenceLength = strlen(binarySequence);  //determine string length
  int squareSize = 16;                          // size of each square in pixels
  int x = 0;                                    // starting x position, different from xPos and yPos global variables
  int y = 0;                                    // starting y position

  // Using the same length sequence, draws a white background block by block
  for (int i = 0; i < sequenceLength; i++) {  // Iterate through array digit by digit until sequence is finished
    char digit = binarySequence[i];           // digit is stored, either 1 or 0
    if (digit == '1') {
      tft.fillRect(x, y, squareSize, squareSize, ILI9341_WHITE);  // If digit is a 1, draw a white square
    } else {
      tft.fillRect(x, y, squareSize, squareSize, ILI9341_WHITE);  // if else, aka a 0, draw a white square
    }

    x += squareSize;  // Increase x coordinate by square pixel size

    if (x >= tft.width()) {  // if X exceeds tft width (240), reset to 0 and adjust Y coordinate by square size (drops to new line)
      x = 0;
      y += squareSize;
    }
    delay(40);  // Buffer milliseconds between each square
  }
  // Using the same length sequence, draws over white background either white or black squares, visual binary code
  x = 0;                                      // x position is reset to return to home position
  y = 0;                                      // x position is reset to return to home position
  for (int i = 0; i < sequenceLength; i++) {  // Iterates through sequence, like previous block of code. Either black or white square
    char digit = binarySequence[i];

    if (digit == '1') {
      tft.fillRect(x, y, squareSize, squareSize, ILI9341_WHITE);
      tone(piezoPin, 250, 40);  // Audible beeps
    } else {
      tft.fillRect(x, y, squareSize, squareSize, ILI9341_BLACK);
      tone(piezoPin, 200, 20);  // Audible beeps, lower frequency
    }

    x += squareSize;

    if (x >= tft.width()) {
      x = 0;
      y += squareSize;
    }
    delay(40);
  }
  delay(2000);                    // Hold on binary visual for X seconds
  tft.fillScreen(ILI9341_WHITE);  // Wipe screen white
}

void sendMessage() {
  String msg = "Hello from node ";
  msg += mesh.getNodeId();
  mesh.sendBroadcast(msg);
  taskSendMessage.setInterval(random(TASK_SECOND * 1, TASK_SECOND * 5));
}

// Needed for painless library
void receivedCallback(uint32_t from, String &msg) {
  Serial.printf("startHere: Received from %u msg=%s\n", from, msg.c_str());
}

void newConnectionCallback(uint32_t nodeId) {
  Serial.printf("--> startHere: New Connection, nodeId = %u\n", nodeId);
}

void changedConnectionCallback() {
  Serial.printf("Changed connections\n");
}

void nodeTimeAdjustedCallback(int32_t offset) {
  Serial.printf("Adjusted time %u. Offset = %d\n", mesh.getNodeTime(), offset);
}
