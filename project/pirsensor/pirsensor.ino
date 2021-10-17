
int ledPin = 12;                // choose the pin for the LED
int inputPin = 8;               // choose the input pin (for PIR sensor)
int pirState = LOW;             // we start, assuming no motion detected
int val = 0;                    // variable for reading the pin status
 float temp;
int tempPin = 9;
int AC =11;
void setup() {
  pinMode(ledPin, OUTPUT);      // declare LED as output
  pinMode(inputPin, INPUT);     // declare sensor as input
   pinMode(AC, INPUT);
 
  Serial.begin(9600);
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
      //temp sensor
      temp=analogRead(tempPin);          //read from A0
  temp=(temp/1024.0)*5.0;      //conversion to volts
  temp= temp*100.0;             //conversion to temp Celsius
  temp=temp*9/5+32;
  if(temp>200 && val== HIGH)
  {
    digitalWrite(AC, HIGH); //TURN ON AC
  }
  else
  {
    digitalWrite(AC, LOW); //TURN ON AC 
  }
   Serial.print("TEMPERATURE = ");
   Serial.print(temp); // display temperature value
   Serial.print("*F");
   Serial.println();
   delay(1000);
  
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
