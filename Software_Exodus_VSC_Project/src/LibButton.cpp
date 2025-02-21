#include "LibButton.h"

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
}

void Button::initButton( TFT_eSPI *gfx, int16_t x, int16_t y, uint16_t w, uint16_t h,
    uint16_t outline, uint16_t fill, uint16_t textcolor,
    char *label, uint8_t textsize, void (*onPress)(TFT_eSPI*))
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

    Button::myButton.initButton(gfx, x, y, w, h, outline, fill , textcolor,label, textsize);
    onClick = onPress;
}

void Button::initButton( TFT_eSPI *gfx, int16_t x, int16_t y, uint16_t w, uint16_t h
    ,uint16_t* image, void (*onPress)(TFT_eSPI*))
{
    Button::gfx = gfx;
    Button::x = x;
    Button::y = y;
    Button::w = w;
    Button::h = h;
    Button::image = image;
    Button::actual_image = image;

    Button::button_image_bool = true;

    Button::myButton.initButton(gfx, x, y, w, h, outline, fill , textcolor,label, textsize);
    onClick = onPress;
}

void Button::toggle_mode( char *toggle_label, uint16_t toggle_color, uint16_t toggle_text_color,void (*offPress)(TFT_eSPI*), bool toggle_mode)
{

    Button::toggle_mode_bool = toggle_mode;
    Button::toggle_label = toggle_label;
    Button::toggle_color = toggle_color;
    Button::toggle_text_color = toggle_text_color;
    
    toggle_state = false;

    Button::offClick = offPress;
    
}

void Button::toggle_mode(uint16_t* image_toggle, void (*offPress)(TFT_eSPI*), bool toggle_mode)
{

    Button::toggle_mode_bool = toggle_mode;
    Button::toggle_label = toggle_label;
    Button::toggle_color = toggle_color;
    
    toggle_state = false;
    
    Button::offClick = offPress;
}

void Button::draw(bool invert)
{
    if(button_image_bool == true)
    {
        if ((invert == true)&&(image_press != nullptr))
        {
            actual_image = image_press;
        }else{
            actual_image = image;
        }
        gfx->pushImage(x - (w/2) , y - (h/2) , w , h, actual_image);
    }else{
        if (invert == true){
            myButton.drawButton(true);
        }else{
            myButton.drawButton();
        }
    }

}

void Button::refreshTouch(uint16_t touch_x, uint16_t touch_y, bool pressed)
{
    
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
                onClick(gfx);
            }else{
                if (button_image_bool == true){
                    actual_image = image;
                }else{
                    myButton.initButton(gfx,x,y,w,h,outline,fill,textcolor,label,textsize);
                }
                offClick(gfx);
            }
            draw();
        }else{
            draw(true);
            onClick(gfx);
        }
    }

    if ((myButton.justReleased())&&(toggle_mode_bool == false))
    {
        draw();
    }
}

