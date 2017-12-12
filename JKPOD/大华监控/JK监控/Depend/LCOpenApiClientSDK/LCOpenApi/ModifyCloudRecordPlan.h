/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: unknown, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_ModifyCloudRecordPlan_H_
#define _LC_OPENAPI_CLIENT_ModifyCloudRecordPlan_H_

#include "LCOpenApiClientSdk.h"

/** DESCRIPTION: 
修改设备通道的云录像存储计划
 */

typedef struct ModifyCloudRecordPlanRequest 
{
	LCOpenApiRequest base;

	struct ModifyCloudRecordPlanRequestData
	{
		
		/** 参考开放平台Wiki对应modifyCloudRecordPlan方法的rules规则 */
		CSTR rules;
		/** 授权token(userToken或accessToken) */
		CSTR token;
		/** 通道号 */
		CSTR channelId;
		/** [cstr]modifyCloudRecordPlan */
		#define _STATIC_ModifyCloudRecordPlanRequestData_method "modifyCloudRecordPlan"
		CSTR method;
		/** 设备序列号 */
		CSTR deviceId;

	} data;

} ModifyCloudRecordPlanRequest;

C_API ModifyCloudRecordPlanRequest *LCOPENAPI_INIT(ModifyCloudRecordPlanRequest);

typedef struct ModifyCloudRecordPlanResponse 
{
	LCOpenApiResponse base;

	struct ModifyCloudRecordPlanResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} ModifyCloudRecordPlanResponse;

C_API ModifyCloudRecordPlanResponse *LCOPENAPI_INIT(ModifyCloudRecordPlanResponse);

#endif
