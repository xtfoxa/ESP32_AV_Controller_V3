#ifndef DEVICE_H
#define DEVICE_H

#include <Arduino.h>
#include "scene.h"

/*************************************************
 * Device State
 *************************************************/

typedef struct
{
    bool a[8];
    bool b[5];

    bool projectorOn;

    bool amplifierOn;

    uint8_t ampInput;

    bool videoMode;

} DeviceState;


/*************************************************
 * 初始化
 *************************************************/

void Device_Init();

void Device_Task();


/*************************************************
 * Scene接口
 *************************************************/

void Device_ApplyScene(const SceneConfig *scene);

void Device_Shutdown();


/*************************************************
 * Driver封装
 *************************************************/

void Device_SetA(uint8_t port,bool on);

void Device_SetB(uint8_t port,bool on);

void Device_AllOff();

void Device_AmpPower(bool on);

void Device_AmpInput(uint8_t input);

void Device_Projector(bool on);


/*************************************************
 * Diff Engine
 *************************************************/

void Device_BuildTarget(
    const SceneConfig *scene,
    DeviceState &target
);

void Device_GenerateDiff(
    const DeviceState &current,
    const DeviceState &target,
    const SceneConfig *scene
);


/*************************************************
 * Queue
 *************************************************/

typedef enum
{
    DEV_NONE = 0,

    DEV_A_POWER,

    DEV_B_POWER,

    DEV_PROJECTOR,

    DEV_AMP_POWER,

    DEV_AMP_INPUT,

    DEV_DELAY

} DeviceAction;

typedef struct
{
    DeviceAction action;

    uint8_t id;

    bool value;

    uint16_t delayMs;

} DeviceTask;


/*************************************************
 * 全局状态
 *************************************************/

extern DeviceState currentDeviceState;

#endif