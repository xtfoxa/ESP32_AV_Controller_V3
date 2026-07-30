/*************************************************
 *
 * ESP32 AV Controller V3.3 Final
 *
 *************************************************/

#include <Arduino.h>

#include "config.h"

#include "system.h"

#include "device.h"

#include "scene.h"

#include "ui.h"

#include "touch.h"

#include "eastcato.h"

#include "amplifier.h"

#include "projector.h"

#include "avwifi.h"

#include <Arduino_GFX_Library.h>


/*************************************************
 *
 * Setup
 *
 *************************************************/

void setup()
{

    Serial.begin(115200);

    delay(500);

    Serial.println();

    Serial.println("==================================");

    Serial.println("ESP32 AV Controller V3.3");

    Serial.println("==================================");


    //--------------------------------
    // LCD
    //--------------------------------

    UI_Init();

    //--------------------------------
    // Touch
    //--------------------------------

    Touch_Init();

    //--------------------------------
    // Device
    //--------------------------------

    Device_Init();

    //--------------------------------
    // Scene
    //--------------------------------

    Scene_Init();

    //--------------------------------
    // UI
    //--------------------------------

    UI_Init();

    //--------------------------------
    // Dashboard
    //--------------------------------

    WiFi_Init();

}


/*************************************************
 *
 * Main Loop
 *
 *************************************************/

void loop()
{


    /*************************************************
     * Device Queue
     *************************************************/

    Device_Task();


    /*************************************************
     * LCD
     *************************************************/

    UI_Task();


    /*************************************************
     * Dashboard
     *************************************************/

    WiFi_Task();

}


Arduino_DataBus *bus = new Arduino_HWSPI(
    TFT_DC,
    TFT_CS,
    TFT_SCLK,
    TFT_MOSI,
    GFX_NOT_DEFINED
);


Arduino_GFX *gfx = new Arduino_ST7789(
    bus,
    TFT_RST,
    1,
    true,
    LCD_WIDTH,
    LCD_HEIGHT,
    LCD_OFFSET_X,
    LCD_OFFSET_Y
);