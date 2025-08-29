# ESP32-Wireless-LED-Dimmer
Dim the onboard LED through WIFI by sending TCP packets which are then sent as UDP to your ESP32.
## How to build
Build using ESP-IDF, in terminal do "idf.py create project ....." then cd into the directory and add the WIFI_PWM_CMD file. Go into the newly created project, and run "idf.py build". Flash onto the ESP32 using "idf.py flash", then compile and run the GUI as well as the client and everything should run smoothly.
