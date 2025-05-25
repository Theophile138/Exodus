/**
 * @file LibScreen.h
 * @brief Déclaration de la classe Screen pour la gestion de l'affichage, des boutons et des jauges sur écran TFT tactile.
 */

#ifndef LibScreen_h
#define LibScreen_h

#include <TFT_eSPI.h>   ///< Bibliothèque spécifique pour écrans TFT
#include <SPI.h>
#include "LibJauge.h"
#include "FS.h"
#include "LibButton.h"

#define SCREEN_WIDTH  240   ///< Largeur de l'écran TFT
#define SCREEN_HEIGHT 320   ///< Hauteur de l'écran TFT

#define CALIBRATION_FILE "/TouchCalData1" ///< Nom du fichier de calibration tactile (SPIFFS)
#define REPEAT_CAL false                  ///< Mettre à true pour forcer la calibration à chaque démarrage

/**
 * @class Screen
 * @brief Classe principale pour gérer l'affichage, les boutons et les jauges sur un écran TFT tactile.
 *
 * Permet d'initialiser l'écran, d'afficher des images, des jauges, de gérer les menus, les boutons tactiles et la calibration.
 */
class Screen {
    
    public:

        /**
         * @brief Constructeur de la classe Screen.
         */
        Screen();

        /**
         * @brief Efface l'écran (remplit de noir).
         */
        void clearScreen();

        /**
         * @brief Affiche l'écran de démarrage avec la version du firmware.
         * @param firmwareVersion Version du firmware à afficher.
         */
        void imageStart(String firmwareVersion);

        /**
         * @brief Initialise le menu de sélection.
         */
        void Select_Menu_init();

        /**
         * @brief Fonction statique pour gérer la boucle du menu de sélection.
         * @param Scr Pointeur vers l'objet Screen courant.
         */
        static void Select_Menu_run(Screen* Scr);
        
        /**
         * @brief Initialise le menu des jauges.
         */
        void Gauge_Menu_init();

        /**
         * @brief Fonction statique pour gérer la boucle du menu des jauges.
         * @param Scr Pointeur vers l'objet Screen courant.
         */
        static void Gauge_Menu_run(Screen* Scr);

        /**
         * @brief Lance la calibration de l'écran tactile.
         */
        void touch_calibrate();

        /**
         * @brief Redessine tous les boutons à l'écran.
         */
        void renderButton();

        /**
         * @brief Pointeur vers la fonction de boucle courante (menu ou jauge).
         */
        void (*run)(Screen*);

        static void emptyFunction(Screen*) {} ///< Fonction vide par défaut pour les callbacks


        // --- Callbacks pour les boutons ---
        static void leftOnclick(Screen* Scr);    ///< Callback pour le bouton gauche
        static void rightOnclick(Screen* Scr);   ///< Callback pour le bouton droit
        static void startOnclick(Screen* Scr);   ///< Callback pour le bouton START (appui)
        static void startOffclick(Screen* Scr);  ///< Callback pour le bouton START (relâchement)
        static void gaugeOnClick(Screen* Scr);   ///< Callback pour le bouton jauge
        static void backOnClick(Screen* Scr);    ///< Callback pour le bouton retour

        linearMeter* linearMeters;   ///< Tableau de jauges linéaires
        bool activeControle;         ///< Indique si le contrôle est actif
        int config_selectionne;      ///< Numéro de la configuration sélectionnée
        analogMeters* myGauge;       ///< Pointeur vers la jauge analogique

    private: 
        
        int number;                  ///< Variable interne pour l'animation ou la sélection
        int index;                   ///< Index courant pour les jauges

        TFT_eSPI* tft;               ///< Pointeur vers l'objet TFT_eSPI

        // static void emptyFunction(Screen*) {Serial.println("NO run set for the sreen !");}
        // Fonction vide appelée si aucune méthode n'est définie pour le bouton

        Button startButton;          ///< Bouton START
        Button leftButton;           ///< Bouton gauche
        Button rightButton;          ///< Bouton droit
        Button gaugeButton;          ///< Bouton jauge
        Button backButton;           ///< Bouton retour

};

#endif