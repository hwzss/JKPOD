/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: unknown, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_ShareDeviceList_H_
#define _LC_OPENAPI_CLIENT_ShareDeviceList_H_

#include "LCOpenApiClientSdk.h"

/** DESCRIPTION: 
设备列表获取
分享的设备详细信息列表

 */

typedef struct ShareDeviceListRequest 
{
	LCOpenApiRequest base;

	struct ShareDeviceListRequestData
	{
		
		/** 第几条到第几条,数字取值范围为：[1,N](N为正整数，且后者＞前者),单次查询上限100 */
		CSTR queryRange;
		/** [cstr]shareDeviceList */
		#define _STATIC_ShareDeviceListRequestData_method "shareDeviceList"
		CSTR method;
		/** 授权token(userToken或accessToken) */
		CSTR token;

	} data;

} ShareDeviceListRequest;

C_API ShareDeviceListRequest *LCOPENAPI_INIT(ShareDeviceListRequest);

typedef struct ShareDeviceListResponse 
{
	LCOpenApiResponse base;

	struct ShareDeviceListResponseData
	{
		
		/** 20 */
		CSTR count;
		/** define a list with struct of ShareDeviceListResponseData_DevicesElement */
		DECLARE_LIST(struct ShareDeviceListResponseData_DevicesElement
		{
			/** 设备品牌信息：lechange-乐橙设备，general-通用设备 */
			CSTR brand;
			/** 设备基线类型，详见华视微讯设备协议 */
			CSTR baseline;
			/** define a list with struct of ShareDeviceListResponseData_DevicesElement_ChannelsElement */
			DECLARE_LIST(struct ShareDeviceListResponseData_DevicesElement_ChannelsElement
			{
				/** [int]报警布撤防状态，0-撤防，1-布防 */
				int alarmStatus;
				/** 通道名称 */
				CSTR channelName;
				/** 缩略图URL */
				CSTR channelPicUrl;
				/** [int]通道号 */
				int channelId;
				/** [bool]是否在线 */
				BOOL channelOnline;
			}) channels;
			/** [O]设备型号 */
			CSTR deviceModel;
			/** 设备ID */
			CSTR deviceId;
			/** [O]设备能力项，逗号隔开，如AlarmMD,AudioTalk,AlarmPIR,WLAN,VVP2P，详见乐橙开放平台设备协议 */
			CSTR ability;
			/** 设备名称 */
			CSTR name;
			/** [bool]是否有新版本可以升级 */
			BOOL canBeUpgrade;
			/** [int]当前状态：0-离线，1-在线，3-升级中 */
			int status;
			/** [int]加密模式 */
			int encryptMode;
			/** 设备分类（NVR/DVR/HCVR/IPC/SD/IHG/ARC) */
			CSTR deviceCatalog;
			/** 设备软件版本号 */
			CSTR version;
		}) devices;
 
	} data;

} ShareDeviceListResponse;

C_API ShareDeviceListResponse *LCOPENAPI_INIT(ShareDeviceListResponse);

#endif
