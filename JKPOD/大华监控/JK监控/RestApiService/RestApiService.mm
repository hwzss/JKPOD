//
//  RestApiService.m
//  appDemo
//
//  Created by chenjian on 15/5/25.
//  Copyright (c) 2015年 yao_bao. All rights reserved.
//

#import "RestApiService.h"

#import "LCOPenApiClientSDK/LCOpenApi/BeAuthDeviceList.h"
#import "LCOpenApiClientSDK/LCOpenApi/BindDevice.h"
#import "LCOpenApiClientSDK/LCOpenApi/BindDeviceInfo.h"
#import "LCOpenApiClientSDK/LCOpenApi/CheckDeviceBindOrNot.h"
#import "LCOpenApiClientSDK/LCOpenApi/ControlPtz.h"
#import "LCOpenApiClientSDK/LCOpenApi/DeleteAlarmMessage.h"
#import "LCOpenApiClientSDK/LCOpenApi/DeviceList.h"
#import "LCOpenApiClientSDK/LCOpenApi/DeviceOnline.h"
#import "LCOpenApiClientSDK/LCOpenApi/GetAlarmMessage.h"
#import "LCOpenApiClientSDK/LCOpenApi/ModifyDeviceAlarmStatus.h"
#import "LCOpenApiClientSDK/LCOpenApi/QueryCloudRecordNum.h"
#import "LCOpenApiClientSDK/LCOpenApi/QueryCloudRecords.h"
#import "LCOpenApiClientSDK/LCOpenApi/QueryLocalRecordNum.h"
#import "LCOpenApiClientSDK/LCOpenApi/QueryLocalRecords.h"
#import "LCOpenApiClientSDK/LCOpenApi/SetAllStorageStrategy.h"
#import "LCOpenApiClientSDK/LCOpenApi/SetStorageStrategy.h"
#import "LCOpenApiClientSDK/LCOpenApi/ShareDeviceList.h"
#import "LCOpenApiClientSDK/LCOpenApi/UnBindDevice.h"
#import "LCOpenApiClientSDK/LCOpenApi/getStorageStrategy.h"

#define ACCESSTOKEN_LEN 256

const NSString* NETWORK_TIMEOUT = @"网络超时";
const NSString* INTERFACE_FAILED = @"接口调用失败";
const NSString* MSG_SUCCESS = @"成功";
const NSString* MSG_DEVICE_ONLINE = @"设备在线";
const NSString* MSG_DEVICE_OFFLINE = @"设备离线";
const NSString* MSG_DEVICE_IS_BIND = @"设备已绑定";
const NSString* MSG_DEVICE_NOT_BIND = @"设备未绑定";

const NSString* JK_APP_ID = @"lc92b6ac4d595d4f74";
const NSString* JK_App_Secret = @"8d7836c0e91a45b9a07f3a40f89730";
const NSString* JK_APP_Url = @"openapi.lechange.cn";
const int JK_APP_Port = 443;

@interface RestApiService () {
    LCOpenSDK_Api* m_hc;
    char m_accessToken[ACCESSTOKEN_LEN];
}
@end

@implementation RestApiService

static RestApiService* _instance = nil;
+ (RestApiService*)shareMyInstance
{
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        _instance = [[self alloc] initPrivate];
    });
    return _instance;
}

+ (instancetype)alloc
{
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        _instance = [super alloc];
    });
    return _instance;
}

- (instancetype)initPrivate
{
    self = [super init];
    return self;
}

- (instancetype)init
{
    return [[self class] shareMyInstance];
}

- (void)initComponent:(LCOpenSDK_Api*)hc Token:(NSString*)accessTok_In
{
    if (nil != hc) {
        m_hc = hc;
    }
    if (nil != accessTok_In) {
        strncpy(m_accessToken, [accessTok_In UTF8String], sizeof(m_accessToken) - 1);
    }
}

- (BOOL)getDevList:(NSMutableArray*)info_Out Begin:(NSInteger)beginIndex_In End:(NSInteger)endIndex_In Msg:(NSString**)errMsg_Out
{
    DeviceListRequest* req;
    DeviceListResponse* resp;
    NSInteger ret = 0;
    NSString* sRange = [NSString stringWithFormat:@"%ld-%ld", (long)beginIndex_In, (long)endIndex_In];
    req = LCOPENAPI_INIT(DeviceListRequest);
    resp = LCOPENAPI_INIT(DeviceListResponse);

    req->data.token = CS(m_accessToken);
    req->data.queryRange = CS([sRange UTF8String]);

    *errMsg_Out = [INTERFACE_FAILED mutableCopy];
    ret = [m_hc request:req resp:resp timeout:10];
    NSLog(@"getDevList ret[%ld]", (long)ret);
    if (0 == ret) {
        int code = resp->base.code;

        if (HTTP_OK == code) {
            NSString* ret_code;
            if (resp->base.ret_code.cstr) {
                ret_code = [NSString stringWithUTF8String:resp->base.ret_code.cstr];
            }
            if ([ret_code isEqualToString:@"0"]) {
                for (int i = 0; i < resp->data.devices.size; i++) {
                    DeviceInfo* i_deviceInfo = [[DeviceInfo alloc] init];

                    NSLog(@"getDevList deviceid[%s],ability[%s],online[%d],name[%s]", resp->data.devices.array[i].deviceId.cstr, resp->data.devices.array[i].ability.cstr, resp->data.devices.array[i].status, resp->data.devices.array[i].name.cstr);
                    if (resp->data.devices.array[i].deviceId.cstr) {
                        i_deviceInfo->ID = [NSString stringWithUTF8String:resp->data.devices.array[i].deviceId.cstr];
                    }
                    if (resp->data.devices.array[i].ability.cstr) {
                        i_deviceInfo->ability = [NSString stringWithUTF8String:resp->data.devices.array[i].ability.cstr];
                    }
                    i_deviceInfo->devOnline = resp->data.devices.array[i].status;
                    i_deviceInfo->channelSize = resp->data.devices.array[i].channels.size;
                    i_deviceInfo->encryptMode = resp->data.devices.array[i].encryptMode;

                    for (int channelIndex = 0; channelIndex < resp->data.devices.array[i].channels.size && channelIndex < CHANNEL_MAX; channelIndex++) {
                        NSLog(@"getDevList channelId=%d", resp->data.devices.array[i].channels.array[channelIndex].channelId);
                        i_deviceInfo->channelId[channelIndex] = resp->data.devices.array[i].channels.array[channelIndex].channelId;

                        NSLog(@"getDevList channelonline=%d", resp->data.devices.array[i].channels.array[channelIndex].channelOnline);
                        i_deviceInfo->isOnline[channelIndex] = resp->data.devices.array[i].channels.array[channelIndex].channelOnline;

                        NSLog(@"getDevList channelAlarmStatus=%d", resp->data.devices.array[i].channels.array[channelIndex].alarmStatus);

                        i_deviceInfo->alarmStatus[channelIndex] = (AlarmStatus)resp->data.devices.array[i].channels.array[channelIndex].alarmStatus;

                        NSLog(@"getDevList channelCsStatus=%d", resp->data.devices.array[i].channels.array[channelIndex].csStatus);

                        i_deviceInfo->csStatus[channelIndex] = (CloudStorageStatus)resp->data.devices.array[i].channels.array[channelIndex].csStatus;

//                        if (resp->data.devices.array[i].channels.array[channelIndex].channelAbility.cstr) {
//                            NSLog(@"getDevList channelAbility=%s", resp->data.devices.array[i].channels.array[channelIndex].channelAbility.cstr);
//                            i_deviceInfo->channelAbility[channelIndex] = [NSString stringWithUTF8String:resp->data.devices.array[i].channels.array[channelIndex].channelAbility.cstr];
//                        }
                        if (resp->data.devices.array[i].channels.array[channelIndex].channelPicUrl.cstr) {
                            NSLog(@"getDevList channelPicUrl=%s", resp->data.devices.array[i].channels.array[channelIndex].channelPicUrl.cstr);
                            i_deviceInfo->channelPic[channelIndex] = [NSString stringWithUTF8String:resp->data.devices.array[i].channels.array[channelIndex].channelPicUrl.cstr];
                        }
                        if (resp->data.devices.array[i].channels.array[channelIndex].channelName.cstr) {
                            NSLog(@"getDevList channelname=%s", resp->data.devices.array[i].channels.array[channelIndex].channelName.cstr);
                            i_deviceInfo->channelName[channelIndex] = [NSString stringWithUTF8String:resp->data.devices.array[i].channels.array[channelIndex].channelName.cstr];
                        }
                    }
                    [info_Out addObject:i_deviceInfo];
                }
                *errMsg_Out = [MSG_SUCCESS mutableCopy];
            } else if (resp->base.ret_msg.cstr) {
                *errMsg_Out = [NSString stringWithUTF8String:resp->base.ret_msg.cstr];
            }
        } else if (resp->base.ret_msg.cstr) {
            *errMsg_Out = [NSString stringWithUTF8String:resp->base.ret_msg.cstr];
        }
    } else {
        *errMsg_Out = [NETWORK_TIMEOUT mutableCopy];
    }
    LCOPENAPI_DESTROY(req);
    LCOPENAPI_DESTROY(resp);

    return (0 == ret) ? YES : NO;
}

