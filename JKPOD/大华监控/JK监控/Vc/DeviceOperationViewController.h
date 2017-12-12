//
//  DeviceOperationViewController.h
//  LCOpenSDKDemo
//
//  Created by mac318340418 on 16/7/18.
//  Copyright © 2016年 lechange. All rights reserved.
//

#import "DeviceViewController.h"
#import "MyViewController.h"
#import <UIKit/UIKit.h>

@interface DeviceOperationViewController : MyViewController {
    UIActivityIndicatorView* m_progressInd;

    LCOpenSDK_Api* m_hc;
    NSString* m_accessToken;
    NSString* m_strDevSelected;
    NSInteger m_devChnSelected;
    AlarmStatus m_alarmStatus;
    CloudStorageStatus m_cldStrgStatus;

    UILabel* m_toastLab;
}

@property (weak, nonatomic) IBOutlet UIView* m_viewAlarm;
@property (weak, nonatomic) IBOutlet UIView* m_viewCloudStroge;
@property (weak, nonatomic) IBOutlet UISwitch* m_alarmSwitch;
@property (weak, nonatomic) IBOutlet UIActivityIndicatorView* m_alarmActivity;
@property (weak, nonatomic) IBOutlet UISwitch* m_cloudStorageSwitch;
@property (weak, nonatomic) IBOutlet UIActivityIndicatorView* m_cloudStorageActivity;

- (void)setInfo:(LCOpenSDK_Api*)hc Token:(NSString*)token Dev:(NSString*)deviceId Chn:(NSInteger)chn;

@end
