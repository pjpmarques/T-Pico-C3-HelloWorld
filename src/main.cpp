
#include <Arduino.h>
#include <TFT_eSPI.h>

#define TFT_BACKLIGHT     4

TFT_eSPI tft;

void setup() {
  Serial.begin(115200);

  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(TFT_BACKLIGHT, OUTPUT);

  tft.init();
  tft.setRotation(1);
  tft.fillScreen(TFT_BLACK);
  tft.setTextFont(7);
  tft.setTextDatum(MC_DATUM);
  tft.setTextColor(TFT_WHITE, TFT_BLACK);
  digitalWrite(TFT_BACKLIGHT, HIGH);
}

unsigned int count = 0;

void loop() {
  Serial.println(count++);
  digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));

  tft.drawString(String(count), tft.width()/2, tft.height()/2);

  delay(1000);
}
