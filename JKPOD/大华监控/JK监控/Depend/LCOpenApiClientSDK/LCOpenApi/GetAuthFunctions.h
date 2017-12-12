/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: unknown, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_GetAuthFunctions_H_
#define _LC_OPENAPI_CLIENT_GetAuthFunctions_H_

#include "LCOpenApiClientSdk.h"

/** DESCRIPTION: 
获取授权列表
 */

typedef struct GetAuthFunctionsRequest 
{
	LCOpenApiRequest base;

	struct GetAuthFunctionsRequestData
	{
		
		/** [cstr]getAuthFunctions */
		#define _STATIC_GetAuthFunctionsRequestData_method "getAuthFunctions"
		CSTR method;
		/** 授权token(userToken或accessToken) */
		CSTR token;

	} data;

} GetAuthFunctionsRequest;

C_API GetAuthFunctionsRequest *LCOPENAPI_INIT(GetAuthFunctionsRequest);

typedef struct GetAuthFunctionsResponse 
{
	LCOpenApiResponse base;

	struct GetAuthFunctionsResponseData
	{
		
		/** define a list with struct of GetAuthFunctionsResponseData_AuthFunctionsElement */
		DECLARE_LIST(struct GetAuthFunctionsResponseData_AuthFunctionsElement
		{
			/** 权限标示 */
			CSTR function;
			/** 权限描述 */
			CSTR remark;
		}) authFunctions;
 
	} data;

} GetAuthFunctionsResponse;

C_API GetAuthFunctionsResponse *LCOPENAPI_INIT(GetAuthFunctionsResponse);

#endif
