/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: unknown, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_SetAllStorageStrategy_H_
#define _LC_OPENAPI_CLIENT_SetAllStorageStrategy_H_

#include "LCOpenApiClientSdk.h"

/** DESCRIPTION: 
设置3天免费云存储开或关
10003：开发模式下，此接口一天只能调用5次
其他的一些civil返回的错误码的封装

 */

typedef struct SetAllStorageStrategyRequest 
{
	LCOpenApiRequest base;

	struct SetAllStorageStrategyRequestData
	{
		
		/** [cstr]setAllStorageStrategy */
		#define _STATIC_SetAllStorageStrategyRequestData_method "setAllStorageStrategy"
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

} SetAllStorageStrategyRequest;

C_API SetAllStorageStrategyRequest *LCOPENAPI_INIT(SetAllStorageStrategyRequest);

typedef struct SetAllStorageStrategyResponse 
{
	LCOpenApiResponse base;

	struct SetAllStorageStrategyResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} SetAllStorageStrategyResponse;

C_API SetAllStorageStrategyResponse *LCOPENAPI_INIT(SetAllStorageStrategyResponse);

#endif
