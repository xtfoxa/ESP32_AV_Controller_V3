#ifndef TOUCH_H
#define TOUCH_H
#include <Arduino.h>


void Touch_Init();


bool Touch_GetPoint(
    int16_t &x,
    int16_t &y
);



#endif