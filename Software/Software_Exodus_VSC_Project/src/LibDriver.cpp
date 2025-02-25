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
}
void RaiseArm()
{
  parent->setPin(pinParent1,HIGH);
  parent->setPin(pinParent2,LOW);
}

void LowerArm()
{
  parent->setPin(pinParent1,LOW);
  parent->setPin(pinParent2,HIGH);
}
void StopArm()
{
  parent->setPin(pinParent1,LOW);
  parent->setPin(pinParent2,LOW);
}