#define SERIAL_TX 10
#define SERIAL_RX 11

SoftwareSerial espSerial(SERIAL_TX, SERIAL_RX);

float weight = 0;
float temperature = 0;
float distance = 0;
String str;

void serialCom_init()
{
  espSerial.begin(115200);
}

void sendMeasurements()
{
  weight = getWeight();
  temperature = ((float)((int)(10*getTemp())))/10;
  distance = ((float)((int)(10*getDist())))/10;

  str = String(weight) + "," + String(temperature) + "," + String(distance);
  espSerial.println(str);
}