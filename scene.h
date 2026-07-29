#ifndef SCENE_H
#define SCENE_H

#include <Arduino.h>

/*************************************************
 * 场景类型
 *************************************************/
enum SceneType
{
    SCENE_NONE = -1,

    SCENE_CABLE = 0,
    SCENE_MEDIA,
    SCENE_DVD,
    SCENE_DIGITAL,
    SCENE_KTV,

    SCENE_COUNT
};

/*************************************************
 * 场景配置
 *************************************************/
typedef struct
{
    SceneType scene;

    // A组输出（A1~A8）
    bool eastA[8];

    // B组输出（B1~B5）
    bool eastB[5];

    // 功放输入
    uint8_t ampInput;

    // 是否开启投影
    bool useProjector;

    // 视频模式
    bool videoMode;

    // 开机顺序（设备编号）
    uint8_t powerSequence[8];

    // 有效数量
    uint8_t powerCount;

} SceneConfig;


/*************************************************
 * 场景配置表
 *************************************************/
extern const SceneConfig SceneTable[SCENE_COUNT];


/*************************************************
 * Scene Manager
 *************************************************/

// 初始化
void Scene_Init(void);

// 获取配置
const SceneConfig* Scene_Get(SceneType scene);

// 切换场景（唯一入口）
void Scene_Change(SceneType scene);

// 关机
void Scene_Shutdown(void);

// 应用配置（内部调用）
void Scene_Apply(const SceneConfig* cfg);

#endif