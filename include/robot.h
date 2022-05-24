#include <Arduino.h>
#include <Servo.h>

class Robot
{
public:
    Robot();

    void setRightSpeed(int speed);        // Fait
    void setLeftSpeed(int speed);         // Fait
    void stop();                          // Fait
    void move_forward();                  // Fait
    void move_backward();                 // Fait
    void move_left();                     // Fait
    void move_right();                    // Fait
    void move_clamp(int x, int y, int z); // Faits
    void set_clamp_oppened(bool opened);

private:
    int last_x = 0;
    int last_y = 0;
    int last_z = 0;

    Servo clamp;
};