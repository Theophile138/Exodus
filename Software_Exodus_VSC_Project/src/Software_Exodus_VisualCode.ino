#include "configTest1.h"
#include "LibScreen.h"
#include "LibConfig.h"
#include "image_data.h"

#include "LibPeripherique.h"
#include "Arduino.h"
#include "LibCapteur.h"


Screen myScreen;

unsigned long Time;

#define FirmwareVersion "0.3"

void setup() {
  Serial.begin(115200);

  configTest1::init();

  myScreen = Screen(); 
  myScreen.touch_calibrate();
  
  myScreen.imageStart(FirmwareVersion);

  delay(5000);

  myScreen.Select_Menu_init();

  Time = millis();

}

void loop() 
{

  if (millis() - Time > 10){
    Time = millis();
    myScreen.Select_Menu_run();

  }

}


/*

Configuration init_config_verin()
{
  
  String name = "Verin";
  String description = "Configuration V1 pour le verin";

  const uint16_t* myImage = image_mode1;
  const int width = image_mode1_width;


  // Pin pour le registre a decalage
  const int Reg1DataPin = 25; // Pin de l'esp32
  const int Reg1ClockPin = 26;
  const int Reg1TrigPin = 27;
  const int Reg1Length = 16; // Taile du registre (formule cas général, 8 * nombreDeRegistre en serie)
  
  const int Multiplex1PinA = 33;
  const int Multiplex1PinS0 = 4; // pin N°4 sur le registre 1
  const int Multiplex1PinS1 = 5; // pin N°5 ... registre 1
  const int Multiplex1PinS2 = 6; // ect ...
  
  MasterDevice myEsp32 = MasterDevice(); // crée parent ici un esp32
  Registre monRegistre1 = Registre(Reg1DataPin,Reg1ClockPin,Reg1TrigPin,Reg1Length);
  Multiplexeur monMultiplex1 = Multiplexeur(Multiplex1PinS0, Multiplex1PinS1 , Multiplex1PinS2 , Multiplex1PinA , &monRegistre1, &myEsp32); // crée un multiplexeur qui depend d'un registre et de l'esp32
  
  Capteur capteur1 = Capteur(0,&monMultiplex1);
  Capteur capteur2 = Capteur(1,&monMultiplex1);
  Capteur capteur3 = Capteur(2,&monMultiplex1);
  Capteur capteur4 = Capteur(3,&monMultiplex1);
  Capteur capteur5 = Capteur(4,&monMultiplex1);



  Configuration config_verin = Configuration("Verin",myImage,width,image_mode1_height,"Configuration V1 pour le verin");
}

*/