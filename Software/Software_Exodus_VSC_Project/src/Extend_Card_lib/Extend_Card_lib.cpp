#include "Arduino.h"
#include "../Hardware_lib/LibPeripherique.h"
#include "Extend_Card_lib.h"

#if defined(ESP32)

#include "soc/gpio_struct.h" // Pour accéder aux registres GPIO
#include "driver/gpio.h"    // Pour configurer les GPIOs

#endif



Extend_Card::Extend_Card() 
{
  myEsp32 = new MasterDevice(); // crée parent ici un esp32
  monRegistre1 = new Registre(Reg1DataPin,Reg1ClockPin,Reg1TrigPin,Reg1Length);
  monMultiplex1 = new Multiplexeur(Multiplex1PinS0, Multiplex1PinS1 , Multiplex1PinS2 , Multiplex1PinA , monRegistre1, myEsp32); // crée un multiplexeur qui depend d'un registre et de l'esp32
  monMultiplex2 = new Multiplexeur(Multiplex2PinS0, Multiplex2PinS1 , Multiplex2PinS2 , Multiplex2PinA , monRegistre1, monMultiplex1); 
}

void Extend_Card::digitalWrite(int pin , bool value){
  monRegistre1->setPin(pin , value);
}

int Extend_Card::analogRead(int pin){
  monMultiplex1->analogReadAnyDevice(pin);
}  