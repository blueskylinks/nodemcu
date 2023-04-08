int count=0;

void setup() {
  Serial.begin(115200);
  count=1;
  pinMode(D3, INPUT_PULLUP);
  pinMode(D5,OUTPUT);
  pinMode(D6,OUTPUT);
  pinMode(D7,OUTPUT);
  pinMode(D8,OUTPUT);
  Serial.println("connected...");

}

void loop() {
    if(digitalRead(D3)==0){
     Memory_read();   
     if(count == 4){
       count=count+1;
   }

  switch(count)
  {
  case 1:
      digitalWrite(D5, HIGH);
      break;
  case 2:
      digitalWrite(D6, HIGH);
      break;
  case 3:
      digitalWrite(D7, HIGH);
      break;
  case 4:
      digitalWrite(D8, HIGH);
      break;
      default:
  digitalWrite(D5, LOW);
  digitalWrite(D6, LOW);
  digitalWrite(D7, LOW);
  digitalWrite(D8, LOW);
       count= 0;
       break;  
  }
  delay(300);

}

}

void Memory_read(){
  Serial.println("LED NO...");
  Serial.println(count); 
}
