#ifndef CONFIG_H
#define CONFIG_H
#include <Arduino.h>
#include "scene.h"

/*************************************************
 * 系统版本
 *************************************************/
#define FW_VERSION     "V3.0.0"

/*************************************************
 * 硬件版本
 *************************************************/
#define HW_VERSION     "HW1.0"


/*************************************************
 *              LCD ST7789
 *************************************************/

#define TFT_MOSI   2
#define TFT_SCLK   1
#define TFT_CS     39
#define TFT_DC     41
#define TFT_RST    40
#define TFT_BL     6


#define LCD_WIDTH   170
#define LCD_HEIGHT  320


// Arduino_GFX 参数
#define LCD_OFFSET_X 35
#define LCD_OFFSET_Y 0


/*************************************************
 *              CST816 TOUCH
 *************************************************/

#define TP_SDA 15
#define TP_SCL 7

#define CST816_ADDR 0x15



/*************************************************
 *              RS232 UART
 *************************************************/


// A组 EASTCATO 地址00 地址01 

#define UART_A_RX 13
#define UART_A_TX 14


// B组 天逸2300PRO

#define UART_B_RX 11
#define UART_B_TX 12

//C组  宏碁 V7500 投影机

#define PROJECTOR_RX 9
#define PROJECTOR_TX 10


// RS232速度

#define RS232_BAUD 9600

// 端口数量

#define EAST_A_PORTS 8
#define EAST_B_PORTS 5


/*********************************
 * 功放输入
 *********************************/

#define AMP_HDMI1   1
#define AMP_HDMI2   2
#define AMP_HDMI3   3
#define AMP_HDMI4   4
#define AMP_HDMI5   5

#define AMP_AN1     6
#define AMP_AN2     7



/*************************************************
 *              设备延时
 *************************************************/


// 设备上电等待

#define DEVICE_START_DELAY 5000


/*************************************************
 *              LCD颜色
 *************************************************/


#define COLOR_BLACK   0x0000
#define COLOR_WHITE   0xFFFF
#define COLOR_RED     0xF800
#define COLOR_GREEN   0x07E0
#define COLOR_BLUE    0x001F
#define COLOR_GRAY    0x8410

/*************************************************
 *              WIFI
 *************************************************/

#define DEFAULT_WIFI_SSID      "AV_Controller"

#define DEFAULT_WIFI_PASSWORD  "12345678"

#endif