#include "ui.h"
#include "font.h"
#include <Arduino_GFX_Library.h>
#include "config.h"
#include "touch.h"
#include "scene.h"
#include "storage.h"
#include "font.h"

/****************************************************************
 * UI 状态
 ****************************************************************/

static bool uiNeedRefresh = true;

/*************************************************
 *
 * LCD定义
 *
 *************************************************/


Arduino_DataBus *bus =
new Arduino_ESP32SPI(

    TFT_DC,
    TFT_CS,
    TFT_SCLK,
    TFT_MOSI,
    -1

);



Arduino_GFX *gfx =
new Arduino_ST7789(

    bus,

    TFT_RST,

    1,

    true,

    LCD_WIDTH,

    LCD_HEIGHT,

    LCD_OFFSET_X,

    0,

    LCD_OFFSET_X,

    0

);





/*************************************************
 *
 * 颜色
 *
 *************************************************/


#define BTN_COLOR     0x7BEF

#define TEXT_COLOR    0xFFFF

#define ACTIVE_COLOR  0x07E0





/*************************************************
 *
 * 按钮定义
 *
 *************************************************/


struct Button
{

    int x;

    int y;

    int w;

    int h;

    const char *name;

};



Button buttons[6]=
{

    {4,0,104,85,"有线电视"},

    {108,0,104,85,"流媒体"},

    {212,0,104,85,"DVD"},


    {4,85,104,85,"数播"},

    {108,85,104,85,"卡拉OK"},

    {212,85,104,85,"关机"}

};

void UI_Refresh(void)
{
    uiNeedRefresh = true;
    Draw_UI();
}

/*************************************************
 *
 * 绘制按钮
 *
 *************************************************/


void Draw_Button(
    int id,
    bool active
)
{


    uint16_t color;


    if(active)

        color = 0x07E0;       //绿色

    else

        color = 0x8410;       //灰色



    int x =
    buttons[id].x;


    int y =
    buttons[id].y;


    int w =
    buttons[id].w;


    int h =
    buttons[id].h;



    //=====================
    // 双层边框
    //=====================


    gfx->drawRect(

        x,
        y,
        w,
        h,
        color

    );


    gfx->drawRect(

        x+1,
        y+1,
        w-2,
        h-2,
        color

    );



    //=====================
    // 计算文字位置
    //=====================


    int textWidth =
    GetMixedWidth(
        buttons[id].name
    );



    int tx =
    x+(w-textWidth)/2;



    int ty =
    y+34;



    //=====================
    // 中文显示
    //=====================


    DrawChinese16(

        gfx,

        tx,

        ty,

        buttons[id].name,

        0xffff

    );


gfx->setTextColor(0xffff);

gfx->setTextSize(2);


if(id==2)
{

    gfx->setCursor(
        tx,
        ty
    );

    gfx->print("DVD");

}


if(id==4)
{

    gfx->setCursor(
        tx+32,
        ty
    );

    gfx->print("OK");

}


}



/*************************************************
 *
 * 全屏刷新
 *
 *************************************************/


void Draw_UI()
{
    gfx->fillScreen(COLOR_BLACK);

    for (int i = 0; i < 6; i++)
    {
        bool active = false;

        switch (systemState.scene)
        {
            case SCENE_CABLE:
                active = (i == 0);
                break;

            case SCENE_MEDIA:
                active = (i == 1);
                break;

            case SCENE_DVD:
                active = (i == 2);
                break;

            case SCENE_DIGITAL:
                active = (i == 3);
                break;

            case SCENE_KTV:
                active = (i == 4);
                break;

            default:
                active = false;
                break;
        }

        Draw_Button(i, active);
    }
}


/*************************************************
 *
 * 初始化
 *
 *************************************************/


void UI_Init()
{


    pinMode(
        TFT_BL,
        OUTPUT
    );


    // 背光低电平打开

    digitalWrite(
        TFT_BL,
        LOW
    );



    gfx->begin(
        27000000
    );



    Draw_UI();


}


/*************************************************
 *
 * 判断按钮
 *
 *************************************************/


int Check_Button(
    int x,
    int y
)
{


    for(int i=0;i<6;i++)

    {


        if(

            x > buttons[i].x &&

            x < buttons[i].x + buttons[i].w &&

            y > buttons[i].y &&

            y < buttons[i].y + buttons[i].h

        )

        {

            return i;

        }


    }


    return -1;

}


/*************************************************
 *
 * 触摸任务
 *
 *************************************************/

void UI_Task()
{
    // 如果UI需要刷新
    if (uiNeedRefresh)
    {
        uiNeedRefresh = false;
        Draw_UI();
    }

    int16_t x, y;

    if (Touch_GetPoint(x, y))
    {
        Serial.printf("Touch X=%d Y=%d\n", x, y);

        int id = Check_Button(x, y);

        if (id >= 0)
        {
            // 消抖
            delay(150);

            switch (id)
            {
                case 0:
                    Scene_Change(SCENE_CABLE);
                    break;

                case 1:
                    Scene_Change(SCENE_MEDIA);
                    break;

                case 2:
                    Scene_Change(SCENE_DVD);
                    break;

                case 3:
                    Scene_Change(SCENE_DIGITAL);
                    break;

                case 4:
                    Scene_Change(SCENE_KTV);
                    break;

                case 5:
                    Scene_Shutdown();
                    break;
            }
        }
    }
}
