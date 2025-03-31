/*
Theophile Klein - 27/01/2025
*/

#ifndef Extend_Card_lib_h
#define Extend_Card_lib_h

#include "../Hardware_lib/LibPeripherique.h"
#include "Arduino.h"

#if defined(ESP32)

#include "soc/gpio_struct.h" // Pour accéder aux registres GPIO
#include "driver/gpio.h"    // Pour configurer les GPIOs

#endif

class Extend_Card {

  public:
  
    Extend_Card();

    void digitalWrite(int pin, bool value);
    int analogRead(int pin);

    MasterDevice* myEsp32;

    // Pin pour le registre a decalage
  static const int Reg1DataPin = 25; // Pin de l'esp32
  static const int Reg1ClockPin = 26;
  static const int Reg1TrigPin = 27;

  static const int Reg1Length = 16; // Taile du registre (formule cas général, 8 * nombreDeRegistre en serie)b

  Registre* monRegistre1;

  static const int Multiplex1PinA = 36;
  static const int Multiplex1PinS0 = 2;
  static const int Multiplex1PinS1 = 1;
  static const int Multiplex1PinS2 = 0; 

  Multiplexeur* monMultiplex1;

  static const int Multiplex2PinA = 0; // Sur le multiplex 1

  static const int Multiplex2PinS0 = 5;
  static const int Multiplex2PinS1 = 4;
  static const int Multiplex2PinS2 = 3; 
  
  Multiplexeur* monMultiplex2;
};

#endif