/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: unknown, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_QueryCloudRecordCallNum_H_
#define _LC_OPENAPI_CLIENT_QueryCloudRecordCallNum_H_

#include "LCOpenApiClientSdk.h"

/** DESCRIPTION: 
查询开发者开通云存储套餐策略接口的剩余调用次数

 */

typedef struct QueryCloudRecordCallNumRequest 
{
	LCOpenApiRequest base;

	struct QueryCloudRecordCallNumRequestData
	{
		
		/** [cstr]queryCloudRecordCallNum */
		#define _STATIC_QueryCloudRecordCallNumRequestData_method "queryCloudRecordCallNum"
		CSTR method;
		/** 授权token(userToken或accessToken) */
		CSTR token;
		/** [long]云存储套餐ID */
		int64 strategyId;

	} data;

} QueryCloudRecordCallNumRequest;

C_API QueryCloudRecordCallNumRequest *LCOPENAPI_INIT(QueryCloudRecordCallNumRequest);

typedef struct QueryCloudRecordCallNumResponse 
{
	LCOpenApiResponse base;

	struct QueryCloudRecordCallNumResponseData
	{
		
		/** [int]录像总数 */
		int callNum;
 
	} data;

} QueryCloudRecordCallNumResponse;

C_API QueryCloudRecordCallNumResponse *LCOPENAPI_INIT(QueryCloudRecordCallNumResponse);

#endif
