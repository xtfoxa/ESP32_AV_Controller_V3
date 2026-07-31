#include "ui.h"
#include "config.h"
#include "system.h"
#include "scene.h"
#include "touch.h"
#include <Arduino_GFX_Library.h>
#include <Wire.h>
#include "avdisplay.h"
#include "font.h"

#define COLOR_GREEN 0x05E0



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
    uint8_t id;


} UIButton;


/*************************************************
 * 场景按钮
 *************************************************/

static const UIButton buttons[] =
{
    {4,0,104,85,0},
    {108,0,104,85,1},
    {212,0,104,85,2},

    {4,85,104,85,3},
    {108,85,104,85,4},
    {212,85,104,85,5}
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
    SCENE_POWER_OFF          // Power
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

static void Draw_Button_Text(uint8_t id,int16_t x,int16_t y)
{

    switch(id)
    {

        // 有线电视
        case 0:

            DrawChinese16(
                gfx,
                x,
                y,
                "有线电视",
                COLOR_WHITE
            );

            break;


        // 流媒体
        case 1:

            DrawChinese16(
                gfx,
                x,
                y,
                "流媒体",
                COLOR_WHITE
            );

            break;


        // DVD
        case 2:

            gfx->setCursor(x,y);
            gfx->setTextColor(COLOR_WHITE);
            gfx->setTextSize(2);
            gfx->print("DVD");

            break;


        // 数播
        case 3:

            DrawChinese16(
                gfx,
                x,
                y,
                "数播",
                COLOR_WHITE
            );

            break;


        // 卡拉OK
        case 4:

            DrawChinese16(
                gfx,
                x,
                y,
                "卡拉",
                COLOR_WHITE
            );


            gfx->setCursor(
                x+32,
                y
            );

            gfx->setTextColor(COLOR_WHITE);
            gfx->setTextSize(2);
            gfx->print("OK");


            break;


        // 关机
        case 5:

            DrawChinese16(
                gfx,
                x,
                y,
                "关机",
                COLOR_WHITE
            );

            break;

    }

}



void Draw_Button(uint8_t index)
{

    const UIButton &btn = buttons[index];


    uint16_t borderColor = COLOR_WHITE;

    //当前运行场景
    if(buttonSceneMap[index] == systemState.scene)
    {
    borderColor = COLOR_GREEN;
    }

    // 正在点击反馈
    if(buttonSceneMap[index] == systemState.scene)
    {
    borderColor = COLOR_GREEN;
    }


    gfx->drawRoundRect(

    btn.x,
    btn.y,
    btn.w,
    btn.h,
    8,
    borderColor

     );
// 加粗 2~3 像素
    if(borderColor == COLOR_GREEN)
    {

        gfx->drawRoundRect(
            btn.x + 1,
            btn.y + 1,
            btn.w - 2,
            btn.h - 2,
            7,
            borderColor
        );


        gfx->drawRoundRect(
            btn.x + 2,
            btn.y + 2,
            btn.w - 4,
            btn.h - 4,
            6,
            borderColor
        );

    }


    int textWidth;


    switch(btn.id)
    {

        case 0:
            textWidth = GetMixedWidth("有线电视");
            break;


        case 1:
            textWidth = GetMixedWidth("流媒体");
            break;


        case 2:
            textWidth = 3 * 12;   // DVD
            break;


        case 3:
            textWidth = GetMixedWidth("数播");
            break;


        case 4:
            textWidth = GetMixedWidth("卡拉") + 16;
            break;


        case 5:
            textWidth = GetMixedWidth("关机");
            break;


    }


    int16_t tx =
        btn.x + (btn.w - textWidth)/2;


    int16_t ty =
        btn.y + (btn.h-16)/2;


    Draw_Button_Text(

        btn.id,

        tx,

        ty

    );

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

static int Check_Button(
    int16_t x,
    int16_t y
)
{

    for(uint8_t i=0;i<BUTTON_COUNT;i++)
    {

        const UIButton *btn=&buttons[i];


        if(
            x>=btn->x &&
            x<=btn->x+btn->w &&
            y>=btn->y &&
            y<=btn->y+btn->h
        )
        {

            
            uiNeedRefresh = true;


            return btn->id;

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

    // 立即刷新一次，让用户看到反馈
    systemState.scene = SCENE_NONE;

    uiNeedRefresh = true;

    Draw_UI();


    delay(300);


    Scene_Shutdown();


    systemState.scene = SCENE_NONE;

    uiNeedRefresh = true;


    return;
    }
    

    /*************************************************
     * 场景切换
     *************************************************/

    uiNeedRefresh = true;

    Draw_UI();


    Scene_Change(buttonSceneMap[id]);

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