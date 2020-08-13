//FirebaseESP8266.h must be included before ESP8266WiFi.h
#include "FirebaseESP8266.h"
#include "LineNotifyESP8266.h"
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <SoftwareSerial.h>

SoftwareSerial Uno(D5, D6);//(RX/TX)

// 設定網路SSID跟密碼
#define WIFI_SSID "AutoBrake"
#define WIFI_PASSWORD "nlhs7626"
// 設定Firebase
#define FIREBASE_HOST "autobrake-84e92.firebaseio.com"
#define FIREBASE_AUTH "eL9pA7WHnLM0lghZfsQIQ2Vv9c8Zn80RTvoYSH9T"

//設定Line Notify
#define LINE_TOKEN "7QajKfF3dmXdEUiZD3RYg7UqycW9RzPHqIB8HNcNe8N"

// 設定ThingSpeak WRITE API KEY
const char* apiKey = "YWC4QOQSQDNRHQEJ";
const char* resource = "/update?api_key=";

// Thing Speak API server
const char* server = "api.thingspeak.com";

// 定義 FirebaseESP8266 資料物件
FirebaseData firebaseData;

//void printJsonObjectContent(FirebaseData &data);


void setup() {
  // Initializing serial port for debugging purposes
  Serial.begin(9600);
  Uno.begin(9600);
  delay(50);

  pinMode(D5, INPUT);

  pinMode(D6, OUTPUT);
  pinMode(D4, OUTPUT);

  pinMode(D7, INPUT_PULLUP); //enable pull-up resistor

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

  digitalWrite(4, HIGH);

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);

  //Set database read timeout to 1 minute (max 15 minutes)
  Firebase.setReadTimeout(firebaseData, 1000 * 60);
  //tiny, small, medium, large and unlimited.
  //Size and its write timeout e.g. tiny (1s), small (10s), medium (30s) and large (60s).
  Firebase.setwriteSizeLimit(firebaseData, "tiny");

}

int B = -7626;
int T = -7626;
int S = -7626;
int E = 0;
char Err[14];

int L = -7626;
String lon = "";
String lat = "尚未取得";
int tsk = 20;


void loop() {
  while (Uno.available()) {
    char inbox = Uno.read();
    switch (inbox) {
      case 'B':
        B = Uno.parseInt();
        Serial.print("電量：");
        Serial.println(B);
        break;
      case 'T':
        T = Uno.parseInt();
        Serial.print("溫度：");
        Serial.println(T);
        break;
      case 'S':
        S = Uno.parseInt();
        Serial.print("速度：");
        Serial.println(S);
        break;
      case 'E':
        E = Uno.parseInt();
        for (int i = 0; i < E; i++){
          Err[i] = Uno.read();
        }
        Serial.print("危險：");
        Serial.println(E);
        break;
    }
  }


  //----------------Thingspeak----------------//
  if (tsk == 20) {
    tsk = 0;
    String thingspeak = "&field1=";
    if (B != -7626) {
      thingspeak = thingspeak + B;
    }
    if (T != -7626) {
      thingspeak = thingspeak + "&field2=" + T;
    }
    if (S != -7626) {
      thingspeak = thingspeak + "&field3=" + S;
    }
    Serial.println("thingspeak值");
    Serial.println(thingspeak);
    WiFiClient client;
    // 使用 80 Port 連線
    if (client.connect(server, 80)) {
      Serial.println(F("connected"));
    }
    else  {
      Serial.println(F("connection failed"));
      return;
    }
    Serial.print("Request resource: ");
    Serial.println(resource);
    client.print(String("GET ") + resource + apiKey + thingspeak +
                 " HTTP/1.1\r\n" +
                 "Host: " + server + "\r\n" +
                 "Connection: close\r\n\r\n");
    int timeout = 5 * 10; // 5 seconds
    while (!!!client.available() && (timeout-- > 0)) {
      delay(100);
    }
    if (!client.available()) {
      Serial.println("No response, going back to sleep");
    }
    while (client.available()) {
      Serial.write(client.read());
    }
    Serial.println("\nclosing connection");
    client.stop();
  }
  //----------------Thingspeak----------------//


  //----------------Firebase----------------//

  String path = "/autobrake";

  FirebaseJson json;

  Serial.println("------------------------------------");
  Serial.println("Uploading Data...");

  Firebase.setInt(firebaseData, path + "/battery" , B);
  Serial.println("Battery Passed");
  Firebase.setInt(firebaseData, path + "/temp" , T);
  Serial.println("Temp Passed");
  Firebase.setInt(firebaseData, path + "/error" , E);
  Serial.println("Error Passed");
  if (S != -7626) {
    Firebase.setInt(firebaseData, path + "/speed" , S);
    Serial.println("Speed Passed");
  }


  if (Firebase.getString(firebaseData, path + "/lon"))
  {
    Serial.println("lon:");
    lon = firebaseData.stringData();
    Serial.println(lon);
  }
  if (Firebase.getString(firebaseData, path + "/lat"))
  {
    Serial.println("lat:");
    lat = firebaseData.stringData();
    Serial.println(lat);
  }

  //  else
  //  {
  //    Serial.println("FAILED");
  //    Serial.println("REASON: " + firebaseData.errorReason());
  //    Serial.println("------------------------------------");
  //    Serial.println();
  //  }

  //-----------Firebase----------//




  boolean swState = digitalRead(D7);
  Serial.print("危險按鈕:");
  Serial.println(swState);
  if (swState == LOW) { //switch pressed
    L = 1;
  }

  //-----------LineNotify--------//
  if (L != -7626) {
    String Send = "";
    if (L = 1) {
      if (lon != "-7626" && lat != "-7626") {
        Send = "***警告*** 發生危險,目前位置:https://www.google.com/maps?q=" +
               lat.substring(0, lat.indexOf(".") + 7) +
               "," +
               lon.substring(0, lon.indexOf(".") + 7);
        LineNotifyHTTPClient net;
        lineNotify.init(&net, LINE_TOKEN);

        uint8_t status;

        status = lineNotify.sendLineMessage(Send);
        if (status == LineNotifyESP8266::LineStatus::SENT_COMPLETED)
        {
          Serial.println("Send text message completed");
          Serial.println("Text message limit: " + String(lineNotify.textMessageLimit()));
          Serial.println("Text message remaining: " + String(lineNotify.textMessageRemaining()));
          Serial.println("Image message limit: " + String(lineNotify.imageMessageLimit()));
          Serial.println("Image message remaining: " + String(lineNotify.imageMessageRemaining()));
        }
        else if (status == LineNotifyESP8266::LineStatus::SENT_FAILED)
          Serial.println("Send text message was failed!");
        else if (status == LineNotifyESP8266::LineStatus::CONNECTION_FAILED)
          Serial.println("Connection to LINE sevice faild!");
        else if (status == LineNotifyESP8266::LineStatus::NOT_INITIALIZED)
          Serial.println("Line notify was not initialized!");
        Serial.println();



        lineNotify.end();
        L = -7626;
      }
    }
  }
  //-----------LineNotify--------//



  tsk++;
}
