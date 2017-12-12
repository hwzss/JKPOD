/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: unknown, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_DeleteCloudRecords_H_
#define _LC_OPENAPI_CLIENT_DeleteCloudRecords_H_

#include "LCOpenApiClientSdk.h"

/** DESCRIPTION: 
删除云录像片段

 */

typedef struct DeleteCloudRecordsRequest 
{
	LCOpenApiRequest base;

	struct DeleteCloudRecordsRequestData
	{
		
		/** [long]云录像Id */
		int64 recordId;
		/** 授权token(userToken或accessToken) */
		CSTR token;
		/** [cstr]deleteCloudRecords */
		#define _STATIC_DeleteCloudRecordsRequestData_method "deleteCloudRecords"
		CSTR method;

	} data;

} DeleteCloudRecordsRequest;

C_API DeleteCloudRecordsRequest *LCOPENAPI_INIT(DeleteCloudRecordsRequest);

typedef struct DeleteCloudRecordsResponse 
{
	LCOpenApiResponse base;

	struct DeleteCloudRecordsResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} DeleteCloudRecordsResponse;

C_API DeleteCloudRecordsResponse *LCOPENAPI_INIT(DeleteCloudRecordsResponse);

#endif
