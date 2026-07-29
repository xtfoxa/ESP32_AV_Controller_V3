#ifndef EASTCATO_H
#define EASTCATO_H
#include <Arduino.h>

void Eastcato_Init();


/*************************************************
 * A组时序器 A1-A8
 *************************************************/


void East_A1_ON();
void East_A1_OFF();


void East_A2_ON();
void East_A2_OFF();


void East_A3_ON();
void East_A3_OFF();


void East_A4_ON();
void East_A4_OFF();


void East_A5_ON();
void East_A5_OFF();


void East_A6_ON();
void East_A6_OFF();


void East_A7_ON();
void East_A7_OFF();


void East_A8_ON();
void East_A8_OFF();



/*************************************************
 * B组时序器 B1-B5
 *************************************************/


void East_B1_ON();
void East_B1_OFF();


void East_B2_ON();
void East_B2_OFF();


void East_B3_ON();
void East_B3_OFF();


void East_B4_ON();
void East_B4_OFF();


void East_B5_ON();
void East_B5_OFF();


/*************************************************
 * 全部关闭
 *************************************************/


void East_All_OFF();



#endif