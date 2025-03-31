/*
Theophile Klein - 27/01/2025
*/

#include "LibCapteur.h"
#include "LibPeripherique.h"

#include "../Extend_Card_lib/Extend_Card_lib.h"

Capteur::Capteur(int pinAnalog,ParentAnalog* parent)
{
  Capteur::pinAnalog = pinAnalog;
  Capteur::parent = parent;
}

Capteur::Capteur(int pinAnalog, Extend_Card* card){
  Capteur::pinAnalog = pinAnalog;
  Capteur::parent = nullptr;

  if ((pinAnalog > 0) && (pinAnalog < 8)){
    Capteur::parent = card->monMultiplex1;
  }
  if ((pinAnalog > 7) && (pinAnalog < 16)){
    Capteur::parent = card->monMultiplex2;
  }
  
}

int Capteur::getValue()
{
  return parent->analogReadAnyDevice(pinAnalog);
}

// ---------- Capteur MPU6050 ----------
CapteurMPU6050::CapteurMPU6050() {}

void CapteurMPU6050::begin() {
  Wire.begin();
  mpu.initialize();
}

void CapteurMPU6050::getAcceleration(int16_t &ax, int16_t &ay, int16_t &az) {
  mpu.getAcceleration(&ax, &ay, &az);
}

void CapteurMPU6050::getGyroscope(int16_t &gx, int16_t &gy, int16_t &gz) {
  mpu.getRotation(&gx, &gy, &gz);
}