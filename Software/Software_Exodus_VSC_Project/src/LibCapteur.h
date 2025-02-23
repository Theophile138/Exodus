/*
Theophile Klein - 27/01/2025
*/

#ifndef LibCapteur_h
#define LibCapteur_h

#include "LibPeripherique.h"

class Capteur {
  public:

    Capteur(int pinAnalog,ParentAnalog* parent);
    int getValue();

  private: 
    ParentAnalog* parent;
    int pinAnalog;
};


#endif