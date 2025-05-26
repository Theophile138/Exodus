/*
Theophile Klein - 27/01/2025
Paul Escalier - 25/02/2025
*/

#ifndef LibDriver_h
#define LibDriver_h

#include "LibPeripherique.h"

class DriverMotor {
  public:

  //void setDir(int direction);
  DriverMotor(int pinParent1, int pinParent2, ParentDevice* parent);

  void RaiseArm();
  void LowerArm();
  void StopArm();

    /**
     * @brief Change l'état du moteur.
     */
    void toggleActive();

  private: 
    int pinParent1;      ///< Premier pin de commande du moteur
    int pinParent2;      ///< Second pin de commande du moteur
    bool actif;          ///< Indicateur si le moteur est actif ou non
    ParentDevice* parent;///< Pointeur vers l'interface de commande (registre ou direct)
};


#endif