/**
 * Created by K. Suwatchai (Mobizt)
 *
 * Email: k_suwatchai@hotmail.com
 *
 * Github: https://github.com/mobizt/Firebase-ESP-Client
 *
 * Copyright (c) 2022 mobizt
 *
 */

#if defined(ESP32)
#include <WiFi.h>
#elif defined(ESP8266)
#include <ESP8266WiFi.h>
#endif

#include <Firebase_ESP_Client.h>

// Provide the token generation process info.
#include <addons/TokenHelper.h>

// Provide the RTDB payload printing info and other helper functions.
#include <addons/RTDBHelper.h>

/* 1. Define the WiFi credentials */
#define WIFI_SSID "JioFi"
#define WIFI_PASSWORD "chai1115"

/* 2. Define the API Key */
#define API_KEY "AIzaSyDpplKB_Cko3-k4XZczdcE9v_lJGmc2EWo"

/* 3. Define the RTDB URL */
#define DATABASE_URL "https://esp-02-default-rtdb.firebaseio.com" //<databaseName>.firebaseio.com or <databaseName>.<region>.firebasedatabase.app

/* 4. Define the user Email and password that alreadey registerd or added in your project */
#define USER_EMAIL "dhriti.cp@gmail.com"
#define USER_PASSWORD "dhriti1234"

// Define Firebase Data object
FirebaseData fbdo;
FirebaseData fbdo_m1;

FirebaseData fbdo_t1;
FirebaseData fbdo_t2;

FirebaseAuth auth;
FirebaseConfig config;

unsigned long sendDataPrevMillis = 0;
unsigned long cnt=0;
unsigned long ent=0;

int count = 0;

uint32_t idleTimeForStream = 15000;

const int ledPin1 = D6; //GPIO12
const int ledPin2 = D7; //GPIO13
const int swPin1 = D1; //GPIO5
const int swPin2 = D2; //GPIO4
bool swState = false;
int tank_status=0;

void setup()
{
  Serial.begin(115200);
    pinMode(ledPin1, OUTPUT);
    pinMode(swPin1, INPUT_PULLUP);
    pinMode(ledPin2, OUTPUT);
    pinMode(swPin2, INPUT_PULLUP);
    digitalWrite(ledPin1,LOW);
    digitalWrite(ledPin2,LOW);
    
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
   
  if (!Firebase.RTDB.beginStream(&fbdo_m1, "/Nodes/motor1"))
    Serial.printf("sream begin error, %s\n\n", fbdo_m1.errorReason().c_str());
  if (!Firebase.RTDB.beginStream(&fbdo_t1, "/Nodes/tank1"))
    Serial.printf("sream begin error, %s\n\n", fbdo_t1.errorReason().c_str());
    
}

void loop()
{
  if (Firebase.ready())
  {
    if (!Firebase.RTDB.readStream(&fbdo_m1))
      Serial.printf("sream read error, %s\n\n", fbdo_m1.errorReason().c_str());
    if (fbdo_m1.streamTimeout())
    {
      Serial.println("stream timed out, resuming...\n");
        if (!fbdo_m1.httpConnected())
        Serial.printf("error code: %d, reason: %s\n\n", fbdo_m1.httpCode(), fbdo_m1.errorReason().c_str());
    }

    if (!Firebase.RTDB.readStream(&fbdo_t1))
      Serial.printf("sream read error, %s\n\n", fbdo_t1.errorReason().c_str());
    if (fbdo_t1.streamTimeout())
    {
      Serial.println("stream timed out, resuming...\n");
        if (!fbdo_t1.httpConnected())
        Serial.printf("error code: %d, reason: %s\n\n", fbdo_t1.httpCode(), fbdo_t1.errorReason().c_str());
    }
    
    if (fbdo_m1.streamAvailable())
    {
      Serial.printf("value, %s\n\n", fbdo.stringData().c_str());     
      String s1 = fbdo_m1.stringData().c_str();
      int i1 = s1.toInt();
      if(i1 != 1000)
      {
      Serial.printf("Int Value %s", s1);
         digitalWrite(ledPin1,HIGH);
         Serial.println("Motor is on ........");
         delay(i1);
         digitalWrite(ledPin1,LOW);
         Firebase.RTDB.setInt(&fbdo_m1, F("/Nodes/motor1"), 1000);
         Serial.println("Motor is off ........ data reset");
         delay(5000);
      }
    }

    if ((digitalRead(swPin1) == 0) && (tank_status!=1))
    {
        delay(2000);
        Firebase.RTDB.setInt(&fbdo_t1, F("/Nodes/tank1"), 2000);
        Serial.println("Tank is full ......");
        delay(2000);
        Firebase.RTDB.setInt(&fbdo_t1, F("/Nodes/tank1"), 20000);
        Serial.println("Tank is full ......");
        delay(2000);
        Firebase.RTDB.setInt(&fbdo_t1, F("/Nodes/tank1"), 2000);
        Serial.println("Tank is full ......");
        tank_status=1;
    }

    if ((digitalRead(swPin2) == 0) && (tank_status!=2))
    {
        delay(2000);
        Firebase.RTDB.setInt(&fbdo_t1, F("/Nodes/tank1"), 3000);
        Serial.println("Tank is empty ........");
        delay(2000);
        Firebase.RTDB.setInt(&fbdo_t1, F("/Nodes/tank1"), 30000);
        Serial.println("Tank is empty ........");
        delay(2000);
        Firebase.RTDB.setInt(&fbdo_t1, F("/Nodes/tank1"), 3000);
        Serial.println("Tank is empty ........");
        tank_status=2;
    }
  }
 // ESP.deepSleep(60e6);
 delay(10000);
 cnt=cnt+1;
 ent=ent+1;
 Serial.println(cnt);
 Serial.println(ent);
 if(ent==2160){
         digitalWrite(ledPin1,HIGH);
         Serial.println("Motor is on ........");
         delay(180000);
         digitalWrite(ledPin1,LOW);
         Serial.println("Motor is off ........ data reset");
         ent=0;
 }
}
