#include "amplifier.h"
#include "system.h"
#include "config.h"

HardwareSerial SerialB(2);

/****************************************
 * 初始化
 ****************************************/

extern HardwareSerial SerialB;

void Amplifier_Init()
{
   SerialB.begin(
        RS232_BAUD,
        SERIAL_8N1,
        UART_B_RX,
        UART_B_TX
    ); 
}

/****************************************
 * 底层发送
 ****************************************/

static void Amp_Send(
    const char *cmd
)
{

    SerialB.print("#");

    SerialB.print(cmd);

    SerialB.print("*");

    delay(50);

}

/****************************************
 * 功放开机
 *
 * RS232:POWER ON
 ****************************************/

void Amp_ON()
{

    Amp_Send(
        "POWER ON"
    );

}


/****************************************
 * 功放待机
 * RS232:POWER OFF
 * 注意：
 * 这里不是断电
 * A8断电由eastcato负责
 ****************************************/

void Amp_OFF()
{

    Amp_Send(
        "POWER OFF"
    );

}

/****************************************
 * 输入选择
 ****************************************/

void Amplifier_Select(uint8_t input)
{
    switch(input)
    {

        case 1:
            Amp_HDMI1();
            break;

        case 2:
            Amp_HDMI2();
            break;

        case 3:
            Amp_HDMI3();
            break;

        case 4:
            Amp_AN1();
            break;

        case 5:
            Amp_AN2();
            break;

        case 6:
            Amp_OFF();
            break;


    }

}

/****************************************
 * HDMI输入
 ****************************************/


void Amp_HDMI1()
{Amp_Send("#SI HD1");}

void Amp_HDMI2()
{Amp_Send("#SI HD2");}



void Amp_HDMI3()
{Amp_Send("#SI HD3");}


/****************************************
 * 模拟输入
 ****************************************/
void Amp_AN1()
{Amp_Send("#SI AN1");}


void Amp_AN2()
{ Amp_Send("#SI AN2");}

void Amplifier_SetInput(uint8_t input)
{
    Amplifier_Select(input);

    systemState.ampInput = input;
}


void Amplifier_Start(uint8_t input)
{
    // 功放开机
    Amp_ON();

    // 等待功放启动完毕
    delay(36000);

    // 切换输入
    Amplifier_Select(input);

}
