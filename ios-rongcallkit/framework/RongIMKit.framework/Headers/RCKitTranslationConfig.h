//
//  RCKitTranslationConfig.h
//  RongIMKit
//
//  Created by RobinCui on 2022/2/28.
//  Copyright © 2022 RongCloud. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface RCKitTranslationConfig : NSObject
@property (nonatomic, copy, readonly) NSString *srcLanguage;
@property (nonatomic, copy, readonly) NSString *targetLanguage;

- (instancetype)initWithSrcLanguage:(NSString *)srcLanguage
                     targetLanguage:(NSString *)targetLanguage;
@end

NS_ASSUME_NONNULL_END
