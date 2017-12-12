/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: unknown, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_OpenCloudRecord_H_
#define _LC_OPENAPI_CLIENT_OpenCloudRecord_H_

#include "LCOpenApiClientSdk.h"

/** DESCRIPTION: 
开通云存储

 */

typedef struct OpenCloudRecordRequest 
{
	LCOpenApiRequest base;

	struct OpenCloudRecordRequestData
	{
		
		/** 授权token(userToken或accessToken) */
		CSTR token;
		/** [long]云存储套餐ID */
		int64 strategyId;
		/** 通道号 */
		CSTR channelId;
		/** [cstr]openCloudRecord */
		#define _STATIC_OpenCloudRecordRequestData_method "openCloudRecord"
		CSTR method;
		/** 设备序列号 */
		CSTR deviceId;

	} data;

} OpenCloudRecordRequest;

C_API OpenCloudRecordRequest *LCOPENAPI_INIT(OpenCloudRecordRequest);

typedef struct OpenCloudRecordResponse 
{
	LCOpenApiResponse base;

	struct OpenCloudRecordResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} OpenCloudRecordResponse;

C_API OpenCloudRecordResponse *LCOPENAPI_INIT(OpenCloudRecordResponse);

#endif
