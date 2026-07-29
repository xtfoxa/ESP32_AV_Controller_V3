#ifndef SYSTEM_H
#define SYSTEM_H

#include <Arduino.h>

/*************************************************
 * 场景
 *************************************************/
typedef enum
{
    SCENE_NONE = -1,

    SCENE_CABLE = 0,
    SCENE_MEDIA,
    SCENE_DVD,
    SCENE_DIGITAL,
    SCENE_KTV,

    SCENE_COUNT

} SceneType;

/*************************************************
 * 系统状态
 *************************************************/
typedef struct
{
    SceneType scene;

    bool projectorOn;

    bool amplifierOn;

    bool videoMode;

} SystemState;

/*************************************************
 * 全局变量
 *************************************************/
extern SystemState systemState;

#endif