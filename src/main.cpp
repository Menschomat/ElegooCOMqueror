#include "Globals.h"
#include "SerialCommunication.h"
#include "LEDController.h"
#include "MotorController.h"

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
