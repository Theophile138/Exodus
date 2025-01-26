#include "LibPeripherique.h"

const int Reg1DataPin = 25;
const int Reg1ClockPin = 26;
const int Reg1TrigPin = 27;
const int Reg1Length = 8;

Registre* monRegistre1 = new Registre(Reg1DataPin,Reg1ClockPin,Reg1TrigPin,Reg1Length);

const int Multiplex1PinA = 33;
const int Multiplex1PinS0 = 4;
const int Multiplex1PinS1 = 5;
const int Multiplex1PinS2 = 6;

MasterDevice* myEsp32= new MasterDevice();

Multiplexeur monMultiplex1(Multiplex1PinS0, Multiplex1PinS1 , Multiplex1PinS2 , Multiplex1PinA , monRegistre1, myEsp32 );


//const int Multiplex2PinA = 5;
//const int Multiplex2PinS0 = 0;
//const int Multiplex2PinS1 = 1;
//const int Multiplex2PinS2 = 2;

//Multiplexeur monMultiplex2(Multiplex2PinS0, Multiplex2PinS1 , Multiplex2PinS2 , Multiplex2PinA , monRegistre1, &monMultiplex1);

void setup() {
  Serial.begin(115200);
}

void loop() {

  //monMultiplex1.SelectPin(1);
  int value = monMultiplex1.analogReadMultiplexeur(0);
  Serial.print("Sensor1:" + String(value)+",");
  int value2 = monMultiplex1.analogReadMultiplexeur(1);
  Serial.print("Sensor2:" + String(value2)+",");
  int value3 = monMultiplex1.analogReadMultiplexeur(2);
  Serial.print("Sensor3:" + String(value3)+",");
  int value4 = monMultiplex1.analogReadMultiplexeur(3);
  Serial.print("Sensor4:" + String(value4)+",");
  int value5 = monMultiplex1.analogReadMultiplexeur(4);
  Serial.print("Sensor5:" + String(value5)+",");


  Serial.println("");
  delay(100);
}
