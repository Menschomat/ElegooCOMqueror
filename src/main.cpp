#include "Globals.h"
#include "SerialCommunication.h"
#include "LEDController.h"
#include "MotorController.h"
#include "Servos.h"
#include "Sensors.h"

int timer1 = 0;
int timer2 = 0;
int interval = 500;

void setup()
{
  initializeLEDs();
  initializeSerial();
  initializeMotors();
  initializeServos();
}

void loop()
{
  // Input Handling
  handleSerialInput();
  updateCarMotion();
  updateServos();
  // Output Handling
  timer2 = millis();
  if (interval < abs(timer2 - timer1))
  {
    // Create a JSON object and add the distance data
    StaticJsonDocument<200> doc;
    // Distance
    int distance = measureDistance();
    doc["distance"] = distance;
    // Voltage
    int voltage = measureVoltage();
    doc["voltage"] = voltage;
    // Camera
    int pan = measurePan();
    doc["pan"] = pan;
    int tilt = measureTilt();
    doc["tilt"] = tilt;
    //---------
    serializeJson(doc, Serial);
    Serial.println();
    timer1 = timer2;
  }
}
