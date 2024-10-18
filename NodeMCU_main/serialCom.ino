#define INT_TO_ARDUINO_PIN D7

String inputString = "";       // String to hold incoming data
String strValue1 = "Test values";
String strValue2 = "Second values";
String strValue3 = "fuck my life";

float volume = 0;
float temperature = 0;
float distance = 0;
float maxVolume = 0;


void serialCom_init()
{
  pinMode(INT_TO_ARDUINO_PIN, OUTPUT); // Set GPIO13 (D7) as an output to trigger interrupt to arduino
  // Open serial communications and wait for port to open:
  Serial.begin(115200);
  inputString.reserve(200);    // Reserve memory for the incoming string
}

void trigArduinoInt()
{
  digitalWrite(INT_TO_ARDUINO_PIN, HIGH);
  digitalWrite(INT_TO_ARDUINO_PIN, LOW);
}


void parseInput(String input) {
  // Assuming input is comma-separated (e.g., "12.34,45.67,89.01")
  int firstComma = input.indexOf(',');   // Find first comma
  int secondComma = input.indexOf(',', firstComma + 1);  // Find second comma

  // Extract substrings between the commas and convert to float
  if (firstComma != -1 && secondComma != -1) {
    strValue1 = input.substring(0, firstComma);                 // First float value
    strValue2 = input.substring(firstComma + 1, secondComma);   // Second float value
    strValue3 = input.substring(secondComma + 1);               // Third float value

    
    // Convert strings to floats
    volume = strValue1.toFloat();
    temperature = strValue2.toFloat();
    distance = strValue3.toFloat();

    if (volume > maxVolume) maxVolume = volume; // Save the maximum observed volume

    checkMeasurements(volume, maxVolume, temperature, distance);

    // Print values to verify
    Serial.print("weight: "); Serial.print(volume); Serial.println("ml");
    //Serial.print("weightMax: "); Serial.print(maxVolume); Serial.println("ml");
    Serial.print("temperature: "); Serial.print(temperature); Serial.println("degrees C");
    Serial.print("distance: "); Serial.print(distance); Serial.println("cm");
  }
}

void serialCom_request()
{
  trigArduinoInt();
  while(1)
  { 
    if(Serial.available())
    {
      char inChar = (char)Serial.read();   // Read each character
      inputString += inChar;

      // Check if we've reached the end of the input (newline or specific character)
      if (inChar == '\n') {
        // Process the string when newline is received
        parseInput(inputString);
        inputString = "";  // Clear the string for the next input
        break;
      } 
    }
  }
}