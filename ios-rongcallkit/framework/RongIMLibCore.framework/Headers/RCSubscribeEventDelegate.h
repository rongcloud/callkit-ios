//
//  RCSubscribeEventDelegate.h
//  RongIMLibCore
//
//  Created by chinaspx on 2024/2/22.
//  Copyright © 2024 RongCloud. All rights reserved.
//

#ifndef RCSubscribeEventDelegate_h
#define RCSubscribeEventDelegate_h

NS_ASSUME_NONNULL_BEGIN

@class RCSubscribeEvent, RCSubscribeInfoEvent;
@protocol RCSubscribeEventDelegate <NSObject>
@optional
/// 当订阅事件发生变化时调用此方法。
/// 功能说明：当任何订阅的事件发生变化时，此方法将被触发。
/// 可以通过实现此方法来处理事件的变化，例如更新用户界面或处理新的数据。
/// 通常，该方法在后台线程中被调用，因此更新 UI 时需要切换到主线程。
///
/// - Parameter subscribeEvents: 订阅事件的列表，包含所有发生变化的事件。
/// - Remark: 订阅过期没有通知，开发者需自行关注过期时间
/// - Since: 5.8.1
- (void)onEventChange:(NSArray<RCSubscribeInfoEvent *> *)subscribeEvents;


/// 订阅数据同步完成。
/// 该方法在订阅数据成功同步到设备或系统后调用，用于执行后续处理。
///
/// - Since: 5.8.1
- (void)onSubscriptionSyncCompleted __deprecated_msg("Use onSubscriptionSyncCompleted: instead");


/// 订阅数据同步完成。
/// 该方法在订阅数据成功同步到设备或系统后调用，用于执行后续处理。
///  - Parameter type: 订阅事件的类型
///  - Since: 5.10.0
- (void)onSubscriptionSyncCompleted:(RCSubscribeType)type;


/// 当用户在其他设备上的订阅信息发生变更时调用此方法。
/// 这可以用于更新当前设备上的用户状态，确保订阅信息的一致性。
///
/// - Parameter subscribeEvents: 订阅事件的列表。
/// - Since: 5.8.1
- (void)onSubscriptionChangedOnOtherDevices:(NSArray<RCSubscribeEvent *> *)subscribeEvents;

@end

NS_ASSUME_NONNULL_END

#endif /* RCSubscribeEventDelegate_h */
