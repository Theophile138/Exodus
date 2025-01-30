#include "Arduino.h"
#include "LibPeripherique.h"
#include "soc/gpio_struct.h" // Pour accéder aux registres GPIO
#include "driver/gpio.h"    // Pour configurer les GPIOs

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Registre
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Constructeur du registre
Registre::Registre(int dataPin, int clockPin, int trigPin, int length)
{
  Registre::dataPin = dataPin;
  Registre::clockPin = clockPin;
  Registre::trigPin = trigPin;
  Registre::length = length;

  dataNow = 0;

  Registre::Begin();

}

// Change dans un nombre binaire une petite partie en la remplaçant par un nombre plus petit
// Ex : 01101110 et on veut qu'a partir de la position 3 les valeurs soit 000 , resulta : 011 000 10
int Registre::changeByteInOctet(int largeBinary, int smallBinary,int lengthSmallBin, int position) {

    int decalage = length - position - lengthSmallBin;
    int Mask = ~(((1 << lengthSmallBin) - 1) << decalage);
    int result = (largeBinary & Mask) | (smallBinary << decalage);

    return result;
}

// Version pour registre de la fonction changeByteInOctet
void Registre::changeByte(int smallBinary,int lengthSmallBin, int position){

  //int newValue = changeByteInOctet(dataNow,smallBinary,lengthSmallBin,position);
  //Serial.println("DataNow : "+ String(dataNow) + " smallBinary : " + String(smallBinary) + " LengthSmallBin : " +  String(lengthSmallBin) + " Position : " + String(position));
  dataNow = changeByteInOctet(dataNow,smallBinary,lengthSmallBin,position);
  //Serial.println("dataNow : "+ String(dataNow));
}

// Sert a refresh l'etat des pins du registre
void Registre::Refresh(){
  sendBit(dataNow);
}


void Registre::Begin()
{
    #if defined(ESP32)
      // Configuration des broches en sortie pour ESP32
      gpio_set_direction((gpio_num_t)dataPin, GPIO_MODE_OUTPUT);
      gpio_set_direction((gpio_num_t)clockPin, GPIO_MODE_OUTPUT);
      gpio_set_direction((gpio_num_t)trigPin, GPIO_MODE_OUTPUT);
    #elif defined(ARDUINO)
      // Configuration des broches en sortie pour Arduino
      pinMode(dataPin, OUTPUT);
      pinMode(clockPin, OUTPUT);
      pinMode(trigPin, OUTPUT);
    #endif
}

void Registre::sendBit(int binaryData) {
  // Détection de la plateforme
  #if defined(ESP32)

    for (int i = 0; i < length; i++) {
      // Calcule la valeur du bit
      int bitValue = (binaryData >> i) & 1;

      // Écrit la valeur directement sur la broche dataPin
      if (bitValue) {
        GPIO.out_w1ts = (1 << dataPin); // Set dataPin HIGH
      } else {
        GPIO.out_w1tc = (1 << dataPin); // Set dataPin LOW
      }

      // Génère une impulsion d'horloge sur clockPin
      GPIO.out_w1ts = (1 << clockPin); // Set clockPin HIGH
      GPIO.out_w1tc = (1 << clockPin); // Set clockPin LOW
    }

    // Génère une impulsion sur trigPin
    GPIO.out_w1ts = (1 << trigPin); // Set trigPin HIGH
    GPIO.out_w1tc = (1 << trigPin); // Set trigPin LOW

  #elif defined(ARDUINO)


    for (int i = 0; i < length; i++) {
      // Calcule la valeur du bit
      int bitValue = (binaryData >> i) & 1;

      // Écrit la valeur sur dataPin
      digitalWrite(dataPin, bitValue ? HIGH : LOW);

      // Génère une impulsion d'horloge sur clockPin
      digitalWrite(clockPin, HIGH);
      digitalWrite(clockPin, LOW);
    }

    // Génère une impulsion sur trigPin
    digitalWrite(trigPin, HIGH);
    digitalWrite(trigPin, LOW);
  #endif
}


void Registre::selectPinMultiplexeur(int pinChangeBin, int pin1 , int pin2, int pin3)
{
    if ( (pin2 == (pin1 + 1) ) && (pin3 == (pin2 + 1)) )
    {
      changeByte(pinChangeBin,3,pin1);

      //Serial.println("pinChangeBin : "+ String(pinChangeBin) + "Pin 1 : " + String(Pin1));

    }else
    {
      changeByte(((pinChangeBin>>2) & 1),1,pin1);
      changeByte(((pinChangeBin>>1) & 1),1,pin2);
      changeByte((pinChangeBin & 1),1,pin3);
    }
    //changeByte(pinChange,nbr,position);
    Refresh();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Multiplexeur
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


Multiplexeur::Multiplexeur(int S0 , int S1 , int S2 , int analogPin , ParentDevice* parent, ParentAnalog* parentAnalog)
{
  Multiplexeur::S0=S0;
  Multiplexeur::S1=S1;
  Multiplexeur::S2=S2;
  Multiplexeur::analogPin = analogPin;
  Multiplexeur::parent = parent;
  Multiplexeur::parentAnalog = parentAnalog;
}

void Multiplexeur::SelectPin(int pin)
{
  parent->selectPinMultiplexeur(pin, S0 , S1 , S2);
};

int Multiplexeur::analogReadAnyDevice(int pin)
{
  Multiplexeur::SelectPin(pin);
  int result = Multiplexeur::parentAnalog->analogReadAnyDevice(Multiplexeur::analogPin);
  return result;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//MasterDevice
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void MasterDevice::selectPinMultiplexeur(int pinChangeBin, int pin1, int pin2, int pin3) {
  // Détection de la plateforme
  #if defined(ESP32)
    // ESP32 : Configuration des broches en mode sortie
    gpio_set_direction((gpio_num_t)pin1, GPIO_MODE_OUTPUT);
    gpio_set_direction((gpio_num_t)pin2, GPIO_MODE_OUTPUT);
    gpio_set_direction((gpio_num_t)pin3, GPIO_MODE_OUTPUT);

    // Écriture des bits en utilisant les registres GPIO
    if ((pinChangeBin >> 2) & 1) {
      GPIO.out_w1ts = (1 << pin1); // Pin1 HIGH
    } else {
      GPIO.out_w1tc = (1 << pin1); // Pin1 LOW
    }

    if ((pinChangeBin >> 1) & 1) {
      GPIO.out_w1ts = (1 << pin2); // Pin2 HIGH
    } else {
      GPIO.out_w1tc = (1 << pin2); // Pin2 LOW
    }

    if (pinChangeBin & 1) {
      GPIO.out_w1ts = (1 << pin3); // Pin3 HIGH
    } else {
      GPIO.out_w1tc = (1 << pin3); // Pin3 LOW
    }

  #elif defined(ARDUINO)
    // Arduino : Configuration des broches en mode sortie
    pinMode(pin1, OUTPUT);
    pinMode(pin2, OUTPUT);
    pinMode(pin3, OUTPUT);

    // Écriture des bits en utilisant digitalWrite
    digitalWrite(pin1, ((pinChangeBin >> 2) & 1) ? HIGH : LOW);
    digitalWrite(pin2, ((pinChangeBin >> 1) & 1) ? HIGH : LOW);
    digitalWrite(pin3, (pinChangeBin & 1) ? HIGH : LOW);
  #endif
}

int MasterDevice::analogReadAnyDevice(int pin)
{
  int result = analogRead(pin);
  return result;
}

