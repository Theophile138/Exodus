#include "configTest1.h"
#include "LibScreen.h"

Screen myScreen;

void setup() {
  Serial.begin(115200);
  configTest1::init();

  myScreen = Screen(); 
  myScreen.testScreen();

  pinMode(15,OUTPUT);
  digitalWrite(15,HIGH);

}

void loop() 
{
  // Config pour testé le prototype n°1 :
  configTest1::run();

  myScreen.testScreen();

}