- (BOOL)beAuthDeviceList:(NSMutableArray*)info_Out Begin:(NSInteger)beginIndex_In End:(NSInteger)endIndex_In Msg:(NSString**)errMsg_Out
{
    BeAuthDeviceListRequest* req;
    BeAuthDeviceListResponse* resp;
    NSInteger ret = 0;
    NSString* sRange = [NSString stringWithFormat:@"%ld-%ld", (long)beginIndex_In, (long)endIndex_In];
    req = LCOPENAPI_INIT(BeAuthDeviceListRequest);
    resp = LCOPENAPI_INIT(BeAuthDeviceListResponse);

    req->data.token = CS(m_accessToken);
    req->data.queryRange = CS([sRange UTF8String]);

    *errMsg_Out = [INTERFACE_FAILED mutableCopy];
    ret = [m_hc request:req resp:resp timeout:10];
    NSLog(@"getDevList ret[%ld]", (long)ret);
    if (0 == ret) {
        int code = resp->base.code;

        if (HTTP_OK == code) {
            NSString* ret_code;
            if (resp->base.ret_code.cstr) {
                ret_code = [NSString stringWithUTF8String:resp->base.ret_code.cstr];
            }
            if ([ret_code isEqualToString:@"0"]) {
                for (int i = 0; i < resp->data.devices.size; i++) {
                    DeviceInfo* i_deviceInfo = [[DeviceInfo alloc] init];

                    if (resp->data.devices.array[i].deviceId.cstr) {
                        i_deviceInfo->ID = [NSString stringWithUTF8String:resp->data.devices.array[i].deviceId.cstr];
                    }
                    if (resp->data.devices.array[i].ability.cstr) {
                        i_deviceInfo->ability = [NSString stringWithUTF8String:resp->data.devices.array[i].ability.cstr];
                    }
                    i_deviceInfo->devOnline = resp->data.devices.array[i].status;
                    i_deviceInfo->channelSize = 1;
                    i_deviceInfo->encryptMode = resp->data.devices.array[i].encryptMode;

                    NSLog(@"getDevList channelId=%d", resp->data.devices.array[i].channelId);
                    i_deviceInfo->channelId[0] = resp->data.devices.array[i].channelId;

                    NSLog(@"getDevList channelonline=%d", resp->data.devices.array[i].channelOnline);
                    i_deviceInfo->isOnline[0] = resp->data.devices.array[i].channelOnline;

                    NSLog(@"getDevList channelAlarmStatus=%d", resp->data.devices.array[i].alarmStatus);

                    i_deviceInfo->alarmStatus[0] = (AlarmStatus)resp->data.devices.array[i].alarmStatus;

                    NSLog(@"getDevList channelCsStatus=%d", resp->data.devices.array[i].csStatus);

                    i_deviceInfo->csStatus[0] = (CloudStorageStatus)resp->data.devices.array[i].csStatus;

                    if (resp->data.devices.array[i].channelPicUrl.cstr) {
                        NSLog(@"getDevList channelPicUrl=%s", resp->data.devices.array[i].channelPicUrl.cstr);
                        i_deviceInfo->channelPic[0] = [NSString stringWithUTF8String:resp->data.devices.array[i].channelPicUrl.cstr];
                    }
                    if (resp->data.devices.array[i].channelName.cstr) {
                        i_deviceInfo->channelName[0] = [[NSString stringWithUTF8String:resp->data.devices.array[i].channelName.cstr] stringByAppendingString:@"[authorized]"];
                        NSLog(@"getDevList channelname=%@", i_deviceInfo->channelName[0]);

                    }
                    [info_Out addObject:i_deviceInfo];
                }
                *errMsg_Out = [MSG_SUCCESS mutableCopy];
            } else if (resp->base.ret_msg.cstr) {
                *errMsg_Out = [NSString stringWithUTF8String:resp->base.ret_msg.cstr];
            }
        } else if (resp->base.ret_msg.cstr) {
            *errMsg_Out = [NSString stringWithUTF8String:resp->base.ret_msg.cstr];
        }
    } else {
        *errMsg_Out = [NETWORK_TIMEOUT mutableCopy];
    }
    LCOPENAPI_DESTROY(req);
    LCOPENAPI_DESTROY(resp);

    return (0 == ret) ? YES : NO;
}

