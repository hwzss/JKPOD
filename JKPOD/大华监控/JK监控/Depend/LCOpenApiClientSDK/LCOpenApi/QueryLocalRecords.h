/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: unknown, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_QueryLocalRecords_H_
#define _LC_OPENAPI_CLIENT_QueryLocalRecords_H_

#include "LCOpenApiClientSdk.h"

/** DESCRIPTION: 
按照开始和结束时间查询录像片段

 */

typedef struct QueryLocalRecordsRequest 
{
	LCOpenApiRequest base;

	struct QueryLocalRecordsRequestData
	{
		
		/** 从第几条到第几条,单次查询上限100,1-100表示第1条到第100条,包含100,云录像查询相同 */
		CSTR queryRange;
		/** [cstr]All */
		#define _STATIC_QueryLocalRecordsRequestData_type "All"
		CSTR type;
		/** [cstr]queryLocalRecords */
		#define _STATIC_QueryLocalRecordsRequestData_method "queryLocalRecords"
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

} QueryLocalRecordsRequest;

C_API QueryLocalRecordsRequest *LCOPENAPI_INIT(QueryLocalRecordsRequest);

typedef struct QueryLocalRecordsResponse 
{
	LCOpenApiResponse base;

	struct QueryLocalRecordsResponseData
	{
		
		/** define a list with struct of QueryLocalRecordsResponseData_RecordsElement */
		DECLARE_LIST(struct QueryLocalRecordsResponseData_RecordsElement
		{
			/** 类型，Manual、Event、All */
			CSTR type;
			/** 结束时间，如2010-05-25 23:59:59 */
			CSTR endTime;
			/** 录像文件名 */
			CSTR recordId;
			/** 开始时间，如2010-05-25 00:00:00 */
			CSTR beginTime;
			/** 通道号或通道的设备ID */
			CSTR channelID;
			/** [int]录像文件长度 */
			int fileLength;
		}) records;
 
	} data;

} QueryLocalRecordsResponse;

C_API QueryLocalRecordsResponse *LCOPENAPI_INIT(QueryLocalRecordsResponse);

#endif
