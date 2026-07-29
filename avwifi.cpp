#include "avwifi.h"

#include "wifi_page.h"

#include "scene.h"

#include "system.h"

#include <WiFi.h>

#include <WebServer.h>


/*************************************************
 * WiFi配置
 *************************************************/

static const char *AP_NAME = "ESP32_AV_Controller";

static const char *AP_PASS = "12345678";


/*************************************************
 * WebServer
 *************************************************/

WebServer server(80);


/*************************************************
 * Root
 *************************************************/

void HandleRoot()
{
    server.send_P(
        200,
        "text/html",
        MAIN_PAGE
    );
}
/*************************************************
 * Cable
 *************************************************/

void HandleCable()
{
    Serial.println("WEB : Cable");

    Scene_Change(SCENE_CABLE);

    server.sendHeader("Location","/");

    server.send(303);
}


/*************************************************
 * Media
 *************************************************/

void HandleMedia()
{
    Serial.println("WEB : Media");

    Scene_Change(SCENE_MEDIA);

    server.sendHeader("Location","/");

    server.send(303);
}


/*************************************************
 * DVD
 *************************************************/

void HandleDVD()
{
    Serial.println("WEB : DVD");

    Scene_Change(SCENE_DVD);

    server.sendHeader("Location","/");

    server.send(303);
}


/*************************************************
 * Digital
 *************************************************/

void HandleDigital()
{
    Serial.println("WEB : Digital");

    Scene_Change(SCENE_DIGITAL);

    server.sendHeader("Location","/");

    server.send(303);
}


/*************************************************
 * KTV
 *************************************************/

void HandleKTV()
{
    Serial.println("WEB : KTV");

    Scene_Change(SCENE_KTV);

    server.sendHeader("Location","/");

    server.send(303);
}


/*************************************************
 * Shutdown
 *************************************************/

void HandleShutdown()
{
    Serial.println("WEB : Shutdown");

    Scene_Shutdown();

    server.sendHeader("Location","/");

    server.send(303);
}

/*************************************************
 * Status(JSON)
 *************************************************/

void HandleStatus()
{

    String json = "{";

    /*************************************************
     * Scene
     *************************************************/

    json += "\"scene\":";
    json += String((int)systemState.scene);

    json += ",";

    /*************************************************
     * Amp Input
     *************************************************/

    json += "\"amp\":";
    json += String(systemState.ampInput);

    json += ",";

    /*************************************************
     * Projector
     *************************************************/

    json += "\"projector\":";
    json += (systemState.projectorOn ? "true" : "false");

    json += ",";

    /*************************************************
     * Amplifier
     *************************************************/

    json += "\"amplifier\":";
    json += (systemState.amplifierOn ? "true" : "false");

    json += ",";

    /*************************************************
     * Video Mode
     *************************************************/

    json += "\"video\":";
    json += (systemState.videoMode ? "true" : "false");

    json += "}";

    server.send(
        200,
        "application/json",
        json
    );

}

/*************************************************
 * WiFi初始化
 *************************************************/

void WiFi_Init()
{

    WiFi.mode(WIFI_AP);

    WiFi.softAP(

        AP_NAME,

        AP_PASS

    );

    Serial.println();

    Serial.println("--------------------------------");

    Serial.println("ESP32 AV Controller");

    Serial.print("IP : ");

    Serial.println(

        WiFi.softAPIP()

    );

    Serial.println("--------------------------------");



    /*************************************************
     * Web Routes
     *************************************************/

    server.on(

        "/",

        HandleRoot

    );

    server.on(

        "/cable",

        HandleCable

    );

    server.on(

        "/media",

        HandleMedia

    );

    server.on(

        "/dvd",

        HandleDVD

    );

    server.on(

        "/digital",

        HandleDigital

    );

    server.on(

        "/ktv",

        HandleKTV

    );

    server.on(

        "/shutdown",

        HandleShutdown

    );

    /*************************************************
     * Dashboard状态接口
     *************************************************/

    server.on(

        "/status",

        HandleStatus

    );


    /*************************************************
     * 启动HTTP
     *************************************************/

    server.begin();

    Serial.println("HTTP Server Started");

}


/*************************************************
 * WiFi任务
 *************************************************/

void WiFi_Task()
{

    server.handleClient();

}
