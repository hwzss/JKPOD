/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: unknown, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_ControlPTZ_H_
#define _LC_OPENAPI_CLIENT_ControlPTZ_H_

#include "LCOpenApiClientSdk.h"

/** DESCRIPTION: 
云台控制

 */

typedef struct ControlPTZRequest 
{
	LCOpenApiRequest base;

	struct ControlPTZRequestData
	{
		
		/** [cstr]controlPTZ */
		#define _STATIC_ControlPTZRequestData_method "controlPTZ"
		CSTR method;
		/** 操作行为；move表示移动，locate表示定位 */
		CSTR operation;
		/** 移动持续时间，单位为毫秒。没有duration字段或duration字段填“last”表示一直运动下去 */
		CSTR duration;
		/** 设备序列号,例2342sdfl-df323-23 */
		CSTR deviceId;
		/** [double]水平操作参数 */
		double h;
		/** 授权token(userToken或accessToken) */
		CSTR token;
		/** [double]变倍参数 */
		double z;
		/** 通道号 */
		CSTR channelId;
		/** [double]垂直操作参数 */
		double v;

	} data;

} ControlPTZRequest;

C_API ControlPTZRequest *LCOPENAPI_INIT(ControlPTZRequest);

typedef struct ControlPTZResponse 
{
	LCOpenApiResponse base;

	struct ControlPTZResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} ControlPTZResponse;

C_API ControlPTZResponse *LCOPENAPI_INIT(ControlPTZResponse);

#endif
