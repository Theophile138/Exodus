/*
Theophile Klein - 15/02/2025
Paul Escalier - 25/02/2025
*/

#include "LibDriver.h"
#include "LibPeripherique.h"



DriverMotor::DriverMotor(int pinParent1, int pinParent2, ParentDevice* parent)
{
  DriverMotor::pinParent1 = pinParent1;
  DriverMotor::pinParent2 = pinParent2;
  DriverMotor::parent= parent;
  DriverMotor::actif = false;
}
void DriverMotor::RaiseArm()
{
  if (DriverMotor::actif)
  { 
  parent->setPin(pinParent1,HIGH);
  parent->setPin(pinParent2,LOW);
  }

  else{
    return;
  }
}

void DriverMotor::LowerArm()
{  
  if (DriverMotor::actif)
  { 
  parent->setPin(pinParent1,LOW);
  parent->setPin(pinParent2,HIGH);
  }

  else{
    return;
  }
}

void DriverMotor::toggleActive(){
        DriverMotor::actif = !DriverMotor::actif; 
}

void DriverMotor::StopArm()
{
  parent->setPin(pinParent1,LOW);
  parent->setPin(pinParent2,LOW);
}