#include <Arduino.h>
#include <SoftwareSerial.h>

#include "robot.h"

#define WHEAL_MOTOR_1 2
#define WHEAL_MOTOR_2 3

Robot robot;

SoftwareSerial BT(4, 2);