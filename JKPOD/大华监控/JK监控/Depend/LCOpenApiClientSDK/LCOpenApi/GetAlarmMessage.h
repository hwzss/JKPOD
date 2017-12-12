/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: unknown, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_GetAlarmMessage_H_
#define _LC_OPENAPI_CLIENT_GetAlarmMessage_H_

#include "LCOpenApiClientSdk.h"

/** DESCRIPTION: 
查询某个用户的报警信息（分页）
10003：开发模式下，此接口一天只能调用5次
其他的一些civil返回的错误码的封装

 */

typedef struct GetAlarmMessageRequest 
{
	LCOpenApiRequest base;

	struct GetAlarmMessageRequestData
	{
		
		/** 授权token(userToken或accessToken) */
		CSTR token;
		/** 开始时间，如2010-05-25 00:00:00 */
		CSTR beginTime;
		/** [cstr]getAlarmMessage */
		#define _STATIC_GetAlarmMessageRequestData_method "getAlarmMessage"
		CSTR method;
		/** 拉取报警消息的个数-最大值为100 */
		CSTR count;
		/** 结束时间，如2010-05-25 23:59:59 */
		CSTR endTime;
		/** 通道号或通道的设备ID */
		CSTR channelId;
		/** 不填写默认从头开始拉去 */
		CSTR nextAlarmId;
		/** 设备序列号,例2342sdfl-df323-23 */
		CSTR deviceId;

	} data;

} GetAlarmMessageRequest;

C_API GetAlarmMessageRequest *LCOPENAPI_INIT(GetAlarmMessageRequest);

typedef struct GetAlarmMessageResponse 
{
	LCOpenApiResponse base;

	struct GetAlarmMessageResponseData
	{
		
		/** 123123 */
		CSTR nextAlarmId;
		/** 20 */
		CSTR count;
		/** define a list with struct of GetAlarmMessageResponseData_AlarmsElement */
		DECLARE_LIST(struct GetAlarmMessageResponseData_AlarmsElement
		{
			/** [int]报警类型 */
			int type;
			/** 缩略图URL */
			CSTR thumbUrl;
			/** 设备ID */
			CSTR deviceId;
			/** [long]消息ID */
			int64 alarmId;
			/** [long]报警时间UNIX时间戳秒 */
			int64 time;
			/** 报警图片url */
			DECLARE_LIST(CSTR) picurlArray;
			/** 通道号 */
			CSTR channelId;
			/** 设备或通道的名称 */
			CSTR name;
			/** 报警时设备本地时间，格式如2014-12-12 12:12:12 */
			CSTR localDate;
		}) alarms;
 
	} data;

} GetAlarmMessageResponse;

C_API GetAlarmMessageResponse *LCOPENAPI_INIT(GetAlarmMessageResponse);

#endif
