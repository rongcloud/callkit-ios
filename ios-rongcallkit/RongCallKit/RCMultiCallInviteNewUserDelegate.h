//
//  RCExternalCallDelegate.h
//  RongCallKit
//
//  Created by zhangke on 2018/12/3.
//  Copyright © 2018 Rong Cloud. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@protocol RCMultiCallInviteNewUserDelegate <NSObject>
/**
 多人音视频通话将要弹出选人界面的回调（当用户需要自己实现多人音视频通话的选人界面时使用）
 
 @param existUserIdList 可被选择的所有音视频通话的用户
 @param viewController  多人音视频通话视图控制器
 @param resultBlock     选择用户之后的回调需要（需要用户自己调用该 block 传递所选择音视频通话的用户 id）
  @warming 用户使用该代理时则 RongCallKit 默认的多人音视频通话选人界面界面不会弹出，谨慎使用！
 */
- (void)inviteNewUser:(NSMutableArray *)existUserIdList
               BaseOn:(UIViewController *)viewController
         selectResult:(void (^)(NSArray<NSString *> *userIdList))resultBlock;
@end

NS_ASSUME_NONNULL_END
