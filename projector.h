#ifndef PROJECTOR_H
#define PROJECTOR_H


#include <Arduino.h>


/****************************************
 * 投影机控制
 *
 * Acer V7500
 *
 * RS232:
 *
 * 开机:
 * C01\r
 *
 * 关机:
 * C02\r
 *
 * 状态查询:
 * CR0\r
 ****************************************/



// 初始化

void Projector_Init();



// 投影机开机

void Projector_ON();

//

void Projector_OFF();



// 查询状态（预留）

void Projector_Query();

//辅助函数
void Projector_Stop();
void Projector_Start();


#endif