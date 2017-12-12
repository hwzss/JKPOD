/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: unknown, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_AddRole_H_
#define _LC_OPENAPI_CLIENT_AddRole_H_

#include "LCOpenApiClientSdk.h"

/** DESCRIPTION: 
对设备授权的角色进行管理

 */

typedef struct AddRoleRequest 
{
	LCOpenApiRequest base;

	struct AddRoleRequestData
	{
		
		/** 授权token(userToken或accessToken) */
		CSTR token;
		/** 授权名称,不能超过128个中文 */
		CSTR roleName;
		/** [cstr]addRole */
		#define _STATIC_AddRoleRequestData_method "addRole"
		CSTR method;
		/** 权限列表，以逗号分隔 */
		CSTR authFunctions;

	} data;

} AddRoleRequest;

C_API AddRoleRequest *LCOPENAPI_INIT(AddRoleRequest);

typedef struct AddRoleResponse 
{
	LCOpenApiResponse base;

	struct AddRoleResponseData
	{
		
		/** [long]角色Id */
		int64 roleId;
 
	} data;

} AddRoleResponse;

C_API AddRoleResponse *LCOPENAPI_INIT(AddRoleResponse);

#endif
