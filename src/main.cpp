#include <Arduino.h>
#include <ArduinoJson.h>
#include <FastLED.h>
#include "DeviceDriverSet_xxx0.h"
#include "ApplicationFunctionSet_xxx0.cpp"

#define NUM_LEDS 1
#define DATA_PIN 4 // Set to the correct data pin for your setup

DeviceDriverSet_Motor AppMotor;
Application_xxx Application_ConquerorCarxxx0;
MPU6050_getdata AppMPU6050getdata;
int time1 = 0;
int time2 = 0;
ConquerorCarMotionControl status = stop_it;
int speed = 128;

CRGB leds[NUM_LEDS];

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(9600);
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
  FastLED.setBrightness(20);
  AppMotor.DeviceDriverSet_Motor_Init();
  AppMPU6050getdata.MPU6050_dveInit();
  delay(2000);
  AppMPU6050getdata.MPU6050_calibration();
}

void loop()
{

  // time2 = millis();

  // if (3000 < abs(time2 - time1))
  //{
  //   if (status == Forward)
  //   {
  //     status = Backward;
  //   }
  //   else
  //   {
  //     status = Forward;
  //   }
  //   time1 = time2;
  // }

  if (Serial.available())
  {
    // Read the JSON object from Serial
    StaticJsonDocument<200> doc; // Adjust size according to your needs
    DeserializationError error = deserializeJson(doc, Serial);

    // Test if parsing succeeds.
    if (error)
    {
      Serial.print(F("deserializeJson() failed: "));
      Serial.println(error.c_str());
      status = stop_it;
      leds[0] = CRGB(255, 0, 0);
      FastLED.show();
      return;
    }

    // Read the direction as an integer
    int directionInt = doc["direction"] | status;
    speed = doc["speed"] | speed;
    // Cast the integer to your enum type
    ConquerorCarMotionControl direction = static_cast<ConquerorCarMotionControl>(directionInt);

    // Do something with the values
    Serial.print("Received name: ");
    Serial.println(direction);
    status = direction;

    if (doc.containsKey("color"))
    {
      String hexColor = doc["color"].as<String>();
      long number = strtol(&hexColor[1], NULL, 16);
      // Now 'number' holds the integer value of color

      int r = number >> 16;
      int g = (number >> 8) & 0xFF;
      int b = number & 0xFF;

      leds[0] = CRGB(r, g, b);
      FastLED.show();
    }
  }
  ApplicationFunctionSet_ConquerorCarMotionControl(status /*direction*/, speed /*speed*/);
}
