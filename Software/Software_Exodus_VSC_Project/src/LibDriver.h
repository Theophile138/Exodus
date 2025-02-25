/*
Theophile Klein - 27/01/2025
Paul Escalier - 25/02/2025
*/

#ifndef LibDriver_h
#define LibDriver_h

#include "LibPeripherique.h"

class DriverMotor {
  public:

  //void setDir(int direction);
  DriverMotor(int pinParent1, int pinParent2, ParentDevice* parent);

  void RaiseArm();
  void LowerArm();
  void StopArm();

  private: 
  int pinParent1; 
  int pinParent2;
  ParentDevice* parent;    
};


#endif