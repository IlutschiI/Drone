#include "battery.h"
float getBatteryLevel(uint8_t pin)
{
    int voltageSensorValue = analogRead(A0);
    float voltage = voltageSensorValue * (5 / 1023.0) * 2;
    Serial.print("voltage of battery: ");
    Serial.print(voltage);
    Serial.println("V");
    return voltage;
}