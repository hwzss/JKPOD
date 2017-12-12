/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: unknown, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_GroupList_H_
#define _LC_OPENAPI_CLIENT_GroupList_H_

#include "LCOpenApiClientSdk.h"

/** DESCRIPTION: 
分页获取用户的设备分组列表(最顶层的分组)

 */

typedef struct GroupListRequest 
{
	LCOpenApiRequest base;

	struct GroupListRequestData
	{
		
		/** 第几条到第几条,数字取值范围为：[1,N](N为正整数，且后者＞前者),单次查询上限50 */
		CSTR queryRange;
		/** [cstr]groupList */
		#define _STATIC_GroupListRequestData_method "groupList"
		CSTR method;
		/** 授权token(userToken或accessToken) */
		CSTR token;

	} data;

} GroupListRequest;

C_API GroupListRequest *LCOPENAPI_INIT(GroupListRequest);

typedef struct GroupListResponse 
{
	LCOpenApiResponse base;

	struct GroupListResponseData
	{
		
		/** define a list with struct of GroupListResponseData_GroupsElement */
		DECLARE_LIST(struct GroupListResponseData_GroupsElement
		{
			/** [long]分组的最后修改unix时间戳，精确到秒 */
			int64 ts;
			/** 分组名称 */
			CSTR groupName;
			/** [long]分组id */
			int64 groupId;
		}) groups;
 
	} data;

} GroupListResponse;

C_API GroupListResponse *LCOPENAPI_INIT(GroupListResponse);

#endif
