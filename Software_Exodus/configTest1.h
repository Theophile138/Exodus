#ifndef configTest1_h
#define configTest1_h

#include "LibPeripherique.h"
#include "Arduino.h"

class configTest1 {
public:
  // Déclaration de la methode init, pour le demarge de la class
  static void init();
  static void run();

  // Pin pour le registre a decalage
  static const int Reg1DataPin = 25;
  static const int Reg1ClockPin = 26;
  static const int Reg1TrigPin = 27;
  static const int Reg1Length = 8;

  static Registre* monRegistre1;

  static const int Multiplex1PinA = 33;
  static const int Multiplex1PinS0 = 4;
  static const int Multiplex1PinS1 = 5;
  static const int Multiplex1PinS2 = 6;

  static MasterDevice* myEsp32;

  static Multiplexeur* monMultiplex1;
};

#endif