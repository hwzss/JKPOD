/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: unknown, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_DeleteGroup_H_
#define _LC_OPENAPI_CLIENT_DeleteGroup_H_

#include "LCOpenApiClientSdk.h"

/** DESCRIPTION: 
用户删除分组

 */

typedef struct DeleteGroupRequest 
{
	LCOpenApiRequest base;

	struct DeleteGroupRequestData
	{
		
		/** 授权token(userToken或accessToken) */
		CSTR token;
		/** [cstr]deleteGroup */
		#define _STATIC_DeleteGroupRequestData_method "deleteGroup"
		CSTR method;
		/** [long]分组Id */
		int64 groupId;

	} data;

} DeleteGroupRequest;

C_API DeleteGroupRequest *LCOPENAPI_INIT(DeleteGroupRequest);

typedef struct DeleteGroupResponse 
{
	LCOpenApiResponse base;

	struct DeleteGroupResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} DeleteGroupResponse;

C_API DeleteGroupResponse *LCOPENAPI_INIT(DeleteGroupResponse);

#endif
