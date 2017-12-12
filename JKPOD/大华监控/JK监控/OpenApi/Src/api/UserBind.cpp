/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: unknown, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */

#include "api/UserBind.h"
#include "LCOpenApi_Common.h"
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

/************************************************************************/
/* request                                                              */
/************************************************************************/
namespace LCOpenApi{
static metainfo_t *METAINFO(UserBindRequestData) = NULL;

static int build(LCOpenApi_LCOpenApiRequest *p)
{
	UserBindRequest *req = (UserBindRequest *)p;
	
	p->body = lcopenapi_request_build(p, &req->data, METAINFO(UserBindRequestData),(char*)"T");
	if (p->body.cstr == NULL)
	{
		return -1;
	}
	
	return 0;
}

static void request_destroy(LCOpenApi_LCOpenApiRequest *p)
{
	UserBindRequest *req = (UserBindRequest *)p;
	
	OBJECT_CLEAR(req->data, UserBindRequestData);
	
	LCOPENAPI_REQUEST_CLEAR(req);
	
	free(req);
}

UserBindRequest *LCOpenApi_LCOPENAPI_INIT(UserBindRequest)
{
	UserBindRequest *ptr = (UserBindRequest *)malloc(sizeof(UserBindRequest));
	memset(ptr, 0, sizeof(UserBindRequest));
	
	if (METAINFO(UserBindRequestData) == NULL)
	{
		METAINFO_CREATE(UserBindRequestData,UserBindRequest);
		
		METAINFO_ADD_MEMBER(UserBindRequestData,UserBindRequest, FIELD_TYPE_CSTR, phone);
		METAINFO_ADD_MEMBER(UserBindRequestData, UserBindRequest,FIELD_TYPE_CSTR, smsCode);

	}

	ptr->base.apiname = CS("UserBind");
	ptr->base.fullname = CS("userBind");
	ptr->base.method = CS("POST");
	const_string_append(&ptr->base.uri, "/openapi/userBind");
	ptr->base.content_type = CS("application/json");
	ptr->base.build = build;
	ptr->base.sign = lcopenapi_request_sign;
	ptr->base.destroy = request_destroy;

	return ptr;
}

/************************************************************************/
/* response                                                             */
/************************************************************************/
static metainfo_t *METAINFO(UserBindResponseData) = NULL;

static int parse(LCOpenApi_LCOpenApiResponse *p)
{
	UserBindResponse *resp = (UserBindResponse *)p;
	
	int ret = lcopenapi_response_parse(p, &resp->data, METAINFO(UserBindResponseData));
	if (ret != 0)
	{
		return -1;
	}
	
	return 0;
}

static void response_copy(LCOpenApi_LCOpenApiResponse *p, struct LCOpenApi_LCOpenApiResponse *src)
{
	UserBindResponse *resp = (UserBindResponse *)p;
	UserBindResponse *resp_src = (UserBindResponse *)src;
	
	LCOPENAPI_RESPONSE_COPY(resp, resp_src);
	
	OBJECT_COPY(resp->data, resp_src->data, UserBindResponseData);
}

static void response_destroy(LCOpenApi_LCOpenApiResponse *p)
{
	UserBindResponse *resp = (UserBindResponse *)p;
	
	OBJECT_CLEAR(resp->data, UserBindResponseData);
	
	LCOPENAPI_RESPONSE_CLEAR(resp);

	free(resp);
}

UserBindResponse *LCOpenApi_LCOPENAPI_INIT(UserBindResponse)
{
	UserBindResponse *ptr = (UserBindResponse *)malloc(sizeof(UserBindResponse));
	memset(ptr, 0, sizeof(UserBindResponse));

	if (METAINFO(UserBindResponseData) == NULL)
	{
		METAINFO_CREATE(UserBindResponseData,UserBindResponse);
		
		METAINFO_ADD_MEMBER(UserBindResponseData,UserBindResponse, FIELD_TYPE_INT, _nouse);

	}

	ptr->base.parse = parse;
	ptr->base.copy = response_copy;
	ptr->base.destroy = response_destroy;

	return ptr;
}

}