- (BOOL)shareDeviceList:(NSMutableArray*)info_Out Begin:(NSInteger)beginIndex_In End:(NSInteger)endIndex_In Msg:(NSString**)errMsg_Out
{
    ShareDeviceListRequest* req;
    ShareDeviceListResponse* resp;
    NSInteger ret = 0;
    NSString* sRange = [NSString stringWithFormat:@"%ld-%ld", (long)beginIndex_In, (long)endIndex_In];
    req = LCOPENAPI_INIT(ShareDeviceListRequest);
    resp = LCOPENAPI_INIT(ShareDeviceListResponse);

    req->data.token = CS(m_accessToken);
    req->data.queryRange = CS([sRange UTF8String]);

    *errMsg_Out = [INTERFACE_FAILED mutableCopy];
    ret = [m_hc request:req resp:resp timeout:10];
    NSLog(@"getDevList ret[%ld]", (long)ret);
    if (0 == ret) {
        int code = resp->base.code;

        if (HTTP_OK == code) {
            NSString* ret_code;
            if (resp->base.ret_code.cstr) {
                ret_code = [NSString stringWithUTF8String:resp->base.ret_code.cstr];
            }
            if ([ret_code isEqualToString:@"0"]) {
                for (int i = 0; i < resp->data.devices.size; i++) {
                    DeviceInfo* i_deviceInfo = [[DeviceInfo alloc] init];

                    NSLog(@"getDevList deviceid[%s],ability[%s],online[%d],name[%s]", resp->data.devices.array[i].deviceId.cstr, resp->data.devices.array[i].ability.cstr, resp->data.devices.array[i].status, resp->data.devices.array[i].name.cstr);
                    if (resp->data.devices.array[i].deviceId.cstr) {
                        i_deviceInfo->ID = [NSString stringWithUTF8String:resp->data.devices.array[i].deviceId.cstr];
                    }
                    if (resp->data.devices.array[i].ability.cstr) {
                        i_deviceInfo->ability = [NSString stringWithUTF8String:resp->data.devices.array[i].ability.cstr];
                    }
                    i_deviceInfo->devOnline = resp->data.devices.array[i].status;
                    i_deviceInfo->channelSize = resp->data.devices.array[i].channels.size;
                    i_deviceInfo->encryptMode = resp->data.devices.array[i].encryptMode;

                    for (int channelIndex = 0; channelIndex < resp->data.devices.array[i].channels.size && channelIndex < CHANNEL_MAX; channelIndex++) {
                        NSLog(@"getDevList channelId=%d", resp->data.devices.array[i].channels.array[channelIndex].channelId);
                        i_deviceInfo->channelId[channelIndex] = resp->data.devices.array[i].channels.array[channelIndex].channelId;

                        NSLog(@"getDevList channelonline=%d", resp->data.devices.array[i].channels.array[channelIndex].channelOnline);
                        i_deviceInfo->isOnline[channelIndex] = resp->data.devices.array[i].channels.array[channelIndex].channelOnline;

                        NSLog(@"getDevList channelAlarmStatus=%d", resp->data.devices.array[i].channels.array[channelIndex].alarmStatus);

                        i_deviceInfo->alarmStatus[channelIndex] = (AlarmStatus)resp->data.devices.array[i].channels.array[channelIndex].alarmStatus;
                        if (resp->data.devices.array[i].channels.array[channelIndex].channelPicUrl.cstr) {
                            NSLog(@"getDevList channelPicUrl=%s", resp->data.devices.array[i].channels.array[channelIndex].channelPicUrl.cstr);
                            i_deviceInfo->channelPic[channelIndex] = [NSString stringWithUTF8String:resp->data.devices.array[i].channels.array[channelIndex].channelPicUrl.cstr];
                        }
                        if (resp->data.devices.array[i].channels.array[channelIndex].channelName.cstr) {
                            i_deviceInfo->channelName[channelIndex] = [[NSString stringWithUTF8String:resp->data.devices.array[i].channels.array[channelIndex].channelName.cstr] stringByAppendingString:@"[shared]"];
                             NSLog(@"getDevList channelname=%@",i_deviceInfo->channelName[channelIndex]);
                        }
                    }
                    [info_Out addObject:i_deviceInfo];
                }
                *errMsg_Out = [MSG_SUCCESS mutableCopy];
            } else if (resp->base.ret_msg.cstr) {
                *errMsg_Out = [NSString stringWithUTF8String:resp->base.ret_msg.cstr];
            }
        } else if (resp->base.ret_msg.cstr) {
            *errMsg_Out = [NSString stringWithUTF8String:resp->base.ret_msg.cstr];
        }
    } else {
        *errMsg_Out = [NETWORK_TIMEOUT mutableCopy];
    }
    LCOPENAPI_DESTROY(req);
    LCOPENAPI_DESTROY(resp);

    return (0 == ret) ? YES : NO;
}

- (BOOL)checkDeviceOnline:(NSString*)devID_In Msg:(NSString**)errMsg_Out
{
    DeviceOnlineRequest* req;
    DeviceOnlineResponse* resp;
    NSInteger ret = 0;
    req = LCOPENAPI_INIT(DeviceOnlineRequest);
    resp = LCOPENAPI_INIT(DeviceOnlineResponse);

    req->data.token = CS(m_accessToken);
    req->data.deviceId = CS([devID_In UTF8String]);

    *errMsg_Out = [INTERFACE_FAILED mutableCopy];
    ret = [m_hc request:req resp:resp timeout:10];
    //    NSLog(@"checkDeviceOnline ret[%ld]", (long)ret);

    if (0 == ret) {
        int code = resp->base.code;
        if (HTTP_OK == code) {
            NSString* ret_code;
            if (resp->base.ret_code.cstr) {
                ret_code = [NSString stringWithUTF8String:resp->base.ret_code.cstr];
            }
            if ([ret_code isEqualToString:@"0"]) {
                NSLog(@"checkDeviceOnline success");
                if (resp->data.onLine.cstr) {
                    *errMsg_Out = [@"1" isEqualToString:[NSString stringWithUTF8String:resp->data.onLine.cstr]]
                        ? [MSG_DEVICE_ONLINE mutableCopy]
                        : [MSG_DEVICE_OFFLINE mutableCopy];
                }
            } else if (resp->base.ret_msg.cstr) {
                *errMsg_Out = [NSString stringWithUTF8String:resp->base.ret_msg.cstr];
            }
        } else if (resp->base.ret_msg.cstr) {
            *errMsg_Out = [NSString stringWithUTF8String:resp->base.ret_msg.cstr];
        }
    } else {
        *errMsg_Out = [NETWORK_TIMEOUT mutableCopy];
    }
    LCOPENAPI_DESTROY(req);
    LCOPENAPI_DESTROY(resp);
    return (0 == ret) ? YES : NO;
}

