/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: unknown, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_CheckDeviceBindOrNot_H_
#define _LC_OPENAPI_CLIENT_CheckDeviceBindOrNot_H_

#include "LCOpenApiClientSdk.h"

/** DESCRIPTION: 
设备是否已绑定

 */

typedef struct CheckDeviceBindOrNotRequest 
{
	LCOpenApiRequest base;

	struct CheckDeviceBindOrNotRequestData
	{
		
		/** 授权token(userToken或accessToken) */
		CSTR token;
		/** [cstr]checkDeviceBindOrNot */
		#define _STATIC_CheckDeviceBindOrNotRequestData_method "checkDeviceBindOrNot"
		CSTR method;
		/** 设备序列号,例2342sdfl-df323-23 */
		CSTR deviceId;

	} data;

} CheckDeviceBindOrNotRequest;

C_API CheckDeviceBindOrNotRequest *LCOPENAPI_INIT(CheckDeviceBindOrNotRequest);

typedef struct CheckDeviceBindOrNotResponse 
{
	LCOpenApiResponse base;

	struct CheckDeviceBindOrNotResponseData
	{
		
		/** [bool]是否被绑定到某个账号 */
		BOOL isBind;
		/** [bool]是否属于自己这个账号 */
		BOOL isMine;
 
	} data;

} CheckDeviceBindOrNotResponse;

C_API CheckDeviceBindOrNotResponse *LCOPENAPI_INIT(CheckDeviceBindOrNotResponse);

#endif
