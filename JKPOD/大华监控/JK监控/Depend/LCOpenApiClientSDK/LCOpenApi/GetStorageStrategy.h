/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: unknown, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_GetStorageStrategy_H_
#define _LC_OPENAPI_CLIENT_GetStorageStrategy_H_

#include "LCOpenApiClientSdk.h"

/** DESCRIPTION: 
获取云存储套餐策略,如开通多个，获取最早开通、未到期的云存储

 */

typedef struct GetStorageStrategyRequest 
{
	LCOpenApiRequest base;

	struct GetStorageStrategyRequestData
	{
		
		/** [cstr]getStorageStrategy */
		#define _STATIC_GetStorageStrategyRequestData_method "getStorageStrategy"
		CSTR method;
		/** 通道号 */
		CSTR channelId;
		/** 授权token(userToken或accessToken) */
		CSTR token;
		/** 设备序列号 */
		CSTR deviceId;

	} data;

} GetStorageStrategyRequest;

C_API GetStorageStrategyRequest *LCOPENAPI_INIT(GetStorageStrategyRequest);

typedef struct GetStorageStrategyResponse 
{
	LCOpenApiResponse base;

	struct GetStorageStrategyResponseData
	{
		
		/** [int]套餐状态 -1-未开通 0-过期 1-使用中 2-暂停 */
		int strategyStatus;
		/** [int]套餐ID */
		int strategyId;
		/** 套餐名称 */
		CSTR name;
		/** [bool]是否有默认套餐 */
		BOOL hasDefault;
 
	} data;

} GetStorageStrategyResponse;

C_API GetStorageStrategyResponse *LCOPENAPI_INIT(GetStorageStrategyResponse);

#endif
