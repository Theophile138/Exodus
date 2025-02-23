#ifndef LibButton_h
#define LibButton_h

#include <TFT_eSPI.h> // Hardware-specific library
//#include "LibScreen.h"

class Screen;

class Button
{
    private:

        TFT_eSPI *gfx;
        int16_t x;
        int16_t y;
        uint16_t w;
        uint16_t h;
        uint16_t outline;
        uint16_t fill;
        uint16_t textcolor;
        char *label;
        uint8_t textsize;        

        const uint16_t* image;
        const uint16_t* image_press;
        bool button_image_bool;

        const uint16_t* actual_image;        

        bool toggle_mode_bool;
        char *toggle_label;
        uint16_t toggle_color;
        uint16_t toggle_text_color;
        bool toggle_state;

        uint16_t disable_fill_color; 
        uint16_t disable_textColor;
        bool disable_color_on;

        Screen* scr;

        static void emptyFunction(Screen*) {} // Fonction vide qui ne fait rien si aucune methode a été donné pour le press button
        void (*onClick)(Screen*);
        void (*offClick)(Screen*);

    public:
        Button();

        void initButton( TFT_eSPI *gfx, int16_t x, int16_t y, uint16_t w, uint16_t h,
            uint16_t outline, uint16_t fill, uint16_t textcolor,
            char *label, uint8_t textsize ,Screen* scr = nullptr, void (*onPress)(Screen*) = emptyFunction);
        
        void initButton( TFT_eSPI *gfx, int16_t x, int16_t y, uint16_t w, uint16_t h
            ,const uint16_t* image, const uint16_t* imageOff = nullptr,Screen* scr = nullptr, void (*onPress)(Screen*) = emptyFunction);

        void toggle_mode( char *toggle_label, uint16_t toggle_color, uint16_t toggle_text_color,Screen* scr = nullptr ,void (*offPress)(Screen*) = emptyFunction, bool toggle_button = true);

        void toggle_mode(const uint16_t* image_toggle,Screen* scr = nullptr, void (*offPress)(Screen*) = emptyFunction, bool toggle_button = true );
        
        void disable_color_init(uint16_t fillColor, uint16_t textColor);

        void draw(bool invert = false);

        void refreshTouch(uint16_t touch_x, uint16_t touch_y, bool pressed);

        bool disable;

        TFT_eSPI_Button myButton;
};



#endif