/*
Theophile Klein - 27/01/2025
*/

#ifndef LibDriver_h
#define LibDriver_h

#include "LibPeripherique.h"

class DriverMotor {
  public:

  //void setDir(int direction);
  DriverMotor(int pin1 , int pin2 , int pinEn,ParentDevice* parentDir, ParentDevice* parentPWN);

  private: 
    
    ParentDevice* parentDir;
    ParentDevice* parentPWN;

    int pin1;
    int pin2;
    int pinEn;
};


#endif