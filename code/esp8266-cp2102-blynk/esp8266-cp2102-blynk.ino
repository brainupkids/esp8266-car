#define BLYNK_PRINT Serial

#include "./credentials-blynk.h"
#include "./credentials-wifi.h"

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char wifi_ssid[] = WIFI_SSID;
char wifi_password[] = WIFI_PASSWORD;

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
  Serial.print("X7 = ");
  Serial.print(x);
  Serial.print("; Y7 = ");
  Serial.println(y);
}

void setup() {
  // Debug console
  Serial.begin(115200);

  // Connect and authenticate to Blynk.cloud
  Blynk.begin(BLYNK_AUTH_TOKEN, wifi_ssid, wifi_password);
}

void loop() {
  Blynk.run();
}
