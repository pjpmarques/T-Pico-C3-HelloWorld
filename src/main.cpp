
#include <Arduino.h>
#include <TFT_eSPI.h>
#include <RPi_Pico_TimerInterrupt.h>
#include <OneButton.h>

#define TFT_BACKLIGHT     4
#define TFT_CS            22
#define BUTTON_DN         6
#define BUTTON_UP         7

#define TIMER_1SEC        1000L     // 1sec = 1000 milliseconds

TFT_eSPI tft;
RPI_PICO_Timer timer(1);

OneButton up(BUTTON_UP);
OneButton dn(BUTTON_DN);

volatile unsigned int count = 0;
volatile int ch = ':';
volatile uint16_t colour = TFT_WHITE;

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

  tft.setTextColor(colour, TFT_BLACK);
  tft.drawString(str, tft.width()/2, tft.height()/2);
  tft.setTextColor(TFT_WHITE, TFT_BLACK);
  digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));

  ++count;
  ch = (ch == ':') ? ' ' : ':';
  colour = TFT_WHITE;

  return true;
}

void up_click() {
  colour = TFT_BLUE;
}

void dn_click() {
  colour = TFT_GREEN;
}

void setup() {
  Serial.begin(115200);
  Serial.println("Up and runnning");

  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(TFT_BACKLIGHT, OUTPUT);
  pinMode(TFT_CS, OUTPUT);

  tft.init();
  tft.setRotation(1);
  tft.fillScreen(TFT_BLACK);
  tft.setTextFont(7);
  tft.setTextDatum(MC_DATUM);
  tft.setTextColor(TFT_WHITE, TFT_BLACK);
  digitalWrite(TFT_BACKLIGHT, HIGH);
  digitalWrite(TFT_CS, HIGH);

  timer.attachInterruptInterval(TIMER_1SEC * 1000, one_second);

  up.attachClick(up_click);
  dn.attachClick(dn_click);
}
 
void loop() {
  up.tick();
  dn.tick();
  delay(100);
}
