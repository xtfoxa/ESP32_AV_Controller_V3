#ifndef WIFI_PAGE_H
#define WIFI_PAGE_H

const char MAIN_PAGE[] PROGMEM = R"rawliteral(

<!DOCTYPE html>

<html lang="zh-CN">

<head>

<meta charset="UTF-8">

<meta name="viewport" content="width=device-width,initial-scale=1">

<title>ESP32 AV Controller V3</title>

<style>

*{
    box-sizing:border-box;
}

body{

    margin:0;

    background:#1f1f1f;

    font-family:Arial,Helvetica,sans-serif;

    color:white;

    text-align:center;

}

.header{

    background:#303134;

    padding:18px;

    font-size:28px;

    font-weight:bold;

}

.status{

    margin:20px;

    line-height:34px;

    font-size:18px;

}

.status span{

    color:#00ff88;

    font-weight:bold;

}

button{

    width:240px;

    height:48px;

    margin:8px;

    border:none;

    border-radius:8px;

    background:#505050;

    color:white;

    font-size:18px;

    cursor:pointer;

    transition:.25s;

}

button:hover{

    background:#666;

}

.active{

    background:#0aa84f !important;

}

.power{

    background:#b02020;

}

.power:hover{

    background:#d03030;

}

.footer{

    margin-top:25px;

    color:#999;

    font-size:13px;

}

</style>

</head>

<body>

<div class="header">

ESP32 AV Controller

</div>

<div class="status">

当前场景：

<span id="scene">

Unknown

</span>

<br>

功放输入：

<span id="amp">

--

</span>

<br>

投影：

<span id="projector">

--

</span>

</div>

<button id="btnCable"

onclick="location.href='/cable'">

📺 有线电视

</button>

<br>

<button id="btnMedia"

onclick="location.href='/media'">

🎬 流媒体

</button>

<br>

<button id="btnDVD"

onclick="location.href='/dvd'">

💿 DVD

</button>

<br>

<button id="btnDigital"

onclick="location.href='/digital'">

🎵 数播

</button>

<br>

<button id="btnKTV"

onclick="location.href='/ktv'">

🎤 卡拉OK

</button>

<br><br>

<button class="power"

onclick="location.href='/shutdown'">

⏻ 系统关机

</button>

<div class="footer">

ESP32 AV Controller V3

</div>

</body>

</html>

)rawliteral";

#endif