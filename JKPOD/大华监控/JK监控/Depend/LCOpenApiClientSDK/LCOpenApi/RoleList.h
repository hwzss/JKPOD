/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: unknown, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_RoleList_H_
#define _LC_OPENAPI_CLIENT_RoleList_H_

#include "LCOpenApiClientSdk.h"

/** DESCRIPTION: 
获取角色列表
 */

typedef struct RoleListRequest 
{
	LCOpenApiRequest base;

	struct RoleListRequestData
	{
		
		/** [int]需要查的最大条数，不大于50 */
		int count;
		/** [long]下一个角色id,若要从最新开始查，填-1 */
		int64 nextRoleId;
		/** 授权token(userToken或accessToken) */
		CSTR token;
		/** [cstr]roleList */
		#define _STATIC_RoleListRequestData_method "roleList"
		CSTR method;

	} data;

} RoleListRequest;

C_API RoleListRequest *LCOPENAPI_INIT(RoleListRequest);

typedef struct RoleListResponse 
{
	LCOpenApiResponse base;

	struct RoleListResponseData
	{
		
		/** define a list with struct of RoleListResponseData_RolesElement */
		DECLARE_LIST(struct RoleListResponseData_RolesElement
		{
			/** [int]是否为默认角色：0 - 普通角色，1 - 默认角色 */
			int isDefault;
			/** [long]角色Id */
			int64 roleId;
			/** 角色名称 */
			CSTR roleName;
			/** 权限列表 */
			CSTR authFunctions;
		}) roles;
		/** [long] */
		int64 nextRoleId;
 
	} data;

} RoleListResponse;

C_API RoleListResponse *LCOPENAPI_INIT(RoleListResponse);

#endif