- (BOOL)checkDeviceBindOrNot:(NSString*)devID_In Msg:(NSString**)errMsg_Out
{
    CheckDeviceBindOrNotRequest* req;
    CheckDeviceBindOrNotResponse* resp;
    NSInteger ret = 0;
    req = LCOPENAPI_INIT(CheckDeviceBindOrNotRequest);
    resp = LCOPENAPI_INIT(CheckDeviceBindOrNotResponse);
    req->data.deviceId = CS([devID_In UTF8String]);
    req->data.token = CS(m_accessToken);

    *errMsg_Out = [INTERFACE_FAILED mutableCopy];
    ret = [m_hc request:req resp:resp timeout:10];
    if (0 == ret) {
        int code = resp->base.code;
        if (HTTP_OK == code) {
            NSString* ret_code;
            if (resp->base.ret_code.cstr) {
                ret_code = [NSString stringWithUTF8String:resp->base.ret_code.cstr];
            }
            if ([ret_code isEqualToString:@"0"]) {
                NSLog(@"checkDeviceBindOrNot bMine[%d],bIsBind[%d]",
                    resp->data.isMine, resp->data.isBind);
                *errMsg_Out = resp->data.isBind ? [MSG_DEVICE_IS_BIND mutableCopy] : [MSG_DEVICE_NOT_BIND mutableCopy];
            } else if (resp->base.ret_msg.cstr) {
                *errMsg_Out = [NSString stringWithUTF8String:resp->base.ret_msg.cstr];
            }
        } else if (resp->base.ret_msg.cstr) {
            *errMsg_Out = [NSString stringWithUTF8String:resp->base.ret_msg.cstr];
        }
    } else {
        *errMsg_Out = [NETWORK_TIMEOUT mutableCopy];
    }
    return (0 == ret) ? YES : NO;
}

- (BOOL)bindDevice:(NSString*)devID_In Msg:(NSString**)errMsg_Out
{
    BindDeviceRequest* req;
    BindDeviceResponse* resp;
    NSInteger ret = 0;
    req = LCOPENAPI_INIT(BindDeviceRequest);
    resp = LCOPENAPI_INIT(BindDeviceResponse);
    req->data.deviceId = CS([devID_In UTF8String]);
    req->data.token = CS(m_accessToken);

    *errMsg_Out = [INTERFACE_FAILED mutableCopy];
    ret = [m_hc request:req resp:resp timeout:10];
    //    NSLog(@"bindDevice ret[%ld]", (long)iret);
    if (0 == ret) {
        int code = resp->base.code;
        if (HTTP_OK == code) {
            NSString* ret_code;
            if (resp->base.ret_code.cstr) {
                ret_code = [NSString stringWithUTF8String:resp->base.ret_code.cstr];
            }
            if ([ret_code isEqualToString:@"0"]) {
                NSLog(@"bindDevice success");
                *errMsg_Out = [MSG_SUCCESS mutableCopy];
            } else if (resp->base.ret_msg.cstr) {
                *errMsg_Out = [NSString stringWithUTF8String:resp->base.ret_msg.cstr];
            }
        } else if (resp->base.ret_msg.cstr) {
            *errMsg_Out = [NSString stringWithUTF8String:resp->base.ret_msg.cstr];
        }
    } else {
        *errMsg_Out = [NETWORK_TIMEOUT mutableCopy];
    }
    LCOPENAPI_DESTROY(req);
    LCOPENAPI_DESTROY(resp);
    return (0 == ret) ? YES : NO;
}

- (BOOL)unBindDevice:(NSString*)devID_In Msg:(NSString**)errMsg_Out
{
    UnBindDeviceRequest* req;
    UnBindDeviceResponse* resp;
    NSInteger ret = 0;
    req = LCOPENAPI_INIT(UnBindDeviceRequest);
    resp = LCOPENAPI_INIT(UnBindDeviceResponse);
    req->data.deviceId = CS([devID_In UTF8String]);
    req->data.token = CS(m_accessToken);

    *errMsg_Out = [INTERFACE_FAILED mutableCopy];
    ret = [m_hc request:req resp:resp timeout:10];
    //    NSLog(@"unBindDevice ret[%ld]", (long)iret);
    if (0 == ret) {
        int code = resp->base.code;
        if (HTTP_OK == code) {
            NSString* ret_code;
            if (resp->base.ret_code.cstr) {
                ret_code = [NSString stringWithUTF8String:resp->base.ret_code.cstr];
            }
            if ([ret_code isEqualToString:@"0"]) {
                NSLog(@"unBindDevice success");
                *errMsg_Out = [MSG_SUCCESS mutableCopy];
            } else if (resp->base.ret_msg.cstr) {
                *errMsg_Out = [NSString stringWithUTF8String:resp->base.ret_msg.cstr];
            }
        } else if (resp->base.ret_msg.cstr) {
            *errMsg_Out = [NSString stringWithUTF8String:resp->base.ret_msg.cstr];
        }
    } else {
        *errMsg_Out = [NETWORK_TIMEOUT mutableCopy];
    }
    LCOPENAPI_DESTROY(req);
    LCOPENAPI_DESTROY(resp);
    return (0 == ret) ? YES : NO;
}

- (BOOL)getBindDeviceInfo:(NSString*)devID_In Info_out:(DeviceInfo*)info_out Msg:(NSString**)errMsg_Out
{
    BindDeviceInfoRequest* req;
    BindDeviceInfoResponse* resp;
    NSInteger ret = 0;
    req = LCOPENAPI_INIT(BindDeviceInfoRequest);
    resp = LCOPENAPI_INIT(BindDeviceInfoResponse);
    req->data.deviceId = CS([devID_In UTF8String]);
    req->data.token = CS(m_accessToken);

    *errMsg_Out = [INTERFACE_FAILED mutableCopy];
    ret = [m_hc request:req resp:resp timeout:10];
    //    NSLog(@"getBindDeviceInfo ret[%ld]", (long)iret);
    if (0 == ret) {
        int code = resp->base.code;
        if (HTTP_OK == code) {
            NSString* ret_code;
            if (resp->base.ret_code.cstr) {
                ret_code = [NSString stringWithUTF8String:resp->base.ret_code.cstr];
            }
            if ([ret_code isEqualToString:@"0"]) {
                NSLog(@"getBindDeviceInfo success");
                for (int channelIndex = 0; channelIndex < resp->data.channels.size && channelIndex < CHANNEL_MAX; channelIndex++) {
                    NSLog(@"getBindDevInfo channelname=%s", resp->data.channels.array[channelIndex].channelName.cstr);
                    NSLog(@"getBinddDevInfo channelonline=%d", resp->data.channels.array[channelIndex].channelOnline);
                    info_out->alarmStatus[channelIndex] = (AlarmStatus)resp->data.channels.array[channelIndex].alarmStatus;
                    info_out->csStatus[channelIndex] = (CloudStorageStatus)resp->data.channels.array[channelIndex].csStatus;
                }
                *errMsg_Out = [MSG_SUCCESS mutableCopy];
            } else if (resp->base.ret_msg.cstr) {
                *errMsg_Out = [NSString stringWithUTF8String:resp->base.ret_msg.cstr];
            }
        } else if (resp->base.ret_msg.cstr) {
            *errMsg_Out = [NSString stringWithUTF8String:resp->base.ret_msg.cstr];
        }
    } else {
        *errMsg_Out = [NETWORK_TIMEOUT mutableCopy];
    }
    LCOPENAPI_DESTROY(req);
    LCOPENAPI_DESTROY(resp);
    return (0 == ret) ? YES : NO;
}

