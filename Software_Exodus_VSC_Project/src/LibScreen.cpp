#include "LibScreen.h"

#include "LibGauge.h"

#include <TFT_eSPI.h> // Hardware-specific library
#include <SPI.h>

#include "image_data.h"

#include "FS.h"

#include "LibConfig.h"

Screen::Screen(){
    //tft = new Adafruit_ILI9341(TFT_CS, TFT_DC,TFT_RST);
    tft =new TFT_eSPI(); 
    tft->init();
    tft->setRotation(2);
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
  tft->fillScreen(ILI9341_BLACK);

  tft->pushImage((SCREEN_WIDTH-160)/2, 0, image_mode1_width, image_mode1_height, image_mode1);

  //myGauge = new analogMeters(tft,0,SCREEN_HEIGHT - 126,25,-20,-15,25,50,"% Force");
  
  //tft->setFreeFont(LABEL2_FONT);
  tft->setTextFont(1); // Use GLCD font

  startButton.initButton(tft, SCREEN_WIDTH/2, 170, 200, 35, TFT_WHITE, TFT_GREEN, TFT_WHITE,"START", 2);
  startButton.toggle_mode("STOP",TFT_RED,TFT_WHITE);
  startButton.draw();

  
  leftButton.initButton(tft, 20, 60, 30, 60, TFT_WHITE, TFT_BLUE, TFT_WHITE,"<", 2, Screen::leftOnclick);
  leftButton.draw();

  rightButton.initButton(tft, SCREEN_WIDTH - 20, 60, 30, 60, TFT_WHITE, TFT_BLUE, TFT_WHITE,">", 2,Screen::rightOnclick);
  rightButton.draw();
  
}

void Screen::Select_Menu_run()
{
  uint16_t t_x = 0, t_y = 0; // To store the touch coordinates

  // Pressed will be set true is there is a valid touch on the screen
  bool pressed = tft->getTouch(&t_x, &t_y);
  
  leftButton.refreshTouch(t_x,t_y,pressed);
  rightButton.refreshTouch(t_x,t_y,pressed);
  startButton.refreshTouch(t_x,t_y,pressed);
}

void Screen::leftOnclick(TFT_eSPI* tft){
  tft->pushImage((SCREEN_WIDTH-160)/2, 0, image_mode1_width, image_mode1_height, image_mode1);
}

void Screen::rightOnclick(TFT_eSPI* tft){
  tft->pushImage((SCREEN_WIDTH-160)/2, 0, image_mode2_width, image_mode2_height, image_mode2);
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