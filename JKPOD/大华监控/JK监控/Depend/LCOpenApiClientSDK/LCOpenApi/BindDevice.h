/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: unknown, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_BindDevice_H_
#define _LC_OPENAPI_CLIENT_BindDevice_H_

#include "LCOpenApiClientSdk.h"

/** DESCRIPTION: 
设备绑定
处理设备绑定不成功各种分支逻辑，根据civil返回的错误码来处理。

 */

typedef struct BindDeviceRequest 
{
	LCOpenApiRequest base;

	struct BindDeviceRequestData
	{
		
		/** 授权token(userToken或accessToken) */
		CSTR token;
		/** 设备序列号，例2342sdfl-df323-23 */
		CSTR deviceId;
		/** [cstr]bindDevice */
		#define _STATIC_BindDeviceRequestData_method "bindDevice"
		CSTR method;
		/** 依设备能力，选填 */
		CSTR code;

	} data;

} BindDeviceRequest;

C_API BindDeviceRequest *LCOPENAPI_INIT(BindDeviceRequest);

typedef struct BindDeviceResponse 
{
	LCOpenApiResponse base;

	struct BindDeviceResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} BindDeviceResponse;

C_API BindDeviceResponse *LCOPENAPI_INIT(BindDeviceResponse);

#endif
