/**
 * @file LibCapteur.h
 * @brief Déclarations des classes de capteurs analogiques et MPU6050 pour l'extension d'I/O sur ESP32.
 */

#ifndef LibCapteur_h
#define LibCapteur_h

#include <Wire.h>       ///< Nécessaire pour la communication I2C
#include "MPU6050.h"    ///< Nécessaire pour la classe MPU6050
#include "LibPeripherique.h"
#include "../Extend_Card_lib/Extend_Card_lib.h"

/**
 * @class Capteur
 * @brief Classe générique pour un capteur analogique connecté via un ParentAnalog ou une Extend_Card.
 */
class Capteur {
  public:
    /**
     * @brief Constructeur avec un parent de type ParentAnalog.
     * @param pinAnalog Pin analogique auquel le capteur est connecté.
     * @param parent Pointeur vers l'objet ParentAnalog utilisé pour la lecture.
     */
    Capteur(int pinAnalog, ParentAnalog* parent);

    /**
     * @brief Constructeur avec une carte étendue.
     * @param pinAnalog Pin analogique auquel le capteur est connecté.
     * @param Card Pointeur vers l'objet Extend_Card utilisé pour la lecture.
     */
    Capteur(int pinAnalog, Extend_Card* Card);

    /**
     * @brief Lit la valeur analogique du capteur.
     * @return int Valeur lue sur le pin analogique.
     */
    int getValue();

  private: 
    ParentAnalog* parent; ///< Pointeur vers le parent pour la lecture analogique
    int pinAnalog;        ///< Pin analogique du capteur
};

/**
 * @class CapteurMPU6050
 * @brief Classe pour gérer un capteur MPU6050 (accéléromètre et gyroscope).
 */
class CapteurMPU6050 {
  public:
    /**
     * @brief Constructeur du capteur MPU6050.
     */
    CapteurMPU6050();

    /**
     * @brief Initialise le capteur MPU6050.
     */
    void begin();

    /**
     * @brief Récupère les valeurs d'accélération sur les trois axes.
     * @param ax Référence pour la valeur d'accélération X.
     * @param ay Référence pour la valeur d'accélération Y.
     * @param az Référence pour la valeur d'accélération Z.
     */
    void getAcceleration(int16_t &ax, int16_t &ay, int16_t &az);

    /**
     * @brief Récupère les valeurs de rotation (gyroscope) sur les trois axes.
     * @param gx Référence pour la valeur de rotation X.
     * @param gy Référence pour la valeur de rotation Y.
     * @param gz Référence pour la valeur de rotation Z.
     */
    void getGyroscope(int16_t &gx, int16_t &gy, int16_t &gz);

  private:
    MPU6050 mpu; ///< Instance du capteur MPU6050
};

#endif
