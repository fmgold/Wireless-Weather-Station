#include <Arduino.h>
#include <WiFi.h>
#include <Firebase_ESP_Client.h>

#include <addons/TokenHelper.h>
#include <addons/RTDBHelper.h>

#include <LiquidCrystal_I2C.h> //This library you can add via Include Library > Manage Library > 
#include "DHT.h"

LiquidCrystal_I2C lcd(0x27, 20, 4);


#define WIFI_SSID "user"          //const char* ssid     = "Layomi"; const char* password = "Jesulayomi";   // input your home or public wifi name
#define WIFI_PASSWORD "999999999"                                   //password of wifi ssid

/* 2. Define the API Key */
#define API_KEY " "
//-----------------------------------------------------------------------
/* 3. Define the RTDB URL */
#define DATABASE_URL " "
//-----------------------------------------------------------------------

FirebaseJson jsonData;
FirebaseData fbdo;

FirebaseAuth auth;
FirebaseConfig config;

bool signupOK = false;

#define DHTPIN 14      // what pin we're connected to
#define DHTTYPE DHT11  // DHT 22  (AM2302)

DHT dht(DHTPIN, DHTTYPE);

//const int ldrPin = 35; // Analog pin for LDR

void setup() {
  lcd.init();
  lcd.backlight();

  Serial.begin(9600);
  dht.begin();
  lcd.setCursor(0, 0);  //move cursor to second line, first position
  lcd.print("WIRELESS WEATHER");
  lcd.setCursor(0, 1);  //move cursor to second line, first position
  lcd.print("MONITORING SYSTEM");
  delay(3000);  // wait 1sec
  lcd.clear();

  lcd.setCursor(0, 0);  //move cursor to second line, first position
  lcd.print("Connecting to");
  lcd.setCursor(0, 1);  //move cursor to second line, first position
  lcd.print(WIFI_SSID);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED)
  {
    lcd.setCursor(0, 0);  //move cursor to second line, first position
    lcd.print("not wifi available");
    lcd.print(".");
    Serial.print(".");
    delay(300);
  }
  lcd.clear();
  lcd.setCursor(0, 0);  //move cursor to second line, first position
  lcd.print("CONNECTION ESTABLISHED");
  delay(2000);

  lcd.clear();
  lcd.setCursor(0, 0);  //move cursor to second line, first position
  lcd.print("CONNECTED TO DATABASE");
  delay(2000);
  lcd.clear();



  //-----------------------------------------------------------------------
  Serial.printf("Firebase Client v%s\n\n", FIREBASE_CLIENT_VERSION);

  /* Assign the api key (required) */
  config.api_key = API_KEY;

  /* Assign the RTDB URL (required) */
  config.database_url = DATABASE_URL;

  /* Assign the callback function for the long running token generation task */
  config.token_status_callback = tokenStatusCallback; //see addons/TokenHelper.h
  //-----------------------------------------------------------------------
  /*Or Sign up */
  if (Firebase.signUp(&config, &auth, "", "")) {
    Serial.println("Firebase signUp ok");
    signupOK = true;
  }
  else {
    Serial.printf("%s\n", config.signer.signupError.message.c_str());
  }
  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);
  delay(1000);
}

void loop() {
  int lightIntensity = analogRead(LDR);
  int lightInt = map(lightIntensity, 0, 4023, 0, 100);
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t)) {
    lcd.print("dht not connected");
    Serial.println("Failed to read from DHT sensor!");
    return;
  }


  lcd.setCursor(0, 0);  //move cursor to second line, first position
  lcd.print("HUMIDITY = ");
  lcd.print(h);
  lcd.print("%");
  lcd.setCursor(0, 1);  //move cursor to second line, first position
  lcd.print("TEMP =");
  lcd.print(t);
  lcd.print("C");
  lcd.setCursor(0, 2);  //move cursor to second line, first position
  lcd.print("LIGHT INT =");
  lcd.print(lightInt);
  lcd.print("%");

  Firebase.RTDB.setFloat(&fbdo, "/Humidity", h);
  Firebase.RTDB.setFloat(&fbdo, "/Temperature", t);
  Firebase.RTDB.setFloat(&fbdo, "/Light", lightInt);
  delay(5000);  // wait 1sec
  lcd.clear();

}
