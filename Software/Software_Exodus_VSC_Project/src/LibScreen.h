/*
Theophile Klein - 15/02/2025
*/

#ifndef LibScreen_h
#define LibScreen_h

#include <TFT_eSPI.h> // Hardware-specific library
#include <SPI.h>
#include "LibJauge.h"

#include "FS.h"

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
        static void Select_Menu_run(Screen* Scr);
        
        void Gauge_Menu_init();
        static void Gauge_Menu_run(Screen* Scr);

        void touch_calibrate();
        void renderButton();

        void (*run)(Screen*);

        static void leftOnclick(Screen* Scr);
        static void rightOnclick(Screen* Scr);
        static void startOnclick(Screen* Scr);
        static void startOffclick(Screen* Scr);

        static void gaugeOnClick(Screen* Scr);

        static void backOnClick(Screen* Scr);

        linearMeter* linearMeters;

        bool activeControle;

        int config_selectionne;

        analogMeters* myGauge;

    private: 
        
        int number;
        int index;

        TFT_eSPI* tft;

        //Configuration myListeConfig;

        static void emptyFunction(Screen*) {Serial.println("NO run set for the sreen !");} // Fonction vide qui ne fait rien si aucune methode a été donné pour le press button

        Button startButton;
        Button leftButton;
        Button rightButton;
        Button gaugeButton;

        Button backButton;

  };

#endif