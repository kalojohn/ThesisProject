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

