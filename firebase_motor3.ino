/**
 * Created by K. Suwatchai (Mobizt), contribution - chaitanya.csd@gmail.com
 * Email: k_suwatchai@hotmail.com
 * Github: https://github.com/mobizt/Firebase-ESP-Client
 * Copyright (c) 2022 mobizt
 */

#if defined(ESP32)
  #include <WiFi.h>
  const int ledPin = 16; //GPIO4 or D2 for LED
  const int swPin = 17;  //GPIO5 or D1 for Switch
  bool swState = false;
#endif
#if defined(ESP8266)
  #include <ESP8266WiFi.h>
  const int ledPin1 = D5; //GPIO14 or D5 for LED
  const int ledPin2 = D6; //GPIO12 or D6 for LED
  const int ledPin3 = D7; //GPIO13 or D7 for LED
  const int swPin = D1;  //GPIO5 or D1 for Switch
  bool swState = false;
#endif

#include <Firebase_ESP_Client.h>
// Provide the token generation process info.
#include <addons/TokenHelper.h>
// Provide the RTDB payload printing info and other helper functions.
#include <addons/RTDBHelper.h>

/* 1. Define the WiFi credentials */
#define WIFI_SSID "Airtel_9764005401"
#define WIFI_PASSWORD "air46403"

/* 2. Define the API Key */
#define API_KEY "AIzaSyDpplKB_Cko3-k4XZczdcE9v_lJGmc2EWo"
/* 3. Define the RTDB URL */
#define DATABASE_URL "https://esp-02-default-rtdb.firebaseio.com" //<databaseName>.firebaseio.com or <databaseName>.<region>.firebasedatabase.app
/* 4. Define the user Email and password that alreadey registerd or added in your project */
#define USER_EMAIL "dhriti.cp@gmail.com"
#define USER_PASSWORD "dhriti1234"
// Define Firebase Data object
FirebaseData fbdo1;
FirebaseData fbdo2;
FirebaseData fbdo3;

FirebaseAuth auth;
FirebaseConfig config;

unsigned long sendDataPrevMillis = 0;
int count = 0;
uint32_t idleTimeForStream = 15000;
int msec=1000;

void setup()
{
  Serial.begin(115200);

    pinMode(ledPin1, OUTPUT);
    pinMode(ledPin2, OUTPUT);
    pinMode(ledPin3, OUTPUT);
    pinMode(swPin, INPUT_PULLUP);
    digitalWrite(ledPin1,LOW);
    digitalWrite(ledPin2,LOW);
    digitalWrite(ledPin3,LOW);
    
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();
  Serial.printf("Firebase Client v%s\n\n", FIREBASE_CLIENT_VERSION);
  // For the following credentials, see examples/Authentications/SignInAsUser/EmailPassword/EmailPassword.ino
  /* Assign the api key (required) */
  config.api_key = API_KEY;
  /* Assign the user sign in credentials */
  auth.user.email = USER_EMAIL;
  auth.user.password = USER_PASSWORD;
  /* Assign the RTDB URL (required) */
  config.database_url = DATABASE_URL;
  /* Assign the callback function for the long running token generation task */
  config.token_status_callback = tokenStatusCallback; // see addons/TokenHelper.h
  // Or use legacy authenticate method
  // config.database_url = DATABASE_URL;
  // config.signer.tokens.legacy_token = "<database secret>";

  // To connect without auth in Test Mode, see Authentications/TestMode/TestMode.ino
  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);
  if (!Firebase.RTDB.beginStream(&fbdo1, "/test/stream2/node1"))
  Serial.printf("sream begin error, %s\n\n", fbdo1.errorReason().c_str());
  if (!Firebase.RTDB.beginStream(&fbdo2, "/test/stream2/node2"))
  Serial.printf("sream begin error, %s\n\n", fbdo2.errorReason().c_str());  
  if (!Firebase.RTDB.beginStream(&fbdo3, "/test/stream2/node3"))
  Serial.printf("sream begin error, %s\n\n", fbdo3.errorReason().c_str()); 
}

