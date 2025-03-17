// name: Listener.cpp
// desc: simple solution for communication between smart device and gcss
// creator: @kpers
// date: 03.03.2025

// requires Built-In libraries
#include "Arduino.h"
#include "Listener.h"
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

WiFiUDP udp; // initializes WiFiUDP library

char packet_buffer[255]; // data size

// Listener function
// creates a new listener
// returns void
Listener::Listener(
  char *server_ip,     //
  int server_port,     //
                       //
  int client_port,     // board and Wi-Fi info
                       //
  const char *ssid,    //
  const char *password //
)
{
  _running = false; // variable

  _server_ip = server_ip;         //
  _server_port = server_port;     //
                                  //
  _client_port = client_port;     // board and Wi-Fi info
                                  //
  _ssid = ssid;                   //
  _password = password;           //
}

// send_server function
// sends signal to the server
// returns void
void Listener::send(
  const char *data // data to send
) 
{
  udp.beginPacket(_server_ip, _server_port); // establishes a connection with a remote device to send data via UDP

  char buffer[30];

  sprintf(buffer, data); // debugs data

  udp.printf(buffer); // sends data to the server

  udp.endPacket(); // finish sending data to the server
}

// get_from_server function
// receives signal from server
// returns data
char *Listener::get(

) 
{
  int packet_size = udp.parsePacket(); // checks for the presence of a received UDP packet and returns its size

  if (packet_size) {
    Serial.print("[DEBUG]: Received packet from: "); Serial.println(udp.remoteIP()); // debugs info about sender

    int len = udp.read(packet_buffer, 10); // reads UDP data into the specified buffer

    Serial.printf("Data: %s\n", packet_buffer); //
                                                // debugs data
    Serial.println();                           //

    return packet_buffer; // returns received data
  }

  return "----------"; // returns no data
}

// begin function
// initializes listener
// returns void
void Listener::begin(
  const char *board_info // board info
)
{
  Serial.begin(115200); // initializes Serial
  
  WiFi.begin(_ssid, _password); // initializes Wifi
  
  while (WiFi.status() != WL_CONNECTED) { //
    delay(500); Serial.print(F("."));     // loops until board connects to the Wifi
  }                                       //

  udp.begin(_client_port); // initializes port update
  
  Serial.printf("[DEBUG]: Connected to the WiFi with local port: %s:%i \n", WiFi.localIP().toString().c_str(), _client_port); // debugs successful connection

  while (_running == false) {                           //
    send(board_info);                                   //
                                                        //
    Serial.print("[DEBUG]: Waiting for a response..."); //
    Serial.println();                                   //
                                                        //
    delay(2000);                                        //
                                                        // loops until board pairs with gcss
    if (String(get()) == "successful") {                //
      Serial.print("[DEBUG]: Pairing successful");      //
      Serial.println();                                 //
                                                        //
      break;                                            //
    }                                                   //
  }                                                     //
}