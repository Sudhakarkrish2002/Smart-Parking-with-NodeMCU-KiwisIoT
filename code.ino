#include <ESP8266WiFi.h>
#include <KiwisIoT.h>

const char* ssid = "abcd";
const char* pass = "12345678";
const char* topic = "dash_1795241697023";

#define TRIG D5
#define ECHO D6
#define RED_LED D1
#define GREEN_LED D2

long duration;
float distance;

KiwisIoT kiwisiot(ssid, pass, topic);

void setup() {

  Serial.begin(115200);

  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);

  pinMode(RED_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);

  kiwisiot.begin();

  Serial.println("SMART PARKING SYSTEM");
}

void loop() {

  kiwisiot.run();

  // Ultrasonic sensor
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);

  digitalWrite(TRIG, LOW);

  duration = pulseIn(ECHO, HIGH, 30000);

  if (duration == 0) {

    digitalWrite(RED_LED, LOW);
    digitalWrite(GREEN_LED, LOW);

    Serial.println("Sensor Error");

  }

  else {

    distance = duration * 0.0343 / 2;

    // Serial Monitor distance
    Serial.print("Distance: ");
    Serial.print(distance);
    Serial.println(" cm");

    // Dashboard 2: Distance
    kiwisiot.send("2", String(distance, 2));

    if (distance > 20) {

      digitalWrite(GREEN_LED, HIGH);
      digitalWrite(RED_LED, LOW);

      Serial.println("Status: SAFE");

      // Dashboard 1: Status
      kiwisiot.send("1", "SAFE");

    }

    else {

      digitalWrite(RED_LED, HIGH);
      digitalWrite(GREEN_LED, LOW);

      Serial.println("Status: NOT SAFE");

      // Dashboard 1: Status
      kiwisiot.send("1", "NOT SAFE");

    }
  }

  Serial.println("--------------------");

  delay(1000);
}
