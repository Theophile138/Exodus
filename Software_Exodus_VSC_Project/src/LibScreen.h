/*
Theophile Klein - 15/02/2025
*/

#ifndef LibScreen_h
#define LibScreen_h

#include <TFT_eSPI.h> // Hardware-specific library
#include <SPI.h>

#define SCREEN_WIDTH  240
#define SCREEN_HEIGHT 320

class Screen {
    
    public:

        Screen();

        void clearScreen();
        unsigned long imageStart(String firmwareVersion);

        void StatMenu();

    private: 
        
        TFT_eSPI* tft;
  };

#endif