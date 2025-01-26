#ifndef LibPeripherique_h
#define LibPeripherique_h

#include "Arduino.h"

class ParentDevice
{
  public:
    virtual void selectPinMultiplexeur(int pinChangeBin, int pin1 , int pin2, int pin3) = 0; //Cette méthode virtuelle pure est plutôt dédier aux changement des pins du multiplexeur en même temps. Et elle plutôt dedier au registre
};

class ParentAnalog // Class utilisé pour indiquer qui possède la pin analogique du multiplexeur 
{
  public:
    virtual int analogReadMultiplexeur(int pin) = 0;
};

class MasterDevice : public ParentDevice , public ParentAnalog {
public:
    void selectPinMultiplexeur(int pinChangeBin, int pin1 , int pin2, int pin3) override;
    int analogReadMultiplexeur(int pin) override;
};

class Registre : public ParentDevice
{
  public:
    
    Registre(int dataPin, int clockPin, int trigPin, int length);
    void changeByte(int smallBinary,int lengthSmallBin, int position);
    void Refresh();
    void Begin();
    void selectPinMultiplexeur(int pinChangeBin, int pin1 , int pin2, int pin3) override;
    
  private:
    int changeByteInOctet(int largeBinary, int smallBinary,int lengthSmallBin, int position);
    void sendBit(int binaryData);


      int dataPin;
      int clockPin;
      int trigPin;
      int length;

      int dataNow;
};

class Multiplexeur : public ParentAnalog
{
  public:
    Multiplexeur(int S0 , int S1 , int S2 , int analogPin , ParentDevice* parentSelec , ParentAnalog* parentAnalog);
    int analogReadMultiplexeur(int pin) override;
    void SelectPin(int pin);

  private:
    int S0;
    int S1;
    int S2;
    int analogPin;

    ParentDevice* parent;
    ParentAnalog* parentAnalog;

};

#endif