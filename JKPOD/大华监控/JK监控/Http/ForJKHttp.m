
//
//  ForJKHttp.m
//  safeSheidEstate
//
//  Created by qwkj on 2017/9/15.
//  Copyright © 2017年 qwkj. All rights reserved.
//

#import "ForJKHttp.h"
#import "User.h"
#import "MJExtension.h"

#pragma -mark 获取该小区所有的磁盘信息
#define CIM_getDeviceList_URL @"/EstateService/httpInterface/YWYvideoDevice/getDeviceList"
#define CIM_getDeviceListV2_URL @"/EstateService/httpInterface/YWYvideoDevice/getDeviceListV2"

@implementation ForJKHttp
+(void)SE_getDeviceListV2:(void(^)(NSMutableArray *list))success Error:(RequestError)errorblock  Connectfailure:(RequestConnectfailure)ConnectfailureBlock{
    [CIM_HTTPTool CIM_POST_3:[URLTOOL officialUrlWithStr:CIM_getDeviceListV2_URL] parameters:^(NSMutableDictionary *params) {
        params[@"communityId"]=[User shareInstance].communityId;
    } success:^(id jsonData) {
        NSMutableArray *List = [SE_Device objectArrayWithKeyValuesArray:jsonData];
        if (success) {
            success(List);
        }
    } failure:^(NSString *errorStr) {
        if (errorblock) {
            errorblock(errorStr);
        }
        
    } connectfailure:^(BOOL *isShowErrorAlert) {
        if (ConnectfailureBlock) {
            ConnectfailureBlock(isShowErrorAlert);
        }
    }];
}
+(void)SE_getDeviceList:(void(^)(NSMutableArray *list))success Error:(RequestError)errorblock  Connectfailure:(RequestConnectfailure)ConnectfailureBlock{
    [CIM_HTTPTool CIM_POST_3:[URLTOOL officialUrlWithStr:CIM_getDeviceList_URL] parameters:^(NSMutableDictionary *params) {
        params[@"communityId"]=[User shareInstance].communityId;
    } success:^(id jsonData) {
        NSMutableArray *List = [[jsonData objectForKey:@"deviceIds"] mutableCopy];
        if (success) {
            success(List);
        }
    } failure:^(NSString *errorStr) {
        if (errorblock) {
            errorblock(errorStr);
        }
        
    } connectfailure:^(BOOL *isShowErrorAlert) {
        if (ConnectfailureBlock) {
            ConnectfailureBlock(isShowErrorAlert);
        }
    }];
}

+(void)SE_getVideoCountInfo:(void(^)(NSString *videoToken,NSString *phone))success Error:(RequestError)errorblock  Connectfailure:(RequestConnectfailure)ConnectfailureBlock{
    [CIM_HTTPTool CIM_POST_3:[URLTOOL officialUrlWithStr:CIM_getVideoCountInfo_URL] parameters:^(NSMutableDictionary *params) {
        
    } success:^(id jsonData) {
        NSDictionary *dict = (NSDictionary *)jsonData;
        NSString *videoToken = [dict objectForKey:@"videoToken"];
        NSString *phone = [dict objectForKey:@"phone"];
        if (success) {
            success(videoToken,phone);
        }
    } failure:^(NSString *errorStr) {
        if (errorblock) {
            errorblock(errorStr);
        }
        
    } connectfailure:^(BOOL *isShowErrorAlert) {
        if (ConnectfailureBlock) {
            ConnectfailureBlock(isShowErrorAlert);
        }
    }];
}

@end
