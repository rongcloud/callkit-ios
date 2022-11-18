//
//  RCConversationViewController.h
//  RongIMKit
//
//  Created by xugang on 15/1/22.
//  Copyright (c) 2015年 RongCloud. All rights reserved.
//

#import "RCBaseViewController.h"
#import "RCChatSessionInputBarControl.h"
#import "RCConversationModel.h"
#import "RCEmojiBoardView.h"
#import "RCMessageBaseCell.h"
#import "RCMessageModel.h"
#import "RCPluginBoardView.h"
#import "RCThemeDefine.h"
#import <UIKit/UIKit.h>
#import "RCReferencingView.h"

@class RCLocationMessage;
@class RCCustomerServiceInfo,RCPublicServiceMenuItem;
/*!
 客服服务状态
 */
typedef NS_ENUM(NSUInteger, RCCustomerServiceStatus) {
    /*!
     无客服服务
     */
    RCCustomerService_NoService,

    /*!
     人工客服服务
     */
    RCCustomerService_HumanService,

    /*!
     机器人客服服务
     */
    RCCustomerService_RobotService
};

/*!
 加载消息类型
 @discussion added from 5.1.7
 */
typedef enum : NSUInteger {
    /*!
     同步远端消息成功失败都加载消息
     */
    RCConversationLoadMessageTypeAlways,
    
    /*!
     同步远端消息失败时询问是否加载本地消息
     */
    RCConversationLoadMessageTypeAsk,
    
    /*!
     同步远端消息成功再加载消息
     */
    RCConversationLoadMessageTypeOnlySuccess,
} RCConversationLoadMessageType;

/*!
 会话页面类
 */
@interface RCConversationViewController
    : RCBaseViewController <UICollectionViewDelegate, UICollectionViewDataSource, UICollectionViewDelegateFlowLayout,
                            UIGestureRecognizerDelegate, UIScrollViewDelegate>

#pragma mark - 初始化

/*!
 初始化会话页面

 @param conversationType 会话类型
 @param targetId         目标会话ID

 @return 会话页面对象
 */
- (id)initWithConversationType:(RCConversationType)conversationType targetId:(NSString *)targetId;

#pragma mark - 会话属性

/*!
 当前会话的会话类型
 */
@property (nonatomic) RCConversationType conversationType;

/*!
 目标会话ID
 */
@property (nonatomic, copy) NSString *targetId;

/*!
 目标频道ID
 */
@property (nonatomic, copy) NSString *channelId;

#pragma mark - 会话页面属性
/**
 进入页面时定位的消息的发送时间

 @discussion 用于消息搜索之后点击进入页面等场景
 */
@property (nonatomic, assign) long long locatedMessageSentTime;

/*!
 聊天内容的消息Cell数据模型的数据源

 @discussion 数据源中存放的元素为消息Cell的数据模型，即RCMessageModel对象。
 @warning 非线程安全，请在主线程操作该属性
 */
@property (nonatomic, strong) NSMutableArray *conversationDataRepository;

/*!
 会话页面的CollectionView
 */
@property (nonatomic, strong) UICollectionView *conversationMessageCollectionView;

#pragma mark 导航栏返回按钮中的未读消息数提示
/*!
 需要统计未读数的会话类型数组（在导航栏的返回按钮中显示）

 @discussion 此属性表明在导航栏的返回按钮中需要统计显示哪部分的会话类型的未读数。
 (需要将RCConversationType转为NSNumber构建Array)
 */
@property (nonatomic, strong) NSArray *displayConversationTypeArray;

/*!
 更新导航栏返回按钮中显示的未读消息数

 @discussion 如果您重写此方法，需要注意调用super。
 */
- (void)notifyUpdateUnreadMessageCount;

#pragma mark 右上角的未读消息数提示
/*!
 当未读消息数超过 10 条时，进入会话之后，是否在右上角提示上方存在的未读消息数

 @discussion 默认值为NO。
 开启该提示功能之后，当未读消息数超过 10 条时，进入该会话后，会在右上角提示用户上方存在的未读消息数，用户点击该提醒按钮，会跳转到最开始的未读消息。
 */
@property (nonatomic, assign) BOOL enableUnreadMessageIcon;


