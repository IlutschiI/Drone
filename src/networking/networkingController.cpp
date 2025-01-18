#include "networkingController.h"
#include <WiFiNINA.h>
#include <Arduino.h>
#include <ArduinoJson.h>

char ssid[] = "ArduinoDrone";
char pass[] = "password";
WiFiServer server(80);

NetworkingController::NetworkingController()
{
}

void NetworkingController::start()
{
    Serial.print("Current firmware is: ");
    Serial.println(WiFi.firmwareVersion());
    Serial.print("Latest Firmware is: ");
    Serial.println(WIFI_FIRMWARE_LATEST_VERSION);

    Serial.println("starting AP");
    int status = WiFi.beginAP(ssid, pass);
    Serial.print("Ap starting Status: ");
    Serial.println(status);

    server.begin();
}

void NetworkingController::handlePendingRequests(Response (*callback)(Request))
{
    //Serial.println("checking new requests...");
    WiFiClient client = server.available();

    if (client)
    {                                 // if you get a client,
        Serial.println("new client"); // print a message out the serial port
        String currentLine = "";      // make a String to hold incoming data from the client
        String request = "";
        while (client.connected())
        { // loop while the client's connected
            if (client.available())
            {                           // if there's bytes to read from the client,
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
        JsonDocument requestJson;
        deserializeJson(requestJson, body);
        int power = requestJson["power"];
        Serial.print("power: ");
        Serial.println();
        Serial.println(body);

        Request requestStruct;
        requestStruct.power = power;

        Response response = callback(requestStruct);
        JsonDocument responseJson;
        responseJson["batterySoC"]=response.batterySoC;
        responseJson["batteryVoltage"]=response.batteryVoltage;

        // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
        // and a content-type so the client knows what's coming, then a blank line:
        client.println("HTTP/1.1 200 OK");
        client.println("Content-type: application/json");
        client.print("Content-Length: ");
        client.println(measureJsonPretty(responseJson));
        client.println();
        
        serializeJsonPretty(responseJson, client);

        client.stop();
    }
}
