//
//  RCCallASRConfigController.m
//  RongCallKit
//
//  Created by RongCloud on 25/9/5.
//  Copyright © 2025年 RongCloud. All rights reserved.
//

#import "RCCallASRConfigController.h"
#import "RCCallBaseViewController.h"
#import "RCCallKitUtility.h"
#import <objc/runtime.h>

@interface RCCallASRConfigController () <UITableViewDataSource, UITableViewDelegate>

@property (nonatomic, strong) UIButton *translationButton;
@property (nonatomic, strong) UITableView *translationTableView;
@property (nonatomic, strong) UIView *translationContainer;
@property (nonatomic, strong) NSArray *destLangDisplayArray;
@property (nonatomic, strong) NSArray *destLangCodeArray;
@property (nonatomic, strong) NSArray *tableData;
@property (nonatomic, strong) UIView *customActionSheet;
@property (nonatomic, strong) UIView *actionSheetContainer;
@property (nonatomic, strong) UITableView *actionSheetTableView;
@property (nonatomic, strong) UIButton *cancelButton;

@end

@implementation RCCallASRConfigController

- (instancetype)init {
    self = [super init];
    if (self) {
        self.destLangDisplayArray = @[RCCallKitLocalizedString(@"subtitle_translation_display_none"),
                                      RCCallKitLocalizedString(@"subtitle_translation_display_chinese"),
                                      RCCallKitLocalizedString(@"subtitle_translation_display_english"),
                                      RCCallKitLocalizedString(@"subtitle_translation_display_arabic")];
        self.destLangCodeArray = @[@"none", @"zh", @"en", @"ar"];
        self.destLangCode = @"none"; // 初始化默认值
        self.tableData = @[
            @{@"title": RCCallKitLocalizedString(@"subtitle_translation_display"), @"type": @"selection"},
            @{@"title": RCCallKitLocalizedString(@"subtitle_bilingual_captions"), @"type": @"switch"}
        ];
    }
    return self;
}

- (void)viewDidLoad {
    [super viewDidLoad];
    // 初始化数据
    self.view.backgroundColor = [self adaptiveBackgroundColor];
    if (@available(iOS 11.0, *)) {
    } else {
         self.automaticallyAdjustsScrollViewInsets = NO;
    }
    [self.navigationItem setTitle:RCCallKitLocalizedString(@"subtitle_caption")];
    
    UIBarButtonItem *leftBarButtonItem = [[UIBarButtonItem alloc] initWithImage:[RCCallKitUtility isArabic] ? [RCCallKitUtility imageFromVoIPBundle:@"voip/forward.png"] : [RCCallKitUtility imageFromVoIPBundle:@"voip/back.png"] style:UIBarButtonItemStylePlain target:self action:@selector(backButtonClick:)];
    self.navigationItem.leftBarButtonItem = leftBarButtonItem;
    [self configTranslationUI];
}

- (void)viewWillAppear:(BOOL)animated {
    [super viewWillAppear:animated];
    if (@available(iOS 13.0, *)) {
        UINavigationBarAppearance *appearance = [UINavigationBarAppearance new];
        [appearance configureWithOpaqueBackground];
        appearance.backgroundColor = [self adaptiveBackgroundColor];
        appearance.titleTextAttributes = @{
            NSFontAttributeName: [UIFont boldSystemFontOfSize:20],
            NSForegroundColorAttributeName: [self adaptiveTextColor]
        };
        self.navigationController.navigationBar.scrollEdgeAppearance = appearance;
        self.navigationController.navigationBar.standardAppearance = appearance;
    } else {
        [self.navigationController.navigationBar setTitleTextAttributes:@{
            NSFontAttributeName: [UIFont boldSystemFontOfSize:20],
            NSForegroundColorAttributeName: [self adaptiveTextColor]
        }];
        self.navigationController.navigationBar.barTintColor = [self adaptiveBackgroundColor];
    }
}

