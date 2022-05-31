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

    pinMode(BLUETOOTH_READ, INPUT);
    pinMode(BLUETOOTH_WRITE, OUTPUT);

    Serial.begin(9600);
    BT.begin(9600);

    robot.stop();

    // set the arm to an initial position
    //robot.move_clamp(550, 0, 50);
    Serial.println("Hello World !");
}

String readStringUntil2(char terminator)
{
    String str;

    while (BT.available())
    {
        delay(1);
        char c = BT.read();
        if (c == terminator)
        {
            break;
        }

        str += c;
    }

    return str;
}

void loop()
{
    if (!BT.available())
        return;

    String data = readStringUntil2('\n'); // read the data received

    if (data.length() == 0)
    {
        return;
    }

    // Serial.println("data : " + data);

    StaticJsonDocument<200> json;
    deserializeJson(json, data);
    //JsonObject obj = json.to<JsonObject>();
    const char *type = json["type"];
    Serial.println(type);

    if (strcmp(type, "OPEN_CLOSE_CLAMP") == 0)
    {
        boolean val = json["value"];
        Serial.println(val);
        if (val)
        {
            robot.move_forward();
        }
        else
        {
            robot.move_backward();
        }

        robot.set_clamp_oppened(json["value"]);
    }
    else if (strcmp(type, "MOVE_ROBOT") == 0 /*&& obj.containsKey("angle") && obj.containsKey("strength") */)
    {
        int angle = json["angle"];
        int strengh = json["strength"];
        Serial.print("angle: ");
        Serial.print(angle);
        Serial.print("strength: ");
        Serial.println(strengh);

        if (strengh == 0)
        {
            robot.stop();
        }
        else if (angle > 50 && angle < 130)
        {
            robot.move_forward();
        }
        else if (angle > 130 && angle < 230)
        {
            robot.move_left();
        }
        else if (angle > 230 && angle < 330)
        {
            robot.move_backward();
        }
        else if (angle > 330 || angle < 50)
        {
            robot.move_right();
        }
        else
        {
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
    //  }
}
