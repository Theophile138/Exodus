#ifndef LibButton_h
#define LibButton_h

#include <TFT_eSPI.h> // Hardware-specific library

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

        uint16_t* image;
        uint16_t* image_press;
        bool button_image_bool;

        uint16_t* actual_image;        

        bool toggle_mode_bool;
        char *toggle_label;
        uint16_t toggle_color;
        uint16_t toggle_text_color;
        bool toggle_state;

        static void emptyFunction(TFT_eSPI*) {} // Fonction vide qui ne fait rien si aucune methode a été donné pour le press button
        void (*onClick)(TFT_eSPI*);
        void (*offClick)(TFT_eSPI*);

    public:
        Button();

        void initButton( TFT_eSPI *gfx, int16_t x, int16_t y, uint16_t w, uint16_t h,
            uint16_t outline, uint16_t fill, uint16_t textcolor,
            char *label, uint8_t textsize , void (*onPress)(TFT_eSPI*) = emptyFunction);
        
        void initButton( TFT_eSPI *gfx, int16_t x, int16_t y, uint16_t w, uint16_t h
            ,uint16_t* image, void (*onPress)(TFT_eSPI*) = emptyFunction);

        void toggle_mode( char *toggle_label, uint16_t toggle_color, uint16_t toggle_text_color, void (*offPress)(TFT_eSPI*) = emptyFunction, bool toggle_button = true);

        void toggle_mode(uint16_t* image_toggle, void (*offPress)(TFT_eSPI*) = emptyFunction, bool toggle_button = true );
        
        void draw(bool invert = false);

        void refreshTouch(uint16_t touch_x, uint16_t touch_y, bool pressed);

        TFT_eSPI_Button myButton;
};



#endif