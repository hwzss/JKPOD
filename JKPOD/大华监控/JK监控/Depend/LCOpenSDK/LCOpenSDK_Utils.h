//
//  LCOpenSDK_Utils.h
//  LCOpenSDK
//
//  Created by chenjian on 16/7/14.
//  Copyright (c) 2016年 lechange. All rights reserved.
//

#ifndef LCOpenSDK_LCOpenSDK_Utils_h
#define LCOpenSDK_LCOpenSDK_Utils_h
#import <Foundation/Foundation.h>

@interface LCOpenSDK_Utils: NSObject

/**
*数据解密
*
*@param pSrcBufIn     [in]  待解密数据内容
*@param srcBufLenIn   [in]  数据实际长度
*@param devKeyIn      [in]  解密密钥
*@param pDestBufOut   [out] 解密后数据内容
*@param destBufLenOut [out] 解密后数据长度
*
*@return 解密结果
*   0, 表示解密成功
*   1, 表示完整性校验失败
*   2, 表示密钥错误
*   3, 表示图片非加密
*   4, 不支持的加密方式
*   5, 缓冲区长度不够
*   99,内部错误
*/

-(NSInteger) decryptPic:(NSData *)pSrcBufIn key:(NSString*)devKeyIn bufOut:(NSData**)pDestBufOut;

@end

#endif
