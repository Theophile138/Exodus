#ifndef LibPeripherique_h
#define LibPeripherique_h

#include "Arduino.h"

/**
 * @file LibPeripherique.h
 * @brief Classes pour gérer les multiplexeurs et registres pour d'augmenter la capacité I/O de l'ESP.
 */

/**
 * @class ParentDevice
 * @brief Interface pour les périphériques pouvant être sélectionnés par un multiplexeur ou contrôlés par un registre.
 */
class ParentDevice
{
  public:
    /**
     * @brief Sélectionne un canal sur un multiplexeur.
     * @param pinChangeBin Valeur binaire à appliquer sur les pins de sélection.
     * @param pin1 Premier pin de sélection.
     * @param pin2 Deuxième pin de sélection.
     * @param pin3 Troisième pin de sélection.
     */
    virtual void selectPinMultiplexeur(int pinChangeBin, int pin1 , int pin2, int pin3) = 0;

    /**
     * @brief Définit l'état d'un pin (utilisé pour les registres).
     * @param pin Numéro du pin à modifier.
     * @param value Valeur à appliquer (HIGH ou LOW).
     */
    virtual void setPin(int pin , bool value);
};

/**
 * @class ParentAnalog
 * @brief Interface pour les périphériques capables de lire une valeur analogique.
 */
class ParentAnalog
{
  public:
    /**
     * @brief Lit la valeur analogique d'un canal donné.
     * @param pin Numéro du canal à lire.
     * @return Valeur analogique lue.
     */
    virtual int analogReadAnyDevice(int pin) = 0;
};

/**
 * @class MasterDevice
 * @brief Implémente ParentDevice et ParentAnalog pour gérer directement les pins du microcontrôleur.
 */
class MasterDevice : public ParentDevice , public ParentAnalog {
public:
    /**
     * \copydoc ParentDevice::selectPinMultiplexeur
     */
    void selectPinMultiplexeur(int pinChangeBin, int pin1 , int pin2, int pin3) override;

    /**
     * \copydoc ParentDevice::setPin
     */
    void setPin(int pin , bool value) override;

    /**
     * \copydoc ParentAnalog::analogReadAnyDevice
     */
    int analogReadAnyDevice(int pin) override;
};

/**
 * @class Registre
 * @brief Classe pour piloter un registre.
 *
 * Permet d'augmenter le nombre de sorties digitales disponibles.
 */
class Registre : public ParentDevice
{
  public:
    /**
     * @brief Constructeur du registre.
     * @param dataPin Pin de données.
     * @param clockPin Pin d'horloge.
     * @param trigPin Pin de validation.
     * @param length Nombre de bits du registre.
     */
    Registre(int dataPin, int clockPin, int trigPin, int length);

    /**
     * @brief Modifie une partie des données du registre.
     * @param smallBinary Valeur à insérer.
     * @param lengthSmallBin Taille de la valeur à insérer.
     * @param position Position de départ dans le registre.
     */
    void changeByte(int smallBinary,int lengthSmallBin, int position);

    /**
     * @brief Met à jour l'état des sorties du registre.
     */
    void Refresh();

    /**
     * @brief Initialise le registre (configuration des pins).
     */
    void Begin();

    /**
     * \copydoc ParentDevice::selectPinMultiplexeur
     */
    void selectPinMultiplexeur(int pinChangeBin, int pin1 , int pin2, int pin3) override;

    /**
     * \copydoc ParentDevice::setPin
     */
    void setPin(int pin , bool value) override;

  private:
    /**
     * @brief Modifie une partie d'un nombre binaire.
     */
    int changeByteInOctet(int largeBinary, int smallBinary,int lengthSmallBin, int position);

    /**
     * @brief Envoie les données sur le registre.
     */
    void sendBit(int binaryData);

    int dataPin;   ///< Pin de données
    int clockPin;  ///< Pin d'horloge
    int trigPin;   ///< Pin de validation (latch)
    int length;    ///< Nombre de bits du registre

    int dataNow;   ///< Données courantes du registre
};

/**
 * @class Multiplexeur
 * @brief Classe pour piloter un multiplexeur analogique (ex : CD4051).
 *
 * Permet de sélectionner une entrée et de lire sa valeur via un multiplexeur.
 */
class Multiplexeur : public ParentAnalog
{
  public:
    /**
     * @brief Constructeur du multiplexeur.
     * @param S0 Pin de sélection S0.
     * @param S1 Pin de sélection S1.
     * @param S2 Pin de sélection S2.
     * @param analogPin Pin analogique de lecture.
     * @param parentSelec Pointeur vers l'objet ParentDevice pour la sélection.
     * @param parentAnalog Pointeur vers l'objet ParentAnalog pour la lecture.
     */
    Multiplexeur(int S0 , int S1 , int S2 , int analogPin , ParentDevice* parentSelec , ParentAnalog* parentAnalog);

    /**
     * \copydoc ParentAnalog::analogReadAnyDevice
     */
    int analogReadAnyDevice(int pin) override;

    /**
     * @brief Sélectionne un canal du multiplexeur.
     * @param pin Numéro du canal à sélectionner.
     */
    void SelectPin(int pin);

  private:
    int S0; ///< Pin de sélection S0
    int S1; ///< Pin de sélection S1
    int S2; ///< Pin de sélection S2
    int analogPin; ///< Pin analogique pour la lecture

    ParentDevice* parent; ///< Pointeur vers le parent pour la sélection
    ParentAnalog* parentAnalog; ///< Pointeur vers le parent pour la lecture
};

#endif