#include "LibScreen.h"

#include "SPI.h"
#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"

#include "image_data.h"

Screen::Screen(){
    tft = new Adafruit_ILI9341(TFT_CS, TFT_DC,TFT_RST);
    tft->begin();

    pixelArray = (uint16_t*)malloc(SCREEN_WIDTH * (SCREEN_HEIGHT/2) * sizeof(uint16_t));
}

void Screen::testScreen(){

/*
  Serial.println(F("Benchmark                Time (microseconds)"));

    Serial.print(F("Circles (filled)         "));
    Serial.println(testFilledCircles(10, ILI9341_MAGENTA));
  
    Serial.print(F("Circles (outline)        "));
    Serial.println(testCircles(10, ILI9341_WHITE));
    delay(500);

    Serial.print(F("Pixel                    "));
    Serial.println(testDrawPixel());
    delay(500);

    Serial.print(F("PixelByPixel             "));
    Serial.println(testDrawPixelByPixel());
    delay(500);
*/
    Serial.print(F("Image start             "));
    Serial.println(imageStart());
    delay(500);

}

void Screen::clearScreen()
{
    tft->fillScreen(ILI9341_BLACK);
}


unsigned long Screen::testDrawPixel() {
  unsigned long start;

  tft->fillScreen(ILI9341_BLACK);

  randomSeed(analogRead(0));
  for (int i = 0; i < SCREEN_WIDTH * (SCREEN_HEIGHT/2); i++) {
    uint8_t red = random(256);
    uint8_t green = random(256);
    uint8_t blue = random(256);
    pixelArray[i] = tft->color565(red, green, blue);
  }

  start = micros();

  tft->drawRGBBitmap(0, 0, pixelArray, SCREEN_WIDTH, (SCREEN_HEIGHT/2));

/*
  randomSeed(analogRead(0));
  for (int i = 0; i < SCREEN_WIDTH * (SCREEN_HEIGHT/2); i++) {
    uint8_t red = random(256);
    uint8_t green = random(256);
    uint8_t blue = random(256);
    pixelArray[i] = tft->color565(red, green, blue);
  }
*/

  tft->drawRGBBitmap(0, (SCREEN_HEIGHT/2), pixelArray, SCREEN_WIDTH, (SCREEN_HEIGHT/2));
  return micros() - start;
}

unsigned long Screen::testDrawPixelByPixel() {
  unsigned long start;

  tft->fillScreen(ILI9341_BLACK);

  start = micros();

  for (int x = 0; x < SCREEN_WIDTH; x++) {
    for (int y = 0; y < SCREEN_HEIGHT; y++) {
      
      // Générer des couleurs aléatoires
      uint8_t red = random(256);    // Valeur aléatoire pour le rouge
      uint8_t green = random(256);  // Valeur aléatoire pour le vert
      uint8_t blue = random(256);   // Valeur aléatoire pour le bleu
  
      // Convertir la couleur en RGB565
      uint16_t color = tft->color565(red, green, blue);
  
      // Dessiner le pixel à la position (x, y) avec la couleur aléatoire
      tft->drawPixel(x, y, color);
    }
  }
  

  return micros() - start;
}

unsigned long Screen::imageStart(){

  unsigned long start;


  tft->fillScreen(ILI9341_BLACK);

  start = micros();

  tft->drawRGBBitmap(0, 0,image_data,240, 240);

  return micros() - start;

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