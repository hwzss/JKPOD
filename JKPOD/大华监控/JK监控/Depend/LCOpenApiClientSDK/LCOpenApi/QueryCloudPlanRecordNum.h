/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: unknown, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_QueryCloudPlanRecordNum_H_
#define _LC_OPENAPI_CLIENT_QueryCloudPlanRecordNum_H_

#include "LCOpenApiClientSdk.h"

/** DESCRIPTION: 
按月查询有录像的时间总数（以“天”为单位）

 */

typedef struct QueryCloudPlanRecordNumRequest 
{
	LCOpenApiRequest base;

	struct QueryCloudPlanRecordNumRequestData
	{
		
		/** [cstr]queryCloudPlanRecordNum */
		#define _STATIC_QueryCloudPlanRecordNumRequestData_method "queryCloudPlanRecordNum"
		CSTR method;
		/** 授权token(userToken或accessToken) */
		CSTR token;
		/** 结束时间，如2010-05-25 23:59:59 */
		CSTR endTime;
		/** 通道号或通道的设备ID */
		CSTR channelId;
		/** 开始时间，如2010-05-25 00:00:00 */
		CSTR beginTime;
		/** 设备序列号,例2342sdfl-df323-23 */
		CSTR deviceId;

	} data;

} QueryCloudPlanRecordNumRequest;

C_API QueryCloudPlanRecordNumRequest *LCOPENAPI_INIT(QueryCloudPlanRecordNumRequest);

typedef struct QueryCloudPlanRecordNumResponse 
{
	LCOpenApiResponse base;

	struct QueryCloudPlanRecordNumResponseData
	{
		
		/** [int]录像总数 */
		int recordNum;
 
	} data;

} QueryCloudPlanRecordNumResponse;

C_API QueryCloudPlanRecordNumResponse *LCOPENAPI_INIT(QueryCloudPlanRecordNumResponse);

#endif
