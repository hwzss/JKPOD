/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: unknown, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_DeviceAlarmPlan_H_
#define _LC_OPENAPI_CLIENT_DeviceAlarmPlan_H_

#include "LCOpenApiClientSdk.h"

/** DESCRIPTION: 
获取设备的动检检测计划

 */

typedef struct DeviceAlarmPlanRequest 
{
	LCOpenApiRequest base;

	struct DeviceAlarmPlanRequestData
	{
		
		/** 授权token(userToken或accessToken) */
		CSTR token;
		/** 通道ID */
		CSTR channelId;
		/** [cstr]deviceAlarmPlan */
		#define _STATIC_DeviceAlarmPlanRequestData_method "deviceAlarmPlan"
		CSTR method;
		/** 设备序列号,例2342sdfl-df323-23 */
		CSTR deviceId;

	} data;

} DeviceAlarmPlanRequest;

C_API DeviceAlarmPlanRequest *LCOPENAPI_INIT(DeviceAlarmPlanRequest);

typedef struct DeviceAlarmPlanResponse 
{
	LCOpenApiResponse base;

	struct DeviceAlarmPlanResponseData
	{
		
		/** define a list with struct of DeviceAlarmPlanResponseData_RulesElement */
		DECLARE_LIST(struct DeviceAlarmPlanResponseData_RulesElement
		{
			/** 重复周期 */
			CSTR period;
			/** [bool]是否有效(true:开;false:关) */
			BOOL enable;
			/** 开始时间 */
			CSTR beginTime;
			/** 结束时间 */
			CSTR endTime;
			/** [long]时间戳 */
			int64 timestamp;
		}) rules;
		/** 通道ID */
		CSTR channelId;
 
	} data;

} DeviceAlarmPlanResponse;

C_API DeviceAlarmPlanResponse *LCOPENAPI_INIT(DeviceAlarmPlanResponse);

#endif
