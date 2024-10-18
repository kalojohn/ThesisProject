// +international_country_code + phone number
// Portugal +351, example: +351912345678
String phoneNumber = "306944531881";
String apiKey = "5752796";

void sendMessage(String message){

  // Data to send with HTTP POST
  String url = "http://api.callmebot.com/whatsapp.php?phone=" + phoneNumber + "&apikey=" + apiKey + "&text=" + urlEncode(message);
  WiFiClient client;    
  HTTPClient http;
  http.begin(client, url);

  // Specify content-type header
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");
  
  // Send HTTP POST request
  int httpResponseCode = http.POST(url);
  if (httpResponseCode == 200){
    Serial.println("Message sent successfully");
  }
  else{
    Serial.println("Error sending the message");
    Serial.print("HTTP response code: ");
    Serial.println(httpResponseCode);
  }

  // Free resources
  http.end();
}


#define MAX_VOLUME  300 //in grams --> equivalent to milliliters
#define FREEZE_TEMP  20 //temperature in Celcius under which we send an alert 
#define PRESENCE_DISTANCE  10 //distance in centimeters under which it indicates that someone is present
#define REPORT_INTERVAL 600000  // 10 minutes in milliseconds (600,000 ms)

unsigned long volume_lastReportTime = 0;  // Variable to store the last event report time
unsigned long volumeLoss_lastReportTime = 0;  // Variable to store the last event report time
unsigned long temperature_lastReportTime = 0;  // Variable to store the last event report time
unsigned long distance_lastReportTime = 0;  // Variable to store the last event report time

bool distFirstOccurrence = true;
bool volumeFirstOccurrence = true;
bool tempFirstOccurrence = true;
bool volumeLossFirstOccurence = true;


void checkMeasurements(float volume, float maxVolume, float temperature, float distance)
{
  if (distance < PRESENCE_DISTANCE && ((distFirstOccurrence || (millis() - distance_lastReportTime >= REPORT_INTERVAL))))
    {
      distFirstOccurrence = false;
      distance_lastReportTime = millis();
      distAlert = true;
    }

    if (temperature < FREEZE_TEMP && ((tempFirstOccurrence || (millis() - temperature_lastReportTime >= REPORT_INTERVAL))))
    {
      tempFirstOccurrence = false;
      temperature_lastReportTime = millis();
      tempAlert = true;
    }

    if (volume > 0.9 * MAX_VOLUME && ((volumeFirstOccurrence || (millis() - volume_lastReportTime >= REPORT_INTERVAL))))
    {
      volumeFirstOccurrence = false;
      volume_lastReportTime = millis();
      weightAlert = true;
    }

    if (maxVolume > 100 && volume < 0.95*maxVolume && ((volumeLossFirstOccurence || (millis() - volumeLoss_lastReportTime >= REPORT_INTERVAL))))
    {
      volumeLossFirstOccurence = false;
      volumeLoss_lastReportTime = millis();
      weightLossAlert = true;
    }
}