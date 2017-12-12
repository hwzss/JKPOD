/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: unknown, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_DeleteUserAuthTager_H_
#define _LC_OPENAPI_CLIENT_DeleteUserAuthTager_H_

#include "LCOpenApiClientSdk.h"

/** DESCRIPTION: 
删除授权对象
 */

typedef struct DeleteUserAuthTagerRequest 
{
	LCOpenApiRequest base;

	struct DeleteUserAuthTagerRequestData
	{
		
		/** [long]授权ID */
		int64 authId;
		/** 被授权的手机号 */
		CSTR userPhone;
		/** 授权token(userToken或accessToken) */
		CSTR token;
		/** [cstr]deleteUserAuthTager */
		#define _STATIC_DeleteUserAuthTagerRequestData_method "deleteUserAuthTager"
		CSTR method;

	} data;

} DeleteUserAuthTagerRequest;

C_API DeleteUserAuthTagerRequest *LCOPENAPI_INIT(DeleteUserAuthTagerRequest);

typedef struct DeleteUserAuthTagerResponse 
{
	LCOpenApiResponse base;

	struct DeleteUserAuthTagerResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} DeleteUserAuthTagerResponse;

C_API DeleteUserAuthTagerResponse *LCOPENAPI_INIT(DeleteUserAuthTagerResponse);

#endif
