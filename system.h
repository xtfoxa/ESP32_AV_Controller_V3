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
    SceneType scene;          // 当前场景

    bool projectorOn;         // 投影状态

    bool amplifierOn;         // 功放状态

    bool videoMode;           // 是否视频模式

    uint8_t ampInput;         // 当前功放输入(AMP_HDMI1...AMP_AN2)

} SystemState;

/*************************************************
 * 全局变量
 *************************************************/
extern SystemState systemState;

#endif