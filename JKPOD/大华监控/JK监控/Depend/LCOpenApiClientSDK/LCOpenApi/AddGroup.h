/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: unknown, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_AddGroup_H_
#define _LC_OPENAPI_CLIENT_AddGroup_H_

#include "LCOpenApiClientSdk.h"

/** DESCRIPTION: 
添加分组

 */

typedef struct AddGroupRequest 
{
	LCOpenApiRequest base;

	struct AddGroupRequestData
	{
		
		/** [long]父分组Id */
		int64 parentGroupId;
		/** 授权token(userToken或accessToken) */
		CSTR token;
		/** 分组名称 */
		CSTR groupName;
		/** [cstr]addGroup */
		#define _STATIC_AddGroupRequestData_method "addGroup"
		CSTR method;

	} data;

} AddGroupRequest;

C_API AddGroupRequest *LCOPENAPI_INIT(AddGroupRequest);

typedef struct AddGroupResponse 
{
	LCOpenApiResponse base;

	struct AddGroupResponseData
	{
		
		/** [long]分组id */
		int64 groupId;
 
	} data;

} AddGroupResponse;

C_API AddGroupResponse *LCOPENAPI_INIT(AddGroupResponse);

#endif
