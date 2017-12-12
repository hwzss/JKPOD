/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: unknown, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */

#include "api/UserToken.h"
#include "LCOpenApi_Common.h"
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

/************************************************************************/
/* request                                                              */
/************************************************************************/
namespace LCOpenApi{
static metainfo_t *METAINFO(UserTokenRequestData) = NULL;

static int build(LCOpenApi_LCOpenApiRequest *p)
{
	UserTokenRequest *req = (UserTokenRequest *)p;
	
	p->body = lcopenapi_request_build(p, &req->data, METAINFO(UserTokenRequestData),(char*)"T");
	if (p->body.cstr == NULL)
	{
		return -1;
	}
	
	return 0;
}

static void request_destroy(LCOpenApi_LCOpenApiRequest *p)
{
	UserTokenRequest *req = (UserTokenRequest *)p;
	
	OBJECT_CLEAR(req->data, UserTokenRequestData);
	
	LCOPENAPI_REQUEST_CLEAR(req);
	
	free(req);
}

UserTokenRequest *LCOpenApi_LCOPENAPI_INIT(UserTokenRequest)
{
	UserTokenRequest *ptr = (UserTokenRequest *)malloc(sizeof(UserTokenRequest));
	memset(ptr, 0, sizeof(UserTokenRequest));
	
	if (METAINFO(UserTokenRequestData) == NULL)
	{
		METAINFO_CREATE(UserTokenRequestData,UserTokenRequest);
		
		METAINFO_ADD_MEMBER(UserTokenRequestData,UserTokenRequest, FIELD_TYPE_CSTR, phone);

	}

	ptr->base.apiname = CS("UserToken");
	ptr->base.fullname = CS("userToken");
	ptr->base.method = CS("POST");
	const_string_append(&ptr->base.uri, "/openapi/userToken");
	ptr->base.content_type = CS("application/json");
	ptr->base.build = build;
	ptr->base.sign = lcopenapi_request_sign;
	ptr->base.destroy = request_destroy;

	return ptr;
}

/************************************************************************/
/* response                                                             */
/************************************************************************/
static metainfo_t *METAINFO(UserTokenResponseData) = NULL;

static int parse(LCOpenApi_LCOpenApiResponse *p)
{
	UserTokenResponse *resp = (UserTokenResponse *)p;
	
	int ret = lcopenapi_response_parse(p, &resp->data, METAINFO(UserTokenResponseData));
	if (ret != 0)
	{
		return -1;
	}
	
	return 0;
}

static void response_copy(LCOpenApi_LCOpenApiResponse *p, struct LCOpenApi_LCOpenApiResponse *src)
{
	UserTokenResponse *resp = (UserTokenResponse *)p;
	UserTokenResponse *resp_src = (UserTokenResponse *)src;
	
	LCOPENAPI_RESPONSE_COPY(resp, resp_src);
	
	OBJECT_COPY(resp->data, resp_src->data, UserTokenResponseData);
}

static void response_destroy(LCOpenApi_LCOpenApiResponse *p)
{
	UserTokenResponse *resp = (UserTokenResponse *)p;
	
	OBJECT_CLEAR(resp->data, UserTokenResponseData);
	
	LCOPENAPI_RESPONSE_CLEAR(resp);

	free(resp);
}

UserTokenResponse *LCOpenApi_LCOPENAPI_INIT(UserTokenResponse)
{
	UserTokenResponse *ptr = (UserTokenResponse *)malloc(sizeof(UserTokenResponse));
	memset(ptr, 0, sizeof(UserTokenResponse));

	if (METAINFO(UserTokenResponseData) == NULL)
	{
		METAINFO_CREATE(UserTokenResponseData,UserTokenResponse);
		
		METAINFO_ADD_MEMBER(UserTokenResponseData,UserTokenResponse, FIELD_TYPE_CSTR, userToken);

	}

	ptr->base.parse = parse;
	ptr->base.copy = response_copy;
	ptr->base.destroy = response_destroy;

	return ptr;
}
}