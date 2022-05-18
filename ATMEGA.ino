#include <avr/sleep.h>
#include <ArduinoJson.h>

//Arduino

#define echoPin 12 // attach pin D2 Arduino to pin Echo of HC-SR04
#define trigPin 11 //attach pin D3 Arduino to pin Trig of HC-SR04
const int buttonPin = 2; //Button to perform interrupt

// defines variables
long duration; // variable for theduration of sound wave travel
int distance; // variable for the distance measurement

void setup() {
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPin, INPUT_PULLUP); // Sets the echoPin as an INPUT
  digitalWrite(trigPin, HIGH); 
  
  Serial.begin(9600); // // Serial Communication is starting with 9600 of baudrate speedS
 
}

void loop() {

   detachInterrupt(0);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
  // Displays the distance on the Serial Monitor
  
  DynamicJsonDocument doc(1024);
  doc["sensor"]= 9;
  doc["distance"] = distance;
  doc["site"] = 2;
  String jsonStr;
  serializeJson(doc, jsonStr);
  
  Serial.println(jsonStr);
  delay(2000);
  Going_to_sleep();
}

void Going_to_sleep() {
sleep_enable();

  attachInterrupt(0,wakeUp,FALLING);
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
  digitalWrite(trigPin, LOW);
  sleep_cpu();
  
  //Serial.println("Just woke up!");
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
}

void wakeUp() {
  sleep_disable();
     
}
