#define ONE_WIRE_BUS 5 // Data wire of Temperature Sensor connected to digital pin 5

OneWire oneWire(ONE_WIRE_BUS);
// Pass our oneWire reference to Dallas Temperature sensor 
DallasTemperature sensors(&oneWire);

void tempSensor_init()
{
  sensors.begin();
}

void tempSensor_main()
{
  // Call sensors.requestTemperatures() to issue a global temperature and Requests to all devices on the bus
  sensors.requestTemperatures(); 
  
  Serial.print("Celsius temperature: ");
  // Why "byIndex"? You can have more than one IC on the same bus. 0 refers to the first IC on the wire
  Serial.println(sensors.getTempCByIndex(0));
}

float getTemp()
{
  sensors.requestTemperatures(); 
  return sensors.getTempCByIndex(0);
}