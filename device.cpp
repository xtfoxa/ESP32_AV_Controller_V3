#include "device.h"
#include "eastcato.h"
#include "amplifier.h"
#include "projector.h"
#include "scene.h"
#include "system.h"
#include "config.h"

/*************************************************
 *
 * Device State
 *
 *************************************************/

DeviceState currentDeviceState;


/*************************************************
 *
 * Device Queue
 *
 *************************************************/

#define DEVICE_QUEUE_SIZE 32


static DeviceTask deviceQueue[DEVICE_QUEUE_SIZE];

static uint8_t queueHead = 0;
static uint8_t queueTail = 0;

static bool queueRunning = false;

static uint32_t nextExecuteTime = 0;


/*************************************************
 *
 * Queue
 *
 *************************************************/

static void Queue_Clear()
{

    queueHead = 0;

    queueTail = 0;

    queueRunning = false;

}


static bool Queue_IsEmpty()
{

    return queueHead == queueTail;

}


static bool Queue_IsFull()
{

    return ((queueTail + 1) % DEVICE_QUEUE_SIZE) == queueHead;

}


static bool Queue_Push(
    DeviceAction action,
    uint8_t id,
    bool value,
    uint16_t delayMs
)
{

    if (Queue_IsFull())
        return false;

    deviceQueue[queueTail].action = action;

    deviceQueue[queueTail].id = id;

    deviceQueue[queueTail].value = value;

    deviceQueue[queueTail].delayMs = delayMs;

    queueTail++;

    if (queueTail >= DEVICE_QUEUE_SIZE)
        queueTail = 0;

    return true;

}


static bool Queue_Pop(DeviceTask &task)
{

    if (Queue_IsEmpty())
        return false;

    task = deviceQueue[queueHead];

    queueHead++;

    if (queueHead >= DEVICE_QUEUE_SIZE)
        queueHead = 0;

    return true;

}


/*************************************************
 *
 * Driver Wrapper
 *
 *************************************************/

void Device_SetA(uint8_t port,bool on)
{

    switch(port)
    {

        case 1:

            if(on) East_A1_ON();
            else   East_A1_OFF();

            break;

        case 2:

            if(on) East_A2_ON();
            else   East_A2_OFF();

            break;

        case 3:

            if(on) East_A3_ON();
            else   East_A3_OFF();

            break;

        case 4:

            if(on) East_A4_ON();
            else   East_A4_OFF();

            break;

        case 5:

            if(on) East_A5_ON();
            else   East_A5_OFF();

            break;

        case 6:

            if(on) East_A6_ON();
            else   East_A6_OFF();

            break;

        case 7:

            if(on) East_A7_ON();
            else   East_A7_OFF();

            break;

        case 8:

            if(on) East_A8_ON();
            else   East_A8_OFF();

            break;

    }

}

/*************************************************
 *
 * B Driver
 *
 *************************************************/

void Device_SetB(uint8_t port,bool on)
{

    switch(port)
    {

        case 1:

            if(on) East_B1_ON();
            else   East_B1_OFF();

            break;

        case 2:

            if(on) East_B2_ON();
            else   East_B2_OFF();

            break;

        case 3:

            if(on) East_B3_ON();
            else   East_B3_OFF();

            break;

        case 4:

            if(on) East_B4_ON();
            else   East_B4_OFF();

            break;

        case 5:

            if(on) East_B5_ON();
            else   East_B5_OFF();

            break;

    }

}


/*************************************************
 *
 * 全部关闭
 *
 *************************************************/

void Device_AllOff()
{

    East_All_OFF();

}


/*************************************************
 *
 * Amplifier
 *
 *************************************************/

void Device_AmpPower(bool on)
{

    if(on)
    {
        Amp_ON();
    }
    else
    {
        Amp_OFF();
    }

}


void Device_AmpInput(uint8_t input)
{

    Amplifier_Select(input);

}


/*************************************************
 *
 * Projector
 *
 *************************************************/

void Device_Projector(bool on)
{

    if(on)
    {
        Projector_Start();
    }
    else
    {
        Projector_Stop();
    }

}


/*************************************************
 *
 * Device Init
 *
 *************************************************/

void Device_Init()
{

    Queue_Clear();

}


/*************************************************
 *
 * Shutdown
 *
 *************************************************/

void Device_Shutdown()
{

    Queue_Clear();

    Device_Projector(false);

    Device_AmpPower(false);

    Device_AllOff();

}

/*************************************************
 *
 * Device Task
 *
 *************************************************/

void Device_Task()
{

    if (Queue_IsEmpty())
    {
        queueRunning = false;
        return;
    }

    if (!queueRunning)
    {
        queueRunning = true;
        nextExecuteTime = millis();
    }

    if (millis() < nextExecuteTime)
        return;

    DeviceTask task;

    if (!Queue_Pop(task))
        return;

    switch (task.action)
    {

        /*********************************************
         * A组
         *********************************************/

        case DEV_A_POWER:

            Device_SetA(

                task.id,

                task.value

            );

            break;


        /*********************************************
         * B组
         *********************************************/

        case DEV_B_POWER:

            Device_SetB(

                task.id,

                task.value

            );

            break;


        /*********************************************
         * 投影
         *********************************************/

        case DEV_PROJECTOR:

            Device_Projector(

                task.value

            );

            break;


        /*********************************************
         * 功放电源
         *********************************************/
        case DEV_AMP_POWER:

            if(task.value)
            {
               Amplifier_Start(
                currentDeviceState.ampInput
               );
             }
             else
             {
                  Device_AmpPower(false);
             }

               break;



        /*********************************************
         * 功放输入
         *********************************************/

        case DEV_AMP_INPUT:

            Device_AmpInput(

                task.id

            );

            break;


        /*********************************************
         * Delay
         *********************************************/

        case DEV_DELAY:

            break;


        default:

            break;

    }


    nextExecuteTime = millis() + task.delayMs;

}


