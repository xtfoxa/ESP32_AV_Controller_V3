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

#include "avdisplay.h"


/*************************************************
 *
 * Setup
 *
 *************************************************/

void setup()
{

    Serial.begin(115200);

    delay(500);


    Serial.println("START");

    Display_Init();
    Serial.println("display");

    Touch_Init();

    Device_Init();

    Scene_Init();

    UI_Init();

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

