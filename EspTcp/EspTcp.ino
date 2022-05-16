
#include <ArduinoJson.h>
#include <WiFi.h>

const char* ssid = "AndroidAP";
const char* password = "12345678";

const uint16_t port = 9999;
const char * host = "Lizas-MacBook-Pro.local";

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("...");
  }
  Serial.print("WiFi connected with IP: "); 
  Serial.println(WiFi.localIP());
}


void loop() {


  DynamicJsonDocument doc(1024);
  doc["sensor"]= 11;
  doc["flow_rate"] = 150;
  doc["site"] = 2;
  String jsonStr; 
  serializeJson(doc, jsonStr);
 
  WiFiClient client;
  if (!client.connect(host, port)) {
    Serial.println("Connection to host failed");
    delay(1000);
    return;
  }


  
  Serial.println("Connected to server successful!");
  client.print(jsonStr);
  
  Serial.println("Disconnecting..."); 
  client.stop();
  delay(10000);

  
}
