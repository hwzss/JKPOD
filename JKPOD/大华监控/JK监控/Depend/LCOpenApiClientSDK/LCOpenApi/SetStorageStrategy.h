/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: unknown, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_SetStorageStrategy_H_
#define _LC_OPENAPI_CLIENT_SetStorageStrategy_H_

#include "LCOpenApiClientSdk.h"

/** DESCRIPTION: 
设置3天免费云存储开或关
10003：开发模式下，此接口一天只能调用5次
其他的一些civil返回的错误码的封装

 */

typedef struct SetStorageStrategyRequest 
{
	LCOpenApiRequest base;

	struct SetStorageStrategyRequestData
	{
		
		/** [cstr]setStorageStrategy */
		#define _STATIC_SetStorageStrategyRequestData_method "setStorageStrategy"
		CSTR method;
		/** 状态，1表示开启，0表示关闭 */
		CSTR status;
		/** 通道ID */
		CSTR channelId;
		/** 授权token(userToken或accessToken) */
		CSTR token;
		/** 设备序列号,例2342sdfl-df323-23 */
		CSTR deviceId;

	} data;

} SetStorageStrategyRequest;

C_API SetStorageStrategyRequest *LCOPENAPI_INIT(SetStorageStrategyRequest);

typedef struct SetStorageStrategyResponse 
{
	LCOpenApiResponse base;

	struct SetStorageStrategyResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} SetStorageStrategyResponse;

C_API SetStorageStrategyResponse *LCOPENAPI_INIT(SetStorageStrategyResponse);

#endif
