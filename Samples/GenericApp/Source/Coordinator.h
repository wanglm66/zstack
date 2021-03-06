/*>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
* 文件名  ： Coordinator
* 作者    ： maluyao
* 版本    ： V1.0.0
* 时间    ： 2021/5/17
* 简要    ： Coordinator的头文件  
********************************************************************
* 副本
*
*>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>*/
#ifndef COORDINATOR_H
#define COORDINATOOR_H
/* 头文件 ----------------------------------------------------------------*/
#include "ZComDef.h"
/* 宏定义 ----------------------------------------------------------------*/
#define GENERICAPP_ENDPOINT 10

#define GENERICAPP_PROFID 0X0F04

#define GENERICAPP_DEVICEID 0X0001

#define GENERICAPP_DEVICE_VERSION 0

#define GENERICAPP_FLAGS 0

#define GENERICAPP_MAX_CLUSTERS 1
#define GENERICAPP_CLUSTERID 1
/* 结构体或枚举 ----------------------------------------------------------*/
/* 函数声明---------------------------------------------------------------*/
/* 外部变量引用 ----------------------------------------------------------*/ 

void GenericApp_MessageMSGCB( afIncomingMSGPacket_t *pckt );
void GenericApp_SendTheMessage( void);


extern void GenericApp_Init(byte task_id);

extern UINT16 GenericApp_ProcessEvent(byte task_id,UINT16 events);

#endif
