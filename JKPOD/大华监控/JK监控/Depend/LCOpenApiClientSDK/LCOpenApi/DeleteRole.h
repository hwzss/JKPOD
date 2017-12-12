/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: unknown, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_DeleteRole_H_
#define _LC_OPENAPI_CLIENT_DeleteRole_H_

#include "LCOpenApiClientSdk.h"

/** DESCRIPTION: 
删除用户角色
 */

typedef struct DeleteRoleRequest 
{
	LCOpenApiRequest base;

	struct DeleteRoleRequestData
	{
		
		/** [long]角色Id */
		int64 roleId;
		/** 授权token(userToken或accessToken) */
		CSTR token;
		/** [cstr]deleteRole */
		#define _STATIC_DeleteRoleRequestData_method "deleteRole"
		CSTR method;

	} data;

} DeleteRoleRequest;

C_API DeleteRoleRequest *LCOPENAPI_INIT(DeleteRoleRequest);

typedef struct DeleteRoleResponse 
{
	LCOpenApiResponse base;

	struct DeleteRoleResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} DeleteRoleResponse;

C_API DeleteRoleResponse *LCOPENAPI_INIT(DeleteRoleResponse);

#endif
