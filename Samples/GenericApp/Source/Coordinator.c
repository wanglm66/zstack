/*>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
* 文件名  ： Coordinator
* 作者    ： wangsihui
* 版本    ： V1.0.0
* 时间    ： 2021/5/17
* 简要    ： 协调器  
********************************************************************
* 副本
*
*>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>*/
/* 头文件 ----------------------------------------------------------------*/
#include  "OSAL.h"
#include  "AF.h"
#include  "ZDAPP.h"
#include  "ZDObject.h"
#include  "ZDProfile.h"
#include  <string.h>
#include  "Coordinator.h"
#include  "DebugTrace.h"
#if !defined(WIN32)
#include "OnBoard.h"
#endif

#include "hal_lcd.h"
#include "hal_led.h"
#include "hal_key.h"
#include "hal_uart.h"

const cId_t GenericApp_ClusterList[GENERICAPP_MAX_CLUSTERS] =
//GENERICAPP_MAX_CLUSTERS在Coordinator.h文件中定义的宏
{
    GENERICAPP_CLUSTERID
};
//以下数据结构可以用来描述一个ZigBee设备节点
const SimpleDescriptionFormat_t GenericApp_SimpleDesc =
{
    GENERICAPP_ENDPOINT,
    GENERICAPP_PROFID,
    GENERICAPP_DEVICEID,
    GENERICAPP_DEVICE_VERSION,
    GENERICAPP_FLAGS,
    GENERICAPP_MAX_CLUSTERS,
    (cId_t *)GenericApp_ClusterList,
    0,
    (cId_t *)NULL
};

endPointDesc_t GenericApp_epDesc; //节点描述符
byte GenericApp_TaskID; //任务优先级
byte GenericApp_TransID;//数据发送序列号


void GenericApp_MessageMSGCB(afIncomingMSGPacket_t *pckt );//消息处理函数
void GenericApp_SendTheMessage(void);//数据发送函数


void GenericApp_Init(byte task_id)
{
    
    GenericApp_TaskID              =task_id;//初始化任务优先级
    GenericApp_TransID             = 0;//将数据包的序号初始化为0,
    GenericApp_epDesc.endPoint     =GENERICAPP_ENDPOINT;
    GenericApp_epDesc.task_id      =&GenericApp_TaskID;
    GenericApp_epDesc.simpleDesc   =(SimpleDescriptionFormat_t *)&GenericApp_SimpleDesc;
    GenericApp_epDesc.latencyReq   =noLatencyReqs;//对节点描述符进行初始化
    afRegister( &GenericApp_epDesc);//使用afRegister函数将节点描述符进行注册
    
}
//消息处理函数，完成对接收数据的处理
UINT16 GenericApp_ProcessEvent( byte task_id, UINT16 events )
{
    afIncomingMSGPacket_t *MSGpkt;//定义一个指向接收消息结构体的指针MSGpkt
    if ( events & SYS_EVENT_MSG )
    {
        MSGpkt = (afIncomingMSGPacket_t *)osal_msg_receive(GenericApp_TaskID);//使用osal_msg_receive函数从消息队列上接收消息
        while ( MSGpkt )
        {
            switch ( MSGpkt->hdr.event )
            {
            case AF_INCOMING_MSG_CMD:
                GenericApp_MessageMSGCB( MSGpkt );
                break;
            default:
                break;
            }
            osal_msg_deallocate( (uint8 *) MSGpkt );
            MSGpkt = (afIncomingMSGPacket_t *)osal_msg_receive
                ( GenericApp_TaskID );
        }
        return (events^SYS_EVENT_MSG);
    }
    return 0 ;
}

//实现数据发送
void GenericApp_MessageMSGCB( afIncomingMSGPacket_t *pkt)
{
    unsigned char buffer[4]=" ";
    switch ( pkt->clusterId )
    {
    case GENERICAPP_CLUSTERID:
        osal_memcpy(buffer,pkt->cmd.Data,3);
        if((buffer[0]=='L')||(buffer[1]=='E')||(buffer[2]=='D'))
        {
            HalLedBlink(HAL_LED_2,0,50,500);
        }
        else
        {
            HalLedSet(HAL_LED_2,HAL_LED_MODE_ON);
        }
        break;
        
    }
}
