/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: unknown, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_SetUserAuthTager_H_
#define _LC_OPENAPI_CLIENT_SetUserAuthTager_H_

#include "LCOpenApiClientSdk.h"

/** DESCRIPTION: 
设置授权对象(单一设备授权)
 */

typedef struct SetUserAuthTagerRequest 
{
	LCOpenApiRequest base;

	struct SetUserAuthTagerRequestData
	{
		
		/** [long]角色ID */
		int64 roleId;
		/** [cstr]setUserAuthTager */
		#define _STATIC_SetUserAuthTagerRequestData_method "setUserAuthTager"
		CSTR method;
		/** 被授权的手机号 */
		CSTR userPhone;
		/** 通道号 */
		CSTR channelId;
		/** 授权token(userToken或accessToken) */
		CSTR token;
		/** 设备序列号 */
		CSTR deviceId;

	} data;

} SetUserAuthTagerRequest;

C_API SetUserAuthTagerRequest *LCOPENAPI_INIT(SetUserAuthTagerRequest);

typedef struct SetUserAuthTagerResponse 
{
	LCOpenApiResponse base;

	struct SetUserAuthTagerResponseData
	{
		
		/** [long]授权Id */
		int64 authId;
 
	} data;

} SetUserAuthTagerResponse;

C_API SetUserAuthTagerResponse *LCOPENAPI_INIT(SetUserAuthTagerResponse);

#endif
