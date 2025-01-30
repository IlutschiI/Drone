#include <Arduino.h>
#include <Servo.h>
#include <networking/networkingController.h>
#include <battery/battery.h>

Servo pwm = Servo();
Servo pwm2 = Servo();
Servo pwm3 = Servo();
Servo pwm4 = Servo();
NetworkingController networkingController;

float mapf(float x, float in_min, float in_max, float out_min, float out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void _calibrateESC(){
  pwm.write(180);
  pwm2.write(180);
  pwm3.write(180);
  pwm4.write(180);
  Serial.println("connect power now...");
  delay(5000);
  pwm.write(0);
  pwm2.write(0);
  pwm3.write(0);
  pwm4.write(0);
}

void setup()
{
  Serial.begin(9600);
  // wait for serial port to connect
  while (!Serial)
  {
    ;
  }
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pwm.attach(6, 1000, 2000);
  pwm2.attach(5, 1000, 2000);
  pwm3.attach(9, 1000, 2000);
  pwm4.attach(10, 1000, 2000);
  //_calibrateESC();
  networkingController.start();
}

int power = 0;
int batteryLevel = 0;
float batteryVoltage = 0;

void loop()
{
  networkingController.handlePendingRequests([](Request request) -> Response {
    power = mapf(request.power, 0.0, 1.0, 0.0, 180.0);
    Serial.print("power: ");
    Serial.println(power);
    //power = request.power;
    return Response{.batterySoC = batteryLevel, .batteryVoltage = batteryVoltage};
  });
  batteryLevel = getBatteryLevel(A1);
  batteryVoltage = getBatteryVoltage(A1);
  pwm.write(power);
  pwm2.write(power);
  pwm3.write(power);
  pwm4.write(power);
}
