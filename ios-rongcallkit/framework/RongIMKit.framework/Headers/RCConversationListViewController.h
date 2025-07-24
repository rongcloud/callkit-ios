//
//  RCConversationListViewController.h
//  RongIMKit
//
//  Created by xugang on 15/1/22.
//  Copyright (c) 2015年 RongCloud. All rights reserved.
//

#import "RCBaseViewController.h"
#import "RCConversationBaseCell.h"
#import "RCConversationModel.h"
#import "RCThemeDefine.h"
#import <UIKit/UIKit.h>
#import "RCBaseTableView.h"
@class RCNetworkIndicatorView;

NS_ASSUME_NONNULL_BEGIN

/// 会话列表界面类
@interface RCConversationListViewController : RCBaseViewController <UITableViewDataSource, UITableViewDelegate>

#pragma mark - 初始化

/// 初始化会话列表
///
/// - Parameter displayConversationTypeArray:    列表中需要显示的会话类型数组(需要将RCConversationType转为NSNumber构建Array)
/// - Parameter collectionConversationTypeArray:
/// 列表中需要聚合为一条显示的会话类型数组(需要将RCConversationType转为NSNumber构建Array)
/// - Returns: 会话列表对象
/// 聚合为一条显示指的是，将指定会话类型的所有会话在会话列表中聚合显示成一条，点击进入会显示该会话类型的所有会话列表。
- (instancetype)initWithDisplayConversationTypes:(NSArray *)displayConversationTypeArray
                      collectionConversationType:(nullable NSArray *)collectionConversationTypeArray;

#pragma mark - 设置需要显示和聚合显示的会话类型

/// 列表中需要显示的会话类型数组
/// 数组中的元素为RCConversationType转换的NSNumber
/// 默认显示单聊、群聊、聊天室、公众号、客服、系统的会话
@property (nonatomic, strong) NSArray *displayConversationTypeArray;

/// 列表中需要聚合为一条显示的会话类型数组
/// 数组中的元素为RCConversationType转换的NSNumber
@property (nonatomic, strong, nullable) NSArray *collectionConversationTypeArray;

/// 设置在列表中需要显示的会话类型
/// - Parameter conversationTypeArray: 列表中需要显示的会话类型数组(需要将RCConversationType转为NSNumber构建Array)
/// 默认显示单聊、群聊、聊天室、公众号、客服、系统的会话
- (void)setDisplayConversationTypes:(NSArray *)conversationTypeArray;

/// 设置在列表中需要聚合为一条显示的会话类型
/// - Parameter conversationTypeArray: 列表中需要聚合为一条显示的会话类型数组(需要将RCConversationType转为NSNumber构建Array)
- (void)setCollectionConversationType:(nullable NSArray *)conversationTypeArray;

/// 当前会话列表是否为从聚合Cell点击进入的子会话列表
/// 您在点击会话列表中的聚合Cell跳转到到子会话列表时，需要将此属性设置为YES。
@property (nonatomic, assign) BOOL isEnteredToCollectionViewController;

#pragma mark - 置顶的会话排序优先
/// 查询结果的排序方式，是否置顶优先，传 true 表示置顶会话优先返回，否则结果只以会话时间排序
@property(nonatomic, assign) BOOL topPriority;

#pragma mark - 列表属性

/// 列表中会话数据模型的数据源
///
/// 数据源中存放的元素为会话Cell的数据模型，即RCConversationModel对象。
/// - Warning: 非线程安全，请在主线程操作此属性
@property (nonatomic, strong) NSMutableArray *conversationListDataSource;

/// 列表的TableView
@property (nonatomic, strong) RCBaseTableView *conversationListTableView;

#pragma mark - 网络连接变化状态提醒

/// 当网络断开时，是否在Tabel View Header中显示网络连接不可用的提示。
/// 默认值为YES。
@property (nonatomic, assign) BOOL isShowNetworkIndicatorView;

