#include "configTest1.h"
#include "LibScreen.h"
#include "LibConfig.h"
#include "image_data.h"

#include "LibPeripherique.h"
#include "Arduino.h"
#include "LibCapteur.h"


Screen myScreen;

unsigned long Time_screen;
unsigned long Time;
unsigned long total_time1;

unsigned long Time_config;
unsigned long total_time2;

int iteration1;
int iteration2;

#define FirmwareVersion "0.5"

float timeDelay = 10000;

void setup() {
  Serial.begin(115200);

  myScreen = Screen(); 
  myScreen.touch_calibrate();
  
  configTest1::init(&myScreen);

  myScreen.imageStart(FirmwareVersion);

  delay(5000);

  myScreen.Select_Menu_init();

  Time_screen = millis();
  
  Time_config = micros();

  Time = millis();

  total_time1 = 0;
  iteration1 = 0;

  total_time2 = 0;
  iteration2 = 0;

}

void loop() 
{

  if (millis() - Time_screen > 20){
    Time_screen = millis();
    myScreen.run(&myScreen);
    total_time1 = total_time1 + (millis() - Time_screen);
    iteration1 ++;
  }

  if (micros() - Time_config > 400){
    Time_config = micros();
    Task2();
    total_time2 = total_time2 + (micros() - Time_config);
    iteration2 ++;
  }



  
  if (millis() - Time >= timeDelay){
  
    Serial.print("Temp de gestion des taches sur "+String(timeDelay/1000.0));
    //Serial.print(" seconde :");
    //Serial.print(total_time1);
    Serial.print("  Ecran :");
    Serial.print((total_time1/timeDelay)*100);
    Serial.print("%");
    Serial.print("  Run config :");
    Serial.print((total_time2/(timeDelay*1000))*100);
    Serial.print("%");

    Serial.println("");

    float temp_moyen1 = total_time1/((float)iteration1);
    float temp_moyen2 = total_time2/((float)iteration2);
    Serial.print("Le temps moyen en miliseconde est de :");
    Serial.print(" Ecran :");
    Serial.print(temp_moyen1);
    Serial.println("");

    Serial.print("Le temps moyen en microseconde est de :");
    Serial.print(" Run config :");
    Serial.print(temp_moyen2);

    Serial.println("");

    iteration1 = 0;
    iteration2 = 0;

    total_time1 = 0;
    total_time2 = 0;

    Time = millis();

    

  }
  
}

void Task2(){
  
  configTest1::run();
  myScreen.linearMeters[0].new_value = (int)(configTest1::value1*100.0/4095.0);
  myScreen.linearMeters[1].new_value = (int)(configTest1::value2*100.0/4095.0);
  myScreen.linearMeters[2].new_value = (int)(configTest1::value3*100.0/4095.0);
  myScreen.linearMeters[3].new_value = (int)(configTest1::value4*100.0/4095.0);
  myScreen.linearMeters[4].new_value = (int)(configTest1::value5*100.0/4095.0);
  myScreen.linearMeters[5].new_value = (int)(configTest1::value6*100.0/4095.0);

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