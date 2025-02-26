#include "LibScreen.h"

#include "LibJauge.h"

#include <TFT_eSPI.h> // Hardware-specific library
#include <SPI.h>

#include "image_data.h"

#include "FS.h"
#include "configTest1.h"

Screen::Screen(){
    //tft = new Adafruit_ILI9341(TFT_CS, TFT_DC,TFT_RST);
    tft =new TFT_eSPI(); 
    tft->init();
    tft->setRotation(2);

    linearMeters = new linearMeter[6];  // Allocation dynamique
    myGauge = new analogMeters();

    run = emptyFunction;

    activeControle = false;

    config_selectionne = 0;
}

void Screen::clearScreen()
{
    tft->fillScreen(ILI9341_BLACK);
}

void Screen::imageStart(String firmwareVersion){
  
  tft->fillScreen(ILI9341_BLACK);
  tft->setSwapBytes(true);

  tft->pushImage(0, 0, image_StartImg_width, image_StartImg_height, image_StartImg);

  tft->setTextColor(TFT_WHITE);  // Text colour

  tft->drawCentreString("Exodus Firmware V"+firmwareVersion, SCREEN_WIDTH/2, 270, 2); // Comment out to avoid font 4
}

void Screen::Select_Menu_init()
{
  tft->fillScreen(TFT_BLACK);

  tft->pushImage((SCREEN_WIDTH-160)/2, 0, image_mode1_width, image_mode1_height, image_mode1);

  tft->setTextFont(1); // Use GLCD font

  startButton.initButton(tft, SCREEN_WIDTH/2, 170, 200, 35, TFT_WHITE, TFT_GREEN, TFT_WHITE,"START", 2 , this, startOnclick);
  startButton.toggle_mode("STOP",TFT_RED,TFT_WHITE,this,startOffclick);
  startButton.draw();

  
  leftButton.initButton(tft, 20, 60, 30, 60, TFT_WHITE, TFT_BLUE, TFT_WHITE,"<", 2,this, leftOnclick);
  leftButton.disable_color_init(TFT_DARKGREY,TFT_WHITE);
  leftButton.draw();

  rightButton.initButton(tft, SCREEN_WIDTH - 20, 60, 30, 60, TFT_WHITE, TFT_BLUE, TFT_WHITE,">", 2,this,rightOnclick);
  rightButton.disable_color_init(TFT_DARKGREY,TFT_WHITE);
  rightButton.draw();

  gaugeButton.initButton(tft,SCREEN_WIDTH-(image_gaugeButton_on_width/2),SCREEN_HEIGHT - (image_gaugeButton_on_height/2),
    image_gaugeButton_on_width, image_gaugeButton_on_height, image_gaugeButton_on, image_gaugeButton_off,this,gaugeOnClick);
  gaugeButton.disable = true;
  gaugeButton.draw();
  
  run = Select_Menu_run;

}

void Screen::Select_Menu_run(Screen* scr)
{
  uint16_t t_x = 0, t_y = 0; // To store the touch coordinates

  // Pressed will be set true is there is a valid touch on the screen
  bool pressed = false;

  if (scr->tft->getTouchRawZ()>200){
    pressed = scr->tft->getTouch(&t_x, &t_y);
  }

  scr->leftButton.refreshTouch(t_x,t_y,pressed);
  scr->rightButton.refreshTouch(t_x,t_y,pressed);
  scr->startButton.refreshTouch(t_x,t_y,pressed);
  scr->gaugeButton.refreshTouch(t_x,t_y,pressed);
}

void Screen::leftOnclick(Screen* scr){
  scr->tft->pushImage((SCREEN_WIDTH-160)/2, 0, image_mode1_width, image_mode1_height, image_mode1);
  scr->config_selectionne = 0;
}

void Screen::rightOnclick(Screen* scr){
  scr->tft->pushImage((SCREEN_WIDTH-160)/2, 0, image_mode2_width, image_mode2_height, image_mode2);
  scr->config_selectionne = 1;
}

void Screen::startOnclick(Screen* scr){

  scr->leftButton.disable = true;
  scr->rightButton.disable = true;
  scr->gaugeButton.disable = false;

  scr->leftButton.draw();
  scr->rightButton.draw();
  scr->gaugeButton.draw();

  scr->activeControle = true;

    // Le mieux serai d'appeler le init de la config qui serait donné par une instance dans la class screen
    if (scr->config_selectionne == 0){
      configTest1::init(scr);
    }else{
      scr->linearMeters[0].disable = false;
      scr->linearMeters[1].disable = false;
      scr->linearMeters[2].disable = false;
      scr->linearMeters[3].disable = false;
      scr->linearMeters[4].disable = false;
      scr->linearMeters[5].disable = false;
    }

}

void Screen::startOffclick(Screen* scr){
  scr->leftButton.disable = false;
  scr->rightButton.disable = false;
  scr->gaugeButton.disable = true;

  scr->leftButton.draw();
  scr->rightButton.draw();
  scr->gaugeButton.draw();

  scr->activeControle = false;
}

