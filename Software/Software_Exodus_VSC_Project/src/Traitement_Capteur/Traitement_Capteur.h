#ifndef Traitement_Capteur_h
#define Traitement_Capteur__h

#include "../Hardware_lib/LibCapteur.h"

class Capteur_De_Force {
  public:

  //void setDir(int direction);
    Capteur_De_Force(Capteur* Force1);
    Capteur_De_Force(Capteur* Force1, Capteur* Force2);

    bool setActiveCapteur(int nombre);

  private: 
    Capteur* Force1;
    Capteur* Force2;
    
    int nbr_capteur;   
    int nbr_active_capteur;
};


#endif