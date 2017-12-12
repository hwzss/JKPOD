/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: unknown, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_CloudRecordPlan_H_
#define _LC_OPENAPI_CLIENT_CloudRecordPlan_H_

#include "LCOpenApiClientSdk.h"

/** DESCRIPTION: 
获取设备通道的云录像存储计划
Period：生效的周期
        everyday：每天 等价于周一到周日
        Monday：每周一
        Tuesday：每周二
        Wednesday：每周三
        Thursday：每周四
        Friday：每周五
        Saturday：每周六
        Sunday：每周日
    可出现“Monday, Wednesday, Friday”的方式多选。
 */

typedef struct CloudRecordPlanRequest 
{
	LCOpenApiRequest base;

	struct CloudRecordPlanRequestData
	{
		
		/** [cstr]cloudRecordPlan */
		#define _STATIC_CloudRecordPlanRequestData_method "cloudRecordPlan"
		CSTR method;
		/** 通道号 */
		CSTR channelId;
		/** 授权token(userToken或accessToken) */
		CSTR token;
		/** 设备序列号 */
		CSTR deviceId;

	} data;

} CloudRecordPlanRequest;

C_API CloudRecordPlanRequest *LCOPENAPI_INIT(CloudRecordPlanRequest);

typedef struct CloudRecordPlanResponse 
{
	LCOpenApiResponse base;

	struct CloudRecordPlanResponseData
	{
		
		/** define a list with struct of CloudRecordPlanResponseData_RulesElement */
		DECLARE_LIST(struct CloudRecordPlanResponseData_RulesElement
		{
			/** 结束时间 */
			CSTR endTime;
			/** [long]时间戳 */
			int64 timestamp;
			/** 重复周期 */
			CSTR period;
			/** 开始时间 */
			CSTR beginTime;
		}) rules;
		/** 通道ID */
		CSTR channelId;
		/** [int]每日最长拉流时间（单位：小时） */
		int limitTime;
		/** [int]上行带宽（单位：M） */
		int upstream;
 
	} data;

} CloudRecordPlanResponse;

C_API CloudRecordPlanResponse *LCOPENAPI_INIT(CloudRecordPlanResponse);

#endif
