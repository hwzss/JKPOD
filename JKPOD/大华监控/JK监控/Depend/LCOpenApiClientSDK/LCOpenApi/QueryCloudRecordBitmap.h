/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: unknown, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_QueryCloudRecordBitmap_H_
#define _LC_OPENAPI_CLIENT_QueryCloudRecordBitmap_H_

#include "LCOpenApiClientSdk.h"

/** DESCRIPTION: 
按月查询有录像的时间（以“天”为单位）
10003：开发模式下，此接口一天只能调用5次
其他的一些civil返回的错误码的封装

 */

typedef struct QueryCloudRecordBitmapRequest 
{
	LCOpenApiRequest base;

	struct QueryCloudRecordBitmapRequestData
	{
		
		/** [cstr]queryCloudRecordBitmap */
		#define _STATIC_QueryCloudRecordBitmapRequestData_method "queryCloudRecordBitmap"
		CSTR method;
		/** [int]月 */
		int month;
		/** 授权token(userToken或accessToken) */
		CSTR token;
		/** 通道号或通道的设备ID */
		CSTR channelId;
		/** [int]年 */
		int year;
		/** 设备序列号,例2342sdfl-df323-23 */
		CSTR deviceId;

	} data;

} QueryCloudRecordBitmapRequest;

C_API QueryCloudRecordBitmapRequest *LCOPENAPI_INIT(QueryCloudRecordBitmapRequest);

typedef struct QueryCloudRecordBitmapResponse 
{
	LCOpenApiResponse base;

	struct QueryCloudRecordBitmapResponseData
	{
		
		/** 日掩码-1111100000111110000011111000001 */
		CSTR bitmap;
 
	} data;

} QueryCloudRecordBitmapResponse;

C_API QueryCloudRecordBitmapResponse *LCOPENAPI_INIT(QueryCloudRecordBitmapResponse);

#endif
