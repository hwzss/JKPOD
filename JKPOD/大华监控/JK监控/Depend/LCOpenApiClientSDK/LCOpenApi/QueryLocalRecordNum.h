/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: unknown, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_QueryLocalRecordNum_H_
#define _LC_OPENAPI_CLIENT_QueryLocalRecordNum_H_

#include "LCOpenApiClientSdk.h"

/** DESCRIPTION: 
查询某个设备本地的录像总数

 */

typedef struct QueryLocalRecordNumRequest 
{
	LCOpenApiRequest base;

	struct QueryLocalRecordNumRequestData
	{
		
		/** [cstr]All */
		#define _STATIC_QueryLocalRecordNumRequestData_type "All"
		CSTR type;
		/** [cstr]queryLocalRecordNum */
		#define _STATIC_QueryLocalRecordNumRequestData_method "queryLocalRecordNum"
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

} QueryLocalRecordNumRequest;

C_API QueryLocalRecordNumRequest *LCOPENAPI_INIT(QueryLocalRecordNumRequest);

typedef struct QueryLocalRecordNumResponse 
{
	LCOpenApiResponse base;

	struct QueryLocalRecordNumResponseData
	{
		
		/** [int]录像总数 */
		int recordNum;
 
	} data;

} QueryLocalRecordNumResponse;

C_API QueryLocalRecordNumResponse *LCOPENAPI_INIT(QueryLocalRecordNumResponse);

#endif