- (void)configTranslationUI {
    self.translationContainer = [[UIView alloc] init];
    self.translationContainer.translatesAutoresizingMaskIntoConstraints = NO;
    self.translationContainer.backgroundColor = [self adaptiveBackgroundColor];

    UILabel *title = [[UILabel alloc] init];
    title.translatesAutoresizingMaskIntoConstraints = NO;
    title.text = RCCallKitLocalizedString(@"subtitle_translation_setting");
    title.font = [UIFont systemFontOfSize:14];
    title.textColor = [self adaptiveSecondaryTextColor];

    self.translationTableView = [[UITableView alloc] initWithFrame:CGRectZero style:UITableViewStylePlain];
    self.translationTableView.translatesAutoresizingMaskIntoConstraints = NO;
    self.translationTableView.backgroundColor = [self adaptiveSecondaryBackgroundColor];
    UIView *backgroundView = [[UIView alloc] init];
    backgroundView.backgroundColor = [self adaptiveSecondaryBackgroundColor];
    self.translationTableView.backgroundView = backgroundView;
    self.translationTableView.layer.cornerRadius = 10;
    self.translationTableView.clipsToBounds = YES;
    self.translationTableView.separatorStyle = UITableViewCellSeparatorStyleSingleLine;
    self.translationTableView.separatorInset = UIEdgeInsetsMake(0, 20, 0, 0);
    self.translationTableView.scrollEnabled = NO;
    self.translationTableView.dataSource = self;
    self.translationTableView.delegate = self;
    
    // 强制立即应用背景色
    [self.translationTableView setNeedsLayout];
    [self.translationTableView layoutIfNeeded];

    [self.translationContainer addSubview:title];
    [self.translationContainer addSubview:self.translationTableView];
    
    [self.view addSubview:self.translationContainer];
    
    // 设置约束
    [NSLayoutConstraint activateConstraints:@[
        // translationContainer 约束
        [self.translationContainer.leadingAnchor constraintEqualToAnchor:self.view.leadingAnchor constant:15],
        [self.translationContainer.trailingAnchor constraintEqualToAnchor:self.view.trailingAnchor constant:-15],
        [self.translationContainer.topAnchor constraintEqualToAnchor:self.view.safeAreaLayoutGuide.topAnchor constant:20],
        [self.translationContainer.heightAnchor constraintEqualToConstant:160],
        
        // title 约束 - 左上角
        [title.leadingAnchor constraintEqualToAnchor:self.translationContainer.leadingAnchor constant:0],
        [title.topAnchor constraintEqualToAnchor:self.translationContainer.topAnchor constant:0],
        
        // translationTableView 约束 - 中间区域
        [self.translationTableView.leadingAnchor constraintEqualToAnchor:self.translationContainer.leadingAnchor constant:0],
        [self.translationTableView.trailingAnchor constraintEqualToAnchor:self.translationContainer.trailingAnchor constant:0],
        [self.translationTableView.topAnchor constraintEqualToAnchor:title.bottomAnchor constant:10],
        [self.translationTableView.heightAnchor constraintEqualToConstant:120]
    ]];
}

- (void)backButtonClick:(UIButton *)sender {
    [self.navigationController dismissViewControllerAnimated:YES completion:nil];
    if (self.configCallback) {
        self.configCallback([self.destLangCode isEqualToString:@"none"] ? nil : self.destLangCode, self.displayDualLangUI);
    }
}

- (UIStatusBarStyle)preferredStatusBarStyle {
    return [self adaptiveStatusBarStyle];
}

// 更新导航栏样式
- (void)updateNavigationBarForCurrentTheme {
    if (@available(iOS 13.0, *)) {
        UINavigationBarAppearance *appearance = [UINavigationBarAppearance new];
        [appearance configureWithOpaqueBackground];
        appearance.backgroundColor = [self adaptiveBackgroundColor];
        appearance.titleTextAttributes = @{
            NSFontAttributeName: [UIFont boldSystemFontOfSize:20],
            NSForegroundColorAttributeName: [self adaptiveTextColor]
        };
        self.navigationController.navigationBar.scrollEdgeAppearance = appearance;
        self.navigationController.navigationBar.standardAppearance = appearance;
    } else {
        [self.navigationController.navigationBar setTitleTextAttributes:@{
            NSFontAttributeName: [UIFont boldSystemFontOfSize:20],
            NSForegroundColorAttributeName: [self adaptiveTextColor]
        }];
        self.navigationController.navigationBar.barTintColor = [self adaptiveBackgroundColor];
    }
}

