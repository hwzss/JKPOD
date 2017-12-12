/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 34876, Author: 21818, Date: 2016-05-25 10:30:44 +0800 
 *  SHOULD NOT MODIFY!
 */




#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include "LCOpenApi_Common.h"
#include "api/AccessToken.h"

/************************************************************************/
/* request                                                              */
/************************************************************************/

namespace LCOpenApi{
static metainfo_t *METAINFO(AccessTokenRequestData) = NULL;

static int build(LCOpenApi_LCOpenApiRequest *p)
{
	AccessTokenRequest *req = (AccessTokenRequest *)p;
	
	p->body = lcopenapi_request_build(p, &req->data, METAINFO(AccessTokenRequestData),(char*)"T");
	if (p->body.cstr == NULL)
	{
		return -1;
	}
	
	return 0;
}

static void request_destroy(LCOpenApi_LCOpenApiRequest *p)
{
	AccessTokenRequest *req = (AccessTokenRequest *)p;
	
	OBJECT_CLEAR(req->data, AccessTokenRequestData);
	
	LCOPENAPI_REQUEST_CLEAR(req);
	
	free(req);
}

AccessTokenRequest *LCOpenApi_LCOPENAPI_INIT(AccessTokenRequest)
{
	AccessTokenRequest *ptr = (AccessTokenRequest *)malloc(sizeof(AccessTokenRequest));
	memset(ptr, 0, sizeof(AccessTokenRequest));
	
	if (METAINFO(AccessTokenRequestData) == NULL)
	{
		METAINFO_CREATE(AccessTokenRequestData,AccessTokenRequest);
		
		METAINFO_ADD_MEMBER(AccessTokenRequestData,AccessTokenRequest, FIELD_TYPE_CSTR, phone);

	}

	ptr->base.apiname = CS("AccessToken");
	ptr->base.fullname = CS("accessToken");
	ptr->base.method = CS("POST");
	const_string_append(&ptr->base.uri, "/openapi/accessToken");
	ptr->base.content_type = CS("application/json");
	ptr->base.build = build;
	ptr->base.sign = lcopenapi_request_sign;
	ptr->base.destroy = request_destroy;

	return ptr;
}

/************************************************************************/
/* response                                                             */
/************************************************************************/
static metainfo_t *METAINFO(AccessTokenResponseData) = NULL;

static int parse(LCOpenApi_LCOpenApiResponse *p)
{
	AccessTokenResponse *resp = (AccessTokenResponse *)p;
	
	int ret = lcopenapi_response_parse(p, &resp->data, METAINFO(AccessTokenResponseData));
	if (ret != 0)
	{
		return -1;
	}
	
	return 0;
}

static void response_copy(LCOpenApi_LCOpenApiResponse *p, struct LCOpenApi_LCOpenApiResponse *src)
{
	AccessTokenResponse *resp = (AccessTokenResponse *)p;
	AccessTokenResponse *resp_src = (AccessTokenResponse *)src;
	
	LCOPENAPI_RESPONSE_COPY(resp, resp_src);
	
	OBJECT_COPY(resp->data, resp_src->data, AccessTokenResponseData);
}

static void response_destroy(LCOpenApi_LCOpenApiResponse *p)
{
	AccessTokenResponse *resp = (AccessTokenResponse *)p;
	
	OBJECT_CLEAR(resp->data, AccessTokenResponseData);
	
	LCOPENAPI_RESPONSE_CLEAR(resp);

	free(resp);
}

AccessTokenResponse *LCOpenApi_LCOPENAPI_INIT(AccessTokenResponse)
{
	AccessTokenResponse *ptr = (AccessTokenResponse *)malloc(sizeof(AccessTokenResponse));
	memset(ptr, 0, sizeof(AccessTokenResponse));

	if (METAINFO(AccessTokenResponseData) == NULL)
	{
		METAINFO_CREATE(AccessTokenResponseData,AccessTokenResponse);
		
		METAINFO_ADD_MEMBER(AccessTokenResponseData,AccessTokenResponse, FIELD_TYPE_CSTR, accessToken);

	}

	ptr->base.parse = parse;
	ptr->base.copy = response_copy;
	ptr->base.destroy = response_destroy;

	return ptr;
}

}