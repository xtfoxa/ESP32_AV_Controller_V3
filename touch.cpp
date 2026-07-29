#include "touch.h"

#include <Wire.h>

#include "config.h"



void Touch_Init()
{

    Wire.begin(
        TP_SDA,
        TP_SCL
    );


    Serial.println(
        "CST816 READY"
    );

}




bool Touch_GetPoint(
    int16_t &x,
    int16_t &y
)
{

    uint8_t buf[5];


    Wire.beginTransmission(
        CST816_ADDR
    );


    Wire.write(
        0x02
    );


    if(
        Wire.endTransmission()!=0
    )
    {
        return false;
    }



    Wire.requestFrom(
        CST816_ADDR,
        5
    );


    int i=0;


    while(
        Wire.available()
    )
    {
        buf[i++]=Wire.read();
    }



    if(i!=5)
    {
        return false;
    }



    uint8_t touch =
        buf[0];



    if(touch==0)
    {
        return false;
    }




    uint16_t rawX =
    ((buf[1]&0x0F)<<8)
    |
    buf[2];



    uint16_t rawY =
    ((buf[3]&0x0F)<<8)
    |
    buf[4];



    /*
       根据实际屏幕验证后的方向

       横屏170×320

    */

    x = rawY;


    y = 169 - rawX;



    if(x<0)
        x=0;

    if(x>319)
        x=319;



    if(y<0)
        y=0;

    if(y>169)
        y=169;



    return true;

}