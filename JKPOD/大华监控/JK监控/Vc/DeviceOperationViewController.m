//
//  DeviceOperationViewController.m
//  LCOpenSDKDemo
//
//  Created by mac318340418 on 16/7/18.
//  Copyright © 2016年 lechange. All rights reserved.
//

#import "DeviceOperationViewController.h"
#import "RestApiService.h"

@interface DeviceOperationViewController ()

@end

@implementation DeviceOperationViewController

- (void)viewDidLoad
{
    [super viewDidLoad];
    [self initWindowView];
    // Do any additional setup after loading the view.
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (void)initWindowView
{

    UINavigationItem* item = [[UINavigationItem alloc] initWithTitle:@"设备操作"];
    super.m_navigationBar.tintColor = [UIColor colorWithRed:0 green:0 blue:0 alpha:0];

    UIButton* left = [UIButton buttonWithType:UIButtonTypeCustom];
    //left.backgroundColor = [UIColor whiteColor];
    [left setFrame:CGRectMake(0, 0, 50, 30)];
    UIImage* img = [UIImage imageNamed:@"common_btn_back.png"];

    [left setBackgroundImage:img forState:UIControlStateNormal];
    [left addTarget:self action:@selector(onBack) forControlEvents:UIControlEventTouchUpInside];
    UIBarButtonItem* leftBtn = [[UIBarButtonItem alloc] initWithCustomView:left];
    [item setLeftBarButtonItem:leftBtn animated:NO];
    [super.m_navigationBar pushNavigationItem:item animated:NO];

    [self.view addSubview:super.m_navigationBar];

    m_progressInd = [[UIActivityIndicatorView alloc] initWithActivityIndicatorStyle:UIActivityIndicatorViewStyleGray];
    m_progressInd.transform = CGAffineTransformMakeScale(2.0, 2.0);
    m_progressInd.center = CGPointMake(self.view.center.x, self.view.center.y);
    [self.view addSubview:m_progressInd];

    m_toastLab = [[UILabel alloc] initWithFrame:CGRectMake(0, 0, 300, 50)];
    m_toastLab.center = self.view.center;
    m_toastLab.backgroundColor = [UIColor whiteColor];
    m_toastLab.textAlignment = NSTextAlignmentCenter;
    [self.view addSubview:m_toastLab];

    [self.view bringSubviewToFront:m_toastLab];
    [self.view bringSubviewToFront:m_progressInd];
    self.m_viewAlarm.hidden = YES;
    self.m_viewCloudStroge.hidden = YES;
    m_toastLab.hidden = YES;
    self.m_alarmActivity.hidden = YES;
    [self.m_alarmActivity startAnimating];
    self.m_cloudStorageActivity.hidden = YES;
    [self.m_cloudStorageActivity startAnimating];
    [self getChnStatus];
}

- (void)setInfo:(LCOpenSDK_Api*)hc Token:(NSString*)token Dev:(NSString*)deviceId Chn:(NSInteger)chn
{
    m_hc = hc;
    m_accessToken = [token mutableCopy];
    m_strDevSelected = [deviceId mutableCopy];
    m_devChnSelected = chn;
}

- (IBAction)onAlarmPlan:(UISwitch*)sender
{
    self.m_alarmActivity.hidden = NO;
    RestApiService* restApiService = [RestApiService shareMyInstance];
    if (ALARM_ON == m_alarmStatus) {
        m_alarmStatus = ALARM_OFF;
        dispatch_queue_t alarmPlanTrue = dispatch_queue_create("alarmPlanFalse", nil);
        dispatch_async(alarmPlanTrue, ^{
            NSString *errMsg;
            [restApiService modifyDeviceAlarmStatus:m_strDevSelected Chnl:m_devChnSelected Enable:false Msg:&errMsg];
            if (![errMsg isEqualToString:[MSG_SUCCESS mutableCopy]]) {
                m_alarmStatus = ALARM_ON;
            }
            dispatch_async(dispatch_get_main_queue(), ^{
                self.m_alarmActivity.hidden = YES;
                [self setAlarmSwitch:m_alarmStatus];
            });
        });
    }
    else if (ALARM_OFF == m_alarmStatus) {
        m_alarmStatus = ALARM_ON;
        dispatch_queue_t alarmPlanTrue = dispatch_queue_create("alarmPlanTrue", nil);
        dispatch_async(alarmPlanTrue, ^{
            NSString* errMsg;
            [restApiService modifyDeviceAlarmStatus:m_strDevSelected Chnl:m_devChnSelected Enable:true Msg:&errMsg];
            if (![errMsg isEqualToString:[MSG_SUCCESS mutableCopy]]) {
                m_alarmStatus = ALARM_OFF;
            }
            dispatch_async(dispatch_get_main_queue(), ^{
                self.m_alarmActivity.hidden = YES;
                [self setAlarmSwitch:m_alarmStatus];
            });
        });
    }
}

- (IBAction)onStorageStrategy:(UISwitch*)sender
{
    self.m_cloudStorageActivity.hidden = NO;
    RestApiService* restApiService = [RestApiService shareMyInstance];
    if (STORAGE_ON == m_cldStrgStatus) {
        m_cldStrgStatus = STORAGE_BREAK_OFF;
        dispatch_queue_t downQueue = dispatch_queue_create("storageStrategyOff", nil);
        dispatch_async(downQueue, ^{
            NSString* errMsg;
            [restApiService setAllStorageStrategy:m_strDevSelected Chnl:m_devChnSelected Enable:@"off" Msg:&errMsg];
            if (![errMsg isEqualToString:[MSG_SUCCESS mutableCopy]]) {
                m_cldStrgStatus = STORAGE_ON;
            }
            dispatch_async(dispatch_get_main_queue(), ^{
                self.m_cloudStorageActivity.hidden = YES;
                [self setCloudStorageSwitch:m_cldStrgStatus];
            });
        });
    }
    else if (STORAGE_NOT_OPEN == m_cldStrgStatus || STORAGE_USELESS == m_cldStrgStatus || STORAGE_BREAK_OFF == m_cldStrgStatus) {
        m_cldStrgStatus = STORAGE_ON;
        dispatch_queue_t storageStrategyOn = dispatch_queue_create("storageStrategyOn", nil);
        dispatch_async(storageStrategyOn, ^{
            NSString* errMsg;
            [restApiService setAllStorageStrategy:m_strDevSelected Chnl:m_devChnSelected Enable:@"on" Msg:&errMsg];
            if (![errMsg isEqualToString:[MSG_SUCCESS mutableCopy]]) {
                m_cldStrgStatus = STORAGE_BREAK_OFF;
            }
            dispatch_async(dispatch_get_main_queue(), ^{
                self.m_cloudStorageActivity.hidden = YES;
                [self setCloudStorageSwitch:m_cldStrgStatus];
            });
        });
    }
}

- (void)onBack
{
    [self dismissViewControllerAnimated:YES completion:nil];
    [self.navigationController popViewControllerAnimated:YES];
}

- (void)setAlarmSwitch:(AlarmStatus)status
{
    switch (status) {
    case ALARM_ON:
        [self.m_alarmSwitch setOn:YES];
        break;
    case ALARM_OFF:
        [self.m_alarmSwitch setOn:NO];
        break;
    default:
        break;
    }
}

- (void)setCloudStorageSwitch:(CloudStorageStatus)status
{
    switch (status) {
    case STORAGE_ON:
        [self.m_cloudStorageSwitch setOn:YES];
        break;
    case STORAGE_BREAK_OFF:
    case STORAGE_NOT_OPEN:
    case STORAGE_USELESS:
        [self.m_cloudStorageSwitch setOn:NO];
        break;
    default:
        break;
    }
}

- (void)getChnStatus
{
    [self showLoading];
    dispatch_queue_t get_status = dispatch_queue_create("get_status", nil);
    dispatch_async(get_status, ^{
        NSString* errMsg;
        DeviceInfo* bindDeviceInfo = [[DeviceInfo alloc] init];
        RestApiService* restApiService = [RestApiService shareMyInstance];
        [restApiService getBindDeviceInfo:m_strDevSelected Info_out:bindDeviceInfo Msg:&errMsg];
        if (![errMsg isEqualToString:[MSG_SUCCESS mutableCopy]]) {
            dispatch_sync(dispatch_get_main_queue(), ^{
                [self hideLoading];
                m_toastLab.text = errMsg;
                m_toastLab.hidden = NO;
            });
            return;
        }
        m_alarmStatus = bindDeviceInfo->alarmStatus[m_devChnSelected];
        m_cldStrgStatus = bindDeviceInfo->csStatus[m_devChnSelected];

        dispatch_async(dispatch_get_main_queue(), ^{
            [self setAlarmSwitch:m_alarmStatus];
            [self setCloudStorageSwitch:m_cldStrgStatus];
            [self hideLoading];
            self.m_viewAlarm.hidden = NO;
            self.m_viewCloudStroge.hidden = NO;
        });
    });
}

// 显示滚动轮指示器
- (void)showLoading
{
    [m_progressInd startAnimating];
}

// 消除滚动轮指示器
- (void)hideLoading
{
    if ([m_progressInd isAnimating]) {
        [m_progressInd stopAnimating];
    }
}

- (void)dealloc
{
    NSLog(@"DeviceOperationViewController dealloc");
}
@end
