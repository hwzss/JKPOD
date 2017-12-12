#ifndef _LCOPENAPI_CLIENT_BASEDEF_H_
#define _LCOPENAPI_CLIENT_BASEDEF_H_

#include <stdio.h>

#ifdef LCOPENAPICLIENT_EXPORTS
    #ifdef __cplusplus
    #define C_API extern "C" _declspec(dllexport)
    #else
    #define C_API _declspec(dllexport)
    #endif
#else
    #ifdef __cplusplus
    #define C_API extern "C"
    #else
    #define C_API
    #endif
#endif

#ifdef WIN32
typedef long long int64;
#else
#include <inttypes.h>
typedef int64_t int64;
#endif


// 布尔型 BOOL
/*
	IOS_DH:				标识编译的.a库为IOS版本,需要定义BOOL为signed char(与IOS系统保持一致)
	TARGET_OS_IPHONE：	标识目前的编译环境为IOS的真实环境,因此不要重定义BOOL,否则冲突
	其他			：	linux or win,需要定义BOOL类型
*/
#ifdef IOS_DH
typedef signed char BOOL;
#elif TARGET_OS_IPHONE

#else
typedef int BOOL;
#endif

#endif
