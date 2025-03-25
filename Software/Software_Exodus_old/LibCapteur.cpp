#include "LibCapteur.h"

// ---------- Capteur de Force ----------
CapteurDeForce::CapteurDeForce(int pinAnalog, ParentAnalog* parent)
{
  this->pinAnalog = pinAnalog;
  this->parent = parent;
}

int CapteurDeForce::getValue()
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