- (BOOL)getAlarmMsg:(NSString*)devID_In Chnl:(NSInteger)iCh_In Begin:(NSString*)beginTime_In End:(NSString*)endTime_In Info:(NSMutableArray*)msgInfo_Out Count:(NSInteger)count_In Msg:(NSString**)errMsg_Out
{
    GetAlarmMessageRequest* req;
    GetAlarmMessageResponse* resp;
    NSInteger ret = 0;
    char strCh[10] = { 0 };
    char strCount[10] = { 0 };
    snprintf(strCount, sizeof(strCount) - 1, "%ld", (long)count_In);
    snprintf(strCh, sizeof(strCh) - 1, "%ld", (long)iCh_In);
    req = LCOPENAPI_INIT(GetAlarmMessageRequest);
    resp = LCOPENAPI_INIT(GetAlarmMessageResponse);
    req->data.token = CS(m_accessToken);
    req->data.deviceId = CS([devID_In UTF8String]);
    req->data.channelId = CS(strCh);
    req->data.beginTime = CS([beginTime_In UTF8String]);
    req->data.endTime = CS([endTime_In UTF8String]);
    req->data.count = CS(strCount);

    *errMsg_Out = [INTERFACE_FAILED mutableCopy];
    ret = [m_hc request:req resp:resp timeout:10];
    if (0 == ret) {
        int code = resp->base.code;
        if (HTTP_OK == code) {
            NSString* ret_code;
            if (resp->base.ret_code.cstr) {
                ret_code = [NSString stringWithUTF8String:resp->base.ret_code.cstr];
            }
            if ([ret_code isEqualToString:@"0"]) {
                for (int i = 0; i < resp->data.alarms.size; i++) {
                    AlarmMessageInfo* i_alarmMessageInfo = [[AlarmMessageInfo alloc] init];
                    if (resp->data.alarms.array[i].deviceId.cstr) {
                        i_alarmMessageInfo->deviceId = [NSString stringWithUTF8String:resp->data.alarms.array[i].deviceId.cstr];
                    }
                    i_alarmMessageInfo->channel = atoi(resp->data.alarms.array[i].channelId.cstr);
                    if (resp->data.alarms.array[i].name.cstr) {
                        i_alarmMessageInfo->channelName = [NSString stringWithUTF8String:resp->data.alarms.array[i].name.cstr];
                    }
                    i_alarmMessageInfo->alarmId = resp->data.alarms.array[i].alarmId;
                    if (resp->data.alarms.array[i].thumbUrl.cstr) {
                        i_alarmMessageInfo->thumbnail = [NSString stringWithUTF8String:resp->data.alarms.array[i].thumbUrl.cstr];
                    }
                    for (int j = 0; j < resp->data.alarms.array[i].picurlArray.size && j < PIC_ARRAY_MAX; j++) {
                        if (resp->data.alarms.array[i].picurlArray.array[j].cstr) {
                            i_alarmMessageInfo->picArray[j] = [NSString stringWithUTF8String:resp->data.alarms.array[i].picurlArray.array[j].cstr];
                        }
                    }
                    if (resp->data.alarms.array[i].localDate.cstr) {
                        i_alarmMessageInfo->localDate = [NSString stringWithUTF8String:resp->data.alarms.array[i].localDate.cstr];
                    }
                    [msgInfo_Out addObject:i_alarmMessageInfo];
                }
                *errMsg_Out = [MSG_SUCCESS mutableCopy];
            } else if (resp->base.ret_msg.cstr) {
                *errMsg_Out = [NSString stringWithUTF8String:resp->base.ret_msg.cstr];
            }
        } else if (resp->base.ret_msg.cstr) {
            *errMsg_Out = [NSString stringWithUTF8String:resp->base.ret_msg.cstr];
        }
    } else {
        *errMsg_Out = [NETWORK_TIMEOUT mutableCopy];
    }
    LCOPENAPI_DESTROY(req);
    LCOPENAPI_DESTROY(resp);
    return (0 == ret) ? YES : NO;
}

- (BOOL)deleteAlarmMsg:(int64_t)alarmId Msg:(NSString**)errMsg_Out
{
    DeleteAlarmMessageRequest* req;
    DeleteAlarmMessageResponse* resp;
    NSInteger ret = 0;
    req = LCOPENAPI_INIT(DeleteAlarmMessageRequest);
    resp = LCOPENAPI_INIT(DeleteAlarmMessageResponse);
    req->data.token = CS(m_accessToken);
    req->data.indexId = alarmId;

    *errMsg_Out = [INTERFACE_FAILED mutableCopy];
    ret = [m_hc request:req resp:resp timeout:10];
    if (0 == ret) {
        int code = resp->base.code;
        if (HTTP_OK == code) {
            NSString* ret_code;
            if (resp->base.ret_code.cstr) {
                ret_code = [NSString stringWithUTF8String:resp->base.ret_code.cstr];
            }
            if ([ret_code isEqualToString:@"0"]) {
                NSLog(@"deleteAlarmMsg [%lld] success", alarmId);
                *errMsg_Out = [MSG_SUCCESS mutableCopy];
            } else if (resp->base.ret_msg.cstr) {
                *errMsg_Out = [NSString stringWithUTF8String:resp->base.ret_msg.cstr];
            }
        } else if (resp->base.ret_msg.cstr) {
            *errMsg_Out = [NSString stringWithUTF8String:resp->base.ret_msg.cstr];
        }
    } else {
        *errMsg_Out = [NETWORK_TIMEOUT mutableCopy];
    }
    LCOPENAPI_DESTROY(req);
    LCOPENAPI_DESTROY(resp);
    return (0 == ret) ? YES : NO;
}

