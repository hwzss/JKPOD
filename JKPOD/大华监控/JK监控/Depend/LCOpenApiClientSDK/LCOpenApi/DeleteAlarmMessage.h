/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: unknown, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_DeleteAlarmMessage_H_
#define _LC_OPENAPI_CLIENT_DeleteAlarmMessage_H_

#include "LCOpenApiClientSdk.h"

/** DESCRIPTION: 
删除某个用户的某个报警

 */

typedef struct DeleteAlarmMessageRequest 
{
	LCOpenApiRequest base;

	struct DeleteAlarmMessageRequestData
	{
		
		/** 授权token(userToken或accessToken) */
		CSTR token;
		/** [cstr]deleteAlarmMessage */
		#define _STATIC_DeleteAlarmMessageRequestData_method "deleteAlarmMessage"
		CSTR method;
		/** [long]消息ID */
		int64 indexId;

	} data;

} DeleteAlarmMessageRequest;

C_API DeleteAlarmMessageRequest *LCOPENAPI_INIT(DeleteAlarmMessageRequest);

typedef struct DeleteAlarmMessageResponse 
{
	LCOpenApiResponse base;

	struct DeleteAlarmMessageResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} DeleteAlarmMessageResponse;

C_API DeleteAlarmMessageResponse *LCOPENAPI_INIT(DeleteAlarmMessageResponse);

#endif
