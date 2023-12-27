#include <HCSR04.h>
#include "Globals.h"
#define VOL_MEASURE_PIN A3
// Initialize sensor that uses digital pins 13 and 12.
const byte triggerPin = 13;
const byte echoPin = 12;
UltraSonicDistanceSensor distanceSensor(triggerPin, echoPin);
unsigned long vol_measure_time = 0;

void voltageInit()
{
    pinMode(VOL_MEASURE_PIN, INPUT);
}

float measureDistance()
{
    return distanceSensor.measureDistanceCm();
}

float measureVoltage()
{

    vol_measure_time = millis();
    float voltage = (analogRead(VOL_MEASURE_PIN) * 5) * ((10 + 1.5) / 1.5) / 1024; // Read voltage value
                                                                                   // float voltage = (analogRead(VOL_MEASURE_PIN) * 0.0375);
    voltage = voltage + (voltage * 0.08);
    return voltage;
}

int measurePan()
{
    return pan;
}

int measureTilt()
{
    return tilt;
}
