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

//Battery State of Charge (SoC) -> voltage
// 100% ->  8.40V
// 95%  ->  8.30V
// 90%  ->  8.22V
// 85%  ->  8.16V
// 80%  ->  8.05V
// 75%  ->  7.97V
// 70%  ->  7.91V
// 65%  ->  7.83V
// 60%  ->  7.75V
// 55%  ->  7.71V
// 50%  ->  7.67V
// 45%  ->  7.63V
// 40%  ->  7.59V
// 35%  ->  7.57V
// 30%  ->  7.53V
// 25%  ->  7.49V
// 20%  ->  7.45V
// 15%  ->  7.41V
// 10%  ->  7.37V
// 5%   ->  7.22V
// 0%   ->  6.55V