#pragma mark 右上角的未读 @ 消息数提示
/*!
 当收到的消息中有 @ 消息时，进入会话之后，是否在右上角提示未读 @ 消息数

 @discussion 默认值为YES。
 开启该提示功能之后，当一个会话收到大量消息时（超过一个屏幕能显示的内容），
 进入该会话后，会在右上角提示用户上方存在的未读 @ 消息数，用户点击该提醒按钮，会跳转到最早的未读 @ 消息处，同时未读 @ 消息数量减 1，再次点击，未读 @ 消息数量根据当前屏幕内看到的个数相应减少。
 */
@property (nonatomic, assign) BOOL enableUnreadMentionedIcon;

/*!
 该会话的未读消息数
 */
@property (nonatomic, assign) NSInteger unReadMessage;

/*!
 右上角未读消息数提示的Label

 @discussion 当 unReadMessage > 10  右上角会显示未读消息数。
 */
@property (nonatomic, strong) UILabel *unReadMessageLabel;

/*!
 右上角未读消息数提示的按钮
 */
@property (nonatomic, strong) UIButton *unReadButton;

/*!
 右上角@消息数提示的Label
 */
@property (nonatomic, strong) UILabel *unReadMentionedLabel;


@property (nonatomic, strong) UIImageView *unreadRightBottomIcon;

/*!
 右上角@消息数提示的按钮
 */
@property (nonatomic, strong) UIButton *unReadMentionedButton;

#pragma mark 右下角的未读消息数提示
/*!
 当前阅读区域的下方收到消息时，是否在会话页面的右下角提示下方存在未读消息

 @discussion 默认值为NO。不支持聊天室
 开启该提示功能之后，当会话页面滑动到最下方时，此会话中收到消息会自动更新；
 当用户停留在上方某个区域阅读时，此会话收到消息时，会在右下角显示未读消息提示，而不会自动滚动到最下方，
 用户点击该提醒按钮，会滚动到最下方。
 */
@property (nonatomic, assign) BOOL enableNewComingMessageIcon;

/*!
 右下角未读消息数提示的Label
 */
@property (nonatomic, strong) UILabel *unReadNewMessageLabel;

#pragma mark - 输入工具栏

/*!
 会话页面下方的输入工具栏
 */
@property (nonatomic, strong) RCChatSessionInputBarControl *chatSessionInputBarControl;
/*!
 禁用系统表情, 建议在RCConversationViewController 创建后立刻赋值
 */
@property (nonatomic, assign) BOOL  disableSystemEmoji;
/*!
 输入框的默认输入模式

 @discussion 默认值为RCChatSessionInputBarInputText，即文本输入模式。 请在[super viewWillAppear:animated]之后调用
 */
@property (nonatomic) RCChatSessionInputBarInputType defaultInputType;

/*!
 会话扩展显示区域

 @discussion 可以自定义显示会话页面的view。
 */
@property (nonatomic, strong) UIView *extensionView;

/*!
 输入框上方引用内容显示View

*/
@property (nonatomic, strong) RCReferencingView *referencingView;

/*!
 输入工具栏占位文本 label，默认为 nil，不显示占位
 
 在会话页面的 viewDidLoad 写如下代码即可
 self.placeholderLabel = [[UILabel alloc] initWithFrame:CGRectMake(10, 10, 180, 20)];
 self.placeholderLabel.text = @"测试 Placeholder";
 self.placeholderLabel.textColor = [UIColor grayColor];
*/
@property (nonatomic, strong) UILabel *placeholderLabel;

/*!
 输入框中内容发生变化的回调

 @param inputTextView 文本输入框
 @param range         当前操作的范围
 @param text          插入的文本
 */
- (void)inputTextView:(UITextView *)inputTextView
    shouldChangeTextInRange:(NSRange)range
            replacementText:(NSString *)text;

/*!
 输入工具栏尺寸（高度）发生变化的回调

 @param chatInputBar 输入工具栏
 @param frame        输入工具栏最终需要显示的Frame

 @discussion 如重写此方法，请先调用父类方法。
 */
- (void)chatInputBar:(RCChatSessionInputBarControl *)chatInputBar shouldChangeFrame:(CGRect)frame;

/*!
 扩展功能板的点击回调

 @param pluginBoardView 输入扩展功能板View
 @param tag             输入扩展功能(Item)的唯一标示
 */
- (void)pluginBoardView:(RCPluginBoardView *)pluginBoardView clickedItemWithTag:(NSInteger)tag;

#pragma mark - 显示设置

