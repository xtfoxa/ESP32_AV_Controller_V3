#include "eastcato.h"
#include "config.h"
#include "system.h"


HardwareSerial SerialA(1);


/*************************************************
 * 初始化
 *************************************************/

void Eastcato_Init()
{

    SerialA.begin(
        RS232_BAUD,
        SERIAL_8N1,
        UART_A_RX,
        UART_A_TX
    );


}


//==============================
// A组 A1-A8 开关
//==============================


// A1
const uint8_t A1_ON[] =
{
    0xCA,0x20,0x00,0x18,0x02,0x01,0x01,0xAC
};


const uint8_t A1_OFF[] =
{
    0xCA,0x20,0x00,0x18,0x02,0x01,0x00,0xAC
};



// A2
const uint8_t A2_ON[] =
{
    0xCA,0x20,0x00,0x18,0x02,0x02,0x01,0xAC
};


const uint8_t A2_OFF[] =
{
    0xCA,0x20,0x00,0x18,0x02,0x02,0x00,0xAC
};



// A3
const uint8_t A3_ON[] =
{
    0xCA,0x20,0x00,0x18,0x02,0x03,0x01,0xAC
};


const uint8_t A3_OFF[] =
{
    0xCA,0x20,0x00,0x18,0x02,0x03,0x00,0xAC
};



// A4
const uint8_t A4_ON[] =
{
    0xCA,0x20,0x00,0x18,0x02,0x04,0x01,0xAC
};


const uint8_t A4_OFF[] =
{
    0xCA,0x20,0x00,0x18,0x02,0x04,0x00,0xAC
};



// A5
const uint8_t A5_ON[] =
{
    0xCA,0x20,0x00,0x18,0x02,0x05,0x01,0xAC
};


const uint8_t A5_OFF[] =
{
    0xCA,0x20,0x00,0x18,0x02,0x05,0x00,0xAC
};



// A6 投影
const uint8_t A6_ON[] =
{
    0xCA,0x20,0x00,0x18,0x02,0x06,0x01,0xAC
};


const uint8_t A6_OFF[] =
{
    0xCA,0x20,0x00,0x19,0x03,0x20,0x00,0x82,0xAC
};



// A7
const uint8_t A7_ON[] =
{
    0xCA,0x20,0x00,0x18,0x02,0x07,0x01,0xAC
};


const uint8_t A7_OFF[] =
{
    0xCA,0x20,0x00,0x18,0x02,0x07,0x00,0xAC
};



// A8 功放
const uint8_t A8_ON[] =
{
    0xCA,0x20,0x00,0x18,0x02,0x08,0x01,0xAC
};


const uint8_t A8_OFF[] =
{
    0xCA,0x20,0x00,0x19,0x03,0x80,0x00,0x82,0xAC
};



/*************************************************
 * 底层发送
 *************************************************/

static void East_WriteA(
    const uint8_t *cmd,
    uint8_t len
)
{
    SerialA.write(
        cmd,
        len
    );
}


/*************************************************
 * A组控制
 *************************************************/


void East_A1_ON()
{
    East_WriteA(A1_ON,sizeof(A1_ON));
    delay(500);
    
}


void East_A1_OFF()
{
    delay(500);
    East_WriteA(A1_OFF,sizeof(A1_OFF));
    
}



void East_A2_ON()
{
    East_WriteA(A2_ON,sizeof(A2_ON));
    delay(500);
    
}


void East_A2_OFF()
{
    delay(500);
    East_WriteA(A2_OFF,sizeof(A2_OFF));
    
}



void East_A3_ON()
{
    East_WriteA(A3_ON,sizeof(A3_ON));
    delay(500);
    
}


void East_A3_OFF()
{
    delay(500);
    East_WriteA(A3_OFF,sizeof(A3_OFF));
    
}



void East_A4_ON()
{
    East_WriteA(A4_ON,sizeof(A4_ON));
    delay(500);
    
}


void East_A4_OFF()
{
    delay(500);
    East_WriteA(A4_OFF,sizeof(A4_OFF));
    
}



void East_A5_ON()
{
    East_WriteA(A5_ON,sizeof(A5_ON));
    delay(500);
    
}


