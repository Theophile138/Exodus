/**
 * @file LibButton.h
 * @brief Déclaration de la classe Button pour la gestion de boutons graphiques sur écran tactile avec TFT_eSPI.
 */

#ifndef LibButton_h
#define LibButton_h

#include <TFT_eSPI.h> ///< Bibliothèque spécifique pour écrans TFT
// #include "LibScreen.h"

class Screen;

/**
 * @class Button
 * @brief Classe pour créer et gérer des boutons graphiques (texte ou image), avec gestion du tactile, du mode toggle et de l'état désactivé.
 *
 * Permet d'afficher des boutons sur un écran TFT, de gérer leur état (pressé, relâché, désactivé), d'utiliser des images ou du texte,
 * et de définir des callbacks pour les actions (onClick, offClick).
 */
class Button
{
    private:
        TFT_eSPI *gfx;                ///< Pointeur vers l'objet graphique TFT
        int16_t x;                    ///< Position X du centre du bouton
        int16_t y;                    ///< Position Y du centre du bouton
        uint16_t w;                   ///< Largeur du bouton
        uint16_t h;                   ///< Hauteur du bouton
        uint16_t outline;             ///< Couleur du contour
        uint16_t fill;                ///< Couleur de fond
        uint16_t textcolor;           ///< Couleur du texte
        char *label;                  ///< Texte affiché sur le bouton
        uint8_t textsize;             ///< Taille du texte

        const uint16_t* image;        ///< Image principale du bouton (format RGB565)
        const uint16_t* image_press;  ///< Image affichée lors de l'appui ou en mode désactivé
        bool button_image_bool;       ///< Indique si le bouton utilise une image

        const uint16_t* actual_image; ///< Image actuellement affichée

        // --- Mode toggle ---
        bool toggle_mode_bool;        ///< Indique si le bouton est en mode toggle
        char *toggle_label;           ///< Texte du bouton en mode toggle
        uint16_t toggle_color;        ///< Couleur de fond en mode toggle
        uint16_t toggle_text_color;   ///< Couleur du texte en mode toggle
        bool toggle_state;            ///< État actuel du toggle

        // --- Couleurs pour état désactivé ---
        uint16_t disable_fill_color;  ///< Couleur de fond en mode désactivé
        uint16_t disable_textColor;   ///< Couleur du texte en mode désactivé
        bool disable_color_on;        ///< Indique si les couleurs désactivées sont utilisées

        Screen* scr;                  ///< Pointeur vers l'écran associé

        static void emptyFunction(Screen*) {} ///< Fonction vide par défaut pour les callbacks
        void (*onClick)(Screen*);             ///< Callback appelé lors de l'appui
        void (*offClick)(Screen*);            ///< Callback appelé lors du relâchement (toggle)

    public:
        /**
         * @brief Constructeur par défaut du bouton.
         */
        Button();

        /**
         * @brief Initialise un bouton texte.
         * @param gfx Pointeur vers l'objet graphique TFT.
         * @param x Position X du centre.
         * @param y Position Y du centre.
         * @param w Largeur.
         * @param h Hauteur.
         * @param outline Couleur du contour.
         * @param fill Couleur de fond.
         * @param textcolor Couleur du texte.
         * @param label Texte à afficher.
         * @param textsize Taille du texte.
         * @param scr Pointeur vers l'écran associé (optionnel).
         * @param onPress Callback à appeler lors de l'appui (optionnel).
         */
        void initButton(TFT_eSPI *gfx, int16_t x, int16_t y, uint16_t w, uint16_t h,
                        uint16_t outline, uint16_t fill, uint16_t textcolor,
                        char *label, uint8_t textsize, Screen* scr = nullptr, void (*onPress)(Screen*) = emptyFunction);

        /**
         * @brief Initialise un bouton image.
         * @param gfx Pointeur vers l'objet graphique TFT.
         * @param x Position X du centre.
         * @param y Position Y du centre.
         * @param w Largeur.
         * @param h Hauteur.
         * @param image Image principale (RGB565).
         * @param imageOff Image affichée lors de l'appui ou en mode désactivé (optionnel).
         * @param scr Pointeur vers l'écran associé (optionnel).
         * @param onPress Callback à appeler lors de l'appui (optionnel).
         */
        void initButton(TFT_eSPI *gfx, int16_t x, int16_t y, uint16_t w, uint16_t h,
                        const uint16_t* image, const uint16_t* imageOff = nullptr, Screen* scr = nullptr, void (*onPress)(Screen*) = emptyFunction);

        /**
         * @brief Active le mode toggle (texte).
         * @param toggle_label Texte en mode toggle.
         * @param toggle_color Couleur de fond en mode toggle.
         * @param toggle_text_color Couleur du texte en mode toggle.
         * @param scr Pointeur vers l'écran associé (optionnel).
         * @param offPress Callback à appeler lors du relâchement (optionnel).
         * @param toggle_button Active/désactive le mode toggle.
         */
        void toggle_mode(char *toggle_label, uint16_t toggle_color, uint16_t toggle_text_color, Screen* scr = nullptr, void (*offPress)(Screen*) = emptyFunction, bool toggle_button = true);

        /**
         * @brief Active le mode toggle (image).
         * @param image_toggle Image à afficher en mode toggle.
         * @param scr Pointeur vers l'écran associé (optionnel).
         * @param offPress Callback à appeler lors du relâchement (optionnel).
         * @param toggle_button Active/désactive le mode toggle.
         */
        void toggle_mode(const uint16_t* image_toggle, Screen* scr = nullptr, void (*offPress)(Screen*) = emptyFunction, bool toggle_button = true);

        /**
         * @brief Initialise les couleurs à utiliser en mode désactivé.
         * @param fillColor Couleur de fond désactivée.
         * @param textColor Couleur du texte désactivé.
         */
        void disable_color_init(uint16_t fillColor, uint16_t textColor);

        /**
         * @brief Dessine le bouton à l'écran.
         * @param invert Si vrai, affiche le bouton en mode inversé (pressé/désactivé).
         */
        void draw(bool invert = false);

        /**
         * @brief Met à jour l'état du bouton en fonction du tactile.
         * @param touch_x Coordonnée X du toucher.
         * @param touch_y Coordonnée Y du toucher.
         * @param pressed État du toucher (pressé ou non).
         */
        void refreshTouch(uint16_t touch_x, uint16_t touch_y, bool pressed);

        bool disable; ///< Indique si le bouton est désactivé

        TFT_eSPI_Button myButton; ///< Objet bouton de la bibliothèque TFT_eSPI
};

#endif