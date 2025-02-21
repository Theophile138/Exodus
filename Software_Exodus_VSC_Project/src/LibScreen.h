/*
Theophile Klein - 15/02/2025
*/

#ifndef LibScreen_h
#define LibScreen_h

#include <TFT_eSPI.h> // Hardware-specific library
#include <SPI.h>
#include "LibGauge.h"

#include "FS.h"

#include "LibConfig.h"
#include "LibButton.h"

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

class Screen {
    
    public:

        Screen();

        void clearScreen();
        void imageStart(String firmwareVersion);

        void Select_Menu_init();
        void Select_Menu_run();
        
        void touch_calibrate();
        void renderButton();

        static void leftOnclick(TFT_eSPI* tft);
        static void rightOnclick(TFT_eSPI* tft);

    private: 
        
        TFT_eSPI* tft;

        analogMeters* myGauge;

        //Configuration myListeConfig;

        Button startButton;
        Button leftButton;
        Button rightButton;


  };

#endif