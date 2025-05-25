/*
 * @file Extend_Card_lib.h
 * @brief Déclaration de la classe Extend_Card pour gérer l'extension d'entrées/sorties via registres à décalage et multiplexeurs sur ESP32.
 */

#ifndef Extend_Card_lib_h
#define Extend_Card_lib_h

#include "../Hardware_lib/LibPeripherique.h"
#include "Arduino.h"

#if defined(ESP32)
#include "soc/gpio_struct.h" // Pour accéder aux registres GPIO
#include "driver/gpio.h"    // Pour configurer les GPIOs
#endif

/**
 * @class Extend_Card
 * @brief Classe permettant de gérer des extensions d'entrées/sorties grâce à un registre et deux multiplexeurs.
 *
 * Cette classe facilite étend le nombre d'entrées/sorties sur un ESP32 en utilisant un registre pour les sorties digitales
 * et deux multiplexeurs pour les entrées analogiques.
 */
class Extend_Card {

  public:
    /**
     * @brief Constructeur de la classe Extend_Card.
     *
     * Initialise les objets MasterDevice, Registre et Multiplexeur nécessaires à l'extension des I/O.
     */
    Extend_Card();

    /**
     * @brief Écrit une valeur digitale sur un pin de sortie.
     * @param pin Numéro du pin virtuel (géré par le registre).
     * @param value Valeur à écrire (HIGH ou LOW).
     */
    void digitalWrite(int pin, bool value);

    /**
     * @brief Lit une valeur analogique.
     * @param pin Numéro du pin à lire (géré par le multiplexeur).
     * @return int Valeur analogique lue.
     */
    int analogRead(int pin);

    /**
     * @brief Pointeur vers l'objet MasterDevice qui représente l'ESP32.
     */
    MasterDevice* myEsp32;

    // --- Registre à décalage ---

    static const int Reg1DataPin = 25;   ///< Pin de données du registre à décalage (ESP32)
    static const int Reg1ClockPin = 26;  ///< Pin d'horloge du registre à décalage (ESP32)
    static const int Reg1TrigPin = 27;   ///< Pin de validation (latch) du registre à décalage (ESP32)
    static const int Reg1Length = 16;    ///< Taille du registre à décalage (en bits)
    Registre* monRegistre1;         ///< Pointeur vers l'objet Registre

    // --- Multiplexeur 1 ---

    static const int Multiplex1PinA = 36;   ///< Pin analogique de lecture du multiplexeur 1
    static const int Multiplex1PinS0 = 2;  ///< Pin de sélection S0 du multiplexeur 1
    static const int Multiplex1PinS1 = 1;  ///< Pin de sélection S1 du multiplexeur 1
    static const int Multiplex1PinS2 = 0;  ///< Pin de sélection S2 du multiplexeur 1
    Multiplexeur* monMultiplex1;       ///< Pointeur vers l'objet Multiplexeur 1

    // --- Multiplexeur 2 (en cascade) ---

    static const int Multiplex2PinA = 0;   ///< Pin analogique de lecture du multiplexeur 2 (sur le multiplexeur 1)
    static const int Multiplex2PinS0 = 5;  ///< Pin de sélection S0 du multiplexeur 2
    static const int Multiplex2PinS1 = 4;  ///< Pin de sélection S1 du multiplexeur 2
    static const int Multiplex2PinS2 = 3;  ///< Pin de sélection S2 du multiplexeur 2
    Multiplexeur* monMultiplex2;       ///< Pointeur vers l'objet Multiplexeur 2
};

#endif