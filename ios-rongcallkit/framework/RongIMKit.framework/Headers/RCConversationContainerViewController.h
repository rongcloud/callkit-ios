#import <UIKit/UIKit.h>

@class RCConversationListViewController;
@class RCConversationViewController;
@class RCConversationModel;
@class RCConversationContainerViewController;

NS_ASSUME_NONNULL_BEGIN

/// 会话容器的布局代理，回调在主线程执行。
@protocol RCConversationContainerViewControllerDelegate <NSObject>
@optional

/// 询问是否允许容器展开为双栏布局。
///
/// iOS 14 及以上在布局更新期间调用，可能多次调用。
/// 返回 YES 后，SDK 仍会检查可用空间及系统布局条件；未实现时由 SDK 决定是否展开。
/// - Parameter container: 当前会话容器。
/// - Parameter size: 当前容器视图的尺寸，尚未扣除安全区。
/// - Returns: YES 表示允许展开，NO 表示保持单栏布局。
- (BOOL)conversationContainer:(RCConversationContainerViewController *)container shouldExpandForSize:(CGSize)size;

/// 容器的实际双栏状态发生变化时调用。
/// - Parameter container: 当前会话容器。
/// - Parameter expanded: YES 表示列表与会话并排显示，NO 表示使用单栏布局。
- (void)conversationContainer:(RCConversationContainerViewController *)container didChangeExpanded:(BOOL)expanded;
@end

/// 管理会话列表、会话页面及其导航的自适应双栏容器。
///
/// 根据当前容器的可用空间、系统布局条件及代理返回值，在单栏与双栏布局之间自动切换。
/// 仅 iOS 14 及以上支持双栏，更低版本始终使用单栏布局。
/// 容器内部管理导航控制器，应直接放入 Tab 或其他父容器，不要在外部再次包装导航控制器。
/// 所有配置和页面操作必须在主线程执行。
@interface RCConversationContainerViewController : UIViewController

#pragma mark - 初始化

/// 不支持此初始化方式，请使用 initWithConversationListViewController:。
- (instancetype)init NS_UNAVAILABLE;
/// 不支持此初始化方式，请使用 initWithConversationListViewController:。
+ (instancetype)new NS_UNAVAILABLE;
/// 不支持此初始化方式，请使用 initWithConversationListViewController:。
- (instancetype)initWithNibName:(nullable NSString *)nibNameOrNil bundle:(nullable NSBundle *)nibBundleOrNil NS_UNAVAILABLE;
/// 不支持从归档或 Storyboard 创建，请使用 initWithConversationListViewController:。
- (instancetype)initWithCoder:(NSCoder *)coder NS_UNAVAILABLE;

/// 使用会话列表初始化容器，由容器管理列表的导航及会话页面的呈现。
/// - Parameter listViewController: 会话列表控制器，必须尚未属于其他父控制器。
/// - Returns: 会话容器对象。
- (instancetype)initWithConversationListViewController:(RCConversationListViewController *)listViewController;

#pragma mark - 布局与页面配置

/// 布局代理，用于限制双栏展开及接收实际布局状态变化通知。
@property (nonatomic, weak, nullable) id<RCConversationContainerViewControllerDelegate> delegate;

/// 自定义会话页面的创建回调，默认为 nil。
///
/// showConversationModel:animated: 需要创建新页面时调用，默认列表点击会通过该方法打开会话。
/// model 为目标会话的数据模型；回调应返回已完成业务配置、尚未属于其他父控制器的会话页面。
/// 返回 nil 表示取消本次打开操作；未设置时由 SDK 创建并配置默认会话页面。
/// 复用当前会话或调用 presentConversationViewController:animated: 时不会调用此回调。
@property (nonatomic, copy, nullable) RCConversationViewController * _Nullable (^conversationViewControllerFactory)(RCConversationModel *model);

