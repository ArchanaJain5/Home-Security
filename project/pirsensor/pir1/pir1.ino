void setup() {

  pinMode(8, INPUT); //Pin 2 as INPUT

  pinMode(12, OUTPUT); //PIN 3 as OUTPUT

}


void loop() {

  if (digitalRead(8) == HIGH) // check if PIR is triggered.

  {
    Serial.println("Motion detected!");

  digitalWrite(12, HIGH);   // turn the LED/Buzz ON

  delay(100);                       // wait for 100 msecond

  digitalWrite(12, LOW);   // turn the LED/Buzz OFF

  delay(100);                       // wait for 100 msecond

  }

}
