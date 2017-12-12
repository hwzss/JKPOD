#define _CRT_SECURE_NO_WARNINGS
#include <string.h>
#include <stdarg.h>
#include "LCOpenApi_ClientSdk.h"
#include "LCOpenApi_FreeBuffer.h"
#include "curl/win32/curl.h"
#include "algorithm/LCOpenApi_algorithm.h"


namespace LCOpenApi{
#ifdef WIN32
#define snprintf sprintf_s
#endif


/************************************************************************/
/* global                                                               */
/************************************************************************/
static CSTR g_client_version = CS("1.0");
static CSTR g_appId;
    static CSTR g_appSecret;

static unsigned int g_serialNo = 0;

void LCOpenApi_lcopenapi_client_set_appId(const char *appId)
{
	CS_CLEAR(g_appId);
	g_appId = CS(appId);
}
void LCOpenApi_lcopenapi_client_set_appSecret(const char *appSecret)
{
	CS_CLEAR(g_appSecret);
	g_appSecret = CS(appSecret);
}

CSTR LCOpenApi_lcopenapi_client_get_version()
{
	return g_client_version;
}

CSTR LCOpenApi_lcopenapi_client_get_appId()
{
	return g_appId;
}
CSTR LCOpenApi_lcopenapi_client_get_appSecret()
{
	return g_appSecret;
}

unsigned int LCOpenApi_lcopenapi_client_get_serialNo()
{
	int sNo = 0;

	sNo = g_serialNo++;
	return sNo;
}

/************************************************************************/
/* struct                                                               */
/************************************************************************/
typedef struct
{
	CURL *curl;
	free_buffer_t resp_buf;
}curl_obj_t;

typedef struct
{
	int port;
	CSTR host;

	CSTR appId;
	CSTR appSecret;
} client_t;

/************************************************************************/
/* callback                                                             */
/************************************************************************/
static size_t write_data(void *buffer, size_t size, size_t nmemb, void *user)
{
	curl_obj_t *curl_obj = (curl_obj_t *)user;

	free_buffer_append(&curl_obj->resp_buf, buffer, size * nmemb);

	return size * nmemb;
}

/************************************************************************/
/* curl obj                                                                      */
/************************************************************************/
static curl_obj_t* _curl_obj_create()
{
	curl_obj_t *curl_obj = (curl_obj_t *)malloc(sizeof(curl_obj_t));
	if (!curl_obj)
	{
		printf("[%s:%d]malloc curl_obj fail!\n",__FUNCTION__,__LINE__);
		return NULL;
	}

	memset(curl_obj, 0, sizeof(curl_obj_t));
	
	curl_obj->curl = curl_easy_init();
	if (!curl_obj->curl)
	{
		printf("[%s:%d]curl_easy_init fail!\n",__FUNCTION__,__LINE__);
        free(curl_obj);
		return NULL;
	}

	return curl_obj;
}

static void _curl_obj_destroy(curl_obj_t *curl_obj)
{
	if (curl_obj)
	{
		curl_easy_cleanup(curl_obj->curl);
		free_buffer_destroy(&curl_obj->resp_buf);
		free(curl_obj);
	}
}

/************************************************************************/
/*  api                                                                 */
/************************************************************************/
LCOpenApi_LCOpenApiClient LCOpenApi_lcopenapi_client_create(const char *host, int port)
{
	client_t *pc = (client_t *)malloc(sizeof(client_t));
	if (!pc)
	{
		printf("[%s:%d]malloc fail!\n",__FUNCTION__,__LINE__);
		return NULL;
	}
	memset(pc, 0, sizeof(client_t));

	pc->host = CS(host);
	pc->port = port;

	return (LCOpenApi_LCOpenApiClient)pc;
}

void LCOpenApi_lcopenapi_client_destroy(LCOpenApi_LCOpenApiClient hc)
{
	client_t *pc = (client_t *)hc;
	if (pc)
	{
		CS_CLEAR(pc->host);
		free(pc);
	}
}

static int LCOpenApi_parse_response(curl_obj_t *curl_obj, LCOpenApi_LCOpenApiResponse *resp)
{
	long code = 0;
	long header_size = 0;
	CSTR headers;
	char str_code[16] = {0};

	curl_easy_getinfo(curl_obj->curl, CURLINFO_RESPONSE_CODE, &code);
	curl_easy_getinfo(curl_obj->curl, CURLINFO_HEADER_SIZE, &header_size);

	if (header_size < 0)
	{
		printf("[%s:%d]http response headers error!\n",__FUNCTION__,__LINE__);
		return -1;
	}
	headers = const_string_new_length(curl_obj->resp_buf.ptr, header_size);

	snprintf(str_code, sizeof(str_code), " %ld ", code);

	resp->headers = headers;
	resp->code = code;
	resp->desc = const_string_sub_between(headers, str_code, "\r\n");

	resp->content_length = (int)curl_obj->resp_buf.length - header_size;
	resp->content = CS(curl_obj->resp_buf.ptr + header_size);

	printf( "[%s:%d]response body:\n%s", __FUNCTION__,__LINE__,resp->content.cstr);

	resp->parse(resp);

	return 0;
}

static int LCOpenApi_request(client_t *pc, curl_obj_t *curl_obj, LCOpenApi_LCOpenApiRequest *req, LCOpenApi_LCOpenApiResponse *resp, long timeout, const char *datetime)
{
	char url[1024] = {0};
	CURLcode res;
	struct curl_slist *headers = NULL;
//	char attrHeader[200] = {0};

	// 组装
	req->build(req);
	

	// 签名
	CS_CLEAR(req->signMd5);
	req->sign(req,LCOpenApi_lcopenapi_client_get_appId().cstr,LCOpenApi_lcopenapi_client_get_appSecret().cstr,datetime);

	printf("[%s:%d]request: %s\n",__FUNCTION__,__LINE__, req->uri.cstr);
	printf( "[%s:%d]request body:\n%s",__FUNCTION__,__LINE__, req->body.cstr);

	// 设定超时
	curl_easy_setopt(curl_obj->curl, CURLOPT_TIMEOUT, timeout);

	
	if (pc->port == 443)
	{
		curl_easy_setopt(curl_obj->curl, CURLOPT_SSL_VERIFYPEER, 0); // whether verifies the authenticity of the peer's certificate  

		// 设置URL
		snprintf(url, sizeof(url), "https://%s:%d%s", pc->host.cstr, pc->port, req->uri.cstr);
	}
	else
	{
		// 设置URL
		snprintf(url, sizeof(url), "http://%s:%d%s", pc->host.cstr, pc->port, req->uri.cstr);
	}

	curl_easy_setopt(curl_obj->curl, CURLOPT_URL, url);

	// 设置为短连接，去掉Accept头
	headers = curl_slist_append(headers, "Connection: close");
	headers = curl_slist_append(headers, "Accept:");

	// 如果是POST，加入content
	if (0 == strcmp(req->method.cstr, "POST"))
	{
		char hbuf[1024] = {0};
		snprintf(hbuf, sizeof(hbuf), "Content-Type: %s", req->content_type.cstr);
		headers = curl_slist_append(headers, hbuf);
		curl_easy_setopt(curl_obj->curl, CURLOPT_POST, 1);
		curl_easy_setopt(curl_obj->curl, CURLOPT_POSTFIELDS, req->body.cstr);
	}

	// 将头域设置进去
	curl_easy_setopt(curl_obj->curl, CURLOPT_HTTPHEADER, headers);

	// 需要清一下接收缓存
	free_buffer_clear(&curl_obj->resp_buf);

	// 执行
	res = curl_easy_perform(curl_obj->curl);
	if (res != CURLE_OK)
	{
		printf("[%s:%d]curl_easy_perform fail[%d]\n",__FUNCTION__,__LINE__, res);
		return -1;
	}
	
	// 清除slist内存
	curl_slist_free_all(headers);

	// 解析response
	return LCOpenApi_parse_response(curl_obj, resp);
}

int LCOpenApi_lcopenapi_client_request(LCOpenApi_LCOpenApiClient hc, LCOpenApi_LCOpenApiRequest *req, LCOpenApi_LCOpenApiResponse *resp, int timeout)
{
	int ret;
	curl_obj_t *curl_obj = NULL;

	client_t *pc = (client_t *)hc;
	if (!pc || !req || !resp)
	{
		return -1;
	}

	curl_obj = _curl_obj_create();
	if (!curl_obj)
	{
		return -1;
	}

	curl_easy_setopt(curl_obj->curl, CURLOPT_FOLLOWLOCATION, 1);
	curl_easy_setopt(curl_obj->curl, CURLOPT_WRITEFUNCTION, write_data);
	curl_easy_setopt(curl_obj->curl, CURLOPT_WRITEDATA, curl_obj);
	curl_easy_setopt(curl_obj->curl, CURLOPT_HEADER, 1);
	curl_easy_setopt(curl_obj->curl, CURLOPT_NOSIGNAL, 1);

	ret = LCOpenApi_request(pc, curl_obj, req, resp, timeout, NULL);
	if (ret != 0)
	{
		return -1;
	}

	printf("[%s:%d]response [%s] return: %d",__FUNCTION__,__LINE__, req->apiname.cstr, resp->code);

	if (req->messageId.cstr && resp->id.cstr && strcmp(req->messageId.cstr,resp->id.cstr))
	{
		printf("[%s:%d]not match,requestid[%s],response id[%s]\n",__FUNCTION__,__LINE__,req->messageId.cstr,resp->id.cstr);
		_curl_obj_destroy(curl_obj);
		return -1;
	}
	_curl_obj_destroy(curl_obj);
	return 0;
}

}