/*
Theophile Klein - 15/02/2025
*/

#ifndef LibScreen_h
#define LibScreen_h

#include <TFT_eSPI.h> // Hardware-specific library
#include <SPI.h>
#include "LibGauge.h"

#include "FS.h"

#define SCREEN_WIDTH  240
#define SCREEN_HEIGHT 320

// This is the file name used to store the calibration data
// You can change this to create new calibration files.
// The SPIFFS file name must start with "/".
#define CALIBRATION_FILE "/TouchCalData1"

// Set REPEAT_CAL to true instead of false to run calibration
// again, otherwise it will only be done once.
// Repeat calibration if you change the screen rotation.
#define REPEAT_CAL false

// Keypad start position, key sizes and spacing
#define KEY_X 40 // Centre of key
#define KEY_Y 96
#define KEY_W 62 // Width and height
#define KEY_H 30
#define KEY_SPACING_X 18 // X and Y gap
#define KEY_SPACING_Y 20
#define KEY_TEXTSIZE 1   // Font size multiplier

// Using two fonts since numbers are nice when bold
#define LABEL1_FONT &FreeSansOblique12pt7b // Key label font 1
#define LABEL2_FONT &FreeSansBold12pt7b    // Key label font 2

class Screen {
    
    public:

        Screen();

        void clearScreen();
        unsigned long imageStart(String firmwareVersion);

        void StatMenu();

        analogMeters* myGauge;
        
        void touch_calibrate();
        void renderButton();

        bool startButtonActive;

    private: 
        
        TFT_eSPI* tft;
        TFT_eSPI_Button startButton;
        TFT_eSPI_Button leftButton;
        TFT_eSPI_Button rightButton;


  };

#endif