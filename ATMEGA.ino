#include <avr/sleep.h>
#include <ArduinoJson.h>

#define echoPin 2 // attach pin D2 Arduino to pin Echo of HC-SR04
#define trigPin 3 //attach pin D3 Arduino to pin Trig of HC-SR04
const int buttonPin = 2; //Button to perform interrupt

// defines variables
long duration; // variable for the duration of sound wave travel
int distance; // variable for the distance measurement

void setup() {
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPin, INPUT_PULLUP); // Sets the echoPin as an INPUT
  digitalWrite(trigPin, HIGH);
  // pinMode(echoPin, INPUT);
  Serial.begin(9600); // // Serial Communication is starting with 9600 of baudrate speed
  Serial.println("Ultrasonic Sensor HC-SR04 Test"); // print some text in Serial Monitor
  Serial.println("with Arduino UNO R3");
}

void loop() {
  
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
  // Displays the distance on the Serial Monitor
  
  DynamicJsonDocument doc(1024);
  doc["sensor"]= 1;
  doc["water_depth"] = distance;
  doc["site"] = 2;
  String jsonStr;
  serializeJson(doc, jsonStr);
  Serial.println(jsonStr);
    Going_to_sleep();
  
}

void Going_to_sleep() {
  sleep_enable();
  Serial.println("Sleep\n");
  attachInterrupt(digitalPinToInterrupt(buttonPin),wakeUp,LOW);
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
  digitalWrite(trigPin, LOW);
  sleep_cpu();
  
  Serial.println("Just woke up!");
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
}

void wakeUp() {
  Serial.println("Interrupt Fired");
  sleep_disable();
  detachInterrupt(0);
}
