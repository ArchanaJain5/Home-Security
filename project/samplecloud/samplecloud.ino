#include <ThingSpeak.h>
#include <ESP8266WiFi.h>

// Network Parameters
const char* ssid     = "SSSSSSS";
const char* password = "PPPPPPPPPP";

// ThingSpeak information
char thingSpeakAddress[] = "api.thingspeak.com";
unsigned long channelID = NNNNNN;
char* readAPIKey = "XXXXXXXXXXXXXXXX";
char* writeAPIKey = "YYYYYYYYYYYYYYYY";
const unsigned long postingInterval = 120L * 1000L;
unsigned int dataFieldOne = 1;                            // Field to write temperature data
unsigned int dataFieldTwo = 2;                       // Field to write temperature data
unsigned int dataFieldThree = 3;                     // Field to write elapsed time data
unsigned int aField = 6;                             //Field to hold first constant of the thermistor calibration                
unsigned int bField = 7;                             //Field to hold second constant of the thermistor calibration
unsigned int cField = 8;                             //Field to hold third constant of the thermistor calibration

// Global variables
// These constants are device specific.  You will need to get them from the manufacturer or determine them yourself.
float aConst = 2.25E-02;   
float bConst = -0.003422894649;
float cConst = 0.00001518485044;

unsigned long lastConnectionTime = 0;
long lastUpdateTime = 0; 
WiFiClient client;                                  

void setup() {

Serial.begin(9600);
Serial.println("Start");
connectWiFi();

// Read the constants at startup.
aConst = readTSData( channelID, aField );
bConst = readTSData( channelID, bField );
cConst = readTSData( channelID, cField );
}

void loop() {
    
    // Only update if posting time is exceeded
    if (millis() - lastUpdateTime >=  postingInterval) {
        
        float fahrenheitTemperature, celsiusTemperature;
        
        lastUpdateTime = millis();
        
        float readValue = analogRead(A0);
        float logR = log( 10000 * ( 1024 / readValue - 1 ));                 // Separate the calculation for simplicity and debugging
        
        celsiusTemperature = 1 / ( aConst + bConst * logR + cConst * pow(logR,3) ) - 273.15;   // Calculate the temperature in Celsius
        fahrenheitTemperature = celsiusTemperature * 9 / 5 + 32;
        Serial.println("ADC =  " + String( readValue )+ " Temp = "+String( fahrenheitTemperature ));
        write2TSData( channelID , dataFieldOne , celsiusTemperature , dataFieldTwo , fahrenheitTemperature , dataFieldThree , millis() );      // Write the temperature in F, C, and time since starting.
    }
}

int connectWiFi(){
    
    while (WiFi.status() != WL_CONNECTED) {
      
        WiFi.begin( ssid, password );
        delay(2500);
        Serial.println("Connecting to WiFi");
    }
    
    Serial.println( "Connected" );
    ThingSpeak.begin( client );
}

  float readTSData( long TSChannel,unsigned int TSField ){
    
  float data =  ThingSpeak.readFloatField( TSChannel, TSField, readAPIKey );
  Serial.println( " Data read from ThingSpeak: " + String( data, 9 ) );
  return data;
  
}

// Use this function if you want to write a single field
int writeTSData( long TSChannel, unsigned int TSField, float data ){
  int  writeSuccess = ThingSpeak.writeField( TSChannel, TSField, data, writeAPIKey ); // Write the data to the channel
  if ( writeSuccess ){
    
    Serial.println( String(data) + " written to Thingspeak." );
    }
    
    return writeSuccess;
}

//use this function if you want multiple fields simultaneously
int write2TSData( long TSChannel, unsigned int TSField1, float field1Data, unsigned int TSField2, long field2Data, unsigned int TSField3, long field3Data ){

  ThingSpeak.setField( TSField1, field1Data );
  ThingSpeak.setField( TSField2, field2Data );
  ThingSpeak.setField( TSField3, field3Data );
   
  int writeSuccess = ThingSpeak.writeFields( TSChannel, writeAPIKey );
  return writeSuccess;
}
