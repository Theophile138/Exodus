/**
 * @file LibDriver.h
 * @brief Déclaration de la classe DriverMotor pour piloter un vérin via deux sorties digitales.
 */

#ifndef LibDriver_h
#define LibDriver_h

#include "LibPeripherique.h"

/**
 * @class DriverMotor
 * @brief Classe pour piloter un vérin via deux sorties digitales.
 *
 * Cette classe permet de contrôler la montée, la descente et l'arrêt d'un vérin en utilisant deux sorties digitales, 
 * qui peuvent être connectées soit directement à l'ESP32, soit à un registre à décalage via l'interface ParentDevice.
 */
class DriverMotor {
  public:
    /**
     * @brief Constructeur du DriverMotor.
     * @param pinParent1 Numéro du premier pin de commande (direction 1).
     * @param pinParent2 Numéro du second pin de commande (direction 2).
     * @param parent Pointeur vers l'objet ParentDevice utilisé pour piloter les pins (direct ou registre).
     */
    DriverMotor(int pinParent1, int pinParent2, ParentDevice* parent);

    /**
     * @brief Active la montée du vérin.
     */
    void RaiseArm();

    /**
     * @brief Active la descente du vérin.
     */
    void LowerArm();

    /**
     * @brief Arrête le vérin.
     */
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