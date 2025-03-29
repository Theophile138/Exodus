/*
Theophile Klein - 27/01/2025
*/

#ifndef configTest1_h
#define configTest1_h

#include "LibPeripherique.h"
#include "Arduino.h"
#include "LibCapteur.h"
#include "LibDriver.h"

#if defined(ESP32)

#include "soc/gpio_struct.h" // Pour accéder aux registres GPIO
#include "driver/gpio.h"    // Pour configurer les GPIOs

#include "LibScreen.h"

#endif

class configTest1 {
public:
  
  #if defined(ESP32)

  // Déclaration de la methode init, pour le demarge de la class
  static void init(Screen* scr);

  #else

  static void init();
  
  #endif

  static void run();

  // Pin pour le registre a decalage
  static const int Reg1DataPin = 25; // Pin de l'esp32
  static const int Reg1ClockPin = 26;
  static const int Reg1TrigPin = 27;
  static const int Reg1Length = 16; // Taile du registre (formule cas général, 8 * nombreDeRegistre en serie)b

  static Registre* monRegistre1;

  static const int Multiplex1PinA = 36;
  static const int Multiplex1PinS0 = 2; // pin N°4 sur le registre 1
  static const int Multiplex1PinS1 = 1; // pin N°5 ... registre 1
  static const int Multiplex1PinS2 = 0; // ect ...

  static MasterDevice* myEsp32;
  static Multiplexeur* monMultiplex1;

  static Capteur* capteurForce1;
  static Capteur* capteurForce2;
  static Capteur* capteurForce3;
  static Capteur* capteurForce4;
  static Capteur* capteurForce5;

  static DriverMotor* verin;

  static int dir;
  static int dir2;

  static int value1;
  static int value2;
  static int value3;
  static int value4;
  static int value5;
  static int value6;
};

#endif