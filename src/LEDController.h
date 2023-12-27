#include <ArduinoJson.h>

void updateLEDColor(const StaticJsonDocument<200>& doc);
void setColorFromHexString(const String& hexColor);
void setColor(int r, int g, int b);
