//
//  openApiService.m
//  appDemo
//
//  Created by chenjian on 16/7/8.
//  Copyright (c) 2016年 yao_bao. All rights reserved.
//

#import "OpenApiService.h"
#import "api/AccessToken.h"
#import "api/UserBind.h"
#import "api/UserBindSms.h"
#import "api/UserToken.h"
using namespace LCOpenApi;

@implementation OpenApiService
- (NSInteger)getAccessToken:(NSString*)ip_In port:(NSInteger)port_In appId:(NSString*)appId_In appSecret:(NSString*)appSecret_In phone:(NSString*)phoneNum_In token:(NSString**)accessTok_Out errcode:(NSString**)strErrCode_Out errmsg:(NSString**)errMsg_Out
{
    appId_In = @"lc92b6ac4d595d4f74";
    appSecret_In = @"8d7836c0e91a45b9a07f3a40f89730";
    LCOpenApi_LCOpenApiClient chc = LCOpenApi_lcopenapi_client_create([ip_In UTF8String], (int)port_In);
    LCOpenApi_lcopenapi_client_set_appId([appId_In UTF8String]);
    LCOpenApi_lcopenapi_client_set_appSecret([appSecret_In UTF8String]);

    AccessTokenRequest* req;
    AccessTokenResponse* resp;

    int ret = 0;
    req = LCOpenApi_LCOPENAPI_INIT(AccessTokenRequest);
    resp = LCOpenApi_LCOPENAPI_INIT(AccessTokenResponse);
    req->data.phone = CS([phoneNum_In UTF8String]);

    ret = LCOpenApi_lcopenapi_client_request(chc, (LCOpenApi_LCOpenApiRequest*)req, (LCOpenApi_LCOpenApiResponse*)resp, 10);

    printf("getAccessToken ret[%d]\n", ret);
    bool bret = false;
    if (0 == ret) {
        int code = resp->base.code;
        char* ret_code = resp->base.ret_code.cstr;
        if (HTTP_OK == code) {
            if (!strcmp(ret_code, "0")) {
                if (resp->data.accessToken.cstr) {
                    *accessTok_Out = [NSString stringWithUTF8String:resp->data.accessToken.cstr];
                }
                NSLog(@"getAccessToken accessToken[%@]\n", *accessTok_Out);
                bret = true;
            }
            else {
                *strErrCode_Out = [NSString stringWithUTF8String:ret_code];
                *errMsg_Out = [NSString stringWithUTF8String:resp->base.ret_msg.cstr];
            }
        }
    }
    LCOpenApi_LCOPENAPI_DESTROY(req);
    LCOpenApi_LCOPENAPI_DESTROY(resp);
    LCOpenApi_lcopenapi_client_destroy(chc);
    return bret ? 0 : -1;
}
- (NSInteger)getUserToken:(NSString*)ip_In port:(NSInteger)port_In appId:(NSString*)appId_In appSecret:(NSString*)appSecret_In phone:(NSString*)phoneNum_In token:(NSString**)accessTok_Out errcode:(NSString**)strErrCode_Out errmsg:(NSString**)errMsg_Out
{
    appId_In = @"lc92b6ac4d595d4f74";
    appSecret_In = @"8d7836c0e91a45b9a07f3a40f89730";
    LCOpenApi_LCOpenApiClient chc = LCOpenApi_lcopenapi_client_create([ip_In UTF8String], (int)port_In);
    LCOpenApi_lcopenapi_client_set_appId([appId_In UTF8String]);
    LCOpenApi_lcopenapi_client_set_appSecret([appSecret_In UTF8String]);

    UserTokenRequest* req;
    UserTokenResponse* resp;

    int ret = 0;
    strErrCode_Out[0] = 0;
    errMsg_Out[0] = 0;
    req = LCOpenApi_LCOPENAPI_INIT(UserTokenRequest);
    resp = LCOpenApi_LCOPENAPI_INIT(UserTokenResponse);
    req->data.phone = CS([phoneNum_In UTF8String]);

    ret = LCOpenApi_lcopenapi_client_request(chc, (LCOpenApi_LCOpenApiRequest*)req, (LCOpenApi_LCOpenApiResponse*)resp, 10);

    printf("getUserToken ret[%d]\n", ret);
    bool bret = false;
    if (0 == ret) {
        int code = resp->base.code;
        char* ret_code = resp->base.ret_code.cstr;
        if (HTTP_OK == code) {
            if (!strcmp(ret_code, "0")) {
                if (resp->data.userToken.cstr) {
                    printf("getUserToken[%s]\n", resp->data.userToken.cstr);
                    *accessTok_Out = [NSString stringWithUTF8String:resp->data.userToken.cstr];
                }
                bret = true;
            }
            else {
                *strErrCode_Out = [NSString stringWithUTF8String:ret_code];
                *errMsg_Out = [NSString stringWithUTF8String:resp->base.ret_msg.cstr];
            }
        }
    }
    LCOpenApi_LCOPENAPI_DESTROY(req);
    LCOpenApi_LCOPENAPI_DESTROY(resp);
    LCOpenApi_lcopenapi_client_destroy(chc);
    return bret ? 0 : -1;
}

