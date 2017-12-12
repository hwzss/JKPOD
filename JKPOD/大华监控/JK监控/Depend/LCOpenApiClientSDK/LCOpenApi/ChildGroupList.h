/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: unknown, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_ChildGroupList_H_
#define _LC_OPENAPI_CLIENT_ChildGroupList_H_

#include "LCOpenApiClientSdk.h"

/** DESCRIPTION: 
分页获取该分组下面的子分组

 */

typedef struct ChildGroupListRequest 
{
	LCOpenApiRequest base;

	struct ChildGroupListRequestData
	{
		
		/** 分页取值范围,一次最多获取50条，格式为1-30 */
		CSTR queryRange;
		/** 授权token(userToken或accessToken) */
		CSTR token;
		/** [cstr]childGroupList */
		#define _STATIC_ChildGroupListRequestData_method "childGroupList"
		CSTR method;
		/** [long]分组id */
		int64 groupId;

	} data;

} ChildGroupListRequest;

C_API ChildGroupListRequest *LCOPENAPI_INIT(ChildGroupListRequest);

typedef struct ChildGroupListResponse 
{
	LCOpenApiResponse base;

	struct ChildGroupListResponseData
	{
		
		/** define a list with struct of ChildGroupListResponseData_GroupsElement */
		DECLARE_LIST(struct ChildGroupListResponseData_GroupsElement
		{
			/** [long]分组的最后修改unix时间戳，精确到秒 */
			int64 ts;
			/** 2,分组层级 */
			CSTR level;
			/** 分组名称 */
			CSTR groupName;
			/** [long]分组id */
			int64 groupId;
		}) groups;
 
	} data;

} ChildGroupListResponse;

C_API ChildGroupListResponse *LCOPENAPI_INIT(ChildGroupListResponse);

#endif
