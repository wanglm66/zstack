/*>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
* �ļ���  �� Coordinator
* ����    �� maluyao
* �汾    �� V1.0.0
* ʱ��    �� 2021/5/17
* ��Ҫ    �� Coordinator��ͷ�ļ�  
********************************************************************
* ����
*
*>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>*/
#ifndef COORDINATOR_H
#define COORDINATOOR_H
/* ͷ�ļ� ----------------------------------------------------------------*/
#include "ZComDef.h"
/* �궨�� ----------------------------------------------------------------*/
#define GENERICAPP_ENDPOINT 10

#define GENERICAPP_PROFID 0X0F04

#define GENERICAPP_DEVICEID 0X0001

#define GENERICAPP_DEVICE_VERSION 0

#define GENERICAPP_FLAGS 0

#define GENERICAPP_MAX_CLUSTERS 1
#define GENERICAPP_CLUSTERID 1
/* �ṹ���ö�� ----------------------------------------------------------*/
/* ��������---------------------------------------------------------------*/
/* �ⲿ�������� ----------------------------------------------------------*/ 

void GenericApp_MessageMSGCB( afIncomingMSGPacket_t *pckt );
void GenericApp_SendTheMessage( void);


extern void GenericApp_Init(byte task_id);

extern UINT16 GenericApp_ProcessEvent(byte task_id,UINT16 events);

#endif
