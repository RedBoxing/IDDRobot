#include <Arduino.h>
#include <SoftwareSerial.h>

#include "robot.h"

#define BLUETOOTH_READ 6
#define BLUETOOTH_WRITE 7

Robot robot;

SoftwareSerial BT(BLUETOOTH_READ, BLUETOOTH_WRITE);