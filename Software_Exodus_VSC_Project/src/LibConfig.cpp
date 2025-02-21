#include "LibConfig.h"

Configuration::Configuration(String name,const uint16_t* icone, int iconeWidth, int iconeHeight, String presentation)
{

    Configuration::name = name;
    Configuration::icone = icone;
    Configuration::iconeWidth = iconeWidth;
    Configuration::iconeHeight = iconeHeight;
    Configuration::presentation = presentation;



}