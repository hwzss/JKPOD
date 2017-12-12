/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: unknown, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_FrameReverseStatus_H_
#define _LC_OPENAPI_CLIENT_FrameReverseStatus_H_

#include "LCOpenApiClientSdk.h"

/** DESCRIPTION: 
获取设备翻转状态

 */

typedef struct FrameReverseStatusRequest 
{
	LCOpenApiRequest base;

	struct FrameReverseStatusRequestData
	{
		
		/** 授权token(userToken或accessToken) */
		CSTR token;
		/** 通道ID */
		CSTR channelId;
		/** [cstr]frameReverseStatus */
		#define _STATIC_FrameReverseStatusRequestData_method "frameReverseStatus"
		CSTR method;
		/** 设备序列号,例2342sdfl-df323-23 */
		CSTR deviceId;

	} data;

} FrameReverseStatusRequest;

C_API FrameReverseStatusRequest *LCOPENAPI_INIT(FrameReverseStatusRequest);

typedef struct FrameReverseStatusResponse 
{
	LCOpenApiResponse base;

	struct FrameReverseStatusResponseData
	{
		
		/** normal或reverse */
		CSTR direction;
 
	} data;

} FrameReverseStatusResponse;

C_API FrameReverseStatusResponse *LCOPENAPI_INIT(FrameReverseStatusResponse);

#endif