/*!
 收到的消息是否显示发送者的名字

 @discussion 默认值为YES。
 您可以针对群聊、聊天室、单聊等不同场景，自己定制是否显示发送方的名字。
 */
@property (nonatomic) BOOL displayUserNameInCell;

/*!
 设置进入聊天室需要获取的历史消息数量（仅在当前会话为聊天室时生效）

 @discussion 此属性需要在viewDidLoad之前进行设置。
 -1表示不获取任何历史消息，0表示不特殊设置而使用SDK默认的设置（默认为获取10条）。
 */
@property (nonatomic, assign) int defaultHistoryMessageCountOfChatRoom;

/*!
 设置进入会话页面后下拉刷新从远端获取消息的条数，默认是 10，defaultRemoteHistoryMessageCount 传入 2~20 之间的数值。
 @discussion 此属性需要在viewDidLoad之前进行设置。
 */
@property (nonatomic, assign) int defaultRemoteHistoryMessageCount;

/*!
 设置进入会话页面后下拉刷新从本地数据库取的消息的条数，默认是 10。
 @discussion 此属性需要在viewDidLoad之前进行设置。
 从 5.2.4 及之后版本， SDK 加载消息的个数使用 defaultRemoteHistoryMessageCount， 请勿再使用该字段。
 */
@property (nonatomic, assign) int defaultLocalHistoryMessageCount;

/*!
 加载消息类型（不支持聊天室）
 
 @discussion 加载消息是先从本地获取历史消息，本地有缺失的情况下会从服务端同步缺失的部分。 从服务端同步失败的时候会返回非 0 的 errorCode，同时把本地能取到的消息回调上去。
 @discussion 此属性可以控制从服务端同步失败的时候加载消息的方式。
 @discussion added from 5.1.7
 */
@property (nonatomic, assign) RCConversationLoadMessageType loadMessageType;

/*!
 已经选择的所有消息
 @discussion 只有在 allowsMessageCellSelection 为 YES,才会有有效值
 */
@property (nonatomic, strong, readonly) NSArray<RCMessageModel *> *selectedMessages;

/*!
 会话页面消息是否可编辑选择,如果为 YES,消息 cell 会变为多选样式,如果为 NO，页面恢复初始状态。
 */
@property (nonatomic, assign) BOOL allowsMessageCellSelection;

/*!
 消息编辑选择的状态下页面底部出现的工具视图
 */
@property (nonatomic, strong) UIToolbar *messageSelectionToolbar;

/*!
 提示用户信息并推出当前会话界面

 @param errorInfo 错误提示

 @discussion 在聊天室加入失败SDK会调用此接口，提示用户并退出聊天室。如果您需要修改提示或者不退出，可以重写此方法。
 */
- (void)alertErrorAndLeft:(NSString *)errorInfo;


#pragma mark - 界面操作

/*!
 滚动到列表最下方

 @param animated 是否开启动画效果
 */
- (void)scrollToBottomAnimated:(BOOL)animated;

/*!
 返回前一个页面的方法

 @param sender 事件发起者

 @discussion 其中包含了一些会话页面退出的清理工作，如退出讨论组等。
 如果您重写此方法，请注意调用super。
 */
- (void)leftBarButtonItemPressed:(id)sender;

#pragma mark - 消息操作

#pragma mark 发送消息
/*!
 发送消息

 @param messageContent 消息的内容
 @param pushContent    接收方离线时需要显示的远程推送内容

 @discussion 当接收方离线并允许远程推送时，会收到远程推送。
 远程推送中包含两部分内容，一是pushContent，用于显示；二是pushData，用于携带不显示的数据。

 SDK内置的消息类型，如果您将pushContent置为nil，会使用默认的推送格式进行远程推送。
 自定义类型的消息，需要您自己设置pushContent来定义推送内容，否则将不会进行远程推送。

 如果您需要设置发送的pushData，可以使用RCIM的发送消息接口。
 */
- (void)sendMessage:(RCMessageContent *)messageContent pushContent:(NSString *)pushContent;

/*!
 发送媒体消息(上传图片或文件到App指定的服务器)

 @param messageContent 消息的内容
 @param pushContent    接收方离线时需要显示的远程推送内容
 @param appUpload      是否上传到App指定的服务器

 @discussion
 此方法用于上传媒体信息到您自己的服务器，此时需要将appUpload设置为YES，并实现uploadMedia:uploadListener:回调。
 需要您在该回调中上传媒体信息（图片或文件），并通过uploadListener监听通知SDK同步显示上传进度。

 如果appUpload设置为NO，将会和普通媒体消息的发送一致，上传到融云默认的服务器并发送。
 */