/// 当连接状态变化SDK自动重连时，是否在NavigationBar中显示连接中的提示。
/// 默认是是NO。
@property (nonatomic, assign) BOOL showConnectingStatusOnNavigatorBar;

#pragma mark - 显示相关

/// 列表为空时显示的View
@property (nonatomic, strong) UIView *emptyConversationView;

/// Cell的背景颜色
@property (nonatomic, strong) UIColor *cellBackgroundColor;

/// 置顶会话的Cell背景颜色
@property (nonatomic, strong) UIColor *topCellBackgroundColor;

/// 提示网络连接不可用的 View
@property (nonatomic, strong) RCNetworkIndicatorView *networkIndicatorView;

/// 设置在会话列表中显示的头像形状，矩形或者圆形（全局有效）
///
/// - Parameter avatarStyle: 显示的头像形状
/// 默认值为矩形，即RC_USER_AVATAR_RECTANGLE。
/// 请在viewDidLoad之前设置，此设置在SDK中全局有效。
- (void)setConversationAvatarStyle:(RCUserAvatarStyle)avatarStyle;

/// 设置会话列表界面中显示的头像大小（全局有效），高度必须大于或者等于36
///
/// - Parameter size: 显示的头像大小
/// 默认值为46*46。
/// 请在viewDidLoad之前设置，此设置在SDK中全局有效。
- (void)setConversationPortraitSize:(CGSize)size;

#pragma mark - UI操作回调

#pragma mark 点击事件的回调

/// 点击会话列表中Cell的回调
///
/// - Parameter conversationModelType:   当前点击的会话的Model类型
/// - Parameter model:                   当前点击的会话的Model
/// - Parameter indexPath:               当前会话在列表数据源中的索引值
/// 您需要重写此点击事件，跳转到指定会话的会话页面。
/// 如果点击聚合Cell进入具体的子会话列表，在跳转时，需要将isEnteredToCollectionViewController设置为YES。
- (void)onSelectedTableRow:(RCConversationModelType)conversationModelType
         conversationModel:(RCConversationModel *)model
               atIndexPath:(NSIndexPath *)indexPath;

/// 点击Cell头像的回调
/// - Parameter model:   会话Cell的数据模型
- (void)didTapCellPortrait:(RCConversationModel *)model;

/// 长按Cell头像的回调
/// - Parameter model:   会话Cell的数据模型
- (void)didLongPressCellPortrait:(RCConversationModel *)model;

#pragma mark 删除会话的回调

/// 删除会话的回调
/// - Parameter model:   会话Cell的数据模型
- (void)didDeleteConversationCell:(RCConversationModel *)model;

#pragma mark - Cell加载显示的回调

/// 即将加载增量数据源的回调
/// - Parameter dataSource:      即将加载的增量数据源（元素为RCConversationModel对象）
/// - Returns: 修改后的数据源（元素为RCConversationModel对象）
/// 您可以在回调中修改、添加、删除数据源的元素来定制显示的内容，会话列表会根据您返回的修改后的数据源进行显示。
/// 数据源中存放的元素为会话Cell的数据模型，即RCConversationModel对象。
/// 2.9.21 及其以前版本，dataSource 为全量数据，conversationListDataSource = dataSource
/// 2.9.22 及其以后版本，dataSource 为增量数据，conversationListDataSource += dataSource，如果需要更改全量数据的内容，可以更改 conversationListDataSource
- (NSMutableArray<RCConversationModel *> *)willReloadTableData:(NSMutableArray<RCConversationModel *> *)dataSource;

/// 即将显示Cell的回调
/// - Parameter cell:        即将显示的Cell
/// - Parameter indexPath:   该Cell对应的会话Cell数据模型在数据源中的索引值
/// 您可以在此回调中修改Cell的一些显示属性。
- (void)willDisplayConversationTableCell:(RCConversationBaseCell *)cell atIndexPath:(NSIndexPath *)indexPath;

