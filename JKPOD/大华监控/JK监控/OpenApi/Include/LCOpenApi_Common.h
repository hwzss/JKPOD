#ifndef _LCOPENAPI_COMMON_H_
#define _LCOPENAPI_COMMON_H_

#include "LCOpenApi_ClientSdk.h"
#include "LCOpenApi_ReflectionObject.h"

namespace LCOpenApi{
#define myPrint(fmt,...)	\
	{ char format[2*1024] = {0};	\
		snprintf(format,sizeof(format)-1,"[%s:%d]%s",__FUNCTION__,__LINE__,fmt);	\
		printf(format,##__VA_ARGS__);	\
	}
#define LCOPENAPI_REQUEST_CLEAR(r)			\
	CS_CLEAR((r)->base.apiname);		\
	CS_CLEAR((r)->base.fullname);		\
	CS_CLEAR((r)->base.method);			\
	CS_CLEAR((r)->base.uri);			\
	CS_CLEAR((r)->base.content_type);	\
	CS_CLEAR((r)->base.body);			\
	CS_CLEAR((r)->base.params);			\
	CS_CLEAR((r)->base.messageId);			\
	CS_CLEAR((r)->base.time);			\
	CS_CLEAR((r)->base.nonce);			\
	CS_CLEAR((r)->base.signMd5);			

#define LCOPENAPI_RESPONSE_CLEAR(r)		\
	CS_CLEAR((r)->base.headers);		\
	CS_CLEAR((r)->base.desc);			\
	CS_CLEAR((r)->base.content);		\
	CS_CLEAR((r)->base.id);				\
	CS_CLEAR((r)->base.ret_code);				\
	CS_CLEAR((r)->base.ret_msg);	

#define LCOPENAPI_RESPONSE_COPY(dst, src)								\
	(dst)->base = (src)->base;										\
	(dst)->base.headers = CS((src)->base.headers.cstr);				\
	(dst)->base.desc = CS((src)->base.desc.cstr);					\
	(dst)->base.content = CS((src)->base.content.cstr);				\
	(dst)->base.id = CS((src)->base.id.cstr);				\
	(dst)->base.ret_code = CS((src)->base.ret_code.cstr);				\
	(dst)->base.ret_msg = CS((src)->base.ret_msg.cstr);	


CSTR lcopenapi_request_build(LCOpenApi_LCOpenApiRequest *p, void *obj, metainfo_t *mi, char *isSys);
int lcopenapi_request_sign(LCOpenApi_LCOpenApiRequest *p, const char *appId, const char *appSecret, const char *time);
int lcopenapi_response_parse(LCOpenApi_LCOpenApiResponse *p, void *obj, metainfo_t *mi);

}
#endif
