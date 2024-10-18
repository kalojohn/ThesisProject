This is the source code for the Arduino IDE of my Thesis Project.

Please do the following steps in order to compile the code successfully.

1) Install Arduino IDE
2) Go to File --> Preferences --> Settings Tab --> Additional boards manager URLs and add the following URL: http://arduino.esp8266.com/stable/package_esp8266com_index.json
3) Install the following libraries: DallasTemperature, HX711_Arduino_Library, OneWire, Pushbutton, UrlEncode
4) Replace the WiFi credentials in file NodeMCU_main/NodeMCU_main.ino
5) Replace CallMeBot phoneNumber and apiKey in file NodeMCU_main/sendWhatsApp.ino
