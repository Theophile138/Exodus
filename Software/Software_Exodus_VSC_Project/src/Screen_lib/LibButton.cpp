#include "LibButton.h"
#include "LibScreen.h"

Button::Button(){

    Button::gfx = nullptr;
    Button::x = 0;
    Button::y = 0;
    Button::w = 0;
    Button::h = 0;
    Button::outline = 0;
    Button::fill = 0;
    Button::textcolor = 0;
    Button::label = nullptr;
    Button::textsize = 0;

    Button::image = nullptr;
    Button::image_press = nullptr;
    Button::button_image_bool = false;

    Button::toggle_mode_bool = false;
    Button::toggle_label = nullptr;
    Button::toggle_color = 0;

    disable = false;
    disable_color_on = false;
}

void Button::initButton( TFT_eSPI *gfx, int16_t x, int16_t y, uint16_t w, uint16_t h,
    uint16_t outline, uint16_t fill, uint16_t textcolor,
    char *label, uint8_t textsize,Screen* scr , void (*onPress)(Screen*))
{
    Button::gfx = gfx;
    Button::x = x;
    Button::y = y;
    Button::w = w;
    Button::h = h;
    Button::outline = outline;
    Button::fill = fill;
    Button::textcolor = textcolor;
    Button::label = label;
    Button::textsize = textsize;

    Button::button_image_bool = false;

    Button::scr = scr;

    Button::myButton.initButton(gfx, x, y, w, h, outline, fill , textcolor,label, textsize);
    onClick = onPress;

    Button::disable = false;
}

void Button::initButton( TFT_eSPI *gfx, int16_t x, int16_t y, uint16_t w, uint16_t h
    ,const uint16_t* image, const uint16_t* imageOff,Screen* scr , void (*onPress)(Screen*))
{
    Button::gfx = gfx;
    Button::x = x;
    Button::y = y;
    Button::w = w;
    Button::h = h;
    Button::image = image;
    Button::actual_image = image;
    Button::image_press = imageOff;

    Button::button_image_bool = true;

    Button::scr = scr;

    Button::myButton.initButton(gfx, x, y, w, h, 0, 0 , 0,"", 1);
    onClick = onPress;

    Button::disable = false;
}

void Button::toggle_mode( char *toggle_label, uint16_t toggle_color, uint16_t toggle_text_color,Screen* scr ,void (*offPress)(Screen*), bool toggle_mode)
{

    Button::toggle_mode_bool = toggle_mode;
    Button::toggle_label = toggle_label;
    Button::toggle_color = toggle_color;
    Button::toggle_text_color = toggle_text_color;
    
    if (!(Button::scr)){
        Button::scr = scr;
    }

    toggle_state = false;

    Button::offClick = offPress;
    
}

void Button::toggle_mode(const uint16_t* image_toggle,Screen* scr , void (*offPress)(Screen*), bool toggle_mode)
{

    Button::toggle_mode_bool = toggle_mode;
    Button::toggle_label = toggle_label;
    Button::toggle_color = toggle_color;
    
    if (!(Button::scr)){
        Button::scr = scr;
    }

    toggle_state = false;
    
    Button::offClick = offPress;
}

void Button::draw(bool invert)
{
    if(button_image_bool == true)
    {
        if (((invert == true)||(disable == true))&&(image_press != nullptr))
        {
            actual_image = image_press;
        }else{
            actual_image = image;
        }
        gfx->pushImage(x - (w/2) , y - (h/2) , w , h, actual_image);
    }else{
        if ((invert == true)||(disable == true)){
            
            if ((disable_color_on == true)&&(disable == true)){
                myButton.initButton(gfx, x, y, w, h, outline, disable_fill_color , disable_textColor,label, textsize);
                myButton.drawButton();
            }else{         
                myButton.drawButton(true);
            }
        }else{        
            if (disable_color_on == true){
                myButton.initButton(gfx, x, y, w, h, outline, fill , textcolor,label, textsize);
            }
            myButton.drawButton();
        }
    }

}

void Button::refreshTouch(uint16_t touch_x, uint16_t touch_y, bool pressed)
{
    
    if (disable == false){

        if (pressed && myButton.contains(touch_x, touch_y)) {
            myButton.press(true);  // tell the button it is pressed
        } else {
            myButton.press(false);  // tell the button it is NOT pressed
        }


        if(myButton.justPressed())
        {
            if(toggle_mode_bool == true)
            {
                toggle_state = !toggle_state;
                if (toggle_state == true)
                {
                    if (button_image_bool == true){
                        if (image_press != nullptr){
                            actual_image = image_press;
                        }
                    }else{
                        myButton.initButton(gfx, x, y, w, h, outline,toggle_color ,toggle_text_color, toggle_label, textsize);
                    }
                    onClick(scr);
                }else{
                    if (button_image_bool == true){
                        actual_image = image;
                    }else{
                        myButton.initButton(gfx,x,y,w,h,outline,fill,textcolor,label,textsize);
                    }
                    offClick(scr);
                }
                draw();
            }else{
                draw(true);
                onClick(scr);
            }
        }

        if ((myButton.justReleased())&&(toggle_mode_bool == false))
        {
            draw();
    }
    }
}

void Button::disable_color_init(uint16_t fillColor, uint16_t textColor){
    Button::disable_fill_color = fillColor; 
    Button::disable_textColor = textColor;
    Button::disable_color_on = true;
}