- (BOOL)getRecordNum:(NSString*)devID_In Chnl:(NSInteger)iCh_In Begin:(NSString*)beginTime_In End:(NSString*)endTime_In Num:(NSInteger*)num_Out Msg:(NSString**)errMsg_Out
{
    QueryLocalRecordNumRequest* req;
    QueryLocalRecordNumResponse* resp;
    NSInteger ret = 0;
    char strCh[10] = { 0 };
    snprintf(strCh, sizeof(strCh) - 1, "%ld", (long)iCh_In);
    req = LCOPENAPI_INIT(QueryLocalRecordNumRequest);
    resp = LCOPENAPI_INIT(QueryLocalRecordNumResponse);
    req->data.token = CS(m_accessToken);
    req->data.deviceId = CS([devID_In UTF8String]);
    req->data.channelId = CS(strCh);
    req->data.beginTime = CS([beginTime_In UTF8String]);
    req->data.endTime = CS([endTime_In UTF8String]);

    *errMsg_Out = [INTERFACE_FAILED mutableCopy];
    ret = [m_hc request:req resp:resp timeout:10];
    if (0 == ret) {
        int code = resp->base.code;
        if (HTTP_OK == code) {
            NSString* ret_code;
            if (resp->base.ret_code.cstr) {
                ret_code = [NSString stringWithUTF8String:resp->base.ret_code.cstr];
            }
            if ([ret_code isEqualToString:@"0"]) {
                NSLog(@"getRecordNum num[%d]", resp->data.recordNum);
                *errMsg_Out = [MSG_SUCCESS mutableCopy];
                *num_Out = resp->data.recordNum;
            } else if (resp->base.ret_msg.cstr) {
                *errMsg_Out = [NSString stringWithUTF8String:resp->base.ret_msg.cstr];
            }
        } else if (resp->base.ret_msg.cstr) {
            *errMsg_Out = [NSString stringWithUTF8String:resp->base.ret_msg.cstr];
        }
    } else {
        *errMsg_Out = [NETWORK_TIMEOUT mutableCopy];
    }
    LCOPENAPI_DESTROY(req);
    LCOPENAPI_DESTROY(resp);
    return (0 == ret) ? YES : NO;
}

- (BOOL)getRecords:(NSString*)devID_In Chnl:(NSInteger)iCh_In Begin:(NSString*)beginTime_In End:(NSString*)endTime_In IndexBegin:(NSInteger)beginIndex_In IndexEnd:(NSInteger)endIndex_In InfoOut:(NSMutableArray*)info_Out Msg:(NSString**)errMsg_Out
{
    QueryLocalRecordsRequest* req;
    QueryLocalRecordsResponse* resp;

    NSInteger ret = 0;
    char strCh[10] = { 0 };
    char strRange[100] = { 0 };
    snprintf(strCh, sizeof(strCh) - 1, "%ld", (long)iCh_In);
    snprintf(strRange, sizeof(strRange) - 1, "%ld-%ld", (long)beginIndex_In, (long)endIndex_In);
    req = LCOPENAPI_INIT(QueryLocalRecordsRequest);
    resp = LCOPENAPI_INIT(QueryLocalRecordsResponse);
    req->data.token = CS(m_accessToken);
    req->data.deviceId = CS([devID_In UTF8String]);
    req->data.channelId = CS(strCh);
    req->data.beginTime = CS([beginTime_In UTF8String]);
    req->data.endTime = CS([endTime_In UTF8String]);
    req->data.queryRange = CS(strRange);

    *errMsg_Out = [INTERFACE_FAILED mutableCopy];
    ret = [m_hc request:req resp:resp timeout:60];
    if (0 == ret) {
        int code = resp->base.code;
        if (HTTP_OK == code) {
            NSString* ret_code;
            if (resp->base.ret_code.cstr) {
                ret_code = [NSString stringWithUTF8String:resp->base.ret_code.cstr];
            }
            if ([ret_code isEqualToString:@"0"]) {
                for (int i = 0; i < resp->data.records.size; i++) {
                    RecordInfo* i_recordInfo = [[RecordInfo alloc] init];
                    if (resp->data.records.array[i].recordId.cstr) {
                        i_recordInfo->name = [NSString stringWithUTF8String:resp->data.records.array[i].recordId.cstr];
                        NSLog(@"getRecords[%@],[%d]", i_recordInfo->name, i);
                    }
                    if (resp->data.records.array[i].beginTime.cstr) {
                        i_recordInfo->beginTime = [NSString stringWithUTF8String:resp->data.records.array[i].beginTime.cstr];
                        NSLog(@"getRecords[%@],[%d]", i_recordInfo->beginTime, i);
                    }
                    if (resp->data.records.array[i].endTime.cstr) {
                        i_recordInfo->endTime = [NSString stringWithUTF8String:resp->data.records.array[i].endTime.cstr];
                        NSLog(@"getRecords[%@],[%d]", i_recordInfo->endTime, i);
                    }
                    [info_Out addObject:i_recordInfo];
                }
                *errMsg_Out = [MSG_SUCCESS mutableCopy];
            } else if (resp->base.ret_msg.cstr) {
                *errMsg_Out = [NSString stringWithUTF8String:resp->base.ret_msg.cstr];
            }
        } else if (resp->base.ret_msg.cstr) {
            *errMsg_Out = [NSString stringWithUTF8String:resp->base.ret_msg.cstr];
        }
    } else {
        *errMsg_Out = [NETWORK_TIMEOUT mutableCopy];
    }
    LCOPENAPI_DESTROY(req);
    LCOPENAPI_DESTROY(resp);
    return (0 == ret) ? YES : NO;
}

- (BOOL)getCloudRecordNum:(NSString*)devID_In Chnl:(NSInteger)iCh_In Bengin:(NSString*)beginTime_In End:(NSString*)endTime_In Num:(NSInteger*)num_Out Msg:(NSString**)errMsg_Out
{
    QueryCloudRecordNumRequest* req;
    QueryCloudRecordNumResponse* resp;

    NSInteger ret = 0;
    char iCh[20] = { 0 };
    snprintf(iCh, sizeof(iCh) - 1, "%ld", (long)iCh_In);
    req = LCOPENAPI_INIT(QueryCloudRecordNumRequest);
    resp = LCOPENAPI_INIT(QueryCloudRecordNumResponse);
    req->data.token = CS(m_accessToken);
    req->data.deviceId = CS([devID_In UTF8String]);
    req->data.channelId = CS(iCh);
    req->data.beginTime = CS([beginTime_In UTF8String]);
    req->data.endTime = CS([endTime_In UTF8String]);

    *errMsg_Out = [INTERFACE_FAILED mutableCopy];
    ret = [m_hc request:req resp:resp timeout:10];
    if (0 == ret) {
        int code = resp->base.code;
        if (HTTP_OK == code) {
            NSString* ret_code;
            if (resp->base.ret_code.cstr) {
                ret_code = [NSString stringWithUTF8String:resp->base.ret_code.cstr];
            }
            if ([ret_code isEqualToString:@"0"]) {
                *num_Out = resp->data.recordNum;
                *errMsg_Out = [MSG_SUCCESS mutableCopy];
            } else if (resp->base.ret_msg.cstr) {
                *errMsg_Out = [NSString stringWithUTF8String:resp->base.ret_msg.cstr];
            }
        } else if (resp->base.ret_msg.cstr) {
            *errMsg_Out = [NSString stringWithUTF8String:resp->base.ret_msg.cstr];
        }

    } else {
        *errMsg_Out = [NETWORK_TIMEOUT mutableCopy];
    }
    LCOPENAPI_DESTROY(req);
    LCOPENAPI_DESTROY(resp);
    return (0 == ret) ? YES : NO;
}

