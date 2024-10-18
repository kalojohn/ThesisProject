/**
 * Complete project details at https://RandomNerdTutorials.com/arduino-load-cell-hx711/
 *
 * HX711 library for Arduino - example file
 * https://github.com/bogde/HX711
 *
 * MIT License
 * (c) 2018 Bogdan Necula
 *
**/
// Includes
#include <Arduino.h>
#include "HX711.h"
#include <Pushbutton.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <SoftwareSerial.h>

//Defines
#define BUTTON_PIN 4

//Button
Pushbutton button(BUTTON_PIN);
// Setup a oneWire instance to communicate with any OneWire devices
volatile bool start_Tx = false;

void setup() {

  serialCom_init();
  tempSensor_init();
  distSensor_init();
  scale_init();

  interrupts_init();
}

void loop() {

  if (button.getSingleDebouncedPress()){
    // Serial.println("tare...");
    loadcell_tare();
  }
  
  if (start_Tx == true)
  {
    noInterrupts();
    sendMeasurements();
    start_Tx = false;
    interrupts();
  }
  
}

