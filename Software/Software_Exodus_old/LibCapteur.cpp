/*
Theophile Klein - 27/01/2025
*/

#include "LibCapteur.h"
#include "LibPeripherique.h"

CapteurDeForce::CapteurDeForce(int pinAnalog,ParentAnalog* parent)
{
  CapteurDeForce::pinAnalog = pinAnalog;
  CapteurDeForce::parent = parent;
}

int CapteurDeForce::getValue()
{
  return parent->analogReadAnyDevice(pinAnalog);
}