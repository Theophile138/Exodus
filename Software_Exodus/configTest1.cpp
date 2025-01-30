/*
Theophile Klein - 27/01/2025
*/

#include "Arduino.h"
#include "LibPeripherique.h"
#include "configTest1.h"
#include "LibCapteur.h"

Registre* configTest1::monRegistre1 = nullptr;    // Initialisé à nullptr
MasterDevice* configTest1::myEsp32 = nullptr;     // Initialisé à nullptr
Multiplexeur* configTest1::monMultiplex1 = nullptr; // Initialisé à nullptr
CapteurDeForce* configTest1::capteurForce1 = nullptr; // Initialisé à nullptr

void configTest1::init() 
{

  configTest1::myEsp32 = new MasterDevice(); // crée parent ici un esp32
  configTest1::monRegistre1 = new Registre(Reg1DataPin,Reg1ClockPin,Reg1TrigPin,Reg1Length);
  configTest1::monMultiplex1 = new Multiplexeur(Multiplex1PinS0, Multiplex1PinS1 , Multiplex1PinS2 , Multiplex1PinA , monRegistre1, myEsp32); // crée un multiplexeur qui depend d'un registre et de l'esp32
  
  configTest1::capteurForce1 = new CapteurDeForce(0,monMultiplex1);

}

void configTest1::run(){

  Serial.println("Capteur1:"+String(configTest1::capteurForce1->getValue())+",");

}