/*
Theophile Klein - 15/02/2025
*/

#ifndef LibScreen_h
#define LibScreen_h

#include "SPI.h"
#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"

#define TFT_DC 2
#define TFT_CS 5
#define TFT_RST 4

#define SCREEN_WIDTH  240
#define SCREEN_HEIGHT 320
//175876

class Screen {
    
    public:

        Screen();
        void testScreen();
        void clearScreen();
        unsigned long testDrawPixel();
        unsigned long testDrawPixelByPixel();
        unsigned long imageStart();
  
    private: 

        Adafruit_ILI9341* tft;

        unsigned long testFilledCircles(uint8_t radius, uint16_t color);
        unsigned long testCircles(uint8_t radius, uint16_t color);

        uint16_t* pixelArray;
  };

#endif