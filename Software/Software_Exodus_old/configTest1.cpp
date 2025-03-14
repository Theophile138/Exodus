/*
Theophile Klein - 27/01/2025
*/

#include "Arduino.h"
#include "LibPeripherique.h"
#include "configTest1.h"
#include "LibCapteur.h"

#include "soc/gpio_struct.h" // Pour accéder aux registres GPIO
#include "driver/gpio.h"    // Pour configurer les GPIOs

Registre* configTest1::monRegistre1 = nullptr;    // Initialisé à nullptr
MasterDevice* configTest1::myEsp32 = nullptr;     // Initialisé à nullptr
Multiplexeur* configTest1::monMultiplex1 = nullptr; // Initialisé à nullptr

CapteurDeForce* configTest1::capteurForce1 = nullptr; // Initialisé à nullptr
CapteurDeForce* configTest1::capteurForce2 = nullptr; // Initialisé à nullptr
CapteurDeForce* configTest1::capteurForce3 = nullptr; // Initialisé à nullptr
CapteurDeForce* configTest1::capteurForce4 = nullptr; // Initialisé à nullptr
CapteurDeForce* configTest1::capteurForce5 = nullptr; // Initialisé à nullptr


int configTest1::dir = 0;
int configTest1::dir2 = 0;

void configTest1::init() 
{

  configTest1::myEsp32 = new MasterDevice(); // crée parent ici un esp32
  configTest1::monRegistre1 = new Registre(Reg1DataPin,Reg1ClockPin,Reg1TrigPin,Reg1Length);
  configTest1::monMultiplex1 = new Multiplexeur(Multiplex1PinS0, Multiplex1PinS1 , Multiplex1PinS2 , Multiplex1PinA , monRegistre1, myEsp32); // crée un multiplexeur qui depend d'un registre et de l'esp32
  
  configTest1::capteurForce1 = new CapteurDeForce(0,monMultiplex1);
  configTest1::capteurForce2 = new CapteurDeForce(1,monMultiplex1);
  configTest1::capteurForce3 = new CapteurDeForce(2,monMultiplex1);
  configTest1::capteurForce4 = new CapteurDeForce(3,monMultiplex1);
  configTest1::capteurForce5 = new CapteurDeForce(4,monMultiplex1);


}

void configTest1::run(){
  
  int value = configTest1::capteurForce1->getValue();
  
  /*

  Serial.print("Capteur1:"+String(value)+",");

  delay(100);

  int value2 = configTest1::capteurForce2->getValue();
  Serial.print("Capteur2:"+String(value2)+",");
    
  delay(100);

  */

  int value3 = configTest1::capteurForce3->getValue();
  Serial.print("Capteur3:"+String(value3)+",");
  
  //delay(100);

  int value4 = configTest1::capteurForce4->getValue();
  Serial.print("Capteur4:"+String(value4)+",");
  
  int value5 = configTest1::capteurForce5->getValue();
  Serial.print("Capteur5:"+String(value5)+",");

  //delay(100);

  Serial.print("dir2:"+String(dir2)+",");

  Serial.println("");


  if (value5 == 0){
    
    if (dir2 != 100){
      configTest1::monRegistre1->changeByte(0b01, 2 , 0);
      configTest1::monRegistre1->Refresh();
        // ESP32 : Configuration des broches en mode sortie
        dir2 = 1;
    }
  }

  if ((value5 > 10)&&(value5 < 60))
  {
    if (dir2 != 0){
      configTest1::monRegistre1->changeByte(0b00, 2 , 0);
      configTest1::monRegistre1->Refresh();
   
      dir2 = 0;
    }
  }

  if (value5 > 100)
  {
    if (dir2 != -1){
      configTest1::monRegistre1->changeByte(0b10, 2 , 0);
      configTest1::monRegistre1->Refresh();
      dir2 = -1;
    }
  }


  if (value > 2000){
    
    if (dir != 1){
      configTest1::monRegistre1->changeByte(0b01, 2 , 0);
      configTest1::monRegistre1->Refresh();
        // ESP32 : Configuration des broches en mode sortie
        dir = 1;
    }
  }

  if ((value > 1500)&&(value < 2000))
  {
    if (dir != 0){
      configTest1::monRegistre1->changeByte(0b00, 2 , 0);
      configTest1::monRegistre1->Refresh();
      dir = 0;
    }
  }

  if (value < 1500)
  {
    if (dir != -1){
      configTest1::monRegistre1->changeByte(0b10, 2 , 0);
      configTest1::monRegistre1->Refresh();
      dir = -1;
    }
  }

}
