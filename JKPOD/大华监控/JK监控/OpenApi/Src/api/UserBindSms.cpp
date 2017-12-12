/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: unknown, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */

#include "api/userBindSms.h"
#include "LCOpenApi_Common.h"
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

/************************************************************************/
/* request                                                              */
/************************************************************************/
namespace LCOpenApi{
static metainfo_t *METAINFO(userBindSmsRequestData) = NULL;

static int build(LCOpenApi_LCOpenApiRequest *p)
{
	userBindSmsRequest *req = (userBindSmsRequest *)p;
	
	p->body = lcopenapi_request_build(p, &req->data, METAINFO(userBindSmsRequestData),(char*)"T");
	if (p->body.cstr == NULL)
	{
		return -1;
	}
	
	return 0;
}

static void request_destroy(LCOpenApi_LCOpenApiRequest *p)
{
	userBindSmsRequest *req = (userBindSmsRequest *)p;
	
	OBJECT_CLEAR(req->data, userBindSmsRequestData);
	
	LCOPENAPI_REQUEST_CLEAR(req);
	
	free(req);
}

userBindSmsRequest *LCOpenApi_LCOPENAPI_INIT(userBindSmsRequest)
{
	userBindSmsRequest *ptr = (userBindSmsRequest *)malloc(sizeof(userBindSmsRequest));
	memset(ptr, 0, sizeof(userBindSmsRequest));
	
	if (METAINFO(userBindSmsRequestData) == NULL)
	{
		METAINFO_CREATE(userBindSmsRequestData,userBindSmsRequest);
		
		METAINFO_ADD_MEMBER(userBindSmsRequestData, userBindSmsRequest,FIELD_TYPE_CSTR, phone);

	}

	ptr->base.apiname = CS("userBindSms");
	ptr->base.fullname = CS("userBindSms");
	ptr->base.method = CS("POST");
	const_string_append(&ptr->base.uri, "/openapi/userBindSms");
	ptr->base.content_type = CS("application/json");
	ptr->base.build = build;
	ptr->base.sign = lcopenapi_request_sign;
	ptr->base.destroy = request_destroy;

	return ptr;
}

/************************************************************************/
/* response                                                             */
/************************************************************************/
static metainfo_t *METAINFO(userBindSmsResponseData) = NULL;

static int parse(LCOpenApi_LCOpenApiResponse *p)
{
	userBindSmsResponse *resp = (userBindSmsResponse *)p;
	
	int ret = lcopenapi_response_parse(p, &resp->data, METAINFO(userBindSmsResponseData));
	if (ret != 0)
	{
		return -1;
	}
	
	return 0;
}

static void response_copy(LCOpenApi_LCOpenApiResponse *p, struct LCOpenApi_LCOpenApiResponse *src)
{
	userBindSmsResponse *resp = (userBindSmsResponse *)p;
	userBindSmsResponse *resp_src = (userBindSmsResponse *)src;
	
	LCOPENAPI_RESPONSE_COPY(resp, resp_src);
	
	OBJECT_COPY(resp->data, resp_src->data, userBindSmsResponseData);
}

static void response_destroy(LCOpenApi_LCOpenApiResponse *p)
{
	userBindSmsResponse *resp = (userBindSmsResponse *)p;
	
	OBJECT_CLEAR(resp->data, userBindSmsResponseData);
	
	LCOPENAPI_RESPONSE_CLEAR(resp);

	free(resp);
}

userBindSmsResponse *LCOpenApi_LCOPENAPI_INIT(userBindSmsResponse)
{
	userBindSmsResponse *ptr = (userBindSmsResponse *)malloc(sizeof(userBindSmsResponse));
	memset(ptr, 0, sizeof(userBindSmsResponse));

	if (METAINFO(userBindSmsResponseData) == NULL)
	{
		METAINFO_CREATE(userBindSmsResponseData,userBindSmsResponse);
		
		METAINFO_ADD_MEMBER(userBindSmsResponseData,userBindSmsResponse, FIELD_TYPE_INT, _nouse);

	}

	ptr->base.parse = parse;
	ptr->base.copy = response_copy;
	ptr->base.destroy = response_destroy;

	return ptr;
}

}