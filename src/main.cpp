#include <Arduino.h>
#include <Servo.h>
#include <WiFiNINA.h>
#include <ArduinoJson.h>

char ssid[] = "ArduinoDrone";
char pass[] = "password";
WiFiServer server(80);
int status = WL_IDLE_STATUS;

Servo pwm;

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
  pwm.attach(6, 1000, 2000);
  pwm.write(0);

  Serial.print("Current firmware is: ");
  Serial.println(WiFi.firmwareVersion());
  Serial.print("Latest Firmware is: ");
  Serial.println(WIFI_FIRMWARE_LATEST_VERSION);

  Serial.println("starting AP");
  status = WiFi.beginAP(ssid, pass);
  Serial.print("Ap starting Status: ");
  Serial.println(status);

  server.begin();
}

bool increase = true;

void loop()
{

  WiFiClient client = server.available();

  if (client)
  {                               // if you get a client,
    Serial.println("new client"); // print a message out the serial port
    String currentLine = "";      // make a String to hold incoming data from the client
    String request = "";
    while (client.connected())
    { // loop while the client's connected
      if (client.available())
      {                         // if there's bytes to read from the client,
        char c = client.read(); // read a byte, then
        request += c;
      }
      else
      {
        break;
      }
    }

    int bodyStart = request.indexOf('{');
    int bodyEnd = request.lastIndexOf('}');
    String body = request.substring(bodyStart, bodyEnd + 1);
    JsonDocument doc;
    deserializeJson(doc, body);
    int power = doc["power"];
    Serial.print("power: ");
    Serial.println();
    Serial.println(body);

    pwm.write(power);

    // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
    // and a content-type so the client knows what's coming, then a blank line:
    client.println("HTTP/1.1 200 OK");
    client.println("Content-type:text/html");
    client.println();
    // the content of the HTTP response follows the header:
    client.print("Hello World!");
    // The HTTP response ends with another blank line:
    client.println();

    client.stop();
  }

  int voltageSensorValue = analogRead(A0);
  float voltage = voltageSensorValue * (5/1023.0) *2;
  Serial.print("voltage of battery: ");
  Serial.print(voltage);
  Serial.println("V");
  delay(100);
}
