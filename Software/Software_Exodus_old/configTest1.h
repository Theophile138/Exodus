/*
Theophile Klein - 27/01/2025
*/

#ifndef configTest1_h
#define configTest1_h

#include "LibPeripherique.h"
#include "Arduino.h"
#include "LibCapteur.h"

#include "soc/gpio_struct.h" // Pour accéder aux registres GPIO
#include "driver/gpio.h"    // Pour configurer les GPIOs

class configTest1 {
public:
  // Déclaration de la methode init, pour le demarge de la class
  static void init();
  static void run();

  // Pin pour le registre a decalage
  static const int Reg1DataPin = 25; // Pin de l'esp32
  static const int Reg1ClockPin = 26;
  static const int Reg1TrigPin = 27;
  static const int Reg1Length = 16; // Taile du registre (formule cas général, 8 * nombreDeRegistre en serie)

  static Registre* monRegistre1;

  static const int Multiplex1PinA = 33;
  static const int Multiplex1PinS0 = 4; // pin N°4 sur le registre 1
  static const int Multiplex1PinS1 = 5; // pin N°5 ... registre 1
  static const int Multiplex1PinS2 = 6; // ect ...

  static MasterDevice* myEsp32;

  static Multiplexeur* monMultiplex1;

  static CapteurDeForce* capteurForce1;
  static CapteurDeForce* capteurForce2;
  static CapteurDeForce* capteurForce3;
  static CapteurDeForce* capteurForce4;
  static CapteurDeForce* capteurForce5;

  static int dir;
  static int dir2;
};

#endif