/// Cell状态更新时的回调
/// - Parameter indexPath: 该Cell对应的会话Cell数据模型在数据源中的索引值
/// 当Cell的阅读状态等信息发生改变时的回调，您可以在此回调中更新Cell的显示。
- (void)updateCellAtIndexPath:(NSIndexPath *)indexPath;

#pragma mark - 自定义会话列表Cell

/// 自定义会话Cell显示时的回调
/// - Parameter tableView:       当前TabelView
/// - Parameter indexPath:       该Cell对应的会话Cell数据模型在数据源中的索引值
/// - Returns: 自定义会话需要显示的Cell
- (RCConversationBaseCell *)rcConversationListTableView:(UITableView *)tableView
                                  cellForRowAtIndexPath:(NSIndexPath *)indexPath;

/// 自定义会话Cell显示时的回调
/// - Parameter tableView:       当前TabelView
/// - Parameter indexPath:       该Cell对应的会话Cell数据模型在数据源中的索引值
/// - Returns: 自定义会话需要显示的Cell的高度
- (CGFloat)rcConversationListTableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath;

/// 左滑删除自定义会话时的回调
/// - Parameter tableView:       当前TabelView
/// - Parameter editingStyle:    当前的Cell操作，默认为UITableViewCellEditingStyleDelete
/// - Parameter indexPath:       该Cell对应的会话Cell数据模型在数据源中的索引值
/// 自定义会话Cell在删除时会回调此方法，您可以在此回调中，定制删除的提示UI、是否删除。
/// 如果确定删除该会话，您需要在调用 RCCoreClient 中的接口删除会话或其中的消息，
/// 并从conversationListDataSource和conversationListTableView中删除该会话。
- (void)rcConversationListTableView:(UITableView *)tableView
                 commitEditingStyle:(UITableViewCellEditingStyle)editingStyle
                  forRowAtIndexPath:(NSIndexPath *)indexPath;

#pragma mark - 界面刷新操作

/// 从数据库中重新读取会话列表数据，并刷新会话列表
/// - Warning: 从数据库中重新读取并刷新，会比较耗时，请谨慎使用。
- (void)refreshConversationTableViewIfNeeded;

/// 向列表中插入或更新一条会话，并刷新会话列表界面
/// - Parameter conversationModel:   会话Cell的数据模型
/// 如果该会话Cell数据模型在数据源中已经存在，则会更新数据源中的数据并更新UI；
/// 如果数据源没有该会话Cell的数据模型，则插入数据源再更新UI。
- (void)refreshConversationTableViewWithConversationModel:(RCConversationModel *)conversationModel;

/// 当用户退出登陆时，是否还能继续显示会话列表
/// 默认值为YES。
/// - Warning: 该字段已被废弃，用户会使用 APP  收发个人的敏感消息，如果断开链接之后不关闭数据库，可能出现当前用户看到上个用户的敏感消息，基于安全方面考虑：当断开 SDK 连接的时候，SDK 会把消息数据库关闭
@property (nonatomic, assign) BOOL showConversationListWhileLogOut __deprecated_msg("");

#pragma mark - 其他

/// 在会话列表中，收到新消息的回调
/// - Parameter notification:    收到新消息的notification
/// SDK在此方法中有针对消息接收有默认的处理（如刷新等），如果您重写此方法，请注意调用super。
/// notification的object为RCMessage消息对象，userInfo为NSDictionary对象，其中key值为@"left"，value为还剩余未接收的消息数的NSNumber对象。
- (void)didReceiveMessageNotification:(NSNotification *)notification;

/// 即将更新未读消息数的回调
///
/// 该方法在非主线程回调，如果想在本方法中操作 UI，请手动切换到主线程。
/// 当收到消息或删除会话时，会调用此回调，您可以在此回调中执行未读消息数相关的操作。
- (void)notifyUpdateUnreadMessageCount;

@end
NS_ASSUME_NONNULL_END