void Device_BuildTarget(
    const SceneConfig *scene,
    DeviceState &target
)
{

    memset(&target,0,sizeof(DeviceState));

    //--------------------------------------------------
    // A组
    //--------------------------------------------------

    for(uint8_t i=0;i<8;i++)
    {
        target.a[i]=scene->eastA[i];
    }

    //--------------------------------------------------
    // B组
    //--------------------------------------------------

    for(uint8_t i=0;i<5;i++)
    {
        target.b[i]=scene->eastB[i];
    }

    //--------------------------------------------------
    // 功放
    //--------------------------------------------------

    target.amplifierOn=true;

    target.ampInput=scene->ampInput;

    //--------------------------------------------------
    // 投影
    //--------------------------------------------------

    target.projectorOn=scene->useProjector;

    //--------------------------------------------------
    // 视频模式
    //--------------------------------------------------

    target.videoMode=scene->videoMode;

}

/*************************************************
 *
 * Diff Engine
 *
 *************************************************/

void Device_GenerateDiff(
    const DeviceState &current,
    const DeviceState &target,
    const SceneConfig *scene
)
{

    Queue_Clear();

    /*************************************************
     * A组
     *************************************************/

    for(uint8_t i=0;i<8;i++)
    {

        if(current.a[i]==target.a[i])
            continue;

        Queue_Push(

            DEV_A_POWER,

            i+1,

            target.a[i],

            500

        );

    }

    /*************************************************
     * B组
     *************************************************/

    for(uint8_t i=0;i<5;i++)
    {

        if(current.b[i]==target.b[i])
            continue;

        Queue_Push(

            DEV_B_POWER,

            i+1,

            target.b[i],

            500

        );

    }

    /*************************************************
     * 投影
     *************************************************/

    if(current.projectorOn!=target.projectorOn)
    {

        Queue_Push(

            DEV_PROJECTOR,

            0,

            target.projectorOn,

            DEVICE_START_DELAY

        );

    }

    /*************************************************
     * 功放
     *************************************************/

    if(current.amplifierOn!=target.amplifierOn)
    {

        Queue_Push(

            DEV_AMP_POWER,

            0,

            target.amplifierOn,

            1000

        );

    }

    /*************************************************
     * 输入
     *************************************************/

    if(current.ampInput!=target.ampInput)
    {

        if(current.amplifierOn)
        {Queue_Push(

            DEV_AMP_INPUT,

            target.ampInput,

            true,

            0

        );
        }

    }

}

/*************************************************
 *
 * Queue Generate
 *
 *************************************************/

static void Queue_GenerateFromScene(
    const DeviceState &current,
    const DeviceState &target,
    const SceneConfig *scene
)
{

    for(int8_t i=scene->powerCount-1;i>=0;i--)
    {

        uint8_t dev=scene->powerSequence[i];

        //-----------------------------------------
        // A组
        //-----------------------------------------

        if(dev>=1 && dev<=8)
        {

            uint8_t idx=dev-1;

            if(current.a[idx] && !target.a[idx])
            {

                Queue_Push(

                    DEV_A_POWER,

                    dev,

                    false,

                    300

                );

            }

            continue;

        }

        //-----------------------------------------
        // B组
        //-----------------------------------------

        if(dev>=9 && dev<=13)
        {

            uint8_t idx=dev-9;

            if(current.b[idx] && !target.b[idx])
            {

                Queue_Push(

                    DEV_B_POWER,

                    idx+1,

                    false,

                    300

                );

            }

        }

    }

}


/*************************************************
 *
 * Generate Open Queue
 *
 *************************************************/

static void Queue_GenerateOpen(

    const DeviceState &current,

    const DeviceState &target,

    const SceneConfig *scene

)
{

    for(uint8_t i=0;i<scene->powerCount;i++)
    {

        uint8_t dev=scene->powerSequence[i];

        //-----------------------------------------
        // A组
        //-----------------------------------------

        if(dev>=1 && dev<=8)
        {

            uint8_t idx=dev-1;

            if(!current.a[idx] && target.a[idx])
            {

                Queue_Push(

                    DEV_A_POWER,

                    dev,

                    true,

                    500

                );

            }

            continue;

        }

        //-----------------------------------------
        // B组
        //-----------------------------------------

        if(dev>=9 && dev<=13)
        {

            uint8_t idx=dev-9;

            if(!current.b[idx] && target.b[idx])
            {

                Queue_Push(

                    DEV_B_POWER,

                    idx+1,

                    true,

                    500

                );

            }

        }

    }

}


/*************************************************
 *
 * Apply Scene
 *
 *************************************************/

void Device_ApplyScene(const SceneConfig *scene)
{

    if(scene == nullptr)
        return;

    //----------------------------------------
    // 生成目标状态
    //----------------------------------------

    DeviceState target;

    Device_BuildTarget(

        scene,

        target

    );

    //----------------------------------------
    // 生成执行队列
    //----------------------------------------

    Device_GenerateDiff(

        currentDeviceState,

        target,

        scene

    );

    //----------------------------------------
    // 更新当前状态
    //----------------------------------------

    currentDeviceState = target;

}