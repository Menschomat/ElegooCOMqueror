#include <Arduino.h>
#include <ArduinoJson.h>
#include <FastLED.h>
#include "LEDController.h"
#include "DeviceDriverSet_xxx0.h"
#include "ApplicationFunctionSet_xxx0.cpp"

// Global objects
DeviceDriverSet_Motor AppMotor;
Application_xxx Application_ConquerorCarxxx0;
MPU6050_getdata AppMPU6050getdata;

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

void updateCarMotion()
{
  ApplicationFunctionSet_ConquerorCarMotionControl(status, speed);
}