#pragma mark - Custom ActionSheet

- (void)showCustomActionSheet {
    // 创建背景遮罩 - 覆盖整个屏幕包括导航栏
    CGRect screenBounds = [UIScreen mainScreen].bounds;
    self.customActionSheet = [[UIView alloc] initWithFrame:screenBounds];
    self.customActionSheet.backgroundColor = [UIColor colorWithWhite:0 alpha:0.5];
    self.customActionSheet.alpha = 0;
    
    // 添加点击手势来关闭
    UITapGestureRecognizer *tapGesture = [[UITapGestureRecognizer alloc] initWithTarget:self action:@selector(hideCustomActionSheet)];
    tapGesture.cancelsTouchesInView = NO;
    [self.customActionSheet addGestureRecognizer:tapGesture];
    
    // 创建内容容器
    self.actionSheetContainer = [[UIView alloc] init];
    self.actionSheetContainer.backgroundColor = [self adaptiveSecondaryBackgroundColor];
    self.actionSheetContainer.layer.cornerRadius = 12;
    self.actionSheetContainer.clipsToBounds = YES;
    self.actionSheetContainer.translatesAutoresizingMaskIntoConstraints = NO;
    
    // 创建标题
    UILabel *titleLabel = [[UILabel alloc] init];
    titleLabel.text = RCCallKitLocalizedString(@"subtitle_translation_display");
    titleLabel.font = [UIFont boldSystemFontOfSize:14];
    titleLabel.textColor = [self adaptiveSecondaryTextColor];
    titleLabel.translatesAutoresizingMaskIntoConstraints = NO;
    
    // 创建 TableView
    self.actionSheetTableView = [[UITableView alloc] initWithFrame:CGRectZero style:UITableViewStylePlain];
    self.actionSheetTableView.delegate = self;
    self.actionSheetTableView.dataSource = self;
    self.actionSheetTableView.separatorStyle = UITableViewCellSeparatorStyleSingleLine;
    self.actionSheetTableView.separatorInset = UIEdgeInsetsMake(0, 20, 0, 20);
    self.actionSheetTableView.scrollEnabled = NO;
    self.actionSheetTableView.translatesAutoresizingMaskIntoConstraints = NO;
    self.actionSheetTableView.backgroundColor = [self adaptiveSecondaryBackgroundColor];
    self.actionSheetTableView.rowHeight = 50.0;
    self.actionSheetTableView.estimatedRowHeight = 50.0;
    
    // 创建取消按钮
    self.cancelButton = [[UIButton alloc] init];
    [self.cancelButton setTitle:RCCallKitLocalizedString(@"Cancel") forState:UIControlStateNormal];
    [self.cancelButton setTitleColor:[UIColor systemBlueColor] forState:UIControlStateNormal];
    self.cancelButton.titleLabel.font = [UIFont systemFontOfSize:16];
    self.cancelButton.backgroundColor = [self adaptiveSecondaryBackgroundColor];
    self.cancelButton.layer.cornerRadius = 12;
    self.cancelButton.clipsToBounds = YES;
    self.cancelButton.translatesAutoresizingMaskIntoConstraints = NO;
    [self.cancelButton addTarget:self action:@selector(hideCustomActionSheet) forControlEvents:UIControlEventTouchUpInside];
    
    // 添加子视图
    [self.actionSheetContainer addSubview:titleLabel];
    [self.actionSheetContainer addSubview:self.actionSheetTableView];
    [self.customActionSheet addSubview:self.actionSheetContainer];
    [self.customActionSheet addSubview:self.cancelButton];
    // 添加到 window 以确保覆盖导航栏
    UIWindow *window = [UIApplication sharedApplication].keyWindow;
    if (!window) {
        window = [UIApplication sharedApplication].windows.firstObject;
    }
    [window addSubview:self.customActionSheet];
    
    // 计算动态高度
    NSInteger optionCount = self.destLangCodeArray.count;
    CGFloat titleHeight = 30;
    CGFloat titleTopMargin = 20;
    CGFloat titleBottomMargin = 10;
    CGFloat rowHeight = 50; // 每行高度
    CGFloat contentHeight = titleTopMargin + titleHeight + titleBottomMargin + (optionCount * rowHeight);
    
    // 设置最大高度限制
    CGFloat maxHeight = self.view.bounds.size.height * 0.6; // 最大不超过屏幕高度的60%
    contentHeight = MIN(contentHeight, maxHeight);
    
    // 设置约束
    [NSLayoutConstraint activateConstraints:@[
        // self.actionSheetContainer 约束 - 固定在底部
        [self.actionSheetContainer.leadingAnchor constraintEqualToAnchor:self.customActionSheet.leadingAnchor constant:20],
        [self.actionSheetContainer.trailingAnchor constraintEqualToAnchor:self.customActionSheet.trailingAnchor constant:-20],
        [self.actionSheetContainer.bottomAnchor constraintEqualToAnchor:self.cancelButton.topAnchor constant:-10],
        [self.actionSheetContainer.heightAnchor constraintEqualToConstant:contentHeight],
        
        // titleLabel 约束
        [titleLabel.topAnchor constraintEqualToAnchor:self.actionSheetContainer.topAnchor constant:titleTopMargin],
        [titleLabel.leadingAnchor constraintEqualToAnchor:self.actionSheetContainer.leadingAnchor constant:20],
        [titleLabel.trailingAnchor constraintEqualToAnchor:self.actionSheetContainer.trailingAnchor constant:-20],
        [titleLabel.heightAnchor constraintEqualToConstant:titleHeight],
        
        // actionSheetTableView 约束
        [self.actionSheetTableView.topAnchor constraintEqualToAnchor:titleLabel.bottomAnchor constant:titleBottomMargin],
        [self.actionSheetTableView.leadingAnchor constraintEqualToAnchor:self.actionSheetContainer.leadingAnchor],
        [self.actionSheetTableView.trailingAnchor constraintEqualToAnchor:self.actionSheetContainer.trailingAnchor],
        [self.actionSheetTableView.bottomAnchor constraintEqualToAnchor:self.actionSheetContainer.bottomAnchor],
        
        // self.cancelButton 约束 - 固定在底部
        [self.cancelButton.leadingAnchor constraintEqualToAnchor:self.customActionSheet.leadingAnchor constant:20],
        [self.cancelButton.trailingAnchor constraintEqualToAnchor:self.customActionSheet.trailingAnchor constant:-20],
        [self.cancelButton.bottomAnchor constraintEqualToAnchor:self.customActionSheet.safeAreaLayoutGuide.bottomAnchor constant:-20],
        [self.cancelButton.heightAnchor constraintEqualToConstant:50]
    ]];
    
    // 显示动画
    [UIView animateWithDuration:0.3 animations:^{
        self.customActionSheet.alpha = 1;
    }];
}

