const int trigPin = D1;
const int echoPin = D2;

//define sound velocity in cm/uS
#define SOUND_VELOCITY 0.034
#define CM_TO_INCH 0.393701

long  duration;
float distanceCm;
float distanceInch;
int   tank_size, len;
float cap;
int cap1;
int count=0;

void setup() {
  Serial.begin(115200); // Starts the serial communication
  tank_size=40;
  len=tank_size/10;
  pinMode(D4, OUTPUT);
  pinMode(D5, OUTPUT);  //GPIO14
  pinMode(D6, OUTPUT);  //GPIO12
  pinMode(D7, OUTPUT);  //GPIO13
  pinMode(D8, OUTPUT);
  pinMode(D3, INPUT_PULLUP); 
  tank_blinkall();
  // Buzzer LED 
 

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
  cap=distanceInch/(len*1.5);
  Serial.print("Capacity:");
  cap1=(((int)cap)+0);
  Serial.println(cap1);

  switch(cap1){

    case 1:
      digitalWrite(D4,HIGH);
      digitalWrite(D5,LOW);
      digitalWrite(D6,LOW);
      digitalWrite(D7,LOW);
      digitalWrite(D8,LOW); 
      Serial.println("Level 1 Full");
      tank_full();
    break;

    case 2:
      digitalWrite(D4,LOW);
      digitalWrite(D5,HIGH);
      digitalWrite(D6,LOW);
      digitalWrite(D7,LOW);
      digitalWrite(D8,LOW); 
      Serial.println("Level 2");
    break;

    case 3: 
      digitalWrite(D4,LOW);
      digitalWrite(D5,LOW);
      digitalWrite(D6,HIGH);
      digitalWrite(D7,LOW);
      digitalWrite(D8,LOW); 
      Serial.println("Level 3");
    break;

    case 4:
      digitalWrite(D4,LOW);
      digitalWrite(D5,LOW);
      digitalWrite(D6,LOW);
      digitalWrite(D7,HIGH);
      digitalWrite(D8,LOW); 
      Serial.println("Level 4");
    break;

    case 5:
      digitalWrite(D4,LOW);
      digitalWrite(D5,LOW);
      digitalWrite(D6,LOW);
      digitalWrite(D7,HIGH);
      digitalWrite(D8,LOW); 
      Serial.println("Level 5");
    break;

    case 6:
      digitalWrite(D4,LOW);
      digitalWrite(D5,LOW);
      digitalWrite(D6,LOW);
      digitalWrite(D7,LOW);
      digitalWrite(D8,HIGH); 
      Serial.println("Level 6 Empty");
      tank_empty();
      break;

    case 7:
      digitalWrite(D4,LOW);
      digitalWrite(D5,LOW);
      digitalWrite(D6,LOW);
      digitalWrite(D7,LOW);
      digitalWrite(D8,HIGH); 
      Serial.println("Level 7 Empty");
      tank_empty();
      break;
      
    default:
      digitalWrite(D4,LOW);
      digitalWrite(D5,LOW);
      digitalWrite(D6,LOW);
      digitalWrite(D7,LOW);
      digitalWrite(D8,LOW);                                
   }
    delay(1000);
    count=count+1;
    Serial.println(count);
    if(count>=60){
      Serial.println("Sleep Mode Start.....");
      ESP.deepSleep(1200e6);
    }
 }

 void tank_full(){
  for(int i=0;i<=20; i++){
    digitalWrite(D4,HIGH);
    delay(200);
    digitalWrite(D4,LOW);
    delay(200);
  }
  delay(10000);
 }

   void tank_empty(){
    for(int i=0;i<=10; i++){
    digitalWrite(D8,HIGH);
    delay(1000);
    digitalWrite(D8,LOW);
    delay(1000);
  }
  delay(10000);
 }

  void tank_blinkall(){
     
     digitalWrite(D4,HIGH);
     delay(200);
     digitalWrite(D5,HIGH);
     delay(200);
     digitalWrite(D6,HIGH);
     delay(200);
     digitalWrite(D7,HIGH);
     delay(200);
     digitalWrite(D8,HIGH);     
     delay(1000);

     digitalWrite(D4,LOW);
     digitalWrite(D5,LOW);
     digitalWrite(D6,LOW);
     digitalWrite(D7,LOW);
     digitalWrite(D8,LOW);     
  
  }
  /*
  count=count+1;
  if(count>=24){
    ESP.deepSleep(1200e6);
  }  */
