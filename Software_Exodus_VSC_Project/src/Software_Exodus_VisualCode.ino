#include "configTest1.h"
#include "LibScreen.h"

Screen myScreen;

#define FirmwareVersion "0.1"

void setup() {
  Serial.begin(115200);

  configTest1::init();

  myScreen = Screen(); 
  myScreen.imageStart(FirmwareVersion);

  delay(4000);

  myScreen.StatMenu();
}

void loop() 
{
  // Config pour testé le prototype n°1 :
  //configTest1::run();

  //myScreen.testScreen();

  //Serial.print("Mémoire libre : ");
  //Serial.println(ESP.getFreeHeap());
}