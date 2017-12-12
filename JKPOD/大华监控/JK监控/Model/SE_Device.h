//
//  SE_Device.h
//  shieldEstate
//
//  Created by qwkj on 2017/10/9.
//  Copyright © 2017年 qwkj. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "SE_Channel.h"

@interface SE_Device : NSObject

@property(copy,nonatomic)NSString *deviceIds;
@property(strong,nonatomic)NSArray *channelIdArrayList;
@end
