#define BLYNK_TEMPLATE_ID "TMPL3lv2x1G-Z"
#define BLYNK_TEMPLATE_NAME "smartdustbin"

#define BLYNK_PRINT Serial
#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include <ESP32Servo.h>

// Use GPIO numbers here
#define trig      5    // GPIO 5 (instead of D5)
#define echo      19   // GPIO 19 (instead of D19)
#define irSensor  21   // GPIO 21 (instead of D21)
//#define buzzer 4     // Buzzer removed
#define servoPin  23   // GPIO 23 (instead of D23)

long duration;
int distance;

char auth[] = "XB0Cn7V-nhGMJZU3o_9OCAeugoy_Asuz"; // Your Blynk Auth Token
char ssid[] = "Prasanna";           // Your WiFi SSID
char pass[] = "0123456789";         // Your WiFi password

BlynkTimer timer;
Servo servo;

WidgetLCD lcd(V1);

// Constants representing your bin height range (in cm)
const int maxDistance = 30;  // Distance when bin is empty (lid to bottom)
const int minDistance = 5;   // Distance when bin is full

// To prevent repeated notifications
bool notifiedFull = false;

void setup() {
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  pinMode(irSensor, INPUT);
  //pinMode(buzzer, OUTPUT);

  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass, "blynk.cloud", 80);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();

  IPAddress ip = WiFi.localIP();
  Serial.print("ESP32 IP Address: ");
  Serial.println(ip);

  Blynk.virtualWrite(V2, ip.toString());

  servo.attach(servoPin);
  servo.write(0); // Initially servo door is closed

  timer.setInterval(1000L, sendSensor);

  // Send default bin status on start
  Blynk.virtualWrite(V1, "Initializing");
}

void loop() {
  Blynk.run();
  timer.run();

  int irValue = digitalRead(irSensor);
  if (irValue == HIGH) {
    servo.write(90);  // Open dustbin door when hand detected
  } else {
    servo.write(0);   // Close dustbin door when no hand
  }
}

void sendSensor() {
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);

  duration = pulseIn(echo, HIGH);
  distance = duration * 0.034 / 2;

  if(distance == 0) distance = maxDistance; // Handle sensor errors

  // Calculate fill level as percentage (100% empty, 0% full)
  int fillLevel = map(distance, minDistance, maxDistance, 100, 0);
  fillLevel = constrain(fillLevel, 0, 100);

  // Determine bin status message
  String binStatus;
  if (fillLevel > 70) {
    binStatus = "Full";
    notifiedFull = false; // Reset notification flag when emptied
  } else if (fillLevel > 30) {
    binStatus = "Half Filled";
    notifiedFull = false;
  } else {
    binStatus = "Empty";
    if (!notifiedFull) {
      Blynk.logEvent("dustbin_full", "Dustbin is Full! Please Empty it.");
      notifiedFull = true; // Set flag to avoid repeated notifications
    }
  }


  Serial.print(" Fill Level = ");
  Serial.print(fillLevel);
  Serial.print("%, Status = ");
  Serial.println(binStatus);

  // Send values to Blynk app
  Blynk.virtualWrite(V0, fillLevel);
  Blynk.virtualWrite(V1, binStatus);

  // Update local LCD widget
  lcd.print(0, 0, "Level Of Dustbin");
  lcd.print(0, 1, "Dist: " + String(distance) + " cm");
}
