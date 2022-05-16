#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <WiFi.h>

//for interrupt
const byte inpin = 32;

//for uart
#define RXD2 16
#define TXD2 17

#define uS_TO_S_FACTOR 1000000ULL


const char* ssid = "Cgarden 2";
const char* password = "9497238183";

const uint16_t port = 9999;
const char * host = "192.168.1.32";

RTC_DATA_ATTR int bootCount = 0;
WiFiClient espClient;


void setup() {
  
  Serial.begin(115200);
  Serial2.begin(9600, SERIAL_8N1, RXD2, TXD2);
  bootCount++;
  Serial.println("Boot number: " + String(bootCount));
  Serial.println("Hello, ESP32!");
  String jsonStr;

  print_wakeup_reason();
  uint64_t sleep_time_min = 5; //setting sleeptime

  //sending interrupt pin
  pinMode(inpin, OUTPUT); 
  digitalWrite(inpin, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);                       // wait for a second
  digitalWrite(inpin, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);
 
 //Json object
//  DynamicJsonDocument doc(1024);
//  doc["sensor"]= 11;
//  doc["flow_rate"] = 230;
//  doc["site"] = 2;
//  serializeJson(doc, jsonStr);
  
//receive data on serial
  //another way
  while(Serial.available() == 0) { 
    }
  
  jsonStr = Serial.readString();
  Serial.println(jsonStr);
  
 
  //Conecting to Wi-Fi
  Serial.print("Connecting to ");
  Serial.println(ssid);
  wifiConnect();
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  //TCP connection
  Serial.println(host); 
  if (!espClient.connect(host, port)) {
 
     Serial.println("Connection to host failed");
    Serial.println(espClient.connect(host, port));
    delay(1000);
   
  }
  else{
    Serial.println("TCP Connected");
    espClient.print(jsonStr);
  
  } 

//ESP to sleep mode
  esp_sleep_enable_timer_wakeup(sleep_time_min * 60 *uS_TO_S_FACTOR); //should be in microsec
  Serial.println("The module goes to sleep for: ");
  Serial.println(sleep_time_min * uS_TO_S_FACTOR);
  Serial.println("Going to sleep...");
  Serial.flush(); 
  
  esp_deep_sleep_start();
  
  Serial.println("This will never be printed");
  
}

void print_wakeup_reason(){
  esp_sleep_wakeup_cause_t wakeup_reason;

  wakeup_reason = esp_sleep_get_wakeup_cause();

  switch(wakeup_reason)
  {
    case ESP_SLEEP_WAKEUP_EXT0 : Serial.println("Wakeup caused by external signal using RTC_IO"); break;
    case ESP_SLEEP_WAKEUP_EXT1 : Serial.println("Wakeup caused by external signal using RTC_CNTL"); break;
    case ESP_SLEEP_WAKEUP_TIMER : Serial.println("Wakeup caused by timer"); break;
    case ESP_SLEEP_WAKEUP_TOUCHPAD : Serial.println("Wakeup caused by touchpad"); break;
    case ESP_SLEEP_WAKEUP_ULP : Serial.println("Wakeup caused by ULP program"); break;
    default : Serial.printf("Wakeup was not caused by deep sleep: %d\n",wakeup_reason); break;
  }
}

void wifiConnect() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
}

void loop() {

  
}
