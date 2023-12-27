#include <Servo.h>
#include "Globals.h"
#define PIN_Servo_z 10
#define PIN_Servo_y 11

Servo tilt_servo;
Servo pan_servo;

int pan = 100;
int tilt = 100;

unsigned long pan_time = 0;
unsigned long tilt_time = 0;

void writePan(int val)
{
    if (millis() - pan_time > 20) // Measured every 1000 milliseconds
    {
        pan_servo.write(val);
        pan_time = millis();
    }
}

void writeTilt(int val)
{
    if (millis() - tilt_time > 20) // Measured every 1000 milliseconds
    {
        tilt_servo.write(val);
        tilt_time = millis();
    }
}

void updateServos()
{
    writePan(pan);
    writeTilt(tilt);
}

void initializeServos()
{
    tilt_servo.attach(PIN_Servo_z);
    pan_servo.attach(PIN_Servo_y);
    updateServos();
}
