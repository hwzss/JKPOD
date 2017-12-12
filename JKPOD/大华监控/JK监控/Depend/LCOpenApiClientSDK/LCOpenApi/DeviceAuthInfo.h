/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: unknown, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_DeviceAuthInfo_H_
#define _LC_OPENAPI_CLIENT_DeviceAuthInfo_H_

#include "LCOpenApiClientSdk.h"

/** DESCRIPTION: 
获取某个设备某个通道号的授权信息
 */

typedef struct DeviceAuthInfoRequest 
{
	LCOpenApiRequest base;

	struct DeviceAuthInfoRequestData
	{
		
		/** [cstr]deviceAuthInfo */
		#define _STATIC_DeviceAuthInfoRequestData_method "deviceAuthInfo"
		CSTR method;
		/** 通道号 */
		CSTR channelId;
		/** 授权token(userToken或accessToken) */
		CSTR token;
		/** 设备Id */
		CSTR deviceId;

	} data;

} DeviceAuthInfoRequest;

C_API DeviceAuthInfoRequest *LCOPENAPI_INIT(DeviceAuthInfoRequest);

typedef struct DeviceAuthInfoResponse 
{
	LCOpenApiResponse base;

	struct DeviceAuthInfoResponseData
	{
		
		/** define a list with struct of DeviceAuthInfoResponseData_ShareInfosElement */
		DECLARE_LIST(struct DeviceAuthInfoResponseData_ShareInfosElement
		{
			/** 被授权的手机号码 */
			CSTR phoneNumber;
			/** 授权的功能，可选项见说明，用逗号分隔 */
			CSTR functions;
		}) shareInfos;
		/** [int]剩余分享和授权的数量 */
		int leftShareCount;
		/** [int]允许分享数量, 999表示不限制,999表示为vip */
		int allowShareCount;
 
	} data;

} DeviceAuthInfoResponse;

C_API DeviceAuthInfoResponse *LCOPENAPI_INIT(DeviceAuthInfoResponse);

#endif
