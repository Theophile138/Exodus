#include "LibScreen.h"

#include "LibGauge.h"

#include <TFT_eSPI.h> // Hardware-specific library
#include <SPI.h>

#include "image_data.h"

Screen::Screen(){
    //tft = new Adafruit_ILI9341(TFT_CS, TFT_DC,TFT_RST);
    tft =new TFT_eSPI(); 
    tft->begin();
    tft->setRotation(0);
}

void Screen::clearScreen()
{
    tft->fillScreen(ILI9341_BLACK);
}

unsigned long Screen::imageStart(String firmwareVersion){

  unsigned long start;

  tft->fillScreen(ILI9341_BLACK);
  start = micros();
  tft->setSwapBytes(true);

  tft->pushImage(0, 0, 240, 320, image_data);

  tft->setTextColor(TFT_WHITE);  // Text colour

  //tft->drawCentreString("Exodus Firmware V",SCREEN_WIDTH/2,280,0);
  tft->drawCentreString("Exodus Firmware V"+firmwareVersion, SCREEN_WIDTH/2, 270, 2); // Comment out to avoid font 4
  return micros() - start;
}

void Screen::StatMenu()
{
  tft->fillScreen(ILI9341_BLACK);
  analogMeters myGauge = analogMeters(tft,0,-50,-25,25,50,"% Force");
}

