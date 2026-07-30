#ifndef AVWIFI_H
#define AVWIFI_H

#include <Arduino.h>

/*************************************************
 * WiFi
 *************************************************/

void WiFi_Init();

void WiFi_Task();

/*************************************************
 * Dashboard
 *************************************************/

void Dashboard_Begin();

void Dashboard_SendStatus();

void Dashboard_HandleRequest();

/*************************************************
 * Scene API
 *************************************************/

void Dashboard_SetScene(uint8_t sceneId);

/*************************************************
 * Device API
 *************************************************/

void Dashboard_DeviceControl(
    uint8_t group,
    uint8_t port,
    bool on
);

#endif