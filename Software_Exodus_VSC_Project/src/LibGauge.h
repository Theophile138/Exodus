#ifndef LibGauge_h
#define LibGauge_h

#include <TFT_eSPI.h> // Hardware-specific library
#include <SPI.h>

#define TFT_GREY 0x5AEB

class analogMeters {
    
    public:

        analogMeters(TFT_eSPI* tft, int mideNumber,int minGreenLimite,int maxGreenLimite,int minOrangeLimite,int maxOrangeLimite,String unit);
        void plotNeedle(int value, byte ms_delay);

    private: 
        

        // Variable pour l'analog meter
        float ltx = 0;    // Saved x coord of bottom of needle
        uint16_t osx = 120, osy = 120; // Saved x & y coords
        uint32_t updateTime = 0;       // time for next update
    
        int old_analog =  -999; // Value last displayed

        int mideNumber = 50;

        int minGreenLimite = -50;
        int maxGreenLimite = -25;

        int minOrangeLimite = 25;
        int maxOrangeLimite = 50;

        String unit = "% Force";

        TFT_eSPI* tft;
  };

#endif