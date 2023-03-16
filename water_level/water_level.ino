const int trigPin = D1;
const int echoPin = D2;

//define sound velocity in cm/uS
#define SOUND_VELOCITY 0.034
#define CM_TO_INCH 0.393701

long duration;
float distanceCm;
float distanceInch;


void setup() {
  Serial.begin(115200); // Starts the serial communication
  pinMode(D5, OUTPUT);
  pinMode(D6, OUTPUT);
  pinMode(D7, OUTPUT);
  pinMode(D8, OUTPUT);
  // Buzzer LED 
  pinMode(D4, INPUT_PULLUP);
  pinMode(D3, OUTPUT);  

  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
}

void loop() {
  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  
  // Calculate the distance
  distanceCm = duration * SOUND_VELOCITY/2;
  
  // Convert to inches
  distanceInch = distanceCm * CM_TO_INCH;
  //=====================================================================================

  // Prints the distance on the Serial Monitor
  Serial.print("Distance (cm):\n ");
  Serial.println(distanceCm);
  Serial.print("Distance (inch): ");
  Serial.println(distanceInch);
     
if(digitalRead(D4)==0){
    read_function();
  }     
  if(distanceInch<=40){
    digitalWrite(D5, HIGH);   
    delay(5000);
  }
  else{     
    digitalWrite(D5, LOW); 
    tank_empty();        
  }

  delay(1000);
  
  if (digitalRead(D3)==0) 
  {
   // blink();
  } 
  
  if(distanceInch<=30){
    Serial.print("level 2nd=\n");
    digitalWrite(D6, HIGH);
   // delay(2000); 
  }
  else{
    digitalWrite(D6, LOW);
  }
  
  if(distanceInch<=20){
    Serial.print("level 3rd=\n");
    digitalWrite(D7, HIGH);
   // delay(2000);
  }
  else{
    digitalWrite(D7, LOW);
  }
  
  if(distanceInch<=10){
    digitalWrite(D8, HIGH);
    tank_full();
    delay(5000);
  }
  else{
    digitalWrite(D8, LOW);    
  }
  delay(1000);
  
}
 
 void tank_empty(){
   Serial.println("Tank is empty now....");
   for(int i=1; i<=10;i++)
   {
     Serial.println("Empty and Slow Blink....");
     digitalWrite(D3,LOW);
     delay(500);
     digitalWrite(D3,HIGH);  
     delay(500);  
   }
     digitalWrite(D3,LOW);
 }

 void tank_full() {
   Serial.println("Tank is full now....");
   for(int i=1; i<=20;i++)
   {
     Serial.println("Full and Fast Blink....");
     digitalWrite(D3,LOW);
     delay(200);
     digitalWrite(D3,HIGH);  
     delay(200);  
   }
     digitalWrite(D3,LOW);
  } 

  void memory_read(){
    //added new function to read memory
    int n1;
    int n2;
    int sum=n1+n2;
    Serial.println(sum...);
  }





// void blink(){
//     for(int i=1; i<=10;i++)
//     {
//       Serial.println("blink.....");
//         digitalWrite(D4,HIGH);
//         delay(200);
//         digitalWrite(D4,LOW);
//         delay(200);
//     }

  
