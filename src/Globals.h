#ifndef GLOBALS_H
#define GLOBALS_H

#include <Arduino.h>
#include <FastLED.h>
#include "DeviceDriverSet_xxx0.h" // Update with actual path if needed
#include "ApplicationFunctionSet_xxx0.cpp"

// Constants
#define NUM_LEDS 1
#define DATA_PIN 4
// Global objects
extern DeviceDriverSet_Motor AppMotor;
extern Application_xxx Application_ConquerorCarxxx0;
extern MPU6050_getdata AppMPU6050getdata;
extern CRGB leds[NUM_LEDS];

extern ConquerorCarMotionControl status;
extern int m_speed;
//Turret
extern int pan;
extern int tilt;

#endif // GLOBALS_H