- (void)hideCustomActionSheet {
    [UIView animateWithDuration:0.3 animations:^{
        self.customActionSheet.alpha = 0;
    } completion:^(BOOL finished) {
        [self.customActionSheet removeFromSuperview];
        self.customActionSheet = nil;
        self.actionSheetTableView = nil;
    }];
}

#pragma mark - UITableViewDataSource

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
    if (tableView == self.actionSheetTableView) {
        return self.destLangCodeArray.count;
    }
    return self.tableData.count;
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    if (tableView == self.actionSheetTableView) {
        UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:@"ActionSheetCell"];
        if (!cell) {
            cell = [[UITableViewCell alloc] initWithStyle:UITableViewCellStyleValue1 reuseIdentifier:@"ActionSheetCell"];
            cell.selectionStyle = UITableViewCellSelectionStyleDefault;
        }
        cell.backgroundColor = [self adaptiveSecondaryBackgroundColor];
        cell.accessoryView = nil;
        NSString *key = [self.destLangCodeArray objectAtIndex:indexPath.row];
        NSString *title = [self.destLangDisplayArray objectAtIndex:indexPath.row];
        BOOL isSelected = [key isEqualToString:self.destLangCode];
        
        cell.textLabel.text = title;
        cell.textLabel.textColor = [self adaptiveTextColor];
        cell.textLabel.font = [UIFont systemFontOfSize:16];
        
        if (isSelected) {
            UIImageView *checkImageView = [[UIImageView alloc] initWithImage:[RCCallKitUtility imageFromVoIPBundle:@"voip/checkmark.png"]];
            checkImageView.contentMode = UIViewContentModeScaleAspectFit;
            cell.accessoryView = checkImageView;
        }
        return cell;
    } else {
        // 主 TableView 的 cell
        UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:@"TranslationCell"];
        if (!cell) {
            cell = [[UITableViewCell alloc] initWithStyle:UITableViewCellStyleValue1 reuseIdentifier:@"TranslationCell"];
            cell.selectionStyle = UITableViewCellSelectionStyleNone;
        }
        cell.backgroundColor = [self adaptiveSecondaryBackgroundColor];
        cell.accessoryView = nil;
        cell.detailTextLabel.text = nil;
        
        NSDictionary *data = self.tableData[indexPath.row];
        // 设置标题
        cell.textLabel.text = data[@"title"];
        cell.textLabel.textColor = [self adaptiveTextColor];
        cell.textLabel.font = [UIFont systemFontOfSize:16];
        
        NSString *type = data[@"type"];
        if ([type isEqualToString:@"selection"]) {
            NSInteger index = [self.destLangCodeArray indexOfObject:self.destLangCode];
            if (index != NSNotFound) {
                NSString *displayText = [self.destLangDisplayArray objectAtIndex:index];
                cell.detailTextLabel.text = displayText;
            }
            cell.detailTextLabel.textColor = [self adaptiveSecondaryTextColor];
            cell.detailTextLabel.font = [UIFont systemFontOfSize:16];
            
            // 设置自定义箭头
            UIImageView *arrowImageView = [[UIImageView alloc] initWithImage:[RCCallKitUtility isArabic] ? [RCCallKitUtility imageFromVoIPBundle:@"voip/left_arrow.png"] : [RCCallKitUtility imageFromVoIPBundle:@"voip/right_arrow.png"]];
            arrowImageView.contentMode = UIViewContentModeScaleAspectFit;
            cell.accessoryView = arrowImageView;
        } else if ([type isEqualToString:@"switch"]) {
            // 设置图标
            UIImageView *switchImageView = [[UIImageView alloc] initWithImage:[RCCallKitUtility imageFromVoIPBundle:self.displayDualLangUI ? @"voip/switch_on.png" : @"voip/switch_off.png"]];
            switchImageView.transform = [RCCallKitUtility isArabic] ? CGAffineTransformMakeScale(-1, 1) : CGAffineTransformMakeScale(1, 1);
            switchImageView.contentMode = UIViewContentModeScaleAspectFit;
            cell.accessoryView = switchImageView;
        }
        
        return cell;
    }
}

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath {
    if (tableView == self.actionSheetTableView) {
        // 处理自定义 ActionSheet 的选择
        NSString *selectedKey = [self.destLangCodeArray objectAtIndex:indexPath.row];
        self.destLangCode = selectedKey;
        
        // 刷新主 TableView 的第一行
        NSIndexPath *selectionIndexPath = [NSIndexPath indexPathForRow:0 inSection:0];
        [self.translationTableView reloadRowsAtIndexPaths:@[selectionIndexPath] withRowAnimation:UITableViewRowAnimationNone];
        
        // 关闭 ActionSheet
        [self hideCustomActionSheet];
    } else {
        // 处理主 TableView 的选择
        if (indexPath.row == 0) {
            [self showCustomActionSheet];
        } else if (indexPath.row == 1) {
            self.displayDualLangUI = !self.displayDualLangUI;
            NSIndexPath *switchIndexPath = [NSIndexPath indexPathForRow:1 inSection:0];
            UITableViewCell *cell = [self.translationTableView cellForRowAtIndexPath:switchIndexPath];
            if (cell && cell.accessoryView) {
                // 直接更新 accessoryView 的图片，避免重新创建 cell
                UIImageView *switchImageView = (UIImageView *)cell.accessoryView;
                switchImageView.image = [RCCallKitUtility imageFromVoIPBundle:self.displayDualLangUI ? @"voip/switch_on.png" : @"voip/switch_off.png"];
                switchImageView.transform = [RCCallKitUtility isArabic] ? CGAffineTransformMakeScale(-1, 1) : CGAffineTransformMakeScale(1, 1);
            } else {
                // 如果 cell 不存在，则使用无动画刷新
                [self.translationTableView reloadRowsAtIndexPaths:@[switchIndexPath] withRowAnimation:UITableViewRowAnimationNone];
            }
        }
    }
}

