/**
 * @file LibJauge.h
 * @brief Déclaration des classes analogMeters et linearMeter pour l'affichage de jauges analogiques et linéaires sur un écran TFT.
 */

#ifndef LibJauge_h
#define LibJauge_h

#include <TFT_eSPI.h> ///< Bibliothèque spécifique pour écrans TFT
#include <SPI.h>

#define TFT_GREY 0x5AEB      ///< Couleur grise pour l'affichage TFT
#define KEY_TEXTSIZE 1       ///< Facteur de taille de police

/**
 * @class analogMeters
 * @brief Classe pour afficher une jauge analogique (compteur à aiguille) sur écran TFT.
 *
 * Permet de dessiner une jauge analogique avec zones de couleur, d'afficher l'unité, et de déplacer l'aiguille en fonction d'une valeur.
 */
class analogMeters {
    public:
        /**
         * @brief Constructeur par défaut.
         */
        analogMeters();

        /**
         * @brief Dessine la jauge analogique à l'écran.
         * @param tft Pointeur vers l'objet TFT_eSPI.
         * @param positionX Position X de la jauge.
         * @param positionY Position Y de la jauge.
         * @param mideNumber Valeur centrale de la jauge.
         * @param minGreenLimite Début de la zone verte.
         * @param maxGreenLimite Fin de la zone verte.
         * @param minOrangeLimite Début de la zone orange.
         * @param maxOrangeLimite Fin de la zone orange.
         * @param unit Unité à afficher.
         */
        void drawAnalogMeters(TFT_eSPI* tft, int positionX, int positionY, int mideNumber, int minGreenLimite, int maxGreenLimite, int minOrangeLimite, int maxOrangeLimite, String unit);

        /**
         * @brief Déplace l'aiguille de la jauge à la valeur donnée.
         * @param value Valeur à afficher.
         * @param ms_delay Délai en ms pour l'animation de l'aiguille.
         */
        void plotNeedle(int value, byte ms_delay);

        int height;         ///< Hauteur de la jauge
        int new_value;      ///< Nouvelle valeur à afficher

        /**
         * @brief Rafraîchit l'affichage si la valeur a changé.
         */
        void refresh();

    private: 
        int actual_value;   ///< Valeur actuellement affichée

        // Variables internes pour l'affichage de la jauge
        float ltx = 0;    ///< Coordonnée x du bas de l'aiguille
        uint16_t osx = 120, osy = 120; ///< Coordonnées x et y de l'extrémité de l'aiguille
        uint32_t updateTime = 0;       ///< Temps pour la prochaine mise à jour

        int old_analog =  -999;        ///< Dernière valeur affichée
        int mideNumber = 50;           ///< Valeur centrale de la jauge

        int minGreenLimite = -50;      ///< Début zone verte
        int maxGreenLimite = -25;      ///< Fin zone verte

        int minOrangeLimite = 25;      ///< Début zone orange
        int maxOrangeLimite = 50;      ///< Fin zone orange

        int positionX;                 ///< Position X de la jauge
        int positionY;                 ///< Position Y de la jauge

        String unit = "% Force";       ///< Unité affichée

        TFT_eSPI* tft;                 ///< Pointeur vers l'objet TFT_eSPI
};

/**
 * @class linearMeter
 * @brief Classe pour afficher une jauge linéaire sur écran TFT.
 *
 * Permet de dessiner une jauge linéaire verticale avec curseur mobile et affichage de la valeur.
 */
class linearMeter {
    public:
        /**
         * @brief Constructeur par défaut.
         */
        linearMeter();

        /**
         * @brief Dessine la jauge linéaire à l'écran.
         * @param tft Pointeur vers l'objet TFT_eSPI.
         * @param label Nom de la jauge.
         * @param x Position X.
         * @param y Position Y.
         */
        void plotLinear(TFT_eSPI* tft, char *label, int x, int y);

        /**
         * @brief Déplace le curseur de la jauge à la valeur donnée.
         * @param value Valeur à afficher.
         */
        void plotPointer(int value);

        /**
         * @brief Rafraîchit l'affichage si la valeur a changé.
         */
        void refresh();

        TFT_eSPI* tft;   ///< Pointeur vers l'objet TFT_eSPI
        char* name;      ///< Nom de la jauge
        int x;           ///< Position X
        int y;           ///< Position Y
        int new_value;   ///< Nouvelle valeur à afficher
        bool disable;    ///< Indique si la jauge est désactivée

    private:
        int actual_value; ///< Valeur actuellement affichée
        int old_value;    ///< Dernière valeur affichée
};

#endif