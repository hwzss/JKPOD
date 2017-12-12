/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: unknown, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_GetCloudRecords_H_
#define _LC_OPENAPI_CLIENT_GetCloudRecords_H_

#include "LCOpenApiClientSdk.h"

/** DESCRIPTION: 
按条件查询所有录像记录(倒序展示)

 */

typedef struct GetCloudRecordsRequest 
{
	LCOpenApiRequest base;

	struct GetCloudRecordsRequestData
	{
		
		/** [long]上次取到的最后录像的ID */
		int64 nextRecordId;
		/** [cstr]getCloudRecords */
		#define _STATIC_GetCloudRecordsRequestData_method "getCloudRecords"
		CSTR method;
		/** 授权token(userToken或accessToken) */
		CSTR token;
		/** 开始时间 */
		CSTR beginTime;
		/** 结束时间 */
		CSTR endTime;
		/** 通道号 */
		CSTR channelId;
		/** [int]分页查询的数量 */
		int count;
		/** 设备序列号 */
		CSTR deviceId;

	} data;

} GetCloudRecordsRequest;

C_API GetCloudRecordsRequest *LCOPENAPI_INIT(GetCloudRecordsRequest);

typedef struct GetCloudRecordsResponse 
{
	LCOpenApiResponse base;

	struct GetCloudRecordsResponseData
	{
		
		/** define a list with struct of GetCloudRecordsResponseData_RecordsElement */
		DECLARE_LIST(struct GetCloudRecordsResponseData_RecordsElement
		{
			/** 缩略图Url */
			CSTR thumbUrl;
			/** [long]云录像大小，单位byte */
			int64 size;
			/** 结束时间 */
			CSTR endTime;
			/** 开始时间 */
			CSTR beginTime;
			/** [long]录像Id */
			int64 recordId;
			/** 通道号 */
			CSTR channelId;
			/** [int]加密模式, 0表示默认加密模式, 1表示用户加密模式 */
			int encryptMode;
			/** 设备序列号 */
			CSTR deviceId;
		}) records;
 
	} data;

} GetCloudRecordsResponse;

C_API GetCloudRecordsResponse *LCOPENAPI_INIT(GetCloudRecordsResponse);

#endif
