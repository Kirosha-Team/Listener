// name: Listener.h
// desc: header for Listener.cpp
// creator: @kpers
// created: 03.03.2025
// updated: 25.04.2025

#ifndef LISTENER_H
#define LISTENER_H

#include "Arduino.h"

class Listener
{
  public:
    // Listener function
    // creates a new listener
    // returns void
    Listener(
      char *server_ip,
      int server_port,

      int client_port,

      const char *ssid,
      const char *password
    );

    // send_server function
    // sends signal to the server
    // returns void
    void send(
      const char *data
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
      const char *board_info
    );

  private:
    bool _running;

    char *_server_ip;
    int _server_port;

    int _client_port;

    const char *_ssid;
    const char *_password;
};

#endif