void loop()
{

  // Firebase.ready() should be called repeatedly to handle authentication tasks.
  /*
  if (Firebase.ready() && (millis() - sendDataPrevMillis > idleTimeForStream || sendDataPrevMillis == 0))
  {
    sendDataPrevMillis = millis();
    count++;
    // Due to single FirebaseData object used, stream connection will be interruped to send/receive data
    Serial.printf("Set string... %s\n\n", Firebase.RTDB.setString(&fbdo, "/test/stream/data", "Hello World! " + String(count)) ? "ok" : fbdo.errorReason().c_str());
  } */

  if (Firebase.ready())
  {
    
    if (!Firebase.RTDB.readStream(&fbdo1))
    Serial.printf("sream read error, %s\n\n", fbdo1.errorReason().c_str());
    if (fbdo1.streamTimeout())
    {
      Serial.println("stream timed out, resuming...\n");
      if (!fbdo1.httpConnected())
      Serial.printf("error code: %d, reason: %s\n\n", fbdo1.httpCode(), fbdo1.errorReason().c_str());
    }
    if (fbdo1.streamAvailable())
    {
      Serial.printf("node1 value, %s\n\n", fbdo1.stringData().c_str());
      //Serial.println(Firebase.getCurrentTime());
      String s1 = fbdo1.stringData().c_str();
      int i1 = s1.toInt();
      if(i1 != 0)
      {
         Serial.printf("Stream Value node1 = %s", s1);
         digitalWrite(ledPin1,HIGH);
         delay(i1*msec);
         digitalWrite(ledPin1,LOW);
         Serial.println("Data Reset .....");
         Firebase.RTDB.setInt(&fbdo1, F("/test/stream2/node1"), 0);
         delay(2000);
      }
    }

    if (!Firebase.RTDB.readStream(&fbdo2))
    Serial.printf("sream read error, %s\n\n", fbdo2.errorReason().c_str());
    if (fbdo2.streamTimeout())
    {
      Serial.println("stream timed out, resuming...\n");
      if (!fbdo2.httpConnected())
      Serial.printf("error code: %d, reason: %s\n\n", fbdo2.httpCode(), fbdo2.errorReason().c_str());
    }
    if (fbdo2.streamAvailable())
    {
      Serial.printf("node2 value, %s\n\n", fbdo2.stringData().c_str());
      //Serial.println(Firebase.getCurrentTime());
      String s1 = fbdo2.stringData().c_str();
      int i1 = s1.toInt();
      if(i1 != 0)
      {
         Serial.printf("Stream Value node2 = %s", s1);
         digitalWrite(ledPin2,HIGH);
         delay(i1*msec);
         digitalWrite(ledPin2,LOW);
         Serial.println("Data Reset .....");
         Firebase.RTDB.setInt(&fbdo2, F("/test/stream2/node2"), 0);
         delay(2000);
      }
    }

    if (!Firebase.RTDB.readStream(&fbdo3))
    Serial.printf("sream read error, %s\n\n", fbdo3.errorReason().c_str());
    if (fbdo3.streamTimeout())
    {
      Serial.println("stream timed out, resuming...\n");
      if (!fbdo3.httpConnected())
      Serial.printf("error code: %d, reason: %s\n\n", fbdo3.httpCode(), fbdo3.errorReason().c_str());
    }
    if (fbdo3.streamAvailable())
    {
      Serial.printf("node3 value, %s\n\n", fbdo3.stringData().c_str());
      //Serial.println(Firebase.getCurrentTime());
      String s1 = fbdo3.stringData().c_str();
      int i1 = s1.toInt();
      if(i1 != 0)
      {
         Serial.printf("Stream Value node3 = %s", s1);
         digitalWrite(ledPin3,HIGH);
         delay(i1*msec);
         digitalWrite(ledPin3,LOW);
         Serial.println("Data Reset .....");
         Firebase.RTDB.setInt(&fbdo3, F("/test/stream2/node3"), 0);
         delay(2000);
      }
    }
    
    if (digitalRead(swPin) == 0)
    {
         Serial.println("Trigger.........");
         Firebase.RTDB.setInt(&fbdo3, F("/test/stream2/node3"), 2);
         delay(1*msec);
         digitalWrite(ledPin3,HIGH);
         delay(10*msec);
         Firebase.RTDB.setInt(&fbdo3, F("/test/stream2/node3"), 0);
         digitalWrite(ledPin3,LOW);
    }
    
  }
}
