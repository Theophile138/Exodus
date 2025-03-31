#ifndef LibCapteur_h
#define LibCapteur_h

#include <Wire.h>       // Nécessaire pour I2C
#include <MPU6050.h>    // Nécessaire pour la classe MPU6050
#include "LibPeripherique.h"

#include "../Extend_Card_lib/Extend_Card_lib.h"

class Capteur {
  public:
    Capteur(int pinAnalog, ParentAnalog* parent);
    Capteur(int pinAnalog, Extend_Card* Card);
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