- (NSInteger)userBindSms:(NSString*)ip_In port:(NSInteger)port_In appId:(NSString*)appId_In appSecret:(NSString*)appSecret_In phone:(NSString*)phoneNum_In errcode:(NSString**)strErrCode_Out errmsg:(NSString**)errMsg_Out
{
    
    appId_In = @"lc92b6ac4d595d4f74";
    appSecret_In = @"8d7836c0e91a45b9a07f3a40f89730";
    LCOpenApi_LCOpenApiClient chc = LCOpenApi_lcopenapi_client_create([ip_In UTF8String], (int)port_In);
    LCOpenApi_lcopenapi_client_set_appId([appId_In UTF8String]);
    LCOpenApi_lcopenapi_client_set_appSecret([appSecret_In UTF8String]);

    userBindSmsRequest* req;
    userBindSmsResponse* resp;

    int ret = 0;
    req = LCOpenApi_LCOPENAPI_INIT(userBindSmsRequest);
    resp = LCOpenApi_LCOPENAPI_INIT(userBindSmsResponse);
    req->data.phone = CS([phoneNum_In UTF8String]);

    ret = LCOpenApi_lcopenapi_client_request(chc, (LCOpenApi_LCOpenApiRequest*)req, (LCOpenApi_LCOpenApiResponse*)resp, 10);

    printf("userBindSms ret[%d]\n", ret);
    bool bret = false;
    if (0 == ret) {
        int code = resp->base.code;
        char* ret_code = resp->base.ret_code.cstr;
        if (HTTP_OK == code) {
            if (!strcmp(ret_code, "0")) {
                printf("userBindSms success\n");
                bret = true;
            }
            else {
                *strErrCode_Out = [NSString stringWithUTF8String:ret_code];
                *errMsg_Out = [NSString stringWithUTF8String:resp->base.ret_msg.cstr];
            }
        }
    }
    LCOpenApi_LCOPENAPI_DESTROY(req);
    LCOpenApi_LCOPENAPI_DESTROY(resp);
    LCOpenApi_lcopenapi_client_destroy(chc);
    return bret ? 0 : -1;
}

- (NSInteger)userBind:(NSString*)ip_In port:(NSInteger)port_In appId:(NSString*)appId_In appSecret:(NSString*)appSecret_In phone:(NSString*)phoneNum_In smscode:(NSString*)smsCode errmsg:(NSString**)errMsgOut
{
    appId_In = @"lc92b6ac4d595d4f74";
    appSecret_In = @"8d7836c0e91a45b9a07f3a40f89730";
    LCOpenApi_LCOpenApiClient chc = LCOpenApi_lcopenapi_client_create([ip_In UTF8String], (int)port_In);
    LCOpenApi_lcopenapi_client_set_appId([appId_In UTF8String]);
    LCOpenApi_lcopenapi_client_set_appSecret([appSecret_In UTF8String]);

    UserBindRequest* req;
    UserBindResponse* resp;

    int ret = 0;
    req = LCOpenApi_LCOPENAPI_INIT(UserBindRequest);
    resp = LCOpenApi_LCOPENAPI_INIT(UserBindResponse);
    req->data.phone = CS([phoneNum_In UTF8String]);
    req->data.smsCode = CS([smsCode UTF8String]);

    ret = LCOpenApi_lcopenapi_client_request(chc, (LCOpenApi_LCOpenApiRequest*)req, (LCOpenApi_LCOpenApiResponse*)resp, 10);

    printf("userBind ret[%d]\n", ret);
    bool bret = false;
    if (0 == ret) {
        int code = resp->base.code;
        char* ret_code = resp->base.ret_code.cstr;
        if (HTTP_OK == code) {
            if (!strcmp(ret_code, "0")) {
                printf("userBind success\n");
                bret = true;
            }
            else {
                if (resp->base.ret_msg.cstr) {
                    *errMsgOut = [NSString stringWithUTF8String:resp->base.ret_msg.cstr];
                }
            }
        }
    }
    LCOpenApi_LCOPENAPI_DESTROY(req);
    LCOpenApi_LCOPENAPI_DESTROY(resp);
    LCOpenApi_lcopenapi_client_destroy(chc);
    return bret ? 0 : -1;
}
@end
