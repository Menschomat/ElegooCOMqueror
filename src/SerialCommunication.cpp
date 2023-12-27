#include <Arduino.h>
#include "Globals.h"
#include "SerialCommunication.h"
#include "LEDController.h"

void initializeSerial()
{
    Serial.begin(9600);
    delay(500);
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
        m_speed = doc["speed"] | m_speed;
        Serial.print("Received speed: ");
        Serial.println(m_speed);
    }
}

void reportDeserializationError(const DeserializationError &error)
{
    Serial.print(F("deserializeJson() failed: "));
    Serial.println(error.c_str());
    status = stop_it;
    setColor(255, 0, 0); // Set LED to red
}