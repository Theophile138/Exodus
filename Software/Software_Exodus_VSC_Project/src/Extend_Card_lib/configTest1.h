/*
 * @file configTest1.h
 * @brief Configuration matérielle et logique pour un test d'extension de carte sur ESP32 (registre à décalage, multiplexeur, capteurs, actionneurs).
 */

#ifndef configTest1_h
#define configTest1_h

#include "../Hardware_lib/LibPeripherique.h"
#include "Arduino.h"
#include "../Hardware_lib/LibCapteur.h"
#include "../Hardware_lib/LibDriver.h"

#if defined(ESP32)
#include "soc/gpio_struct.h" // Pour accéder aux registres GPIO
#include "driver/gpio.h"    // Pour configurer les GPIOs
#include "../Screen_lib/LibScreen.h"
#endif

/**
 * @class configTest1
 * @brief Classe statique de configuration pour un test matériel avec registre à décalage, multiplexeur, capteurs et actionneur sur ESP32.
 *
 * Cette classe regroupe la configuration des broches, l'initialisation des objets matériels (registre, multiplexeur, capteurs, moteur)
 * et fournit des méthodes statiques pour initialiser et exécuter le test.
 */
class configTest1 {
public:

  #if defined(ESP32)
  /**
   * @brief Initialise tous les objets matériels pour le test (registre, multiplexeur, capteurs, moteur, écran).
   * @param scr Pointeur vers l'objet écran à configurer.
   */
  static void init(Screen* scr);
  #else
  /**
   * @brief Initialise tous les objets matériels pour le test (registre, multiplexeur, capteurs, moteur).
   */
  static void init();
  #endif

  /**
   * @brief Exécute la boucle principale du test (lecture capteurs, contrôle moteur, affichage, etc.).
   */
  static void run();

  // --- Configuration du registre à décalage ---
  static const int Reg1DataPin;   ///< Pin de données du registre à décalage
  static const int Reg1ClockPin;  ///< Pin d'horloge du registre à décalage
  static const int Reg1TrigPin;   ///< Pin de validation (latch) du registre à décalage
  static const int Reg1Length;    ///< Taille du registre à décalage (en bits)
  static Registre* monRegistre1;  ///< Pointeur vers l'objet Registre

  // --- Configuration du multiplexeur ---
  static const int Multiplex1PinA;   ///< Pin analogique de lecture du multiplexeur
  static const int Multiplex1PinS0;  ///< Pin de sélection S0 du multiplexeur (contrôlé par le registre)
  static const int Multiplex1PinS1;  ///< Pin de sélection S1 du multiplexeur (contrôlé par le registre)
  static const int Multiplex1PinS2;  ///< Pin de sélection S2 du multiplexeur (contrôlé par le registre)
  static MasterDevice* myEsp32;      ///< Pointeur vers l'objet MasterDevice (ESP32)
  static Multiplexeur* monMultiplex1;///< Pointeur vers l'objet Multiplexeur

  // --- Capteurs analogiques (ex: capteurs de force) ---
  static Capteur* capteurForce1; ///< Pointeur vers le capteur de force 1
  static Capteur* capteurForce2; ///< Pointeur vers le capteur de force 2
  static Capteur* capteurForce3; ///< Pointeur vers le capteur de force 3
  static Capteur* capteurForce4; ///< Pointeur vers le capteur de force 4
  static Capteur* capteurForce5; ///< Pointeur vers le capteur de force 5

  // --- Capteur MPU6050 (accéléromètre/gyroscope) ---
  static CapteurMPU6050* capteurMPU; ///< Pointeur vers le capteur MPU6050

  // --- Actionneur (moteur linéaire) ---
  static DriverMotor* verin; ///< Pointeur vers le moteur linéaire

  // --- Variables de direction et de valeurs lues ---
  static int dir;   ///< Variable de direction pour le moteur ou l'état
  static int dir2;  ///< Variable de direction secondaire

  static int value1; ///< Valeur lue du capteur 1
  static int value2; ///< Valeur lue du capteur 2
  static int value3; ///< Valeur lue du capteur 3
  static int value4; ///< Valeur lue du capteur 4
  static int value5; ///< Valeur lue du capteur 5
  static int value6; ///< Valeur lue du capteur 6 (si utilisé)
};

#endif