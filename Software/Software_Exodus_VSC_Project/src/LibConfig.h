#ifndef LibConfig_h
#define LibConfig_h

#include "Arduino.h"
#include "LibPeripherique.h"
#include "LibCapteur.h"

class Configuration
{

    public:

        Configuration(String name,const uint16_t* icone, int iconeWidth, int iconeHeight, String presentation);

        String name;

        void init();
        void show();
        void run();

    private:

        const uint16_t* icone;
        int iconeWidth;
        int iconeHeight; 

        String presentation;


};

#endif