/// 自定义内部导航控制器的创建回调，默认为 nil，必须在容器视图加载前设置。
///
/// rootViewController 为 SDK 提供的根页面。每次调用都应返回独立、尚未属于其他父控制器的导航控制器，
/// 并以 rootViewController 作为导航栈的根页面；不能返回 nil。
/// 此回调用于创建列表导航控制器，以及 iOS 14 及以上的详情导航控制器。
/// 未设置时使用 UINavigationController。
@property (nonatomic, copy, nullable) UINavigationController * _Nonnull (^navigationControllerFactory)(UIViewController *rootViewController);

/// 未打开会话时用于详情栏的占位页，必须尚未属于其他父控制器。
/// 未设置时由 SDK 创建默认占位页；更换占位页时，若当前未打开会话，会立即更新详情导航栈。
@property (nonatomic, strong, nullable) UIViewController *placeholderViewController;

#pragma mark - 当前页面与布局状态

/// 初始化容器时传入的会话列表控制器。
@property (nonatomic, strong, readonly) RCConversationListViewController *conversationListViewController;

/// 容器管理的列表导航控制器，在容器视图加载后可用。
@property (nonatomic, strong, readonly) UINavigationController *listNavigationController;

/// 容器当前管理的会话页面，尚未打开或已通过 closeConversationAnimated: 关闭会话时为 nil。
@property (nonatomic, strong, readonly, nullable) RCConversationViewController *currentConversationViewController;

/// 当前是否实际处于列表与会话并排显示的双栏布局，iOS 14 以下始终为 NO。
/// 此值反映实际布局结果，是否展开由可用空间、系统布局条件及代理返回值共同决定。
@property (nonatomic, assign, readonly, getter=isExpanded) BOOL expanded;

#pragma mark - 会话页面操作

/// 根据会话数据打开会话页面。
///
/// 若会话类型、目标 ID 和频道 ID 均与当前会话一致，则复用当前页面并返回该会话的根页面。
/// 否则通过 conversationViewControllerFactory 创建页面；未设置回调时由 SDK 创建默认页面。
/// - Parameter model: 目标会话的数据模型。
/// - Parameter animated: 是否在支持动画的导航操作中使用过渡动画。
- (void)showConversationModel:(RCConversationModel *)model animated:(BOOL)animated;

/// 呈现已完成业务配置的会话页面，根据当前布局显示在单栏或详情栏中。
///
/// 不调用 conversationViewControllerFactory。若会话类型、目标 ID 和频道 ID 与当前会话一致，
/// 则复用当前页面，忽略传入的新实例，并返回该会话的根页面。
/// - Parameter viewController: 要呈现的会话页面；打开新会话时，该页面必须尚未属于其他父控制器。
/// - Parameter animated: 是否在支持动画的导航操作中使用过渡动画。
- (void)presentConversationViewController:(RCConversationViewController *)viewController animated:(BOOL)animated;

/// 关闭当前会话及从该会话继续打开的页面，并结束编辑。
/// 单栏布局返回列表，双栏布局恢复详情占位页；当前没有会话时仅结束编辑。
/// - Parameter animated: 是否在支持动画的导航操作中使用过渡动画。
- (void)closeConversationAnimated:(BOOL)animated;

/// 通知容器会话已被删除，匹配当前会话时关闭会话及其后续页面。
///
/// 按会话类型、目标 ID 和频道 ID 匹配；聚合会话条目按会话类型匹配。
/// SDK 列表删除会话时会自动调用；自行处理删除逻辑时可调用此方法同步页面状态。
/// 此方法仅同步页面状态，不执行会话数据删除。
/// - Parameter model: 已删除会话的数据模型。
- (void)conversationWasDeleted:(RCConversationModel *)model;

/// 查找指定控制器所属的会话容器。
/// - Parameter viewController: 查找起点，依次检查该控制器自身及其父控制器。
/// - Returns: 最近的会话容器；不在会话容器中时返回 nil。
+ (nullable instancetype)containerForViewController:(UIViewController *)viewController;
@end

NS_ASSUME_NONNULL_END