- (BOOL)getCloudRecords:(NSString*)devID_In Chnl:(NSInteger)iCh_In Begin:(NSString*)beginTime_In End:(NSString*)endTime_In IndexBegin:(NSInteger)beginIndex_In IndexEnd:(NSInteger)endIndex_In InfoOut:(NSMutableArray*)info_Out Msg:(NSString**)errMsg_Out
{
    QueryCloudRecordsRequest* req;
    QueryCloudRecordsResponse* resp;
    NSInteger ret = 0;
    char iCh[20] = { 0 };
    char strRange[50] = { 0 };
    snprintf(iCh, sizeof(iCh) - 1, "%ld", (long)iCh_In);
    snprintf(strRange, sizeof(strRange) - 1, "%ld-%ld", (long)beginIndex_In, (long)endIndex_In);
    req = LCOPENAPI_INIT(QueryCloudRecordsRequest);
    resp = LCOPENAPI_INIT(QueryCloudRecordsResponse);
    req->data.token = CS(m_accessToken);
    req->data.deviceId = CS([devID_In UTF8String]);
    req->data.channelId = CS(iCh);
    req->data.queryRange = CS(strRange);
    req->data.beginTime = CS([beginTime_In UTF8String]);
    req->data.endTime = CS([endTime_In UTF8String]);

    *errMsg_Out = [INTERFACE_FAILED mutableCopy];
    ret = [m_hc request:req resp:resp timeout:10];
    if (0 == ret) {
        int code = resp->base.code;
        if (HTTP_OK == code) {
            NSString* ret_code;
            if (resp->base.ret_code.cstr) {
                ret_code = [NSString stringWithUTF8String:resp->base.ret_code.cstr];
            }
            if ([ret_code isEqualToString:@"0"]) {
                for (int i = 0; i < resp->data.records.size; i++) {
                    RecordInfo* i_recordInfo = [[RecordInfo alloc] init];
                    if (resp->data.records.array[i].endTime.cstr && resp->data.records.array[i].beginTime.cstr) {
                        i_recordInfo->beginTime = [NSString stringWithUTF8String:resp->data.records.array[i].beginTime.cstr];
                        NSLog(@"beginTime getRecords[%@],[%d]", i_recordInfo->beginTime, i);

                        i_recordInfo->endTime = [NSString stringWithUTF8String:resp->data.records.array[i].endTime.cstr];
                        NSLog(@"endTime getRecords[%@],[%d]", i_recordInfo->endTime, i);

                        i_recordInfo->name = [NSString stringWithFormat:@"%@-%@", i_recordInfo->beginTime, i_recordInfo->endTime];
                    }
                    if (resp->data.records.array[i].thumbUrl.cstr) {
                        i_recordInfo->thumbUrl = [NSString stringWithUTF8String:resp->data.records.array[i].thumbUrl.cstr];
                        NSLog(@"thumUrl getRecords[%@],[%d]", i_recordInfo->thumbUrl, i);
                    }
                    if (resp->data.records.array[i].size.cstr) {
                        i_recordInfo->size = [NSString stringWithUTF8String:resp->data.records.array[i].size.cstr];
                        NSLog(@"size getRecords[%@]", i_recordInfo->size);
                    }
                    i_recordInfo->recId = resp->data.records.array[i].recordId;
                    NSLog(@"recId getRecords[%lld]", i_recordInfo->recId);
                    [info_Out addObject:i_recordInfo];
                }
                *errMsg_Out = [MSG_SUCCESS mutableCopy];
            } else if (resp->base.ret_msg.cstr) {
                *errMsg_Out = [NSString stringWithUTF8String:resp->base.ret_msg.cstr];
            }
        } else if (resp->base.ret_msg.cstr) {
            *errMsg_Out = [NSString stringWithUTF8String:resp->base.ret_msg.cstr];
        }
    } else {
        *errMsg_Out = [NETWORK_TIMEOUT mutableCopy];
    }
    LCOPENAPI_DESTROY(req);
    LCOPENAPI_DESTROY(resp);
    return (0 == ret) ? YES : NO;
}

- (BOOL)controlPTZ:(NSString*)devID_In Chnl:(NSInteger)iCh_In Operate:(NSString*)strOperate_In Horizon:(double)iHorizon_In Vertical:(double)iVertical_In Zoom:(double)iZoom_In Duration:(NSInteger)iDuration_In Msg:(NSString**)errMsg_Out
{
    ControlPTZRequest* req;
    ControlPTZResponse* resp;

    NSInteger ret = 0;
    char iCh[10] = { 0 };
    char strDuration[10] = { 0 };
    snprintf(iCh, sizeof(iCh) - 1, "%ld", (long)iCh_In);
    snprintf(strDuration, sizeof(strDuration) - 1, "%ld", (long)iDuration_In);
    req = LCOPENAPI_INIT(ControlPTZRequest);
    resp = LCOPENAPI_INIT(ControlPTZResponse);
    req->data.deviceId = CS([devID_In UTF8String]);
    req->data.duration = CS(strDuration);
    req->data.channelId = CS(iCh);
    req->data.h = iHorizon_In;
    req->data.v = iVertical_In;
    req->data.z = iZoom_In;
    req->data.operation = CS([strOperate_In UTF8String]);
    req->data.token = CS(m_accessToken);

    *errMsg_Out = [INTERFACE_FAILED mutableCopy];
    ret = [m_hc request:req resp:resp timeout:10];
    if (0 == ret) {
        int code = resp->base.code;
        if (HTTP_OK == code) {
            NSString* ret_code;
            if (resp->base.ret_code.cstr) {
                ret_code = [NSString stringWithUTF8String:resp->base.ret_code.cstr];
            }
            if ([ret_code isEqualToString:@"0"]) {
                *errMsg_Out = [MSG_SUCCESS mutableCopy];
            } else if (resp->base.ret_msg.cstr) {
                *errMsg_Out = [NSString stringWithUTF8String:resp->base.ret_msg.cstr];
            }
        } else if (resp->base.ret_msg.cstr) {
            *errMsg_Out = [NSString stringWithUTF8String:resp->base.ret_msg.cstr];
        }
    } else {
        *errMsg_Out = [NETWORK_TIMEOUT mutableCopy];
    }
    LCOPENAPI_DESTROY(req);
    LCOPENAPI_DESTROY(resp);
    return (0 == ret) ? YES : NO;
}

