/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: unknown, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_UnGroupDeviceList_H_
#define _LC_OPENAPI_CLIENT_UnGroupDeviceList_H_

#include "LCOpenApiClientSdk.h"

/** DESCRIPTION: 
分页获取返回所有未分组的设备，包括自己的和别人共享、授权给自己的所有设备
 */

typedef struct UnGroupDeviceListRequest 
{
	LCOpenApiRequest base;

	struct UnGroupDeviceListRequestData
	{
		
		/** 分页取值范围，一次最多获取50条，格式为“1-30” */
		CSTR queryRange;
		/** 授权token(userToken或accessToken) */
		CSTR token;
		/** [cstr]unGroupDeviceList */
		#define _STATIC_UnGroupDeviceListRequestData_method "unGroupDeviceList"
		CSTR method;

	} data;

} UnGroupDeviceListRequest;

C_API UnGroupDeviceListRequest *LCOPENAPI_INIT(UnGroupDeviceListRequest);

typedef struct UnGroupDeviceListResponse 
{
	LCOpenApiResponse base;

	struct UnGroupDeviceListResponseData
	{
		
		/** define a list with struct of UnGroupDeviceListResponseData_DevicesElement */
		DECLARE_LIST(struct UnGroupDeviceListResponseData_DevicesElement
		{
			/** 访问设备的DMS入口地址，例如122.233.34.45:9200 */
			CSTR dms;
			/** 设备基线类型，详见华视微讯设备协议 */
			CSTR baseline;
			/** [int]加密模式, 0表示默认加密模式, 1表示用户加密模式 */
			int encryptMode;
			/** define a list with struct of UnGroupDeviceListResponseData_DevicesElement_ChannelsElement */
			DECLARE_LIST(struct UnGroupDeviceListResponseData_DevicesElement_ChannelsElement
			{
				/** [int]报警布撤防状态，0-撤防，1-布防 */
				int alarmStatus;
				/** [int]云存储状态：-1-未开通 0-已失效 1-使用中 2-套餐暂停 */
				int csStatus;
				/** 如果是分享或者授权过来的通道，填分享或者授权的功能列表（逗号隔开） */
				CSTR functions;
				/** [bool]是否分享或者授权给别人的 */
				BOOL channelBeSharedTo;
				/** [int]SD卡状态：0-异常，1-正常，2-无SD卡，3-格式化中 */
				int sdcardState;
				/** 公开视频的token */
				CSTR publicToken;
				/** [long]公开时间，UNIX时间戳（秒） */
				int64 shareTime;
				/** [int]提醒状态，0-不提醒，1-提醒 */
				int remindStatus;
				/** 通道名称 */
				CSTR channelName;
				/** [long]公开到期时间，UNIX时间戳，单位秒。为0表示设置为非公共视频。 */
				int64 publicExpire;
				/** 通道能力项，逗号隔开，如AlarmMD,AudioTalk,AlarmPIR,WLAN,VVP2P，详见华视微讯设备协议 */
				CSTR channelAbility;
				/** 缩略图URL */
				CSTR channelPicUrl;
				/** [int]通道号 */
				int channelId;
				/** [bool]是否在线 */
				BOOL channelOnline;
				/** [int]channelBeSharedTo为true时有效，0表示同时分享和授权给别人的设备，1表示分享给别人的设备，2表示授权给别人的设备 */
				int channelBeShareToState;
			}) channels;
			/** 设备型号 */
			CSTR deviceModel;
			/** [int]beSharedTo为true时有效，0表示同时分享和授权给别人的设备，1表示分享给别人的设备，2表示授权给别人的设备 */
			int beShareToState;
			/** [bool]是否分享或者授权给别人的 */
			BOOL beSharedTo;
			/** 设备ID */
			CSTR deviceId;
			/** [bool]是否有新版本可以升级 */
			BOOL canBeUpgrade;
			/** [bool]是否在线 */
			BOOL online;
			/** 设备软件版本号 */
			CSTR version;
			/** 设备能力项，逗号隔开，如AlarmMD,AudioTalk,AlarmPIR,WLAN,VVP2P，详见华视微讯设备协议 */
			CSTR ability;
			/** [int]当前状态：0-离线，1-在线，3-升级中 */
			int status;
			/** [bool]是否从别人那里分享或者授权的，分享者信息填在ownerInfo结构中 */
			BOOL beSharedFrom;
			/** 设备分类【NVR/DVR/HCVR/IPC/SD/IHG】 */
			CSTR deviceCatalog;
			/** 设备名称 */
			CSTR name;
		}) devices;
 
	} data;

} UnGroupDeviceListResponse;

C_API UnGroupDeviceListResponse *LCOPENAPI_INIT(UnGroupDeviceListResponse);

#endif
