/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: unknown, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_BeAuthDeviceList_H_
#define _LC_OPENAPI_CLIENT_BeAuthDeviceList_H_

#include "LCOpenApiClientSdk.h"

/** DESCRIPTION: 
获取单个设备的信息

 */

typedef struct BeAuthDeviceListRequest 
{
	LCOpenApiRequest base;

	struct BeAuthDeviceListRequestData
	{
		
		/** 比如1-50 */
		CSTR queryRange;
		/** [cstr]beAuthDeviceList */
		#define _STATIC_BeAuthDeviceListRequestData_method "beAuthDeviceList"
		CSTR method;
		/** 授权token(userToken或accessToken) */
		CSTR token;

	} data;

} BeAuthDeviceListRequest;

C_API BeAuthDeviceListRequest *LCOPENAPI_INIT(BeAuthDeviceListRequest);

typedef struct BeAuthDeviceListResponse 
{
	LCOpenApiResponse base;

	struct BeAuthDeviceListResponseData
	{
		
		/** define a list with struct of BeAuthDeviceListResponseData_DevicesElement */
		DECLARE_LIST(struct BeAuthDeviceListResponseData_DevicesElement
		{
			/** [O]设备品牌信息：lechange-乐橙设备，general-通用设备 */
			CSTR brand;
			/** [int]云存储状态：-1-未开通 0-已失效 1-使用中 2-套餐暂停 */
			int csStatus;
			/** [bool]是否有新版本可以升级 */
			BOOL canBeUpgrade;
			/** [int]当前状态：0-离线，1-在线，3-升级中 */
			int status;
			/** [O]设备分类【NVR/DVR/HCVR/IPC/SD/IHG/ARC】 */
			CSTR deviceCatalog;
			/** [int]报警布撤防状态，0-撤防，1-布防 */
			int alarmStatus;
			/** [O]设备基线类型，详见华视微讯设备协议 */
			CSTR baseline;
			/** 共享或者授权的功能列表（逗号隔开） */
			CSTR functions;
			/** [O]设备能力项，逗号隔开，如AlarmMD,AudioTalk,AlarmPIR,WLAN,VVP2P，详见华视微讯设备协议 */
			CSTR ability;
			/** 设备ID */
			CSTR deviceId;
			/** [O]设备型号 */
			CSTR deviceModel;
			/** 通道名称 */
			CSTR channelName;
			/** 设备名称 */
			CSTR name;
			/** [int]通道号 */
			int channelId;
			/** 缩略图URL */
			CSTR channelPicUrl;
			/** [int]加密模式 */
			int encryptMode;
			/** [bool]是否在线 */
			BOOL channelOnline;
			/** 设备软件版本号 */
			CSTR version;
		}) devices;
 
	} data;

} BeAuthDeviceListResponse;

C_API BeAuthDeviceListResponse *LCOPENAPI_INIT(BeAuthDeviceListResponse);

#endif
