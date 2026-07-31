//第一部分
#include "scene.h"
#include "system.h"
#include "eastcato.h"
#include "amplifier.h"
#include "projector.h"
#include "ui.h"
#include "device.h"


//第二部分
const SceneConfig SceneTable[SCENE_COUNT] =
{

    // SCENE_CABLE
    {

        SCENE_CABLE,

        {true,false,false,false,false,true,false,true},

        {false,false,false,false,false},

        AMP_HDMI1,

        true,

        true,

       //开机顺序
        {1,6,8},

        3

    },

    // SCENE_MEDIA
    {

        SCENE_MEDIA,

        {false,true,false,false,true,true,false,true},

        {false,false,false,false,false},

        AMP_HDMI2,

        true,

        true,

        {2,5,6,8},

        4

    },

    // SCENE_DVD
    {

        SCENE_DVD,

        {false,false,true,false,false,true,false,true},

        {false,false,false,false,false},

        AMP_HDMI3,

        true,

        true,

        {3,6,8},

        3

    },

    // SCENE_DIGITAL
    {

        SCENE_DIGITAL,

        {false,false,false,true,true,false,false,true},

        {false,false,false,false,false},

        AMP_AN1,

        false,

        false,

        {4,5,8},

        3

    },

    // SCENE_KTV
    {

        SCENE_KTV,

        {false,false,false,false,true,true,false,true},

        {true,true,true,true,true},

        AMP_AN2,

        true,

        true,

        {9,10,11,12,13,5,6,8},

        8

    },

    //  SCENE_POWER_OFF
    {
         SCENE_POWER_OFF,
        {false,false,false,false,false,false,false,false},

        {false,false,false,false,false},

        AMP_OFF,

        false,

        false,

        {0},

        0
    

    }

};

//第三部分

const SceneConfig* Scene_Get(SceneType scene)
{

    if(scene < 0 || scene >= SCENE_COUNT)
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
     * 关机特殊场景
     *************************************************/

    if(cfg->scene == SCENE_POWER_OFF)
    {

        Device_Projector(false);


        Device_AmpPower(false);


        for(int i=0;i<8;i++)
        {
            Device_SetA(i+1,false);
        }


        for(int i=0;i<5;i++)
        {
            Device_SetB(i+1,false);
        }


        return;
    }



    /*************************************************
     * 正常影音场景
     *************************************************/


    for(int i=0;i<8;i++)
    {
        Device_SetA(
            i+1,
            cfg->eastA[i]
        );
    }


    for(int i=0;i<5;i++)
    {
        Device_SetB(
            i+1,
            cfg->eastB[i]
        );
    }



    Device_AmpInput(
        cfg->ampInput
    );


    Device_Projector(
        cfg->useProjector
    );








    /*************************************************
     * Eastcato A组
     *************************************************/

    for(int i=0;i<8;i++)
    {
        Device_SetA(i + 1, cfg->eastA[i]);
    }

    /*************************************************
     * Eastcato B组
     *************************************************/

    for(int i=0;i<5;i++)
    {
        Device_SetB(i + 1, cfg->eastB[i]);
    }

    /*************************************************
     * 功放
     *************************************************/

    Device_AmpInput(cfg->ampInput);

    /*************************************************
     * 投影
     *************************************************/

    Device_Projector(cfg->useProjector);

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

    systemState.scene = cfg->scene;

    systemState.projectorOn = cfg->useProjector;

    systemState.videoMode = cfg->videoMode;

    systemState.amplifierOn = true;

    systemState.ampInput = cfg->ampInput;

    /*************************************************
     * 应用设备
     *************************************************/

    Scene_Apply(cfg);


    /*************************************************
     * 刷新UI
     *************************************************/


    //UI_RequestRefresh();

}

//关机
   void Scene_Shutdown(void)
{
    Device_Projector(false);

    Device_AmpPower(false);

    Device_AllOff();

    systemState.scene = SCENE_NONE;
    systemState.projectorOn = false;
    systemState.amplifierOn = false;
    systemState.videoMode = false;
    systemState.ampInput = 0;
}