- (void)sendMediaMessage:(RCMessageContent *)messageContent
             pushContent:(NSString *)pushContent
               appUpload:(BOOL)appUpload;

/*!
 上传媒体信息到App指定的服务器的回调

 @param message        媒体消息（图片消息或文件消息）的实体
 @param uploadListener SDK图片上传进度监听

 @discussion 如果您通过sendMediaMessage:pushContent:appUpload:接口发送媒体消息，则必须实现此回调。
 您需要在此回调中通过uploadListener将上传媒体信息的进度和结果通知SDK，SDK会根据这些信息，自动更新UI。
 */
- (void)uploadMedia:(RCMessage *)message uploadListener:(RCUploadMediaStatusListener *)uploadListener;

/*!
 取消上传媒体消息。

 @param model        媒体消息（文件消息）的Model

 @discussion 如果您通过sendMediaMessage:pushContent:appUpload:发送媒体消息（上传媒体内容到App服务器），需要
 重写此函数，在此函数中取消掉您的上传，并调用uploadListener的cancelBlock告诉融云SDK该发送已经取消。目前仅支持文件消息的取消
 */
- (void)cancelUploadMedia:(RCMessageModel *)model;

/*!
 重新发送消息

 @param messageContent 消息的内容

 @discussion 发送消息失败，点击小红点时，会将本地存储的原消息实体删除，回调此接口将消息内容重新发送。
 如果您需要重写此接口，请注意调用super。
 因 UI 逻辑修改为将原消息移动到会话页面最下方，不删除原消息直接重新发送原消息，但是此方法会重新生成消息发送，故废弃。
 */
- (void)resendMessage:(RCMessageContent *)messageContent __deprecated_msg("Use resendMessageWithModel instead");

/*!
 重新发送消息

 @param model 消息的 Model

 @discussion 发送消息失败，点击小红点时，会将原消息移动到会话页面最下方，不删除原消息，直接重新发送该消息。
 如果您需要重写此接口，请注意调用 super。
 */
- (void)resendMessageWithModel:(RCMessageModel *)model;

#pragma mark 插入消息
/*!
 在会话页面中插入一条消息并展示

 @param message 消息实体

 @discussion 通过此方法插入一条消息，会将消息实体对应的内容Model插入数据源中，并更新UI。
 请注意，这条消息只会在 UI 上插入，并不会存入数据库。
 用户调用这个接口插入消息之后，如果退出会话页面再次进入的时候，这条消息将不再显示。
 */
- (void)appendAndDisplayMessage:(RCMessage *)message;

#pragma mark 删除消息

/*!
 默认值为 NO 长按只删除本地消息，设置为 YES 时长按删除消息，会把远端的消息也进行删除
*/
@property (nonatomic, assign) BOOL needDeleteRemoteMessage;

/*!
 删除消息并更新UI

 @param model 消息Cell的数据模型
 @discussion
 v5.2.3 之前 会话页面只删除本地消息，如果需要删除远端历史消息，需要
    1.重写该方法，并调用 super 删除本地消息
    2.调用删除远端消息接口，删除远端消息
 
 v5.2.3及以后，会话页面会根据 needDeleteRemoteMessage 设置进行处理
    如未设置默认值为NO， 只删除本地消息
    设置为 YES 时， 会同时删除远端消息
 */
- (void)deleteMessage:(RCMessageModel *)model;

#pragma mark 撤回消息
/*!
 撤回消息并更新UI

 @param messageId 被撤回的消息Id
 @discussion 只有存储并发送成功的消息才可以撤回。
 */
- (void)recallMessage:(long)messageId;

#pragma mark - 消息操作的回调

/*!
 准备发送消息的回调

 @param messageContent 消息内容

 @return 修改后的消息内容

 @discussion 此回调在消息准备向外发送时会回调，您可以在此回调中对消息内容进行过滤和修改等操作。
 如果此回调的返回值不为nil，SDK会对外发送返回的消息内容。
 */
- (RCMessageContent *)willSendMessage:(RCMessageContent *)messageContent;

/*!
 发送消息完成的回调

 @param status          发送状态，0表示成功，非0表示失败
 @param messageContent   消息内容
 */
