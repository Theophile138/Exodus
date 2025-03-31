#include "Traitement_Capteur.h"
#include "../Hardware_lib/LibCapteur.h"

Capteur_De_Force::Capteur_De_Force(Capteur* Force1){

  this->Force1 = Force1;
  this->Force2 = nullptr;

  this->nbr_capteur = 1;
}

Capteur_De_Force::Capteur_De_Force(Capteur* Force1, Capteur* Force2){

  this->Force1 = Force1;
  this->Force2 = Force2;

  this->nbr_capteur = 2;
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