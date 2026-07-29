#ifndef DEVICE_H
#define DEVICE_H

#include <Arduino.h>

//
// Eastcato
//
void Device_SetA(uint8_t port,bool on);

void Device_SetB(uint8_t port,bool on);

void Device_AllOff();

//
// 功放
//
void Device_AmpPower(bool on);

void Device_AmpInput(uint8_t input);

//
// 投影
//
void Device_Projector(bool on);

#endif