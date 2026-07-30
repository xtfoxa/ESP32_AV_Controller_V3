#include "ui.h"
#include "config.h"
#include "system.h"
#include "scene.h"
#include "touch.h"
#include <Arduino_GFX_Library.h>
#include <Wire.h>

extern Arduino_GFX *gfx;

/*************************************************
 * UI状态
 *************************************************/

static bool uiNeedRefresh = true;

/*************************************************
 * 按钮定义
 *************************************************/

typedef struct
{
    int16_t x;
    int16_t y;
    int16_t w;
    int16_t h;

    const char *title;

} UIButton;


/*************************************************
 * 场景按钮
 *************************************************/

static const UIButton buttons[] =
{
    {  8,  38,154,38,"Cable"   },
    {  8,  82,154,38,"Media"   },
    {  8, 126,154,38,"DVD"     },
    {  8, 170,154,38,"Digital" },
    {  8, 214,154,38,"KTV"     },
    {  8, 270,154,38,"Power"   }
};

#define BUTTON_COUNT   (sizeof(buttons)/sizeof(buttons[0]))


/*************************************************
 * 按钮 -> 场景
 *************************************************/

static const SceneType buttonSceneMap[] =
{
    SCENE_CABLE,
    SCENE_MEDIA,
    SCENE_DVD,
    SCENE_DIGITAL,
    SCENE_KTV,
    SCENE_NONE          // Power
};


/*************************************************
 * UI初始化
 *************************************************/

void UI_Init(void)
{
    uiNeedRefresh = true;

    Draw_UI();
}


/*************************************************
 * 标题
 *************************************************/

static void Draw_Title(void)
{
    gfx->setTextColor(COLOR_WHITE);

    gfx->setTextSize(2);

    gfx->setCursor(28,18);

    gfx->print("AV Controller");
}

/*************************************************
 * 绘制单个按钮（V3）
 *************************************************/

static void Draw_Button(uint8_t id)
{

    bool active = false;

    switch(systemState.scene)
    {

        case SCENE_CABLE:

            active = (id == 0);

            break;

        case SCENE_MEDIA:

            active = (id == 1);

            break;

        case SCENE_DVD:

            active = (id == 2);

            break;

        case SCENE_DIGITAL:

            active = (id == 3);

            break;

        case SCENE_KTV:

            active = (id == 4);

            break;

        default:

            active = false;

            break;
    }


    const UIButton *btn = &buttons[id];


    /*************************************************
     * 按钮背景
     *************************************************/

    gfx->fillRoundRect(

        btn->x,

        btn->y,

        btn->w,

        btn->h,

        8,

        COLOR_GRAY

    );


    /*************************************************
     * 边框
     *************************************************/

    if(active)
    {

        gfx->drawRoundRect(

            btn->x,

            btn->y,

            btn->w,

            btn->h,

            8,

            COLOR_GREEN

        );

    }
    else
    {

        gfx->drawRoundRect(

            btn->x,

            btn->y,

            btn->w,

            btn->h,

            8,

            COLOR_WHITE

        );

    }


    /*************************************************
     * 文字
     *************************************************/

    gfx->setTextColor(COLOR_WHITE);

    gfx->setTextSize(2);

    int16_t tx = btn->x + 18;

    int16_t ty = btn->y + 24;

    gfx->setCursor(tx,ty);

    gfx->print(btn->title);

}
/*************************************************
 * 绘制整个UI（V3）
 *************************************************/

void Draw_UI(void)
{

    /*************************************************
     * 清屏
     *************************************************/

    gfx->fillScreen(COLOR_BLACK);

    /*************************************************
     * 标题
     *************************************************/

    Draw_Title();

    /*************************************************
     * 六个按钮
     *************************************************/

    for(uint8_t i=0;i<BUTTON_COUNT;i++)
    {
        Draw_Button(i);
    }

}


/*************************************************
 * 请求刷新UI
 *************************************************/

void UI_Refresh(void)
{
    uiNeedRefresh = true;
}


/*************************************************
 * 判断触摸按钮
 *************************************************/

static int Check_Button(int16_t x,int16_t y)
{

    for(uint8_t i=0;i<BUTTON_COUNT;i++)
    {

        const UIButton *btn=&buttons[i];

        if(
            x>=btn->x &&
            x<=(btn->x+btn->w) &&
            y>=btn->y &&
            y<=(btn->y+btn->h)
        )
        {
            return i;
        }

    }

    return -1;

}
/*************************************************
 * UI任务（V3 Final）
 *************************************************/

void UI_Task(void)
{

    /*************************************************
     * UI刷新
     *************************************************/

    if(uiNeedRefresh)
    {
        uiNeedRefresh = false;

        Draw_UI();
    }

    /*************************************************
     * 读取触摸
     *************************************************/

    int16_t x;
    int16_t y;

    if(!Touch_GetPoint(x,y))
        return;

#ifdef DEBUG_TOUCH

    Serial.printf(

        "Touch : %d %d\n",

        x,

        y

    );

#endif

    /*************************************************
     * 判断按钮
     *************************************************/

    int id = Check_Button(x,y);

    if(id < 0)
        return;

    /*************************************************
     * Power按钮
     *************************************************/

    if(buttonSceneMap[id] == SCENE_NONE)
    {
        Scene_Shutdown();

        return;
    }

    /*************************************************
     * 场景切换
     *************************************************/

    Scene_Change(buttonSceneMap[id]);

    delay(180);

}

/*************************************************
 * 调试接口
 *************************************************/

#ifdef DEBUG_UI

void UI_DumpState(void)
{

    Serial.println();

    Serial.println("========== UI ==========");

    Serial.print("Scene : ");

    Serial.println((int)systemState.scene);

    Serial.print("NeedRefresh : ");

    Serial.println(uiNeedRefresh);

    Serial.println("========================");

}

#endif


/*************************************************
 * 获取当前按钮
 *************************************************/

uint8_t UI_GetCurrentButton(void)
{

    switch(systemState.scene)
    {

        case SCENE_CABLE:

            return 0;

        case SCENE_MEDIA:

            return 1;

        case SCENE_DVD:

            return 2;

        case SCENE_DIGITAL:

            return 3;

        case SCENE_KTV:

            return 4;

        default:

            return 255;

    }

}


/*************************************************
 * 强制重绘
 *************************************************/

void UI_ForceRefresh(void)
{

    uiNeedRefresh = true;

}


/*************************************************
 * UI结束
 *************************************************/