/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: unknown, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_UserAuthList_H_
#define _LC_OPENAPI_CLIENT_UserAuthList_H_

#include "LCOpenApiClientSdk.h"

/** DESCRIPTION: 
获取授权列表
 */

typedef struct UserAuthListRequest 
{
	LCOpenApiRequest base;

	struct UserAuthListRequestData
	{
		
		/** [int]需要查的最大条数 */
		int count;
		/** [long]从该授权ID开始查询。若要从最新开始查，填-1 */
		int64 nextAuthId;
		/** 授权token(userToken或accessToken) */
		CSTR token;
		/** [cstr]userAuthList */
		#define _STATIC_UserAuthListRequestData_method "userAuthList"
		CSTR method;

	} data;

} UserAuthListRequest;

C_API UserAuthListRequest *LCOPENAPI_INIT(UserAuthListRequest);

typedef struct UserAuthListResponse 
{
	LCOpenApiResponse base;

	struct UserAuthListResponseData
	{
		
		/** define a list with struct of UserAuthListResponseData_AuthorizationsElement */
		DECLARE_LIST(struct UserAuthListResponseData_AuthorizationsElement
		{
			/** struct of UserAuthListResponseData_AuthorizationsElement_Role */
			struct UserAuthListResponseData_AuthorizationsElement_Role {
				/** [long]角色Id */
				int64 roleId;
				/** 角色名称 */
				CSTR roleName;
				/** 权限列表 */
				CSTR authFunctions;
			} role;
			/** [long]授权Id */
			int64 authId;
			/** 手机号 */
			CSTR phoneNumber;
			/** 授权名称 */
			CSTR authName;
			/** define a list with struct of UserAuthListResponseData_AuthorizationsElement_AuthDevicesElement */
			DECLARE_LIST(struct UserAuthListResponseData_AuthorizationsElement_AuthDevicesElement
			{
				/** 通道号 */
				CSTR channelId;
				/** 通道名称 */
				CSTR channelName;
				/** 设备序列号 */
				CSTR deviceId;
			}) authDevices;
		}) authorizations;
		/** 123456 */
		CSTR nextAuthId;
 
	} data;

} UserAuthListResponse;

C_API UserAuthListResponse *LCOPENAPI_INIT(UserAuthListResponse);

#endif
