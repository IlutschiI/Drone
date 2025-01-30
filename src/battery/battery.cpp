#include "battery.h"
int getBatteryLevel(uint8_t pin)
{
    // Battery State of Charge (SoC) -> voltage
    //  100% ->  8.40V
    //  95%  ->  8.30V
    //  90%  ->  8.22V
    //  85%  ->  8.16V
    //  80%  ->  8.05V
    //  75%  ->  7.97V
    //  70%  ->  7.91V
    //  65%  ->  7.83V
    //  60%  ->  7.75V
    //  55%  ->  7.71V
    //  50%  ->  7.67V
    //  45%  ->  7.63V
    //  40%  ->  7.59V
    //  35%  ->  7.57V
    //  30%  ->  7.53V
    //  25%  ->  7.49V
    //  20%  ->  7.45V
    //  15%  ->  7.41V
    //  10%  ->  7.37V
    //  5%   ->  7.22V
    //  0%   ->  6.55V
    float voltage = getBatteryVoltage(pin);
    if (voltage > 8.3)
    {
        return 100;
    }
    else if (voltage > 8.22)
    {
        return 95;
    }
    else if (voltage > 8.16)
    {
        return 90;
    }
    else if (voltage > 8.05)
    {
        return 85;
    }
    else if (voltage > 7.97)
    {
        return 80;
    }
    else if (voltage > 7.91)
    {
        return 75;
    }
    else if (voltage > 7.83)
    {
        return 70;
    }
    else if (voltage > 7.75)
    {
        return 65;
    }
    else if (voltage > 7.71)
    {
        return 60;
    }
    else if (voltage > 7.67)
    {
        return 55;
    }
    else if (voltage > 7.63)
    {
        return 50;
    }
    else if (voltage > 7.59)
    {
        return 45;
    }
    else if (voltage > 7.57)
    {
        return 40;
    }
    else if (voltage > 7.53)
    {
        return 35;
    }
    else if (voltage > 7.49)
    {
        return 30;
    }
    else if (voltage > 7.45)
    {
        return 25;
    }
    else if (voltage > 7.41)
    {
        return 20;
    }
    else if (voltage > 7.37)
    {
        return 15;
    }
    else if (voltage > 7.22)
    {
        return 10;
    }
    else if (voltage > 6.55)
    {
        return 5;
    }
    return 0;
}

float getBatteryVoltage(uint8_t pin)
{
    int voltageSensorValue = analogRead(A0);
    //Serial.print("voltage: ");
    //Serial.println(voltageSensorValue);
    float voltage = voltageSensorValue * (5 / 1023.0) * 2;
    return voltage;
}
