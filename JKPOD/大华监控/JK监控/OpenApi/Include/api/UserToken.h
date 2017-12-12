/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: unknown, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_UserToken_H_
#define _LC_OPENAPI_CLIENT_UserToken_H_

#include "LCOpenApi_ClientSdk.h"

/** DESCRIPTION: 
在获取userToken之前需要先判断此手机号码对应的用户是否跟此应用(appid)有绑定关�?
错误码：
	10002：该手机号码对应的用户还未与您的应用绑定,先请将此用户绑定您的应用.
 */
namespace LCOpenApi{
typedef struct UserTokenRequest 
{
	LCOpenApi_LCOpenApiRequest base;

	struct UserTokenRequestData
	{
		
		/** 18888888888//用户手机号码 */
		CSTR phone;

	} data;

} UserTokenRequest;

UserTokenRequest *LCOpenApi_LCOPENAPI_INIT(UserTokenRequest);

typedef struct UserTokenResponse 
{
	LCOpenApi_LCOpenApiResponse base;

	struct UserTokenResponseData
	{
		
		/** ********* */
		CSTR userToken;
 
	} data;

} UserTokenResponse;

UserTokenResponse *LCOpenApi_LCOPENAPI_INIT(UserTokenResponse);

}
#endif
