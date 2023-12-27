#include <Arduino.h>
#include <ArduinoJson.h>
#include <FastLED.h>
#include "DeviceDriverSet_xxx0.h"
#include "ApplicationFunctionSet_xxx0.cpp"

// Constants
#define NUM_LEDS 1
#define DATA_PIN 4 // Set to the correct data pin for your setup

// Global objects
DeviceDriverSet_Motor AppMotor;
Application_xxx Application_ConquerorCarxxx0;
MPU6050_getdata AppMPU6050getdata;
CRGB leds[NUM_LEDS];

ConquerorCarMotionControl status = stop_it;
int speed = 128;

// Function Prototypes
void initializeSerial();
void initializeLEDs();
void initializeMotors();
void handleSerialInput();
void updateDirection(const StaticJsonDocument<200> &doc);
void updateSpeed(const StaticJsonDocument<200> &doc);
void reportDeserializationError(const DeserializationError &error);
void updateLEDColor(const StaticJsonDocument<200> &doc);
void setColorFromHexString(const String &hexColor);
void setColor(int r, int g, int b);
void updateCarMotion();

void setup()
{
  initializeLEDs();
  initializeSerial();
  initializeMotors();
}

void loop()
{
  handleSerialInput();
  updateCarMotion();
}

void initializeSerial()
{
  Serial.begin(9600);
  delay(500);
}

void initializeLEDs()
{
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
  FastLED.setBrightness(20);
  setColor(0, 0, 255);
}

void initializeMotors()
{
  setColor(255, 255, 0);
  AppMotor.DeviceDriverSet_Motor_Init();
  AppMPU6050getdata.MPU6050_dveInit();
  delay(2000);
  AppMPU6050getdata.MPU6050_calibration();
  setColor(0, 255, 0);
  delay(500);
  setColor(0, 0, 0);
}

void handleSerialInput()
{
  if (Serial.available())
  {
    StaticJsonDocument<200> doc;
    DeserializationError error = deserializeJson(doc, Serial);
    if (error)
    {
      reportDeserializationError(error);
      return;
    }
    updateDirection(doc);
    updateSpeed(doc);
    updateLEDColor(doc);
  }
}

void updateDirection(const StaticJsonDocument<200> &doc)
{
  if (doc.containsKey("direction"))
  {
    int directionInt = doc["direction"] | static_cast<int>(status);
    status = static_cast<ConquerorCarMotionControl>(directionInt);
    Serial.print("Received direction: ");
    Serial.println(directionInt);
  }
}

void updateSpeed(const StaticJsonDocument<200> &doc)
{
  if (doc.containsKey("speed"))
  {
    speed = doc["speed"] | speed;
    Serial.print("Received speed: ");
    Serial.println(speed);
  }
}

void reportDeserializationError(const DeserializationError &error)
{
  Serial.print(F("deserializeJson() failed: "));
  Serial.println(error.c_str());
  status = stop_it;
  setColor(255, 0, 0); // Set LED to red
}

void updateLEDColor(const StaticJsonDocument<200> &doc)
{
  if (doc.containsKey("color"))
  {
    setColorFromHexString(doc["color"].as<String>());
  }
}

void setColorFromHexString(const String &hexColor)
{
  // A valid hex color code is 7 characters: '#' followed by 6 hex digits
  if (hexColor.length() == 7 && hexColor[0] == '#')
  {
    // Convert the hex part of the string to a long integer
    const char *hexStr = hexColor.c_str() + 1; // Skip the '#' character
    long number = strtol(hexStr, NULL, 16);

    // Extract the individual color components
    int r = (number >> 16) & 0xFF;
    int g = (number >> 8) & 0xFF;
    int b = number & 0xFF;

    // Set the color
    setColor(r, g, b);
  }
  else
  {
    // Handle error - set to a default color or report an error
    Serial.println("Error: Invalid hex color string. Setting to default color.");
    setColor(255, 0, 0); // Perhaps set to red to indicate error
  }
}

void setColor(int r, int g, int b)
{
  leds[0] = CRGB(r, g, b);
  FastLED.show();
}

void updateCarMotion()
{
  ApplicationFunctionSet_ConquerorCarMotionControl(status, speed);
}