- (void)didSendMessage:(NSInteger)status content:(RCMessageContent *)messageContent __deprecated_msg("Use - (void)didSendMessageModel:(NSInteger)status model:(RCMessageModel *)messageModel instead");

/*!
 发送消息完成的回调

 @param status          发送状态，0表示成功，非0表示失败
 @param messageModel   消息内容
 */
- (void)didSendMessageModel:(NSInteger)status model:(RCMessageModel *)messageModel;

/*!
 取消了消息发送的回调

 @param messageContent   消息内容
 */
- (void)didCancelMessage:(RCMessageContent *)messageContent;

/*!
 即将在会话页面插入消息的回调

 @param message 消息实体
 @return        修改后的消息实体

 @discussion 此回调在消息准备插入数据源的时候会回调，您可以在此回调中对消息进行过滤和修改操作。
 如果此回调的返回值不为nil，SDK会将返回消息实体对应的消息Cell数据模型插入数据源，并在会话页面中显示。
 */
- (RCMessage *)willAppendAndDisplayMessage:(RCMessage *)message;

/*!
 即将显示消息Cell的回调

 @param cell        消息Cell
 @param indexPath   该Cell对应的消息Cell数据模型在数据源中的索引值

 @discussion 您可以在此回调中修改Cell的显示和某些属性。
 */
- (void)willDisplayMessageCell:(RCMessageBaseCell *)cell atIndexPath:(NSIndexPath *)indexPath;


/*!
多选模式时，消息将要被选择时的回调

@param model 消息 Cell 的数据模型
@return 是否继续执行选择操作，默认是YES
*/
- (BOOL)willSelectMessage:(RCMessageModel *)model;

/*!
多选模式时，消息将要被取消选择时的回调

@param model 消息 Cell 的数据模型
@return 是否继续执行取消选择操作，默认是YES
*/
- (BOOL)willCancelSelectMessage:(RCMessageModel *)model;

#pragma mark - 自定义消息
/*!
 用户注册自定义消息的入口

 @discussion 如果有自定义消息，请在该方法内执行
 - (void)registerClass:(Class)cellClass forMessageClass:(Class)messageClass
 进行消息注册
 */
- (void)registerCustomCellsAndMessages;
/*!
 注册自定义消息的Cell

 @param cellClass     自定义消息cell的类
 @param messageClass  自定义消息Cell对应的自定义消息的类，该自定义消息需要继承于RCMessageContent

 @discussion
 你需要在cell中重写RCMessageBaseCell基类的sizeForMessageModel:withCollectionViewWidth:referenceExtraHeight:来计算cell的高度。
 
 @discussion 如果有自定义消息，在会话页面子类 registerCustomCellsAndMessages 方法中需优先注册自定义消息的 cell, 再做其他操作;  请不要在其他方法中进行注册, 可能会有渲染时序问题

 */
- (void)registerClass:(Class)cellClass forMessageClass:(Class)messageClass;

/*!
 未注册消息Cell显示的回调

 @param collectionView  当前CollectionView
 @param indexPath       该Cell对应的消息Cell数据模型在数据源中的索引值
 @return                未注册消息需要显示的Cell

 @discussion
 未注册消息的显示主要用于App未雨绸缪的新旧版本兼容，在使用此回调之前，需要将RCIM的showUnkownMessage设置为YES。
 比如，您App在新版本迭代中增加了某种自定义消息，当已经发布的旧版本不能识别，开发者可以在旧版本中预先定义好这些不能识别的消息的显示，
 如提示当前版本不支持，引导用户升级等。
 */
- (RCMessageBaseCell *)rcUnkownConversationCollectionView:(UICollectionView *)collectionView
                                   cellForItemAtIndexPath:(NSIndexPath *)indexPath;

/*!
 未注册消息Cell显示的回调

 @param collectionView          当前CollectionView
 @param collectionViewLayout    当前CollectionView Layout
 @param indexPath               该Cell对应的消息Cell数据模型在数据源中的索引值
 @return                        未注册消息Cell需要显示的高度

 @discussion
 未注册消息的显示主要用于App未雨绸缪的新旧版本兼容，在使用此回调之前，需要将RCIM的showUnkownMessage设置为YES。
 比如，您App在新版本迭代中增加了某种自定义消息，当已经发布的旧版本不能识别，开发者可以在旧版本中预先定义好这些不能识别的消息的显示，
 如提示当前版本不支持，引导用户升级等。
 */
