/*******************************************************************
Fichier "user_setup" pour l'utilisation d'un écran tactile ILI9341
avec un ESP32, avec la bibliothèque TFT_eSPI de Bodmer.
*******************************************************************/

#define ILI9341_DRIVER

#define TFT_CS   5  // Chip select broche D15
#define TFT_DC   2  // Data Command broche D5
#define TFT_RST  4  // Reset broche D4

#define TFT_MOSI 23 // SPI MOSI broche D23
#define TFT_SCLK 18 // SPI SCLK broche D18

#define TOUCH_CS 17     // Touch Screen Chip select pin broche D19

#define TFT_BL   16
#define TFT_BACKLIGHT_ON HIGH 

#define TFT_MISO 19

#define LOAD_GLCD   // Font 1. Original Adafruit 8 pixel font needs ~1820 bytes in FLASH
#define LOAD_FONT2  // Font 2. Small 16 pixel high font, needs ~3534 bytes in FLASH, 96 characters
#define LOAD_FONT4  // Font 4. Medium 26 pixel high font, needs ~5848 bytes in FLASH, 96 characters
#define LOAD_FONT6  // Font 6. Large 48 pixel font, needs ~2666 bytes in FLASH, only characters 1234567890:-.apm
#define LOAD_FONT7  // Font 7. 7 segment 48 pixel font, needs ~2438 bytes in FLASH, only characters 1234567890:.
#define LOAD_FONT8  // Font 8. Large 75 pixel font needs ~3256 bytes in FLASH, only characters 1234567890:-.
#define LOAD_GFXFF  // FreeFonts. Include access to the 48 Adafruit_GFX free fonts FF1 to FF48 and custom fonts

#define SMOOTH_FONT

#define SPI_FREQUENCY  40000000

#define SPI_READ_FREQUENCY  20000000

#define SPI_TOUCH_FREQUENCY  2500000
