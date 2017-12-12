//
//  ForJKHttp.h
//  safeSheidEstate
//
//  Created by qwkj on 2017/9/15.
//  Copyright © 2017年 qwkj. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "CIM_HTTPTool.h"
#import "SE_Device.h"
/**
 监控http
 */
@interface ForJKHttp : NSObject

/**
 获取监控账号，以及token

 @param success 成功
 @param errorblock 失败
 @param ConnectfailureBlock 链接是比啊
 */
+(void)SE_getVideoCountInfo:(void(^)(NSString *videoToken,NSString *phone))success Error:(RequestError)errorblock  Connectfailure:(RequestConnectfailure)ConnectfailureBlock;

/**
 获取小区监控磁盘列表

 @param success 磁盘序列号列表
 @param errorblock 失败
 @param ConnectfailureBlock 链接是比啊
 */
+(void)SE_getDeviceList:(void(^)(NSMutableArray *list))success Error:(RequestError)errorblock  Connectfailure:(RequestConnectfailure)ConnectfailureBlock;
+(void)SE_getDeviceListV2:(void(^)(NSMutableArray *list))success Error:(RequestError)errorblock  Connectfailure:(RequestConnectfailure)ConnectfailureBlock;
@end
