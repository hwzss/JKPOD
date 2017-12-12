//
//  VideoPlay.m
//  appDemo
//
//  Created by yao_bao on 15/4/28.
//  Copyright (c) 2015年 yao_bao. All rights reserved.
//

#import "VideoPlay.h"

@interface VideoPlay () {
    LCOpenSDK_PlayWindow* m_playWindow;
}

@end

@implementation VideoPlay
- (id)initWithRect:(CGRect)rect Index:(int)index
{
    m_playWindow = [[LCOpenSDK_PlayWindow alloc] initPlayWindow:rect Index:index];
    return self;
}
- (void)uninit
{
    [m_playWindow uninitPlayWindow];
}
- (void)setListener:(id<LCOpenSDK_EventListener>)listener
{
    NSLog(@"setListener ====n");
    [m_playWindow setWindowListener:listener];
}
- (UIView*)getWindowView
{
    return [m_playWindow getWindowView];
}
- (void)setWindowFrame:(CGRect)rect
{
    [m_playWindow setWindowFrame:rect];
}
- (void)playRtspReal:(NSString*)accessTok devID:(NSString*)deviceID channel:(NSInteger)chn definition:(NSInteger)defiMode
{
    [m_playWindow playRtspReal:accessTok devID:deviceID channel:chn definition:defiMode];
}
- (void)playRtspReal:(NSString*)accessTok devID:(NSString*)deviceID psk:(NSString*)psk channel:(NSInteger)chn definition:(NSInteger)defiMode
{
    [m_playWindow playRtspReal:accessTok devID:deviceID psk:psk channel:chn definition:defiMode];
}
- (void)playRtspPlaybackByFilename:(NSString*)accessTok devID:(NSString*)deviceID filename:(NSString*)fileName
{
    [m_playWindow playRtspPlaybackByFileName:accessTok devID:deviceID fileName:fileName];
}
- (void)playRtspPlaybackByFilename:(NSString*)accessTok devID:(NSString*)deviceID psk:(NSString*)psk filename:(NSString*)fileName
{
    [m_playWindow playRtspPlaybackByFileName:accessTok devID:deviceID psk:(NSString*)psk fileName:fileName];
}
- (NSInteger)playRtspPlaybackByUtcTime:(NSString*)accessTok devID:(NSString*)deviceID channel:(NSInteger)chn begin:(long)beginTime end:(long)endTime
{
    return [m_playWindow playRtspPlaybackByUtcTime:accessTok devID:deviceID channel:chn begin:beginTime end:endTime];
}
- (NSInteger)playRtspPlaybackByUtcTime:(NSString*)accessTok devID:(NSString*)deviceID psk:(NSString*)psk channel:(NSInteger)chn begin:(long)beginTime end:(long)endTime
{
    return [m_playWindow playRtspPlaybackByUtcTime:accessTok devID:deviceID psk:psk channel:chn begin:beginTime end:endTime];
}
- (void)playCloud:(NSString*)accessTok devID:(NSString*)deviceID recordID:(int64_t)recordID
{
    [m_playWindow playCloud:accessTok devID:deviceID recordID:recordID];
}
- (void)playCloud:(NSString*)accessTok devID:(NSString*)deviceID psk:(NSString*)psk recordID:(int64_t)recordID Type:(NSInteger)type timeOut:(NSInteger)timeOut
{
    [m_playWindow playCloud:accessTok devID:deviceID psk:psk recordID:recordID Type:type timeOut:timeOut];
}
- (void)stopCloud
{
    [m_playWindow stopCloud];
}
- (void)stopRtspReal
{
    [m_playWindow stopRtspReal];
}
- (void)stopRtspPlayback
{
    [m_playWindow stopRtspPlayback];
}
- (BOOL)startRecord:(NSString*)path
{
    NSInteger iret = [m_playWindow startRecord:path recordType:1];
    return (0 == iret) ? YES : NO;
}
- (void)stopRecord
{
    [m_playWindow stopRecord];
}
- (void)setStreamCallback:(LC_OUTPUT_STREAM_FORMAT)streamFormat
{
    [m_playWindow setStreamCallback:streamFormat];
}
- (void)snapShot:(NSString*)path
{
    NSLog(@"test snapshot[%@]\n", path);
    [m_playWindow snapShot:path];
}
- (void)setSurfaceBGColor:(UIColor*)normalColor
{
    [m_playWindow setSurfaceBGColor:normalColor];
}
- (void)stopAudio
{
    [m_playWindow stopAudio];
}
- (void)playAudio
{
    [m_playWindow playAudio];
}
- (NSInteger)seek:(long)timeInfo
{
    return [m_playWindow seek:timeInfo];
}
- (NSInteger)pause
{
    return [m_playWindow pause];
}
- (NSInteger)resume
{
    return [m_playWindow resume];
}

- (void)doScale:(CGFloat)scale
{
    [m_playWindow doScale:scale];
}

- (void)doTranslateX:(CGFloat)x Y:(CGFloat)y
{
    [m_playWindow doTranslateX:x Y:y];
}

@end
