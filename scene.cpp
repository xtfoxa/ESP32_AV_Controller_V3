//第一部分
#include "scene.h"
#include "system.h"
#include "config.h"

#include "eastcato.h"
#include "amplifier.h"
#include "projector.h"

#include "storage.h"
#include "ui.h"


//第二部分
const SceneConfig SceneTable[SCENE_COUNT] =
{

    // SCENE_CABLE
    {

        SCENE_CABLE,

        {true,false,false,false,false,ftrue,false,true},

        {false,false,false,false,false},

        AMP_HDMI1,

        true,

        true,

        {0},

        0

    },

    // SCENE_MEDIA
    {

        SCENE_MEDIA,

        {false,true,false,false,true,true,false,true},

        {false,false,false,false,false},

        AMP_HDMI2,

        true,

        true,

        {0},

        0

    },

    // SCENE_DVD
    {

        SCENE_DVD,

        {false,false,true,false,false,true,false,true},

        {false,false,false,false,false},

        AMP_HDMI3,

        true,

        true,

        {0},

        0

    },

    // SCENE_DIGITAL
    {

        SCENE_DIGITAL,

        {false,false,false,true,true,false,false,true},

        {false,false,false,false,false},

        AMP_AN1,

        true,

        true,

        {0},

        0

    },

    // SCENE_KTV
    {

        SCENE_KTV,

        {false,false,false,false,true,true,false,true},

        {true,true,true,true,true},

        AMP_AN2,

        true,

        true,

        {0},

        0

    }

};

//第三部分

const SceneConfig* Scene_Get(SceneType scene)
{

    if(scene < 0)
        return nullptr;

    if(scene >= SCENE_COUNT)
        return nullptr;

    return &SceneTable[scene];

}

//第四部分
void Scene_Init(void)
{

    systemState.scene = SCENE_NONE;

}


void Scene_Apply(const SceneConfig* cfg)
{

    if(cfg == nullptr)
        return;

    /*************************************************
     * Eastcato A组
     *************************************************/

    for(int i=0;i<8;i++)
    {
        Eastcato_SetA(i + 1, cfg->eastA[i]);
    }

    /*************************************************
     * Eastcato B组
     *************************************************/

    for(int i=0;i<5;i++)
    {
        Eastcato_SetB(i + 1, cfg->eastB[i]);
    }

    /*************************************************
     * 功放
     *************************************************/

    Amplifier_SetInput(cfg->ampInput);

    /*************************************************
     * 投影
     *************************************************/

    if(cfg->useProjector)
        Projector_On();
    else
        Projector_Off();

}

void Scene_Change(SceneType scene)
{

    const SceneConfig* cfg =
        Scene_Get(scene);

    if(cfg == nullptr)
        return;



   /*************************************************
    * 更新系统状态
    *************************************************/

    systemState.scene = scene->scene;

    systemState.projectorOn = scene->useProjector;

    systemState.videoMode = scene->videoMode;

    systemState.amplifierOn = true;

    systemState.ampInput = scene->ampInput;

    /*************************************************
     * 应用设备
     *************************************************/

    Scene_Apply(cfg);

    /*************************************************
     * 保存
     *************************************************/

    Save_SystemState();

    /*************************************************
     * 刷新UI
     *************************************************/

    UI_Refresh();

    //增加同步
    Save_SystemState();

    UI_Refresh();

}

//关机
void Scene_Shutdown(void)
{

    Projector_Off();

    Amplifier_Power(false);

    Eastcato_AllOff();

    systemState.scene = SCENE_NONE;

    Save_SystemState();

    UI_Refresh();

    /*************************************************
    * 更新系统状态
    *************************************************/

    systemState.scene = SCENE_NONE;

    systemState.projectorOn = false;

    systemState.amplifierOn = false;

    systemState.videoMode = false;

    systemState.ampInput = 0;

}