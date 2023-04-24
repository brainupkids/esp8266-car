#define BLYNK_PRINT Serial

#define ROBIGAMI_DEBUG 1

#include "./credentials-blynk.h"
#include "./credentials-wifi.h"

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char wifi_ssid[] = WIFI_SSID;
char wifi_password[] = WIFI_PASSWORD;

#define RightMotorSpeed 5
#define RightMotorDir   0 
#define LeftMotorSpeed  4
#define LeftMotorDir    2

// 312 = 512 - 200
// int minRange = 312;
// 64 = 128 - 64
int minRange = 64;

// 712 = 512 + 200
// int maxRange = 712;
// 292 = 128 + 64
int maxRange = 192;

int minSpeed = 450;
int maxSpeed = 1020;
int noSpeed = 0;


void moveControl(int x, int y) {

  // move forward
  if(y >= maxRange && x >= minRange && x <= maxRange)
  {
    digitalWrite(RightMotorDir,HIGH);
    digitalWrite(LeftMotorDir,HIGH);
    analogWrite(RightMotorSpeed,maxSpeed);
    analogWrite(LeftMotorSpeed,maxSpeed);
    #if defined ROBIGAMI_DEBUG
    Serial.println("Move forward");
    #endif
  }
 
  // move forward right
  else if(x >= maxRange && y >= maxRange)
  {
    digitalWrite(RightMotorDir,HIGH);
    digitalWrite(LeftMotorDir,HIGH);
    analogWrite(RightMotorSpeed,minSpeed);
    analogWrite(LeftMotorSpeed,maxSpeed);
    #if defined ROBIGAMI_DEBUG
    Serial.println("Move forward right");
    #endif
  }

  // move forward left
  else if(x <= minRange && y >= maxRange)
  {
    digitalWrite(RightMotorDir,HIGH);
    digitalWrite(LeftMotorDir,HIGH);
    analogWrite(RightMotorSpeed,maxSpeed);
    analogWrite(LeftMotorSpeed,minSpeed);
    #if defined ROBIGAMI_DEBUG
    Serial.println("Move forward left");
    #endif
  }

  // neutral zone
  else if(y < maxRange && y > minRange && x < maxRange && x > minRange)
  {
    analogWrite(RightMotorSpeed,noSpeed);
    analogWrite(LeftMotorSpeed,noSpeed);
    #if defined ROBIGAMI_DEBUG
    Serial.println("Stand by");
    #endif
  }

  // move back
  else if(y <= minRange && x >= minRange && x <= maxRange)
  {
    digitalWrite(RightMotorDir,LOW);
    digitalWrite(LeftMotorDir,LOW);
    analogWrite(RightMotorSpeed,maxSpeed);
    analogWrite(LeftMotorSpeed,maxSpeed);
    #if defined ROBIGAMI_DEBUG
    Serial.println("Move backward");
    #endif
  }

  // move back and right
  else if(y <= minRange && x <= minRange)
  {
    digitalWrite(RightMotorDir,LOW);
    digitalWrite(LeftMotorDir,LOW);
    analogWrite(RightMotorSpeed,minSpeed);
    analogWrite(LeftMotorSpeed,maxSpeed); 
    #if defined ROBIGAMI_DEBUG
    Serial.println("Move back right");
    #endif
  }

  // move back and left
  else if(y <= minRange && x >= maxRange)
  {
    digitalWrite(RightMotorDir,LOW);
    digitalWrite(LeftMotorDir,LOW);
    analogWrite(RightMotorSpeed,maxSpeed);
    analogWrite(LeftMotorSpeed,minSpeed);
    #if defined ROBIGAMI_DEBUG
    Serial.println("Move back left");
    #endif
  }
}

void initControl() { 
  // initial settings for motors off and direction forward
  pinMode(RightMotorSpeed, OUTPUT);
  pinMode(LeftMotorSpeed, OUTPUT);
  pinMode(RightMotorDir, OUTPUT);
  pinMode(LeftMotorDir, OUTPUT);
 
  digitalWrite(RightMotorSpeed, LOW);
  digitalWrite(LeftMotorSpeed, LOW);
  digitalWrite(RightMotorDir, HIGH);
  digitalWrite(LeftMotorDir,HIGH);
}

// This function is called every time the device is connected to the Blynk.Cloud
BLYNK_CONNECTED()
{
  // Change Web Link Button message to "Congratulations!"
  Blynk.setProperty(V3, "offImageUrl", "https://static-image.nyc3.cdn.digitaloceanspaces.com/general/fte/congratulations.png");
  Blynk.setProperty(V3, "onImageUrl",  "https://static-image.nyc3.cdn.digitaloceanspaces.com/general/fte/congratulations_pressed.png");
  Blynk.setProperty(V3, "url", "https://docs.blynk.io/en/getting-started/what-do-i-need-to-blynk/how-quickstart-device-was-made");
}

BLYNK_WRITE(V7)
{
  int x = param[0].asInt();
  int y = param[1].asInt();

  // Do something with x and y
  logJoystickChange(7, x, y);

  moveControl(x, y);
}

void logJoystickChange(int vPin, int x, int y) {
  Serial.print("Pin: V");
  Serial.print(vPin);
  Serial.print("; X: ");
  Serial.print(x);
  Serial.print("; Y: ");
  Serial.println(y);
}

void setup() {
  // Debug console
  Serial.begin(115200);

  // Connect and authenticate to Blynk.cloud
  Blynk.begin(BLYNK_AUTH_TOKEN, wifi_ssid, wifi_password);

  //
  initControl();
}

void loop() {
  Blynk.run();
}
