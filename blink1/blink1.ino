/*
  Blink

  Turns an LED on for one second, then off for one second, repeatedly.

  Most Arduinos have an on-board LED you can control. On the UNO, MEGA and ZERO
  it is attached to digital pin 13, on MKR1000 on pin 6. LED_BUILTIN is set to
  the correct LED pin independent of which board is used.
  If you want to know what pin the on-board LED is connected to on your Arduino
  model, check the Technical Specs of your board at:
  https://www.arduino.cc/en/Main/Products

  modified 8 May 2014
  by Scott Fitzgerald
  modified 2 Sep 2016
  by Arturo Guadalupi
  modified 8 Sep 2016
  by Colby Newman

  This example code is in the public domain.

  https://www.arduino.cc/en/Tutorial/BuiltInExamples/Blink
*/
int count;
// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
 Serial.begin(115200);
  count=1;
  pinMode(D5, OUTPUT);
  pinMode(D2, INPUT_PULLUP);

  digitalWrite(D5,LOW);
  Serial.println("Fast Blink Start....");
  for(int i=1; i<=10;i++)
  {
    digitalWrite(D5,HIGH);
    delay(200);
    digitalWrite(D5,LOW);
    delay(200);
  }
 Serial.println("Fast Blink End..");
}
// the loop function runs over and over again forever
void loop() {
  if(digitalRead(D2)==0){
    blink_fast();
    delay(3000);
  }

  digitalWrite(D5, HIGH);  // turn the LED on (HIGH is the voltage level)
  // Serial.println("High..");
  delay(1000);                      // wait for a second
  digitalWrite(D5, LOW);   // turn the LED off by making the voltage LOW
 // Serial.println("Low..");  
  delay(1000);                      // wait for a second
 // Serial.print("count=");
  Serial.println(count);    
  if (count==10){
    count=0; 
    blink_fast();
  }
//   count=count+5;
  count++;
}  


void blink_fast(){
  for(int i=1; i<=10;i++)
  {
    digitalWrite(D5,HIGH);
    delay(200);
    digitalWrite(D5,LOW);
    delay(200);
  }
}
