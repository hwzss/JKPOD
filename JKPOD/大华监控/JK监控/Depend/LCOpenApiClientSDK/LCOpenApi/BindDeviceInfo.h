/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: unknown, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_BindDeviceInfo_H_
#define _LC_OPENAPI_CLIENT_BindDeviceInfo_H_

#include "LCOpenApiClientSdk.h"

/** DESCRIPTION: 
获取单个设备的信息

 */

typedef struct BindDeviceInfoRequest 
{
	LCOpenApiRequest base;

	struct BindDeviceInfoRequestData
	{
		
		/** 授权token(userToken或accessToken) */
		CSTR token;
		/** [cstr]bindDeviceInfo */
		#define _STATIC_BindDeviceInfoRequestData_method "bindDeviceInfo"
		CSTR method;
		/** 设备ID */
		CSTR deviceId;

	} data;

} BindDeviceInfoRequest;

C_API BindDeviceInfoRequest *LCOPENAPI_INIT(BindDeviceInfoRequest);

typedef struct BindDeviceInfoResponse 
{
	LCOpenApiResponse base;

	struct BindDeviceInfoResponseData
	{
		
		/** 设备品牌信息：lechange-乐城设备，general-通用设备 */
		CSTR brand;
		/** 设备基线类型，详见华视微讯设备协议 */
		CSTR baseline;
		/** 绑定设备的appId（若为乐橙App绑定，该字段为空字符串） */
		CSTR appId;
		/** 设备型号 */
		CSTR deviceModel;
		/** 设备ID */
		CSTR deviceId;
		/** define a list with struct of BindDeviceInfoResponseData_ChannelsElement */
		DECLARE_LIST(struct BindDeviceInfoResponseData_ChannelsElement
		{
			/** [int]报警布撤防状态，0-撤防，1-布防 */
			int alarmStatus;
			/** 通道名称 */
			CSTR channelName;
			/** [bool]是否分享给别人的,true表示分享给了别人,false表示未分享给别人 */
			BOOL shareStatus;
			/** 缩略图URL */
			CSTR channelPicUrl;
			/** [int]通道号 */
			int channelId;
			/** [bool]是否在线 */
			BOOL channelOnline;
			/** [int]云存储状态：-1-未开通 0-已失效 1-使用中 2-套餐暂停 */
			int csStatus;
		}) channels;
		/** [O]设备能力项，逗号隔开，如AlarmMD,AudioTalk,AlarmPIR,WLAN,VVP2P，详见乐橙开放平台设备协议 */
		CSTR ability;
		/** 设备软件版本号 */
		CSTR version;
		/** [bool] */
		BOOL canBeUpgrade;
		/** [int]当前状态：0-离线，1-在线，3-升级中 */
		int status;
		/** [int]加密模式 */
		int encryptMode;
		/** 设备分类 */
		CSTR deviceCatalog;
		/** 设备名称 */
		CSTR name;
 
	} data;

} BindDeviceInfoResponse;

C_API BindDeviceInfoResponse *LCOPENAPI_INIT(BindDeviceInfoResponse);

#endif
