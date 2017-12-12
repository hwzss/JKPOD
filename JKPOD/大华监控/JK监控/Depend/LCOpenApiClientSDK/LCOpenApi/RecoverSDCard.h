/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: unknown, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_RecoverSDCard_H_
#define _LC_OPENAPI_CLIENT_RecoverSDCard_H_

#include "LCOpenApiClientSdk.h"

/** DESCRIPTION: 
请求初始化SD卡

 */

typedef struct RecoverSDCardRequest 
{
	LCOpenApiRequest base;

	struct RecoverSDCardRequestData
	{
		
		/** [cstr]recoverSDCard */
		#define _STATIC_RecoverSDCardRequestData_method "recoverSDCard"
		CSTR method;
		/** 通道号 */
		CSTR channelId;
		/** 授权token(userToken或accessToken) */
		CSTR token;
		/** 设备序列号 */
		CSTR deviceId;

	} data;

} RecoverSDCardRequest;

C_API RecoverSDCardRequest *LCOPENAPI_INIT(RecoverSDCardRequest);

typedef struct RecoverSDCardResponse 
{
	LCOpenApiResponse base;

	struct RecoverSDCardResponseData
	{
		
		/** 结果 */
		CSTR result;
 
	} data;

} RecoverSDCardResponse;

C_API RecoverSDCardResponse *LCOPENAPI_INIT(RecoverSDCardResponse);

#endif
