#include <Arduino.h>
#include <Servo.h>
#include <networking/networkingController.h>

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

  int voltageSensorValue = analogRead(A0);
  float voltage = voltageSensorValue * (5/1023.0) *2;
  Serial.print("voltage of battery: ");
  Serial.print(voltage);
  Serial.println("V");
  delay(100);
}
