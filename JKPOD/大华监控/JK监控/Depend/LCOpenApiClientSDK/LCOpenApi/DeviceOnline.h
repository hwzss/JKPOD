/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: unknown, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_DeviceOnline_H_
#define _LC_OPENAPI_CLIENT_DeviceOnline_H_

#include "LCOpenApiClientSdk.h"

/** DESCRIPTION: 
设备在线状态

 */

typedef struct DeviceOnlineRequest 
{
	LCOpenApiRequest base;

	struct DeviceOnlineRequestData
	{
		
		/** 授权token(userToken或accessToken) */
		CSTR token;
		/** [cstr]deviceOnline */
		#define _STATIC_DeviceOnlineRequestData_method "deviceOnline"
		CSTR method;
		/** 设备序列号,例2342sdfl-df323-23 */
		CSTR deviceId;

	} data;

} DeviceOnlineRequest;

C_API DeviceOnlineRequest *LCOPENAPI_INIT(DeviceOnlineRequest);

typedef struct DeviceOnlineResponse 
{
	LCOpenApiResponse base;

	struct DeviceOnlineResponseData
	{
		
		/** define a list with struct of DeviceOnlineResponseData_ChannelsElement */
		DECLARE_LIST(struct DeviceOnlineResponseData_ChannelsElement
		{
			/** 0-表示不在线1-表示在线 */
			CSTR onLine;
			/** [int]通道号 */
			int channelId;
		}) channels;
		/** 0-表示不在线1-表示在线 */
		CSTR onLine;
		/** 设备序列号,例2342sdfl-df323-23 */
		CSTR deviceId;
 
	} data;

} DeviceOnlineResponse;

C_API DeviceOnlineResponse *LCOPENAPI_INIT(DeviceOnlineResponse);

#endif