- (BOOL)modifyDeviceAlarmStatus:(NSString*)devID_In Chnl:(NSInteger)iCh_In Enable:(BOOL)enable_In Msg:(NSString**)errMsg_Out
{
    ModifyDeviceAlarmStatusRequest* req;
    ModifyDeviceAlarmStatusResponse* resp;

    NSInteger ret = 0;
    char iCh[10] = { 0 };
    snprintf(iCh, sizeof(iCh) - 1, "%ld", (long)iCh_In);
    req = LCOPENAPI_INIT(ModifyDeviceAlarmStatusRequest);
    resp = LCOPENAPI_INIT(ModifyDeviceAlarmStatusResponse);
    req->data.token = CS(m_accessToken);
    req->data.deviceId = CS([devID_In UTF8String]);
    req->data.channelId = CS(iCh);
    req->data.enable = enable_In;

    *errMsg_Out = [INTERFACE_FAILED mutableCopy];
    ret = [m_hc request:req resp:resp timeout:10];
    if (0 == ret) {
        int code = resp->base.code;
        if (HTTP_OK == code) {
            NSString* ret_code;
            if (resp->base.ret_code.cstr) {
                ret_code = [NSString stringWithUTF8String:resp->base.ret_code.cstr];
            }
            if ([ret_code isEqualToString:@"0"]) {
                *errMsg_Out = [MSG_SUCCESS mutableCopy];
            } else if (resp->base.ret_msg.cstr) {
                *errMsg_Out = [NSString stringWithUTF8String:resp->base.ret_msg.cstr];
            }
        } else if (resp->base.ret_msg.cstr) {
            *errMsg_Out = [NSString stringWithUTF8String:resp->base.ret_msg.cstr];
        }
    } else {
        *errMsg_Out = [NETWORK_TIMEOUT mutableCopy];
    }
    LCOPENAPI_DESTROY(req);
    LCOPENAPI_DESTROY(resp);
    return (0 == ret) ? YES : NO;
}

- (BOOL)setStorageStrategy:(NSString*)devID_In Chnl:(NSInteger)iCh_In Enable:(NSString*)enable_In Msg:(NSString**)errMsg_Out
{
    SetStorageStrategyRequest* req;
    SetStorageStrategyResponse* resp;

    NSInteger ret = 0;
    char iCh[10] = { 0 };
    snprintf(iCh, sizeof(iCh) - 1, "%ld", (long)iCh_In);
    req = LCOPENAPI_INIT(SetStorageStrategyRequest);
    resp = LCOPENAPI_INIT(SetStorageStrategyResponse);
    req->data.token = CS(m_accessToken);
    req->data.deviceId = CS([devID_In UTF8String]);
    req->data.channelId = CS(iCh);
    req->data.status = CS([enable_In UTF8String]);

    *errMsg_Out = [INTERFACE_FAILED mutableCopy];
    ret = [m_hc request:req resp:resp timeout:10];
    if (0 == ret) {
        int code = resp->base.code;
        if (HTTP_OK == code) {
            NSString* ret_code;
            if (resp->base.ret_code.cstr) {
                ret_code = [NSString stringWithUTF8String:resp->base.ret_code.cstr];
            }
            if ([ret_code isEqualToString:@"0"]) {
                *errMsg_Out = [MSG_SUCCESS mutableCopy];
            } else if (resp->base.ret_msg.cstr) {
                *errMsg_Out = [NSString stringWithUTF8String:resp->base.ret_msg.cstr];
            }
        } else if (resp->base.ret_msg.cstr) {
            *errMsg_Out = [NSString stringWithUTF8String:resp->base.ret_msg.cstr];
        }
    } else {
        *errMsg_Out = [NETWORK_TIMEOUT mutableCopy];
    }
    LCOPENAPI_DESTROY(req);
    LCOPENAPI_DESTROY(resp);
    return (0 == ret) ? YES : NO;
}

- (BOOL)setAllStorageStrategy:(NSString*)devID_In Chnl:(NSInteger)iCh_In Enable:(NSString*)enable_In Msg:(NSString**)errMsg_Out
{
    SetAllStorageStrategyRequest* req;
    SetAllStorageStrategyResponse* resp;

    NSInteger ret = 0;
    char iCh[10] = { 0 };
    snprintf(iCh, sizeof(iCh) - 1, "%ld", (long)iCh_In);
    req = LCOPENAPI_INIT(SetAllStorageStrategyRequest);
    resp = LCOPENAPI_INIT(SetAllStorageStrategyResponse);
    req->data.token = CS(m_accessToken);
    req->data.deviceId = CS([devID_In UTF8String]);
    req->data.channelId = CS(iCh);
    req->data.status = CS([enable_In UTF8String]);

    *errMsg_Out = [INTERFACE_FAILED mutableCopy];
    ret = [m_hc request:req resp:resp timeout:10];
    if (0 == ret) {
        int code = resp->base.code;
        if (HTTP_OK == code) {
            NSString* ret_code;
            if (resp->base.ret_code.cstr) {
                ret_code = [NSString stringWithUTF8String:resp->base.ret_code.cstr];
            }
            if ([ret_code isEqualToString:@"0"]) {
                *errMsg_Out = [MSG_SUCCESS mutableCopy];
            } else if (resp->base.ret_msg.cstr) {
                *errMsg_Out = [NSString stringWithUTF8String:resp->base.ret_msg.cstr];
            }
        } else if (resp->base.ret_msg.cstr) {
            *errMsg_Out = [NSString stringWithUTF8String:resp->base.ret_msg.cstr];
        }
    } else {
        *errMsg_Out = [NETWORK_TIMEOUT mutableCopy];
    }
    LCOPENAPI_DESTROY(req);
    LCOPENAPI_DESTROY(resp);
    return (0 == ret) ? YES : NO;
}

- (BOOL)getStorageStrategy:(NSString*)devID_In Chnl:(NSInteger)iCh_In Msg:(NSString**)errMsg_Out
{
    GetStorageStrategyRequest* req;
    GetStorageStrategyResponse* resp;
    
    NSInteger ret = 0;
    char iCh[10] = { 0 };
    snprintf(iCh, sizeof(iCh) - 1, "%ld", (long)iCh_In);
    req = LCOPENAPI_INIT(GetStorageStrategyRequest);
    resp = LCOPENAPI_INIT(GetStorageStrategyResponse);
    req->data.token = CS(m_accessToken);
    req->data.deviceId = CS([devID_In UTF8String]);
    req->data.channelId = CS(iCh);
    
    *errMsg_Out = [INTERFACE_FAILED mutableCopy];
    ret = [m_hc request:req resp:resp timeout:10];
    if (0 == ret) {
        int code = resp->base.code;
        if (HTTP_OK == code) {
            NSString* ret_code;
            if (resp->base.ret_code.cstr) {
                ret_code = [NSString stringWithUTF8String:resp->base.ret_code.cstr];
            }
            if ([ret_code isEqualToString:@"0"]) {
                *errMsg_Out = [MSG_SUCCESS mutableCopy];
            } else if (resp->base.ret_msg.cstr) {
                *errMsg_Out = [NSString stringWithUTF8String:resp->base.ret_msg.cstr];
            }
        } else if (resp->base.ret_msg.cstr) {
            *errMsg_Out = [NSString stringWithUTF8String:resp->base.ret_msg.cstr];
        }
    } else {
        *errMsg_Out = [NETWORK_TIMEOUT mutableCopy];
    }
    LCOPENAPI_DESTROY(req);
    LCOPENAPI_DESTROY(resp);
    return (0 == ret) ? YES : NO;
}

@end
