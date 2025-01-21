#include <Arduino.h>
#include <Servo.h>
#include <networking/networkingController.h>
#include <battery/battery.h>

Servo pwm;
Servo pwm2;
NetworkingController networkingController;

void _calibrateESC(){
  pwm.write(180);
  pwm2.write(180);
  Serial.println("connect power now...");
  delay(10000);
  pwm.write(180);
  pwm2.write(180);
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
  pwm.attach(6, 1000, 2000);
  pwm2.attach(5, 1000, 2000);
  //_calibrateESC();
  networkingController.start();
}

bool increase = true;
int power = 0;

void loop()
{
  networkingController.handlePendingRequests([](Request request) -> Response { // pwm.write(request.power);
    power = request.power;
    return Response{.batterySoC = getBatteryLevel(A0), .batteryVoltage = getBatteryVoltage(A1)};
  });
  pwm.write(power);
  pwm2.write(power);
}
