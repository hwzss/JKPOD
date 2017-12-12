/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: unknown, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_ControlDeviceWifi_H_
#define _LC_OPENAPI_CLIENT_ControlDeviceWifi_H_

#include "LCOpenApiClientSdk.h"

/** DESCRIPTION: 
控制设备的wifi
10003：开发模式下，此接口一天只能调用5次
其他的一些civil返回的错误码的封装

 */

typedef struct ControlDeviceWifiRequest 
{
	LCOpenApiRequest base;

	struct ControlDeviceWifiRequestData
	{
		
		/** wifi密码 */
		CSTR password;
		/** [cstr]controlDeviceWifi */
		#define _STATIC_ControlDeviceWifiRequestData_method "controlDeviceWifi"
		CSTR method;
		/** 授权token(userToken或accessToken) */
		CSTR token;
		/** [bool]连接或断开 */
		BOOL linkEnable;
		/** BSSID */
		CSTR bssid;
		/** 填需要连接的SSID */
		CSTR ssid;
		/** 设备序列号,例2342sdfl-df323-23 */
		CSTR deviceId;

	} data;

} ControlDeviceWifiRequest;

C_API ControlDeviceWifiRequest *LCOPENAPI_INIT(ControlDeviceWifiRequest);

typedef struct ControlDeviceWifiResponse 
{
	LCOpenApiResponse base;

	struct ControlDeviceWifiResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} ControlDeviceWifiResponse;

C_API ControlDeviceWifiResponse *LCOPENAPI_INIT(ControlDeviceWifiResponse);

#endif
