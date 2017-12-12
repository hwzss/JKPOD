/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: unknown, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_ModifyFrameReverseStatus_H_
#define _LC_OPENAPI_CLIENT_ModifyFrameReverseStatus_H_

#include "LCOpenApiClientSdk.h"

/** DESCRIPTION: 
设置设备翻转状态

 */

typedef struct ModifyFrameReverseStatusRequest 
{
	LCOpenApiRequest base;

	struct ModifyFrameReverseStatusRequestData
	{
		
		/** normal或reverse */
		CSTR direction;
		/** [cstr]modifyFrameReverseStatus */
		#define _STATIC_ModifyFrameReverseStatusRequestData_method "modifyFrameReverseStatus"
		CSTR method;
		/** 通道ID */
		CSTR channelId;
		/** 授权token(userToken或accessToken) */
		CSTR token;
		/** 设备序列号,例2342sdfl-df323-23 */
		CSTR deviceId;

	} data;

} ModifyFrameReverseStatusRequest;

C_API ModifyFrameReverseStatusRequest *LCOPENAPI_INIT(ModifyFrameReverseStatusRequest);

typedef struct ModifyFrameReverseStatusResponse 
{
	LCOpenApiResponse base;

	struct ModifyFrameReverseStatusResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} ModifyFrameReverseStatusResponse;

C_API ModifyFrameReverseStatusResponse *LCOPENAPI_INIT(ModifyFrameReverseStatusResponse);

#endif
