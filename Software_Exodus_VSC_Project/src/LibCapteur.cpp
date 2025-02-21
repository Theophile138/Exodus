/*
Theophile Klein - 27/01/2025
*/

#include "LibCapteur.h"
#include "LibPeripherique.h"

Capteur::Capteur(int pinAnalog,ParentAnalog* parent)
{
  Capteur::pinAnalog = pinAnalog;
  Capteur::parent = parent;
}

int Capteur::getValue()
{
  return parent->analogReadAnyDevice(pinAnalog);
}