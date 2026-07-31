#include "avdisplay.h"
#include "config.h"

Arduino_GFX *gfx = nullptr;

Arduino_DataBus *bus = nullptr;


void Display_Init()
{

    bus = new Arduino_HWSPI(
        TFT_DC,
        TFT_CS,
        TFT_SCLK,
        TFT_MOSI,
        -1
    );


    gfx = new Arduino_ST7789(
        bus,
        TFT_RST,
        1,
        true,
        LCD_WIDTH,
        LCD_HEIGHT,
        LCD_OFFSET_X,
        0,
        LCD_OFFSET_X,
        0
    );


    gfx->begin();

    gfx->fillScreen(COLOR_BLACK);

}