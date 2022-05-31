#include <Arduino.h>
#include <SoftwareSerial.h>

// Quick conversion from the Braccio angle system to radians
float b2a(float b);

// Quick conversion from radians to the Braccio angle system
float a2b(float a);

String readStringUntil(SoftwareSerial serial, char terminator);