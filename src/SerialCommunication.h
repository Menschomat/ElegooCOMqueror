#include <ArduinoJson.h>

void initializeSerial();
void handleSerialInput();
void updateDirection(const StaticJsonDocument<200> &doc);
void updateSpeed(const StaticJsonDocument<200> &doc);
void reportDeserializationError(const DeserializationError &error);