void East_A5_OFF()
{
    delay(500);
    East_WriteA(A5_OFF,sizeof(A5_OFF));
    
}




// 投影电源

void East_A6_ON()
{
    East_WriteA(A6_ON,sizeof(A6_ON));
    delay(500);
    

}


void East_A6_OFF()
{
    delay(500);
    East_WriteA(A6_OFF,sizeof(A6_OFF));
    delay(500);
    
}


void East_A7_ON()
{
    East_WriteA(A7_ON,sizeof(A7_ON));
    delay(500);
    
}


void East_A7_OFF()
{
    delay(500);
    East_WriteA(A7_OFF,sizeof(A7_OFF));
    
}



void East_A8_ON()
{
    East_WriteA(A8_ON,sizeof(A8_ON));
    delay(500);
    
}



void East_A8_OFF()
{
    delay(500);
    East_WriteA(A8_OFF,sizeof(A8_OFF));
    delay(500);
    
}

/*************************************************
 * B组指令
 *
 * B时序器地址：
 * CA 20 01
 *************************************************/


// B1

const uint8_t B1_ON[] =
{
    0xCA,0x20,0x01,0x18,0x02,0x01,0x01,0xAC
};


const uint8_t B1_OFF[] =
{
    0xCA,0x20,0x01,0x18,0x02,0x01,0x00,0xAC
};




// B2

const uint8_t B2_ON[] =
{
    0xCA,0x20,0x01,0x18,0x02,0x02,0x01,0xAC
};


const uint8_t B2_OFF[] =
{
    0xCA,0x20,0x01,0x18,0x02,0x02,0x00,0xAC
};




// B3

const uint8_t B3_ON[] =
{
    0xCA,0x20,0x01,0x18,0x02,0x03,0x01,0xAC
};


const uint8_t B3_OFF[] =
{
    0xCA,0x20,0x01,0x18,0x02,0x03,0x00,0xAC
};




// B4

const uint8_t B4_ON[] =
{
    0xCA,0x20,0x01,0x18,0x02,0x04,0x01,0xAC
};


const uint8_t B4_OFF[] =
{
    0xCA,0x20,0x01,0x18,0x02,0x04,0x00,0xAC
};




// B5

const uint8_t B5_ON[] =
{
    0xCA,0x20,0x01,0x18,0x02,0x05,0x01,0xAC
};


const uint8_t B5_OFF[] =
{
    0xCA,0x20,0x01,0x18,0x02,0x05,0x00,0xAC
};



/*************************************************
 * B组控制
 *************************************************/


void East_B1_ON()
{
    East_WriteA(B1_ON,sizeof(B1_ON));
    delay(500);
    
}


void East_B1_OFF()
{
    delay(500);
    East_WriteA(B1_OFF,sizeof(B1_OFF));
    
}


void East_B2_ON()
{
    East_WriteA(B2_ON,sizeof(B2_ON));
    delay(500);
    
}


void East_B2_OFF()
{
    delay(500);
    East_WriteA(B2_OFF,sizeof(B2_OFF));
    
}


void East_B3_ON()
{
    East_WriteA(B3_ON,sizeof(B3_ON));
    delay(500);
    
}


void East_B3_OFF()
{
    delay(500);
    East_WriteA(B3_OFF,sizeof(B3_OFF));
    
}


void East_B4_ON()
{
    East_WriteA(B4_ON,sizeof(B4_ON));
    delay(500);
    
}


void East_B4_OFF()
{
    delay(500);
    East_WriteA(B4_OFF,sizeof(B4_OFF));
    
}


void East_B5_ON()
{
    East_WriteA(B5_ON,sizeof(B5_ON));
    delay(500);
   
}


void East_B5_OFF()
{
    delay(500);
    East_WriteA(B5_OFF,sizeof(B5_OFF));
    
}


/*************************************************
 * 全部关闭
 *************************************************/


void East_All_OFF()
{

    East_A1_OFF();
    East_A2_OFF();
    East_A3_OFF();
    East_A4_OFF();
    East_A5_OFF();
    East_A6_OFF();
    East_A7_OFF();
    East_A8_OFF();



    East_B1_OFF();
    East_B2_OFF();
    East_B3_OFF();
    East_B4_OFF();
    East_B5_OFF();

}