// name: Listener.cpp
// desc: simple solution for communication between smart device and gcss
// creator: @kpers
// created: 03.03.2025
// updated: 25.04.2025

#include "Arduino.h"
#include "Listener.h"
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

WiFiUDP udp;

char *no_result = "----------"

char packet_buffer[255];

// Listener function
// creates a new listener
// returns void
Listener::Listener(
  char *server_ip,
  int server_port,

  int client_port,

  const char *ssid,
  const char *password
)
{
  _running = false;

  _server_ip = server_ip;
  _server_port = server_port;

  _client_port = client_port;

  _ssid = ssid;
  _password = password;
}

// send_server function
// sends signal to the server
// returns void
void Listener::send(
  const char *data
) 
{
  udp.beginPacket(_server_ip, _server_port);

  char buffer[30];

  sprintf(buffer, data);

  udp.printf(buffer);

  udp.endPacket();
}

// get_from_server function
// receives signal from server
// returns data
char *Listener::get(

) 
{
  int packet_size = udp.parsePacket();

  if (packet_size) {
    Serial.print("[DEBUG]: Received packet from: ");
    Serial.println(udp.remoteIP());
    Serial.print(packet_buffer)

    int len = udp.read(packet_buffer, 10);

    String message = String(packet_buffer);

    return message;
  }

  return no_result;
}

// begin function
// initializes listener
// returns void
void Listener::begin(
  const char *board_info
)
{
  Serial.begin(115200);
  
  WiFi.begin(_ssid, _password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    
    Serial.print(F("."));
  }

  udp.begin(_client_port);
  
  Serial.printf("[DEBUG]: Connected to the WiFi with local port: %s:%i", WiFi.localIP().toString().c_str(), _client_port);
  Serial.println();

  while (_running == false) {
    send(board_info);

    Serial.print("[DEBUG]: Waiting for a response...");
    Serial.println();

    delay(2000);

    if (String(get()) == "successful") {
      Serial.print("[DEBUG]: Pairing successful");
      Serial.println();

      break;
    }
  }
}
