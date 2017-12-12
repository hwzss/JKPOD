/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: unknown, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_UnBindDevice_H_
#define _LC_OPENAPI_CLIENT_UnBindDevice_H_

#include "LCOpenApiClientSdk.h"

/** DESCRIPTION: 
设备解绑
处理设备解绑不成功各种分支逻辑，根据civil返回的错误码来处理。
错误码:
10003：开发模式下，此接口一天只能调用5次
其他的一些civil返回的错误码的封装

 */

typedef struct UnBindDeviceRequest 
{
	LCOpenApiRequest base;

	struct UnBindDeviceRequestData
	{
		
		/** 授权token(userToken或accessToken) */
		CSTR token;
		/** [cstr]unBindDevice */
		#define _STATIC_UnBindDeviceRequestData_method "unBindDevice"
		CSTR method;
		/** 设备序列号 */
		CSTR deviceId;

	} data;

} UnBindDeviceRequest;

C_API UnBindDeviceRequest *LCOPENAPI_INIT(UnBindDeviceRequest);

typedef struct UnBindDeviceResponse 
{
	LCOpenApiResponse base;

	struct UnBindDeviceResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} UnBindDeviceResponse;

C_API UnBindDeviceResponse *LCOPENAPI_INIT(UnBindDeviceResponse);

#endif
