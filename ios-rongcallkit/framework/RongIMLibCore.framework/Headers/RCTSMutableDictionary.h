//
//  RCTSMutableDictionary.h
//  RongIMKit
//
//  Created by 岑裕 on 16/5/12.
//  Copyright © 2016 年 RongCloud. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface RCTSMutableDictionary<KeyType, ObjectType> : NSMutableDictionary <KeyType, ObjectType> <NSLocking>

@end
