
#include <Arduino.h>
#include <TFT_eSPI.h>
#include <RPi_Pico_TimerInterrupt.h>

#define TFT_BACKLIGHT     4
#define TIMER_1SEC        1000L     // 1sec = 1000 milliseconds

TFT_eSPI tft;
RPI_PICO_Timer timer(1);

volatile unsigned int count = 0;
volatile int ch = ':';

bool one_second(struct repeating_timer *t) {
  Serial.println(count);

  unsigned int mins = count/60;
  unsigned int secs = count%60;

  char str[80];
  if (mins > 0) {
    sprintf(str, "%u%c%02u", mins, ch, secs);
  } else {
    sprintf(str, "%c%02u", ch, secs);
  }

  tft.drawString(str, tft.width()/2, tft.height()/2);
  digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));

  ++count;
  ch = (ch == ':') ? ' ' : ':';

  return true;
}

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

  timer.attachInterruptInterval(TIMER_1SEC * 1000, one_second);
}
 
void loop() {
  delay(10000);
}