#pragma mark - UITableViewDelegate

- (CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath {
    if (tableView == self.actionSheetTableView) {
        return 50.0; // ActionSheet 每行高度
    }
    return 60.0; // 主 TableView 每行高度
}

#pragma mark - Dark Mode Support

- (UIColor *)adaptiveBackgroundColor {
    if (@available(iOS 13.0, *)) {
        if ([self isDarkMode]) {
            return [UIColor systemBackgroundColor];
        }
    }
    return RongVoIPUIColorFromRGB(0xF2F1F6);
}

- (UIColor *)adaptiveSecondaryBackgroundColor {
    if (@available(iOS 13.0, *)) {
        if ([self isDarkMode]) {
            return [UIColor secondarySystemBackgroundColor];
        }
    }
    return [UIColor whiteColor];
}

- (UIColor *)adaptiveTextColor {
    if (@available(iOS 13.0, *)) {
        if ([self isDarkMode]) {
            return [UIColor labelColor];
        }
    }
    return [UIColor blackColor];
}

- (UIColor *)adaptiveSecondaryTextColor {
    if (@available(iOS 13.0, *)) {
        if ([self isDarkMode]) {
            return [UIColor secondaryLabelColor];
        }
    }
    return RongVoIPUIColorFromRGB(0x7C838E);
}

- (UIStatusBarStyle)adaptiveStatusBarStyle {
    if (@available(iOS 13.0, *)) {
        if ([self isDarkMode]) {
            return UIStatusBarStyleDefault;
        }
    }
    return UIStatusBarStyleLightContent;
}

- (BOOL)isDarkMode {
    if (@available(iOS 13.0, *)) {
        // iOS 13+ 使用 traitCollection 判断
        return self.traitCollection.userInterfaceStyle == UIUserInterfaceStyleDark;
    } else {
        // iOS 13 以下默认返回 NO（浅色模式）
        return NO;
    }
}

#pragma mark - 主题变化监听
- (void)traitCollectionDidChange:(UITraitCollection *)previousTraitCollection {
    [super traitCollectionDidChange:previousTraitCollection];
    
    if (@available(iOS 13.0, *)) {
        // 检查颜色外观是否发生变化
        if ([self.traitCollection hasDifferentColorAppearanceComparedToTraitCollection:previousTraitCollection]) {
            [self updateUIForCurrentTheme];
        }
    }
}

// 更新UI颜色以适配当前主题
- (void)updateUIForCurrentTheme {
    // 更新主视图背景
    self.view.backgroundColor = [self adaptiveBackgroundColor];
    
    // 更新translationContainer背景
    if (self.translationContainer) {
        self.translationContainer.backgroundColor = [self adaptiveBackgroundColor];
    }
    // 更新translationTableView
    if (self.translationTableView) {
        self.translationTableView.backgroundColor = [self adaptiveSecondaryBackgroundColor];
        [self.translationTableView reloadData];
    }
    
    // 更新actionSheetContainer背景
    if (self.actionSheetContainer) {
        self.actionSheetContainer.backgroundColor = [self adaptiveSecondaryBackgroundColor];
    }
    // 更新actionSheetTableView
    if (self.actionSheetTableView) {
        self.actionSheetTableView.backgroundColor = [self adaptiveSecondaryBackgroundColor];
        [self.actionSheetTableView reloadData];
    }
    // 更新cancelButton
    if (self.cancelButton) {
        self.cancelButton.backgroundColor = [self adaptiveSecondaryBackgroundColor];
    }
    
    // 更新导航栏
    [self updateNavigationBarForCurrentTheme];
    
    // 更新状态栏
    [self setNeedsStatusBarAppearanceUpdate];
}

@end
