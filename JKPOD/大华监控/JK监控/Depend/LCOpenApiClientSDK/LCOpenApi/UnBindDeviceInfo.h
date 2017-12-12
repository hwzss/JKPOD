/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: unknown, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_UnBindDeviceInfo_H_
#define _LC_OPENAPI_CLIENT_UnBindDeviceInfo_H_

#include "LCOpenApiClientSdk.h"

/** DESCRIPTION: 
获取授权列表
 */

typedef struct UnBindDeviceInfoRequest 
{
	LCOpenApiRequest base;

	struct UnBindDeviceInfoRequestData
	{
		
		/** [cstr]unBindDeviceInfo */
		#define _STATIC_UnBindDeviceInfoRequestData_method "unBindDeviceInfo"
		CSTR method;
		/** 授权token(userToken或accessToken) */
		CSTR token;
		/** 设备Id */
		CSTR deviceId;

	} data;

} UnBindDeviceInfoRequest;

C_API UnBindDeviceInfoRequest *LCOPENAPI_INIT(UnBindDeviceInfoRequest);

typedef struct UnBindDeviceInfoResponse 
{
	LCOpenApiResponse base;

	struct UnBindDeviceInfoResponseData
	{
		
		/** define a list with struct of UnBindDeviceInfoResponseData_DevicesElement */
		DECLARE_LIST(struct UnBindDeviceInfoResponseData_DevicesElement
		{
			/** 可选,设备品牌信息：lechange-乐橙设备，general-通用设备 */
			CSTR brand;
			/** 可选,设备型号 */
			CSTR baseline;
			/** 可选,设备型号 */
			CSTR deviceModel;
			/** 设备logo图片url */
			CSTR logoUrl;
			/** 设备ID */
			CSTR deviceId;
			/** 设备名称  */
			CSTR name;
			/** [int]当前状态：0-离线，1-在线，3-升级中 */
			int status;
			/** 可选,设备能力项，逗号隔开，如AlarmMD,AudioTalk,AlarmPIR,WLAN,VVP2P，详见   华视微讯设备协议 */
			CSTR ability;
			/** 可选,设备分类【NVR/DVR/HCVR/IPC/SD/IHG/ARC】 */
			CSTR deviceCatalog;
			/** 设备软件版本号 */
			CSTR version;
		}) devices;
 
	} data;

} UnBindDeviceInfoResponse;

C_API UnBindDeviceInfoResponse *LCOPENAPI_INIT(UnBindDeviceInfoResponse);

#endif
