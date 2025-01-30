/*
Theophile Klein - 27/01/2025
*/

#ifndef LibCapteur_h
#define LibCapteur_h

#include "LibPeripherique.h"

class CapteurDeForce {
  public:

    CapteurDeForce(int pinAnalog,ParentAnalog* parent);
    int getValueAnalog();

  private: 
    ParentAnalog* parent;
    int pinAnalog;
};


#endif