/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: unknown, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_UpgradeDevice_H_
#define _LC_OPENAPI_CLIENT_UpgradeDevice_H_

#include "LCOpenApiClientSdk.h"

/** DESCRIPTION: 
设备升级

 */

typedef struct UpgradeDeviceRequest 
{
	LCOpenApiRequest base;

	struct UpgradeDeviceRequestData
	{
		
		/** 授权token(userToken或accessToken) */
		CSTR token;
		/** [cstr]upgradeDevice */
		#define _STATIC_UpgradeDeviceRequestData_method "upgradeDevice"
		CSTR method;
		/** 设备序列号,例2342sdfl-df323-23 */
		CSTR deviceId;

	} data;

} UpgradeDeviceRequest;

C_API UpgradeDeviceRequest *LCOPENAPI_INIT(UpgradeDeviceRequest);

typedef struct UpgradeDeviceResponse 
{
	LCOpenApiResponse base;

	struct UpgradeDeviceResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} UpgradeDeviceResponse;

C_API UpgradeDeviceResponse *LCOPENAPI_INIT(UpgradeDeviceResponse);

#endif
