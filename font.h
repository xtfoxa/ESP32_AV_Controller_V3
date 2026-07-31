#ifndef FONT_H
#define FONT_H
#include <Arduino.h>
#include <Arduino_GFX_Library.h>

//===============================
// 汉字16×16点阵结构
//===============================

typedef struct
{

    uint16_t unicode;       // Unicode编码

    const uint8_t *bitmap;  // 16×16点阵

}
ChineseFont;

//===============================
// 汉字点阵表
//===============================

extern ChineseFont fontTable[];

extern const int fontCount;

//===============================
// 查找字体
//===============================

const uint8_t *FindFont(
    uint16_t code
);

//===============================
// UTF-8解码
//===============================

uint16_t UTF8Decode(
    const char *str,
    int &length
);


//===============================
// 计算混合文字宽度
// 中文16像素
// 英文8像素
//===============================

int GetMixedWidth(

    const char *text

);

//===============================
// 绘制16×16中文
//===============================

void DrawChinese16(

    Arduino_GFX *gfx,

    int x,

    int y,

    const char *text,

    uint16_t color

);


#endif