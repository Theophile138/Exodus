#include "Arduino.h"
#include "LibPeripherique.h"
#include "configTest1.h"

Registre* configTest1::monRegistre1 = nullptr;    // Initialisé à nullptr
MasterDevice* configTest1::myEsp32 = nullptr;     // Initialisé à nullptr
Multiplexeur* configTest1::monMultiplex1 = nullptr; // Initialisé à nullptr

void configTest1::init() 
{

  configTest1::myEsp32 = new MasterDevice(); // crée parent ici un esp32
  configTest1::monRegistre1 = new Registre(Reg1DataPin,Reg1ClockPin,Reg1TrigPin,Reg1Length);
  configTest1::monMultiplex1 = new Multiplexeur(Multiplex1PinS0, Multiplex1PinS1 , Multiplex1PinS2 , Multiplex1PinA , monRegistre1, myEsp32); // crée un multiplexeur qui depend d'un registre et de l'esp32

}

void configTest1::run(){

  int value = monMultiplex1->analogReadMultiplexeur(0);
  Serial.print("Sensor1:" + String(value)+",");
  int value2 = monMultiplex1->analogReadMultiplexeur(1);
  Serial.print("Sensor2:" + String(value2)+",");
  int value3 = monMultiplex1->analogReadMultiplexeur(2);
  Serial.print("Sensor3:" + String(value3)+",");
  int value4 = monMultiplex1->analogReadMultiplexeur(3);
  Serial.print("Sensor4:" + String(value4)+",");
  int value5 = monMultiplex1->analogReadMultiplexeur(4);
  Serial.print("Sensor5:" + String(value5)+",");


  Serial.println("");
  delay(100);

}