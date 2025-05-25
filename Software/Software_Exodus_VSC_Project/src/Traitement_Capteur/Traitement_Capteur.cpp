#include "Traitement_Capteur.h"
#include "../Hardware_lib/LibCapteur.h"

Capteur_De_Force::Capteur_De_Force(Capteur* Force1){

  this->Force1 = Force1;
  this->Force2 = nullptr;

  this->nbr_capteur = 1;

  action_mid = emptyFunction;
  action_high= emptyFunction;
  action_low = emptyFunction;

  int high_etendu = 410; // l'etendu avec 10% 
  int low_etendu = 410;

  int highValue = 4096;
  int lowValue = 0;

}

Capteur_De_Force::Capteur_De_Force(Capteur* Force1, Capteur* Force2){

  this->Force1 = Force1;
  this->Force2 = Force2;

  this->nbr_capteur = 2;

  action_mid = emptyFunction;
  action_high= emptyFunction;
  action_low = emptyFunction;
}

void Capteur_De_Force::run(){



}

bool Capteur_De_Force::setActiveCapteur(int num){

  bool result = false;

  if (num == 1){
    this->nbr_active_capteur = 1;
    result = true;
  }

  if (num == 2){
    this->nbr_active_capteur = 2;
    result = true;
  }

  return result;
}