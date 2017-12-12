/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: unknown, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_PassengerFlow_H_
#define _LC_OPENAPI_CLIENT_PassengerFlow_H_

#include "LCOpenApiClientSdk.h"

/** DESCRIPTION: 
人数统计查询
 */

typedef struct PassengerFlowRequest 
{
	LCOpenApiRequest base;

	struct PassengerFlowRequestData
	{
		
		/** 开始时间 */
		CSTR beginTime;
		/** 授权token(userToken或accessToken) */
		CSTR token;
		/** 粒度 */
		CSTR granularity;
		/** 结束时间 */
		CSTR endTime;
		/** 通道号 */
		CSTR channelId;
		/** [cstr]passengerFlow */
		#define _STATIC_PassengerFlowRequestData_method "passengerFlow"
		CSTR method;
		/** 设备序列号 */
		CSTR deviceId;

	} data;

} PassengerFlowRequest;

C_API PassengerFlowRequest *LCOPENAPI_INIT(PassengerFlowRequest);

typedef struct PassengerFlowResponse 
{
	LCOpenApiResponse base;

	struct PassengerFlowResponseData
	{
		
		/** [List]进入人数 */
		CSTR in;
		/** [int]查询到的记录总数 */
		int total;
		/** [List]离开人数 */
		CSTR out;
 
	} data;

} PassengerFlowResponse;

C_API PassengerFlowResponse *LCOPENAPI_INIT(PassengerFlowResponse);

#endif
