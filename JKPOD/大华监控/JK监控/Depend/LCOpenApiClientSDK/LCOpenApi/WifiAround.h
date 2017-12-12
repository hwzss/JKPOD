/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: unknown, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_WifiAround_H_
#define _LC_OPENAPI_CLIENT_WifiAround_H_

#include "LCOpenApiClientSdk.h"

/** DESCRIPTION: 
获取设备周边wifi信息
enable表示设备是否开启WIFI。
    false：WIFI功能关闭。
    true：WIFI功能开启。
当enable为true时同时返回设备当前环境中的热点列表：

 */

typedef struct WifiAroundRequest 
{
	LCOpenApiRequest base;

	struct WifiAroundRequestData
	{
		
		/** 授权token(userToken或accessToken) */
		CSTR token;
		/** [cstr]wifiAround */
		#define _STATIC_WifiAroundRequestData_method "wifiAround"
		CSTR method;
		/** 设备序列号,例2342sdfl-df323-23 */
		CSTR deviceId;

	} data;

} WifiAroundRequest;

C_API WifiAroundRequest *LCOPENAPI_INIT(WifiAroundRequest);

typedef struct WifiAroundResponse 
{
	LCOpenApiResponse base;

	struct WifiAroundResponseData
	{
		
		/** [bool]是否开启了wifi */
		BOOL enable;
		/** define a list with struct of WifiAroundResponseData_WLanElement */
		DECLARE_LIST(struct WifiAroundResponseData_WLanElement
		{
			/**  SSID  */
			CSTR ssid;
			/** [int]强度 */
			int intensity;
			/** BSSID */
			CSTR bssid ;
			/** 加密方式 */
			CSTR auth;
			/** [int]状态 */
			int linkStatus;
		}) wLan;
 
	} data;

} WifiAroundResponse;

C_API WifiAroundResponse *LCOPENAPI_INIT(WifiAroundResponse);

#endif