- (CGSize)rcUnkownConversationCollectionView:(UICollectionView *)collectionView
                                      layout:(UICollectionViewLayout *)collectionViewLayout
                      sizeForItemAtIndexPath:(NSIndexPath *)indexPath;

#pragma mark - 点击事件回调

/*!
 点击Cell中的消息内容的回调

 @param model 消息Cell的数据模型

 @discussion SDK在此点击事件中，针对SDK中自带的图片、语音、位置等消息有默认的处理，如查看、播放等。
 您在重写此回调时，如果想保留SDK原有的功能，需要注意调用super。
 */
- (void)didTapMessageCell:(RCMessageModel *)model;

/*!
 长按Cell中的消息内容的回调

 @param model 消息Cell的数据模型
 @param view  长按区域的View

 @discussion SDK在此长按事件中，会默认展示菜单。
 您在重写此回调时，如果想保留SDK原有的功能，需要注意调用super。
 */
- (void)didLongTouchMessageCell:(RCMessageModel *)model inView:(UIView *)view;

/*!
 获取长按Cell中的消息时的菜单

 @param model 消息Cell的数据模型

 @discussion SDK在此长按事件中，会展示此方法返回的菜单。
 您在重写此回调时，如果想保留SDK原有的功能，需要注意调用super。
 */
- (NSArray<UIMenuItem *> *)getLongTouchMessageCellMenuList:(RCMessageModel *)model;

/*!
 点击Cell中URL的回调

 @param url   点击的URL
 @param model 消息Cell的数据模型
*/
- (void)didTapUrlInMessageCell:(NSString *)url model:(RCMessageModel *)model;

/*!
 点击撤回消息Cell中重新编辑的回调

 @param model 消息Cell的数据模型

 @discussion 点击撤回消息Cell中重新编辑，会调用此回调，不会再触发didTapMessageCell:。
 */
- (void)didTapReedit:(RCMessageModel *)model;

/*!
 点击引用消息中被引用消息内容预览的回调

 @param model 引用消息Cell的数据模型
*/
- (void)didTapReferencedContentView:(RCMessageModel *)model;

/*!
 点击Cell中电话号码的回调

 @param phoneNumber 点击的电话号码
 @param model       消息Cell的数据模型
 */
- (void)didTapPhoneNumberInMessageCell:(NSString *)phoneNumber model:(RCMessageModel *)model;

/*!
 点击Cell中头像的回调

 @param userId  点击头像对应的用户ID
 */
- (void)didTapCellPortrait:(NSString *)userId;

/*!
 长按Cell中头像的回调

 @param userId  头像对应的用户ID
 */
- (void)didLongPressCellPortrait:(NSString *)userId;

#pragma mark - 语音消息、图片消息、位置消息、文件消息显示与操作

/*!
 开始录制语音消息的回调
 */
- (void)onBeginRecordEvent;

/*!
 结束录制语音消息的回调
 */
- (void)onEndRecordEvent;

/*!
 取消录制语音消息的回调(不会再走 onEndRecordEvent)
 */
- (void)onCancelRecordEvent;
/*!
 是否开启语音消息连续播放

 @discussion 如果设置为YES，在点击播放语音消息时，会将下面所有未播放过的语音消息依次播放。
 */
@property (nonatomic, assign) BOOL enableContinuousReadUnreadVoice;

/*!
 查看图片消息中的图片

 @param model   消息Cell的数据模型

 @discussion SDK在此方法中会默认调用RCImageSlideController下载并展示图片。
 */
- (void)presentImagePreviewController:(RCMessageModel *)model;

/*!
 发送新拍照的图片完成之后，是否将图片在本地另行存储。

 @discussion 如果设置为YES，您需要在saveNewPhotoToLocalSystemAfterSendingSuccess:回调中自行保存。
 */
@property (nonatomic, assign) BOOL enableSaveNewPhotoToLocalSystem;

/*!
 发送新拍照的图片完成之后，将图片在本地另行存储的回调

 @param newImage    图片

 @discussion 您可以在此回调中按照您的需求，将图片另行保存或执行其他操作。
 */
- (void)saveNewPhotoToLocalSystemAfterSendingSuccess:(UIImage *)newImage;

/*!
 查看位置信息的位置详情

 @param locationMessageContent  点击的位置消息

 @discussion SDK在此方法中会默认调用RCLocationViewController在地图中展示位置。
 */
