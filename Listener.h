// name: Listener.h
// desc: header for Listener.cpp
// creator: @kpers
// date: 03.03.2025

// defines Listener library
#ifndef LISTENER_H
#define LISTENER_H

// requires Built-In libraries
#include "Arduino.h"

// creates new class
class Listener
{
  public:
    // Listener function
    // creates a new listener
    // returns void
    Listener(
      char *server_ip,     //
      int server_port,     //
                           //
      int client_port,     // board and Wi-Fi info
                           //
      const char *ssid,    //
      const char *password //
    );

    // send_server function
    // sends signal to the server
    // returns void
    void send(
      const char *data // data to send
    );

    // get_from_server function
    // receives signal from server
    // returns data
    char *get(

    );

    // begin function
    // initializes listener
    // returns void
    void begin(
      const char *board_info // board info
    );

  private:
    bool _running; // variable

    char *_server_ip;      //
    int _server_port;      //
                           //
    int _client_port;      // board and Wi-Fi info
                           //
    const char *_ssid;     //
    const char *_password; //
};

// closes directive
#endif