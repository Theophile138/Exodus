#ifndef Traitement_Capteur_h
#define Traitement_Capteur__h

#include "../Hardware_lib/LibCapteur.h"

class Capteur_De_Force {
  public:

  //void setDir(int direction);
    Capteur_De_Force(Capteur* Force1);
    Capteur_De_Force(Capteur* Force1, Capteur* Force2);

    bool setActiveCapteur(int nombre);

    void run();
    void (*action_mid)(Capteur_De_Force*);
    void (*action_high)(Capteur_De_Force*);
    void (*action_low)(Capteur_De_Force*);

  private: 
    Capteur* Force1;
    Capteur* Force2;
    
    static void emptyFunction(Capteur_De_Force*) {Serial.println("NO run set for Capteur_De_Force !");} // Fonction vide qui ne fait rien si aucune methode a été donné pour le press button
    
    int nbr_capteur;   
    int nbr_active_capteur;

    int high_etendu; // l'etendu
    int low_etendu;

    int highValue;
    int lowValue;
};


#endif