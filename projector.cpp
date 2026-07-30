#include "projector.h"
#include "system.h"
#include "config.h"
#include <SoftwareSerial.h>

/****************************************
 * 投影机 RS232 串口
 ****************************************/
SoftwareSerial ProjectorSerial(
    PROJECTOR_RX,
    PROJECTOR_TX
);

/****************************************
 * 串口初始化
 ****************************************/

void Projector_Init()
{
    ProjectorSerial.begin(9600);
}

/****************************************
 * 底层发送
 ****************************************/

static void Projector_Send(
    const char *cmd
)
{
    ProjectorSerial.print(cmd);
}



//* 投影机开机****/

void Projector_Start()
{
    uint8_t cmd[] =
    {
        0x2A, 0x20,
        0x30, 0x20,
        0x49, 0x52, 0x20,
        0x30, 0x30, 0x31,
        0x0D
    };

    ProjectorSerial.write(cmd, sizeof(cmd));

}

/****************************************
 * 投影机关机
 ****************************************/

void Projector_Stop()
{
    uint8_t cmd[] =
    {
        0x2A, 0x20,
        0x30, 0x20,
        0x49, 0x52, 0x20,
        0x30, 0x30, 0x32,
        0x0D
    };

    ProjectorSerial.write(cmd, sizeof(cmd));

    delay(1000);

  
    // 有些V7500关机需要重复发送
    ProjectorSerial.write(cmd, sizeof(cmd));


}

void Projector_ON()
{
    Projector_Start();
}

void Projector_OFF()
{
    Projector_Stop();
}