<div align="center">
<h1>
    Kirosha-Team/Listener
</h1>
C++ library for communication between smart devices and gestures' controllable smart station.
</div>

## Getting started

### Hardware requirements

> [!NOTE]
> The library requires board with **ESP8266 chip**.

``ESP8266 Board``

##

### Software requirements

``Arduino IDE``

##

### Installation

> [!TIP]
> We recommend downloading the latest release to avoid bugs.

1. Add library to the sketch:

   ```
   Sketch -> Include library -> Add .ZIP library... -> select/downloaded/library
   ```

##

### Usage

> [!CAUTION]
> Don't try to initialize library twice, otherwise an error will occur

First, the **Listener** class is created. After that, we use the **begin** method to connect our smart device to gestures' controllable smart station. The **get** method is used to receive data, and the **send** method is used to send data.

```c++
// imports Listener library
#include <Listener.h>

char *server_ip = ""; // your gestures' controllable smart station ip address
int server_port = 8888; // your gestures' controllable smart station port (default is 8888)

int client_port = 9999; // your device port (default is 9999)

const char *ssid = ""; // your Wi-Fi ssid (name)
const char *password = ""; // your Wi-Fi password

char *device_data = ""; // your device data

// initializes Listener library
Listener listener(server_ip, server_port, client_port, ssid, password);

void setup() {
  // connects to your gestures' controllable smart station
  listener.begin(device_data);
}

void loop() {
  // gets data from your gestures' controllable smart station
  char *received_data = listener.get();

  if (received_data == "your message here") {
    // sends data to your gestures' controllable smart station
    listener.send("your message here");
  }

  // delay for 0.1 second
  delay(100);
}
```

## Contribution
Pull requests are welcome. For major changes, please open an issue first
to discuss what you would like to change.
