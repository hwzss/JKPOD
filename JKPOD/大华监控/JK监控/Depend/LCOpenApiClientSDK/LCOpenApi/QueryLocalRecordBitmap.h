/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: unknown, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_QueryLocalRecordBitmap_H_
#define _LC_OPENAPI_CLIENT_QueryLocalRecordBitmap_H_

#include "LCOpenApiClientSdk.h"

/** DESCRIPTION: 
按月查询有录像的时间（以“天”为单位）
10003：开发模式下，此接口一天只能调用5次
其他的一些civil返回的错误码的封装

 */

typedef struct QueryLocalRecordBitmapRequest 
{
	LCOpenApiRequest base;

	struct QueryLocalRecordBitmapRequestData
	{
		
		/** [cstr]queryLocalRecordBitmap */
		#define _STATIC_QueryLocalRecordBitmapRequestData_method "queryLocalRecordBitmap"
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

} QueryLocalRecordBitmapRequest;

C_API QueryLocalRecordBitmapRequest *LCOPENAPI_INIT(QueryLocalRecordBitmapRequest);

typedef struct QueryLocalRecordBitmapResponse 
{
	LCOpenApiResponse base;

	struct QueryLocalRecordBitmapResponseData
	{
		
		/** 日掩码-1111100000111110000011111000001 */
		CSTR bitmap;
 
	} data;

} QueryLocalRecordBitmapResponse;

C_API QueryLocalRecordBitmapResponse *LCOPENAPI_INIT(QueryLocalRecordBitmapResponse);

#endif
