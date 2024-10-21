//
//  RCUserProfileDefine.h
//  RongIMKit
//
//  Created by zgh on 2024/9/5.
//  Copyright © 2024 RongCloud. All rights reserved.
//

#ifndef RCUserProfileDefine_h
#define RCUserProfileDefine_h

/// 选择状态
typedef NS_ENUM(NSUInteger, RCSelectState) {
    /// 未选择
    RCSelectStateUnselect = 0,
    /// 已选择
    RCSelectStateSelect = 1,
    /// 不可选择
    RCSelectStateDisable = 2,
};

#endif /* RCUserProfileDefine_h */
