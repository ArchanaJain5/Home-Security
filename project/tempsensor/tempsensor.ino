float temp;
int tempPin = 9; // Connect Vout to Analog0 or A0 on Arduino board.

void setup() {
   Serial.begin(9600);
}

void loop() {
  temp=analogRead(tempPin);          //read from A0
  temp=(temp/1024.0)*5.0;      //conversion to volts
  temp= temp*100.0;             //conversion to temp Celsius
  temp=temp*9/5+32;
   Serial.print("TEMPERATURE = ");
   Serial.print(temp); // display temperature value
   Serial.print("*F");
   Serial.println();
   delay(1000); // update sensor reading each one second
}
