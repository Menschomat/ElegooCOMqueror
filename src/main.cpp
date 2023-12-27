#include "Globals.h"
#include "SerialCommunication.h"
#include "LEDController.h"
#include "MotorController.h"
#include "Sensors.h"

int timer1 = 0;
int timer2 = 0;
int interval = 500;

void setup()
{
  initializeLEDs();
  initializeSerial();
  initializeMotors();
}

void loop()
{
  // Input Handling
  handleSerialInput();
  updateCarMotion();
  // Output Handling
  timer2 = millis();
  if (interval < abs(timer2 - timer1))
  {
    // Create a JSON object and add the distance data
    StaticJsonDocument<200> doc;
    int distance = messureDistance();
    doc["distance"] = distance;
    serializeJson(doc, Serial);
    Serial.println();
    timer1 = timer2;
  }
}
