#include "configTest1.h"


void setup() {
  Serial.begin(115200);
  configTest1::init();
}

void loop() 
{
  configTest1::run();
}
