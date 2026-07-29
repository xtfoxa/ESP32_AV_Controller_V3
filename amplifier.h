#ifndef AMPLIFIER_H
#define AMPLIFIER_H
#include <Arduino.h>
//输入定义
#define AMP_HDMI1   1
#define AMP_HDMI2   2
#define AMP_HDMI3   3
#define AMP_AN1     4
#define AMP_AN2     5


// 初始化
void Amplifier_Init();

// 输入选择
void Amplifier_Select(uint8_t input);

// 电源
void Amp_ON();
void Amp_OFF();

// HDMI输入
void Amp_HDMI1();
void Amp_HDMI2();
void Amp_HDMI3();

// 模拟输入
void Amp_AN1();
void Amp_AN2();

//辅助函数
void Amplifier_SetInput(uint8_t input);
void Amplifier_Start(uint8_t input);

#endif