#include <utils.h>

float b2a(float b)
{
    return b / 180.0 * PI - HALF_PI;
}

// Quick conversion from radians to the Braccio angle system
float a2b(float a)
{
    return (a + HALF_PI) * 180 / PI;
}

String readStringUntil(SoftwareSerial BT, char terminator)
{
    String str;

    while (BT.available())
    {
        char c = BT.read();
        if (c == terminator)
        {
            break;
        }

        str += c;
    }

    return str;
}