void Screen::gaugeOnClick(Screen* scr){

  scr->leftButton.disable = true;
  scr->rightButton.disable = true;
  scr->startButton.disable = true;
  scr->gaugeButton.disable = true;


  scr->Gauge_Menu_init();
  
  scr->run = scr->Gauge_Menu_run;


}

void Screen::backOnClick(Screen* scr){
  
  scr->backButton.disable = true; 
  scr->Select_Menu_init();

  scr->run = scr->Select_Menu_run;
}

void Screen::Gauge_Menu_init(){

  tft->fillScreen(TFT_BLACK);
  
  myGauge->drawAnalogMeters(tft,0,0,0,0,25,50,75,"% Force");

  int distance = 40;
  char* labels[] = {"A0", "A1", "A2", "A3", "A4", "A5"};

  for(int i = 0 ; i < 6 ; i++){
    linearMeters[i].plotLinear(tft,labels[i],distance*i,165);
  }

  backButton.initButton(tft, SCREEN_WIDTH/2, myGauge->height + 20, 100, 24, TFT_WHITE, TFT_RED, TFT_WHITE,"BACK", 2,this, backOnClick);
  backButton.draw();

  number = 0;
  index = 0;

}

void Screen::Gauge_Menu_run(Screen* scr){

  /*
  scr->linearMeters[scr->index].plotPointer(scr->number);
  scr->number ++;
  if (scr->number > 100){
    scr->number = 0;
    scr->index++;
    if (scr->index > 5){
      scr->index = 0;
    }
  }
  */



  if (scr->config_selectionne == 0){
    
    scr->linearMeters[0].refresh();
    scr->linearMeters[1].refresh();
    scr->linearMeters[2].refresh();
    scr->linearMeters[3].refresh();
    scr->linearMeters[4].refresh();
    scr->linearMeters[5].refresh();
    
    scr->myGauge->refresh();
  }else{
    scr->number += 4; if (scr->number >= 360) scr->number = 0;
    scr->linearMeters[0].plotPointer(50 + 50 * sin((scr->number + 0) * 0.0174532925));
    scr->linearMeters[1].plotPointer(50 + 50 * sin((scr->number + 60) * 0.0174532925));
    scr->linearMeters[2].plotPointer(50 + 50 * sin((scr->number + 120) * 0.0174532925));
    scr->linearMeters[3].plotPointer(50 + 50 * sin((scr->number + 180) * 0.0174532925));
    scr->linearMeters[4].plotPointer(50 + 50 * sin((scr->number + 240) * 0.0174532925));
    scr->linearMeters[5].plotPointer(50 + 50 * sin((scr->number+ 300) * 0.0174532925));

    scr->myGauge->plotNeedle(50 + 50 * sin((scr->number + 0) * 0.0174532925),0);
  }



  /*
  scr->linearMeters[0].refresh();
  scr->linearMeters[1].refresh();
  scr->linearMeters[2].refresh();
  scr->linearMeters[3].refresh();
  scr->linearMeters[4].refresh();
  scr->linearMeters[5].refresh();
  */

  uint16_t t_x = 0, t_y = 0; // To store the touch coordinates

  bool pressed = false;

  if (scr->tft->getTouchRawZ()>200){
    pressed = scr->tft->getTouch(&t_x, &t_y);
  }
  scr->backButton.refreshTouch(t_x, t_y ,pressed);
}

void Screen::touch_calibrate()
{
  uint16_t calData[5];
  uint8_t calDataOK = 0;

  // check file system exists
  if (!SPIFFS.begin()) {
    Serial.println("Formating file system");
    SPIFFS.format();
    SPIFFS.begin();
  }

  // check if calibration file exists and size is correct
  if (SPIFFS.exists(CALIBRATION_FILE)) {
    if (REPEAT_CAL)
    {
      // Delete if we want to re-calibrate
      SPIFFS.remove(CALIBRATION_FILE);
    }
    else
    {
      fs::File f = SPIFFS.open(CALIBRATION_FILE, "r");
      if (f) {
        if (f.readBytes((char *)calData, 14) == 14)
          calDataOK = 1;
        f.close();
      }
    }
  }

  if (calDataOK && !REPEAT_CAL) {
    // calibration data valid
    tft->setTouch(calData);
  } else {
    // data not valid so recalibrate
    tft->fillScreen(TFT_BLACK);
    tft->setCursor(20, 0);
    tft->setTextFont(2);
    tft->setTextSize(1);
    tft->setTextColor(TFT_WHITE, TFT_BLACK);

    tft->println("Touch corners as indicated");

    tft->setTextFont(1);
    tft->println();

    if (REPEAT_CAL) {
      tft->setTextColor(TFT_RED, TFT_BLACK);
      tft->println("Set REPEAT_CAL to false to stop this running again!");
    }

    tft->calibrateTouch(calData, TFT_MAGENTA, TFT_BLACK, 15);

    tft->setTextColor(TFT_GREEN, TFT_BLACK);
    tft->println("Calibration complete!");

    // store data
    fs::File f = SPIFFS.open(CALIBRATION_FILE, "w");
    if (f) {
      f.write((const unsigned char *)calData, 14);
      f.close();
    }
  }
}