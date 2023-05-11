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

  pinMode(D4, OUTPUT);
  pinMode(D5, OUTPUT);
  pinMode(D6, OUTPUT);
  pinMode(D7, OUTPUT);
  pinMode(D8, OUTPUT);
   
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
  
     
  if(digitalRead(D3)==0){
       Serial.println("Connected..");   
       read_function();
    }    
  if(distanceInch<=50 && distanceInch>=35){
    Serial.print("level 10%\n");    
    tank_empty();      
  }

  if(distanceInch<=35 && distanceInch>=24){
    Serial.print("level 25%\n");
    digitalWrite(D5, HIGH);   
  }
  else{     
    digitalWrite(D5, LOW);        
  }

  if(distanceInch<=24 && distanceInch>=16 ){
    Serial.print("level 50%\n");
    digitalWrite(D6, HIGH);
  }
  else{
    digitalWrite(D6, LOW);
  }
  
  if(distanceInch<=16 && distanceInch>=7 ){
    Serial.print("level 75%\n");
    digitalWrite(D7, HIGH);
  }
  else{
    digitalWrite(D7, LOW);
  }
  
  if(distanceInch<=7 ){
    Serial.print("level 100%\n");    
    tank_full();
  }
  else{
    digitalWrite(D8, LOW);    
  } 
  delay(1000);
}
 
    void tank_empty(){
     Serial.println("Tank is empty now....");
     for(int i=1; i<=5;i++)
     {
       Serial.println("Empty and Slow Blink....");
        digitalWrite(D4,HIGH);
        delay(1000);
        digitalWrite(D4,LOW);  
        delay(1000);  
      }
      delay(20000);
    }

    void tank_full() {
      Serial.println("Tank is full now....");
      for(int i=1; i<=20;i++)
     {
        Serial.println("Full and Fast Blink....");
        digitalWrite(D8,HIGH);
        delay(200);
        digitalWrite(D8,LOW);  
        delay(200);  
     }
     delay(20000);
    } 

    void read_function(){
        Serial.print("Hello world...");
        delay(5000);  
    }        


  
