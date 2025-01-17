#include <Arduino.h>
#include <Servo.h>
#include <networking/networkingController.h>
#include <battery/battery.h>

Servo pwm;
NetworkingController networkingController;

void setup()
{
  Serial.begin(9600);
  // wait for serial port to connect
  while (!Serial)
  {
    ;
  }
  networkingController.start();
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(6, OUTPUT);
  pwm.attach(6, 1000, 2000);
  pwm.write(0);
}

bool increase = true;

void loop()
{

  networkingController.handlePendingRequests([](Request request) -> void {
    pwm.write(request.power);
  });

  getBatteryLevel(A0);
  delay(100);
}
