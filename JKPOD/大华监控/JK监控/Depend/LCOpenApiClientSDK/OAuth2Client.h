#ifndef _LCOPENAPI_CLIENT_OAUTH2CLIENT_H_
#define _LCOPENAPI_CLIENT_OAUTH2CLIENT_H_

#include "basedef.h"

// 错误码
enum
{
	OAC_ERROR_PARAMS = - 1,		// 参数错误
	OAC_ERROR_CURL = - 2,		// curl调用失败
	OAC_ERROR_HTTP = - 3,		// HTTP请求失败
	OAC_ERROR_JSON = - 4,		// JSON解析错误
};

// OAuth2初始信息
typedef struct
{
	char host[256];				// 服务地址
	char client_id[64];			// 客户端ID
	char client_secret[64];		// 客户端密钥
	long timeout;				// 请求超时时间（秒）
} OAuth2Initial;

// AccessToken信息
typedef struct
{
	char access_token[64];		// AccessToken
	char token_type[64];		// AccessToken类型
	int expires_in;				// AccessToken有效时间（秒）
} AccessTokenInfo;

// 使用OAuth2中的password授权模式获取accessToken
// 入参：
//   initial：OAuth2环境参数
//   username：账号用户名
//   password：账号密码，是摘要算法（如md5)之后的密文
// 出参：
//   akinfo：服务器返回的AccessToken信息
// 成功返回0，失败返回错误码
C_API int oauth2_client_get_access_token_by_password(const OAuth2Initial *initial, 
													 const char *username, const char *password, 
													 AccessTokenInfo *akinfo);

// 获取上一次的具体错误描述（非线程安全）
C_API const char *oauth2_client_get_error_info();

#endif
