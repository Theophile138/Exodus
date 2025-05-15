/**
 * @file Traitement_Capteur.h
 * @brief Déclaration de la classe Capteur_De_Force pour la gestion et le traitement de capteurs de force.
 */

#ifndef Traitement_Capteur_h
#define Traitement_Capteur_h

#include "../Hardware_lib/LibCapteur.h"

/**
 * @class Capteur_De_Force
 * @brief Classe pour gérer un ou deux capteurs de force et sélectionner le(s) capteur(s) actif(s).
 *
 * Permet d'initialiser la gestion de 1 ou 2 capteurs de force, de choisir combien sont actifs, et de stocker les pointeurs vers ces capteurs.
 */
class Capteur_De_Force {
  public:
    /**
     * @brief Constructeur pour un seul capteur de force.
     * @param Force1 Pointeur vers le premier capteur de force.
     */
    Capteur_De_Force(Capteur* Force1);

    /**
     * @brief Constructeur pour deux capteurs de force.
     * @param Force1 Pointeur vers le premier capteur de force.
     * @param Force2 Pointeur vers le second capteur de force.
     */
    Capteur_De_Force(Capteur* Force1, Capteur* Force2);

    /**
     * @brief Définit le nombre de capteurs actifs.
     * @param nombre Nombre de capteurs à activer (1 ou 2).
     * @return true si la configuration est acceptée, false sinon.
     */
    bool setActiveCapteur(int nombre);

  private: 
    Capteur* Force1;           ///< Pointeur vers le premier capteur de force
    Capteur* Force2;           ///< Pointeur vers le second capteur de force (ou nullptr si non utilisé)
    int nbr_capteur;           ///< Nombre total de capteurs gérés
    int nbr_active_capteur;    ///< Nombre de capteurs actuellement actifs
};

#endif