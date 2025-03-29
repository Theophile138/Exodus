/*
Theophile Klein - 27/01/2025
*/

#ifndef LibCapteur_h
#define LibCapteur_h

#include <Wire.h>
#include <MPU6050.h> // Bibliothèque nécessaire pour MPU6050
#include "LibPeripherique.h"

// ---------- Capteur de Force ----------
class CapteurDeForce {
  public:
    CapteurDeForce(int pinAnalog, ParentAnalog* parent);
    int getValue();

  private: 
    ParentAnalog* parent;
    int pinAnalog;
};

// ---------- Capteur MPU6050 ----------
class CapteurMPU6050 {
  public:
    CapteurMPU6050();
    void begin();
    void getAcceleration(int16_t &ax, int16_t &ay, int16_t &az);
    void getGyroscope(int16_t &gx, int16_t &gy, int16_t &gz);

  private:
    MPU6050 mpu;
};

#endif
