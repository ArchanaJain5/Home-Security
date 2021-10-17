#include "ACS712.h"

char watt[5];
ACS712 sensor(ACS712_30A, 4);
unsigned long last_time =0;
unsigned long current_time =0;
float Wh =0 ;  
float temp;
int redled=16;
int greenled=5;
int tempPin = 2; // Connect Vout to Analog0 or A0 on Arduino board NODE D4.
int ledPin = 13;                // choose the pin for the LED nodeD7
int inputPin = 12;               // choose the input pin (for PIR sensor) node D6
int pirState = LOW;             // we start, assuming no motion detected
int val = 0;                    // variable for reading the pin status
 float V = 9; 
void setup() {
  pinMode(ledPin, OUTPUT);      // declare LED as output
  pinMode(inputPin, INPUT);     // declare sensor as input
pinMode(redled, OUTPUT);
pinMode(greenled, OUTPUT);
   Serial.begin(115200);
  sensor.calibrate();
 
}
 
void loop(){
  val = digitalRead(inputPin);  // read input value
  if (val == HIGH) {            // check if the input is HIGH
    digitalWrite(ledPin, HIGH);  // turn LED ON
    if (pirState == LOW) {
      // we have just turned on
      Serial.println("Motion detected!");
      // We only want to print on the output change, not state
      pirState = HIGH;
      temp = analogRead(tempPin);
   // read analog volt from sensor and save to variable temp
   temp = temp * 0.48828125;
   // convert the analog volt to its temperature equivalent
   Serial.print("TEMPERATURE = ");
   Serial.print(temp); // display temperature value
   Serial.print("*C");
   Serial.println();
   if(temp>=30) // fan on
   {
   digitalWrite(greenled, HIGH);  // turn GREENLED ON
  float I = sensor.getCurrentAC();
// Serial.println(I);
  float P = V * I;
  last_time = current_time;
  current_time = millis();    
  Wh = Wh+  P *(( current_time -last_time) /3600000.0) ; 
   }
   else // ac on
   {
    digitalWrite(redled, HIGH);  // turn REDLED ON
    float I = sensor.getCurrentAC();
// Serial.println(I);
  float P = V * I;
  last_time = current_time;
  current_time = millis();    
  Wh = Wh+  P *(( current_time -last_time) /3600000.0) ; 
   }
   delay(1000); // update sensor reading each one second
    }
  } else {
    
    digitalWrite(ledPin, LOW); // turn LED OFF
    if (pirState == HIGH){
      // we have just turned of
      Serial.println("Motion ended!");
      // We only want to print on the output change, not state
      pirState = LOW;
    }
  }
}