- (void)presentLocationViewController:(RCLocationMessage *)locationMessageContent;

/*!
 查看文件消息中的文件

 @param model   消息Cell的数据模型

 @discussion SDK在此方法中会默认调用RCFilePreviewViewController下载并展示文件。
 */
- (void)presentFilePreviewViewController:(RCMessageModel *)model;

#pragma mark - 公众号
/*!
 点击公众号菜单

 @param selectedMenuItem  被点击的公众号菜单
 */
- (void)onPublicServiceMenuItemSelected:(RCPublicServiceMenuItem *)selectedMenuItem;

/*!
 点击公众号Cell中的URL的回调

 @param url   被点击的URL
 @param model 被点击的Cell对应的Model
 */
- (void)didTapUrlInPublicServiceMessageCell:(NSString *)url model:(RCMessageModel *)model;

#pragma mark - 客服
/*!
 用户的详细信息，此数据用于上传用户信息到客服后台，数据的nickName和portraitUrl必须填写。
 */
@property (nonatomic, strong) RCCustomerServiceInfo *csInfo;

/*!
客服评价弹出时间，在客服页面停留超过这个时间，离开客服会弹出评价提示框，默认为60s
 */
@property (nonatomic, assign) NSTimeInterval csEvaInterval;
/*!
 评价客服服务,然后离开当前VC的。此方法有可能在离开客服会话页面触发，也可能是客服在后台推送评价触发，也可能用户点击机器人知识库评价触发。应用可以重写此方法来自定义客服评价界面。应用不要直接调用此方法。

 @param serviceStatus  当前的服务类型。
 @param commentId
 评论ID。当是用户主动离开客服会话时，这个id是null；当客服在后台推送评价请求时，这个id是对话id；当用户点击机器人应答评价时，这个是机器人知识库id。
 @param isQuit         评价完成后是否离开

 @discussion
 sdk会在需要评价时调用此函数。如需自定义评价界面，请根据demo的RCDCustomerServiceViewController中的示例来重写此函数。
 */
- (void)commentCustomerServiceWithStatus:(RCCustomerServiceStatus)serviceStatus
                               commentId:(NSString *)commentId
                        quitAfterComment:(BOOL)isQuit;

/*!
 选择客服分组
 @param  groupList    所有客服分组
 @param  resultBlock  resultBlock
 @discussion
 重写这个方法你可以自己重写客服分组界面，当用户选择技能组后，调用resultBlock传入用户选择分组的groupId，如果用户没有选择，可以传nil，会自动分配一个客服分组
 */
- (void)onSelectCustomerServiceGroup:(NSArray *)groupList result:(void (^)(NSString *groupId))resultBlock;

/*!
 离开客服界面

 @discussion 调用此方法离开客服VC。
 */
- (void)customerServiceLeftCurrentViewController;

/*!
 客服服务模式变化

 @param newMode  新的客服服务模式。
 */
- (void)onCustomerServiceModeChanged:(RCCSModeType)newMode;

/*!
 客服通告

 @param announceMsg  客服通告内容
 @param announceClickUrl  客服通告链接url

 @discussion 此方法带回通告栏的展示内容及点击链接，须 App 自己实现
 */
- (void)announceViewWillShow:(NSString *)announceMsg announceClickUrl:(NSString *)announceClickUrl;

/*!
 输入框内输入了@符号，即将显示选人界面的回调

 @param selectedBlock 选人后的回调
 @param cancelBlock   取消选人的回调

 @discussion
 开发者如果想更换选人界面，可以重写方法，弹出自定义的选人界面，选人结束之后，调用selectedBlock传入选中的UserInfo即可。
 */
- (void)showChooseUserViewController:(void (^)(RCUserInfo *selectedUserInfo))selectedBlock
                              cancel:(void (^)(void))cancelBlock;

/*!
 合并转发消息的回调

 @param index            0 是逐条转发消息, 1 是合并转发消息。
 @param completedBlock   返回需要转发到的会话的列表。

 @discussion
 开发者如果想更换转发消息的选择会话界面，可以重写此方法，弹出自定义的选择会话界面，选择结束之后，调用completedBlock传入选中的会话即可。
 */
- (void)forwardMessage:(NSInteger)index completed:(void (^)(NSArray<RCConversation *> *conversationList))completedBlock;
@end
