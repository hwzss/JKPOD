/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: unknown, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_ModifyDeviceAlarmPlan_H_
#define _LC_OPENAPI_CLIENT_ModifyDeviceAlarmPlan_H_

#include "LCOpenApiClientSdk.h"

/** DESCRIPTION: 
配置设备通道的动检计划

 */

typedef struct ModifyDeviceAlarmPlanRequest 
{
	LCOpenApiRequest base;

	struct ModifyDeviceAlarmPlanRequestData
	{
		
		/** 参考开放平台Wiki对应modifyDeviceAlarmPlan方法的rules规则 */
		CSTR rules;
		/** [cstr]modifyDeviceAlarmPlan */
		#define _STATIC_ModifyDeviceAlarmPlanRequestData_method "modifyDeviceAlarmPlan"
		CSTR method;
		/** 通道ID */
		CSTR channelId;
		/** 授权token(userToken或accessToken) */
		CSTR token;
		/** 设备序列号,例2342sdfl-df323-23 */
		CSTR deviceId;

	} data;

} ModifyDeviceAlarmPlanRequest;

C_API ModifyDeviceAlarmPlanRequest *LCOPENAPI_INIT(ModifyDeviceAlarmPlanRequest);

typedef struct ModifyDeviceAlarmPlanResponse 
{
	LCOpenApiResponse base;

	struct ModifyDeviceAlarmPlanResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} ModifyDeviceAlarmPlanResponse;

C_API ModifyDeviceAlarmPlanResponse *LCOPENAPI_INIT(ModifyDeviceAlarmPlanResponse);

#endif
