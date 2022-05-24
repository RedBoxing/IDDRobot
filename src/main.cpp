#include "main.h"
#include "utils.h"
#include "ArduinoJson.h"

// https://github.com/cgxeiji/CGx-InverseK

void setup()
{
    /* ------------------------------- */
    /* Initialize the motors        */
    /* ------------------------------- */

    /* ------------------------------- */
    /* Initialize the bluetooth        */
    /* ------------------------------- */

    Serial.begin(9600);
    BT.begin(9600);

    // set the arm to an initial position
    //robot.move_clamp(550, 0, 50);
}

void loop() 
{
    while (true)
    { // if data is received by the bluetooth module
        if (BT.available() > 0)
        {
            String data = readStringUntil(BT, '\n'); // read the data received
            Serial.println(data);

            StaticJsonDocument<200> json;
            deserializeJson(json, data);
            char *type = json["type"];

            if (type == "OPEN_CLOSE_CLAMP")
            {
                robot.set_clamp_oppened(json["value"]);
            }
            else if (type == "MOVE_ROBOT") {
                int angle = json["angle"];
                int strengh = json["strength"];

                if (angle > 90 && angle < 180) {
                    robot.move_forward();
                }
                else if(angle < 90) {
                    robot.move_left();
                }
                else if (angle > 180 && angle < 280) {
                    robot.move_right();
                } else if(angle > 280) {
                    robot.move_backward();
                } else {
                    robot.stop();
                }
            }
            else if (type == "MOVE_CLAMP")
            {
             /*   if (json.("value"))
                {
                    char *value = json[value];
                    if (value == "forward")
                    {
                        move_clamp(last_x + 50, last_y, last_z);
                    }
                    else if (value == "backward")
                    {
                        move_clamp(last_x - 50, last_y, last_z);
                    }
                }
                else if (json.hasOwnProperty("pos"))
                {
                    JSONVar pos = json["pos"];
                    float a0, a1, a2, a3;

                    if (InverseK.solve(pos["x"], pos["y"], pos["z"], a0, a1, a2, a3))
                    {
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
                    }*/
              //  }
            }
        }
    }
}
