/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: unknown, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_SetDeviceSnap_H_
#define _LC_OPENAPI_CLIENT_SetDeviceSnap_H_

#include "LCOpenApiClientSdk.h"

/** DESCRIPTION: 
设置摄像头抓图
注：客户端请求时间间隔需大于等于1s，若客户端请求时间间隔小于3s，默认返回上一次抓图图片。
返回结果中，抓图访问地址（url）1年内有效。
 */

typedef struct SetDeviceSnapRequest 
{
	LCOpenApiRequest base;

	struct SetDeviceSnapRequestData
	{
		
		/** [bool]图片是否加密，true:加密,false:不加密 */
		BOOL encrypt;
		/** 通道ID */
		CSTR channelId;
		/** [cstr]setDeviceSnap */
		#define _STATIC_SetDeviceSnapRequestData_method "setDeviceSnap"
		CSTR method;
		/** 设备序列号,例2342sdfl-df323-23 */
		CSTR deviceId;

	} data;

} SetDeviceSnapRequest;

C_API SetDeviceSnapRequest *LCOPENAPI_INIT(SetDeviceSnapRequest);

typedef struct SetDeviceSnapResponse 
{
	LCOpenApiResponse base;

	struct SetDeviceSnapResponseData
	{
		
		/** 抓图访问地址 */
		CSTR url;
 
	} data;

} SetDeviceSnapResponse;

C_API SetDeviceSnapResponse *LCOPENAPI_INIT(SetDeviceSnapResponse);

#endif
