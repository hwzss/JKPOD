/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: unknown, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_CurrentDeviceWifi_H_
#define _LC_OPENAPI_CLIENT_CurrentDeviceWifi_H_

#include "LCOpenApiClientSdk.h"

/** DESCRIPTION: 
设备当前连接的热点信息

 */

typedef struct CurrentDeviceWifiRequest 
{
	LCOpenApiRequest base;

	struct CurrentDeviceWifiRequestData
	{
		
		/** 授权token(userToken或accessToken) */
		CSTR token;
		/** [cstr]currentDeviceWifi */
		#define _STATIC_CurrentDeviceWifiRequestData_method "currentDeviceWifi"
		CSTR method;
		/** 设备序列号,例2342sdfl-df323-23 */
		CSTR deviceId;

	} data;

} CurrentDeviceWifiRequest;

C_API CurrentDeviceWifiRequest *LCOPENAPI_INIT(CurrentDeviceWifiRequest);

typedef struct CurrentDeviceWifiResponse 
{
	LCOpenApiResponse base;

	struct CurrentDeviceWifiResponseData
	{
		
		/** 若连接了热点，填热点的名称；若未连接，填空 */
		CSTR ssid;
		/** [bool]是否连接了wifi */
		BOOL linkEnable;
 
	} data;

} CurrentDeviceWifiResponse;

C_API CurrentDeviceWifiResponse *LCOPENAPI_INIT(CurrentDeviceWifiResponse);

#endif
