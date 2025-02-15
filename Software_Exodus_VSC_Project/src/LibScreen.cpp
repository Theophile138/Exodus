#include "LibScreen.h"

#include "SPI.h"
#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"

Screen::Screen(){
    tft = new Adafruit_ILI9341(TFT_CS, TFT_DC,TFT_RST);
    tft->begin();
}

void Screen::testScreen(){
    Serial.println(F("Benchmark                Time (microseconds)"));

    Serial.print(F("Circles (filled)         "));
    Serial.println(testFilledCircles(10, ILI9341_MAGENTA));
  
    Serial.print(F("Circles (outline)        "));
    Serial.println(testCircles(10, ILI9341_WHITE));
    delay(500);

}

void Screen::clearScreen()
{
    tft->fillScreen(ILI9341_BLACK);
}

unsigned long Screen::testFilledCircles(uint8_t radius, uint16_t color) {
  unsigned long start;
  int x, y, w = tft->width(), h = tft->height(), r2 = radius * 2;

  tft->fillScreen(ILI9341_BLACK);
  start = micros();
  for(x=radius; x<w; x+=r2) {
    for(y=radius; y<h; y+=r2) {
      tft->fillCircle(x, y, radius, color);
    }
  }

  return micros() - start;
}

unsigned long Screen::testCircles(uint8_t radius, uint16_t color) {
  unsigned long start;
  int           x, y, r2 = radius * 2,
                w = tft->width()  + radius,
                h = tft->height() + radius;

  // Screen is not cleared for this one -- this is
  // intentional and does not affect the reported time.
  start = micros();
  for(x=0; x<w; x+=r2) {
    for(y=0; y<h; y+=r2) {
      tft->drawCircle(x, y, radius, color);
    }
  }

  return micros() - start;
}