#include "LEDController.h"
#include <FastLED.h>

#define NUM_LEDS 1
#define DATA_PIN 4 // Set to the correct data pin for your setup

CRGB leds[NUM_LEDS];

void initializeLEDs()
{
    FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
    FastLED.setBrightness(20);
    setColor(0, 0, 255);
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