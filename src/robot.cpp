#include "robot.h"
#include "InverseK.h"
#include "utils.h"

#define MOTOR_A_DIRECTION 12
#define MOTOR_B_DIRECTION 13

#define MOTOR_A_PWM 3
#define MOTOR_B_PWM 11

#define CLAMP_MOTOR 5

Robot::Robot()
{

    pinMode(MOTOR_A_PWM, OUTPUT);
    pinMode(MOTOR_B_PWM, OUTPUT);

    //clamp.attach(CLAMP_MOTOR);

    /* ------------------------------- */
    /* Initialize the kinematics       */
    /* ------------------------------- */

    // Setup the lengths and rotation limits for each link
    /*   Link base, upperarm, forearm, hand;

    base.init(0, b2a(0.0), b2a(180.0));
    upperarm.init(200, b2a(15.0), b2a(165.0));
    forearm.init(200, b2a(0.0), b2a(180.0));
    hand.init(270, b2a(0.0), b2a(180.0));

    // Attach the links to the inverse kinematic model
    InverseK.attach(base, upperarm, forearm, hand);*/
}

void Robot::move_clamp(int x, int y, int z)
{
    float a0, a1, a2, a3;

    if (InverseK.solve(x, y, z, a0, a1, a2, a3))
    {
        last_x = x;
        last_y = y;
        last_z = z;

        Serial.print(a2b(a0));
        Serial.print(',');
        Serial.print(a2b(a1));
        Serial.print(',');
        Serial.print(a2b(a2));
        Serial.print(',');
        Serial.println(a2b(a3));
    }
    else
    {
        Serial.println("No solution found!");
    }
}

void Robot::setRightSpeed(int speed)
{
    if (speed < 0)
    {
        speed = -speed;
        digitalWrite(MOTOR_B_DIRECTION, LOW);
    }
    else
    {
        digitalWrite(MOTOR_B_DIRECTION, HIGH);
    }

    analogWrite(MOTOR_B_PWM, speed);
}

void Robot::setLeftSpeed(int speed)
{
    if (speed < 0)
    {
        speed = -speed;
        digitalWrite(MOTOR_A_DIRECTION, LOW);
    }
    else
    {
        digitalWrite(MOTOR_A_DIRECTION, HIGH);
    }

    analogWrite(MOTOR_A_PWM, speed);
}

void Robot::stop()
{
    setLeftSpeed(0);
    setRightSpeed(0);
}

void Robot::move_forward()
{
    setLeftSpeed(100);
    setRightSpeed(100);
}

void Robot::move_backward()
{
    setLeftSpeed(-100);
    setRightSpeed(-100);
}

void Robot::move_left()
{
    setLeftSpeed(-100);
    setRightSpeed(100);
}

void Robot::move_right()
{
    setLeftSpeed(100);
    setRightSpeed(-100);
}

void Robot::set_clamp_oppened(bool opened)
{
    clamp.write(opened ? 180 : 0);
}