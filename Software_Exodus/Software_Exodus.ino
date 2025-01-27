#include "LibPeripherique.h"
#include "configTest1.h"


void setup() {
  Serial.begin(115200);
  configTest1::init();
}

void loop() {

  //monMultiplex1.SelectPin(1);
  configTest1::run();
}
