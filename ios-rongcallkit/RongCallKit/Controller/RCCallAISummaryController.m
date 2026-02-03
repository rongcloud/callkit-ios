//
//  RCCallAISummaryController.m
//  RongCallKit
//
//  Created by RongCloud on 25/12/8.
//  Copyright © 2025年 RongCloud. All rights reserved.
//

#import "RCCallAISummaryController.h"
#import <WebKit/WebKit.h>
#import <RongCallLib/RongCallLib.h>
#import "RCAdapteRongIMKitHeader.h"
#import "RCCallKitUtility.h"
#import "cmark.h"

@interface RCCallAISummaryController () <WKNavigationDelegate, UITableViewDataSource, UITableViewDelegate>

@property (nonatomic, copy) NSString *taskId;
@property (nonatomic, copy) NSString *callId;
@property (nonatomic, assign) BOOL displayStartSummaryButton;
@property (nonatomic, assign) BOOL autoGenSummary;
@property (nonatomic, assign) BOOL isSummaryStarted;
@property (nonatomic, assign) BOOL waitingForASRStart;
@property (nonatomic, assign) BOOL isASRStarted;

@property (nonatomic, strong) UIButton *startSummaryButton;
@property (nonatomic, strong) UIView *toolbarView;
@property (nonatomic, strong) UILabel *contentLabel;
@property (nonatomic, strong) UIButton *refreshButton;
@property (nonatomic, strong) UIButton *languageButton;
@property (nonatomic, strong) UIView *contentContainer;
@property (nonatomic, strong) WKWebView *webView;

@property (nonatomic, strong) NSMutableString *accumulatedContent;
@property (nonatomic, strong) NSTimer *typingTimer;
@property (nonatomic, assign) NSInteger currentIndex;
@property (nonatomic, assign) BOOL isUpdatingContent;
@property (nonatomic, assign) NSInteger currentRequestId;
@property (nonatomic, assign) NSInteger typingRequestId;
@property (nonatomic, copy) NSString *selectedLanguage;

@property (nonatomic, strong) NSArray<NSString *> *languageDisplayArray;
@property (nonatomic, strong) NSArray<NSString *> *languageCodeArray;

@property (nonatomic, strong) UIView *customActionSheet;
@property (nonatomic, strong) UIView *actionSheetContainer;
@property (nonatomic, strong) UITableView *actionSheetTableView;
@property (nonatomic, strong) UIButton *cancelButton;

@end

@implementation RCCallAISummaryController

- (instancetype)initWithTaskId:(NSString *)taskId
                        callId:(NSString *)callId
     displayStartSummaryButton:(BOOL)displayStartSummaryButton
              isSummaryStarted:(BOOL)isSummaryStarted
                  isASRStarted:(BOOL)isASRStarted
                autoGenSummary:(BOOL)autoGenSummary
                defaultContent:(NSString *)defaultContent {
    if (self = [super init]) {
        _taskId = taskId;
        _callId = callId;
        _displayStartSummaryButton = displayStartSummaryButton;
        _autoGenSummary = autoGenSummary;
        _isSummaryStarted = isSummaryStarted;
        _isASRStarted = isASRStarted;
        if (defaultContent.length > 0) {
            _accumulatedContent = [NSMutableString stringWithString:defaultContent];
        }
    }
    return self;
}

- (void)dealloc {
    [[NSNotificationCenter defaultCenter] removeObserver:self];
    [self stopTypingEffect];
}

- (void)viewDidLoad {
    [super viewDidLoad];
    
    self.view.backgroundColor = [self adaptiveBackgroundColor];
    self.selectedLanguage = RCCallKitLocalizedString(@"subtitle_translation_display_chinese");
    self.languageDisplayArray = @[
        RCCallKitLocalizedString(@"subtitle_translation_display_chinese"),
        RCCallKitLocalizedString(@"subtitle_translation_display_english"),
        RCCallKitLocalizedString(@"subtitle_translation_display_arabic")
    ];
    self.languageCodeArray = @[@"zh", @"en", @"ar"];
    
    [[NSNotificationCenter defaultCenter] addObserver:self
                                             selector:@selector(handleSummarizationStatusChange:)
                                                 name:@"RCCallSummarizationStatusDidChangeNotification"
                                               object:nil];
    
    [[NSNotificationCenter defaultCenter] addObserver:self
                                             selector:@selector(handleASRStatusChange:)
                                                 name:@"RCCallASRStatusDidChangeNotification"
                                               object:nil];
    
    [self.navigationItem setTitle:RCCallKitLocalizedString(@"ai_summary_title")];
    
    if (self.displayStartSummaryButton) {
        self.startSummaryButton = [[UIButton alloc] init];
        [self updateStartSummaryImage];
        [self.startSummaryButton addTarget:self action:@selector(startSummaryButtonClicked) forControlEvents:UIControlEventTouchUpInside];
        UIBarButtonItem *leftBarButtonItem = [[UIBarButtonItem alloc] initWithCustomView:self.startSummaryButton];
        self.navigationItem.leftBarButtonItem = leftBarButtonItem;
    }
    
    UIBarButtonItem *closeButtonItem = [[UIBarButtonItem alloc] initWithImage:[RCCallKitUtility imageFromVoIPBundle:@"voip/close.png"]
                                                                        style:UIBarButtonItemStylePlain
                                                                       target:self
                                                                       action:@selector(backButtonClick:)];
    self.navigationItem.rightBarButtonItem = closeButtonItem;
    
    [self setupUI];
    [self loadInitialHTMLStructure];
}

- (void)viewWillAppear:(BOOL)animated {
    [super viewWillAppear:animated];
    [self updateNavigationBarForCurrentTheme];
}

- (void)viewWillDisappear:(BOOL)animated {
    [super viewWillDisappear:animated];
    [self stopTypingEffect];
}

#pragma mark - UI Setup

- (void)setupUI {
    // 工具栏视图（总结内容 + 刷新按钮 + 语言选择）
    self.toolbarView = [[UIView alloc] init];
    self.toolbarView.backgroundColor = [UIColor clearColor];
    self.toolbarView.translatesAutoresizingMaskIntoConstraints = NO;
    [self.view addSubview:self.toolbarView];
    
    // 总结内容标签
    self.contentLabel = [[UILabel alloc] init];
    self.contentLabel.text = RCCallKitLocalizedString(@"summary_content");
    self.contentLabel.font = [UIFont systemFontOfSize:16];
    self.contentLabel.textColor = [self adaptiveSecondaryTextColor];
    self.contentLabel.translatesAutoresizingMaskIntoConstraints = NO;
    [self.toolbarView addSubview:self.contentLabel];
    
    // 刷新按钮
    self.refreshButton = [[UIButton alloc] init];
    [self.refreshButton setImage:[RCCallKitUtility imageFromVoIPBundle:@"voip/refresh.png"] forState:UIControlStateNormal];
    [self.refreshButton addTarget:self action:@selector(refreshContent) forControlEvents:UIControlEventTouchUpInside];
    self.refreshButton.translatesAutoresizingMaskIntoConstraints = NO;
    [self.toolbarView addSubview:self.refreshButton];
    
    // 语言选择按钮
    self.languageButton = [[UIButton alloc] init];
    [self.languageButton setTitle:self.selectedLanguage forState:UIControlStateNormal];
    [self.languageButton setImage:[RCCallKitUtility imageFromVoIPBundle:@"voip/up.png"] forState:UIControlStateNormal];
    [self.languageButton setTitleColor:[self adaptiveTextColor] forState:UIControlStateNormal];
    self.languageButton.titleLabel.font = [UIFont systemFontOfSize:16];
    self.languageButton.titleLabel.lineBreakMode = NSLineBreakByTruncatingTail;
    self.languageButton.contentHorizontalAlignment = UIControlContentHorizontalAlignmentRight;
    [self.languageButton addTarget:self action:@selector(showCustomLanguageActionSheet) forControlEvents:UIControlEventTouchUpInside];
    self.languageButton.translatesAutoresizingMaskIntoConstraints = NO;
    [self.toolbarView addSubview:self.languageButton];
    [self updateLanguageButtonImagePosition];
    
    // 内容容器
    self.contentContainer = [[UIView alloc] init];
    self.contentContainer.backgroundColor = [self adaptiveSecondaryBackgroundColor];
    self.contentContainer.layer.cornerRadius = 10;
    self.contentContainer.clipsToBounds = YES;
    self.contentContainer.translatesAutoresizingMaskIntoConstraints = NO;
    [self.view addSubview:self.contentContainer];
    
    // WebView
    WKWebViewConfiguration *config = [[WKWebViewConfiguration alloc] init];
    self.webView = [[WKWebView alloc] initWithFrame:CGRectZero configuration:config];
    self.webView.navigationDelegate = self;
    self.webView.scrollView.showsVerticalScrollIndicator = YES;
    self.webView.backgroundColor = [UIColor clearColor];
    self.webView.opaque = NO;
    self.webView.translatesAutoresizingMaskIntoConstraints = NO;
    [self.contentContainer addSubview:self.webView];
    
    // 布局约束
    [NSLayoutConstraint activateConstraints:@[
        // 工具栏
        [self.toolbarView.topAnchor constraintEqualToAnchor:self.view.safeAreaLayoutGuide.topAnchor constant:10],
        [self.toolbarView.leadingAnchor constraintEqualToAnchor:self.view.leadingAnchor constant:15],
        [self.toolbarView.trailingAnchor constraintEqualToAnchor:self.view.trailingAnchor constant:-15],
        [self.toolbarView.heightAnchor constraintEqualToConstant:30],
        
        // 总结内容标签
        [self.contentLabel.leadingAnchor constraintEqualToAnchor:self.toolbarView.leadingAnchor],
        [self.contentLabel.centerYAnchor constraintEqualToAnchor:self.toolbarView.centerYAnchor],
        
        // 刷新按钮
        [self.refreshButton.leadingAnchor constraintEqualToAnchor:self.contentLabel.trailingAnchor constant:8],
        [self.refreshButton.centerYAnchor constraintEqualToAnchor:self.toolbarView.centerYAnchor],
        [self.refreshButton.widthAnchor constraintEqualToConstant:24],
        [self.refreshButton.heightAnchor constraintEqualToConstant:24],
        
        // 语言按钮（固定最大宽度，避免挤占其他元素）
        [self.languageButton.leadingAnchor constraintGreaterThanOrEqualToAnchor:self.refreshButton.trailingAnchor constant:10],
        [self.languageButton.trailingAnchor constraintEqualToAnchor:self.toolbarView.trailingAnchor],
        [self.languageButton.centerYAnchor constraintEqualToAnchor:self.toolbarView.centerYAnchor],
        [self.languageButton.widthAnchor constraintLessThanOrEqualToConstant:100],
        
        // 内容容器
        [self.contentContainer.topAnchor constraintEqualToAnchor:self.toolbarView.bottomAnchor constant:10],
        [self.contentContainer.leadingAnchor constraintEqualToAnchor:self.view.leadingAnchor constant:15],
        [self.contentContainer.trailingAnchor constraintEqualToAnchor:self.view.trailingAnchor constant:-15],
        [self.contentContainer.bottomAnchor constraintEqualToAnchor:self.view.safeAreaLayoutGuide.bottomAnchor constant:-20],
        
        // WebView
        [self.webView.topAnchor constraintEqualToAnchor:self.contentContainer.topAnchor],
        [self.webView.leadingAnchor constraintEqualToAnchor:self.contentContainer.leadingAnchor],
        [self.webView.trailingAnchor constraintEqualToAnchor:self.contentContainer.trailingAnchor],
        [self.webView.bottomAnchor constraintEqualToAnchor:self.contentContainer.bottomAnchor],
    ]];
}

- (void)updateLanguageButtonImagePosition {
    if (!self.languageButton) {
        return;
    }
    CGFloat spacing = 4.0;
    if ([RCCallKitUtility isArabic]) {
        // RTL：图标在左，文字在右
        self.languageButton.semanticContentAttribute = UISemanticContentAttributeForceLeftToRight;
        self.languageButton.imageEdgeInsets = UIEdgeInsetsMake(0, -spacing, 0, spacing);
        self.languageButton.titleEdgeInsets = UIEdgeInsetsMake(0, spacing, 0, -spacing);
    } else {
        // LTR：图标在右，文字在左
        self.languageButton.semanticContentAttribute = UISemanticContentAttributeForceRightToLeft;
        self.languageButton.imageEdgeInsets = UIEdgeInsetsMake(0, spacing, 0, -spacing);
        self.languageButton.titleEdgeInsets = UIEdgeInsetsMake(0, -spacing, 0, spacing);
    }
}

#pragma mark - Actions

- (void)backButtonClick:(UIButton *)sender {
    [self.navigationController dismissViewControllerAnimated:YES completion:nil];
}

- (void)refreshContent {
    [self fetchSummarizationContent];
}

- (NSString *)languageCodeForSelectedLanguage {
    if (self.selectedLanguage.length == 0) {
        return @"";
    }
    NSUInteger idx = [self.languageDisplayArray indexOfObject:self.selectedLanguage];
    if (idx != NSNotFound && idx < self.languageCodeArray.count) {
        return self.languageCodeArray[idx];
    }
    return @"zh";
}

- (BOOL)isRTLForSelectedLanguage {
    return [[self languageCodeForSelectedLanguage] isEqualToString:@"ar"];
}

- (void)showCustomLanguageActionSheet {
    if (self.customActionSheet.superview) {
        return;
    }
    
    // 创建背景遮罩 - 覆盖整个屏幕包括导航栏
    CGRect screenBounds = [UIScreen mainScreen].bounds;
    self.customActionSheet = [[UIView alloc] initWithFrame:screenBounds];
    self.customActionSheet.backgroundColor = [UIColor colorWithWhite:0 alpha:0.5];
    self.customActionSheet.alpha = 0;
    
    // 添加点击手势来关闭
    UITapGestureRecognizer *tapGesture = [[UITapGestureRecognizer alloc] initWithTarget:self action:@selector(hideCustomLanguageActionSheet)];
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
    [self.cancelButton addTarget:self action:@selector(hideCustomLanguageActionSheet) forControlEvents:UIControlEventTouchUpInside];
    
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
    NSInteger optionCount = self.languageDisplayArray.count;
    CGFloat titleHeight = 30;
    CGFloat titleTopMargin = 20;
    CGFloat titleBottomMargin = 10;
    CGFloat rowHeight = 50;
    CGFloat contentHeight = titleTopMargin + titleHeight + titleBottomMargin + (optionCount * rowHeight);
    
    // 设置最大高度限制
    CGFloat maxHeight = self.view.bounds.size.height * 0.6;
    contentHeight = MIN(contentHeight, maxHeight);
    
    // 设置约束
    [NSLayoutConstraint activateConstraints:@[
        [self.actionSheetContainer.leadingAnchor constraintEqualToAnchor:self.customActionSheet.leadingAnchor constant:20],
        [self.actionSheetContainer.trailingAnchor constraintEqualToAnchor:self.customActionSheet.trailingAnchor constant:-20],
        [self.actionSheetContainer.bottomAnchor constraintEqualToAnchor:self.cancelButton.topAnchor constant:-10],
        [self.actionSheetContainer.heightAnchor constraintEqualToConstant:contentHeight],
        
        [titleLabel.topAnchor constraintEqualToAnchor:self.actionSheetContainer.topAnchor constant:titleTopMargin],
        [titleLabel.leadingAnchor constraintEqualToAnchor:self.actionSheetContainer.leadingAnchor constant:20],
        [titleLabel.trailingAnchor constraintEqualToAnchor:self.actionSheetContainer.trailingAnchor constant:-20],
        [titleLabel.heightAnchor constraintEqualToConstant:titleHeight],
        
        [self.actionSheetTableView.topAnchor constraintEqualToAnchor:titleLabel.bottomAnchor constant:titleBottomMargin],
        [self.actionSheetTableView.leadingAnchor constraintEqualToAnchor:self.actionSheetContainer.leadingAnchor constant:0],
        [self.actionSheetTableView.trailingAnchor constraintEqualToAnchor:self.actionSheetContainer.trailingAnchor constant:0],
        [self.actionSheetTableView.bottomAnchor constraintEqualToAnchor:self.actionSheetContainer.bottomAnchor constant:0],
        
        [self.cancelButton.leadingAnchor constraintEqualToAnchor:self.customActionSheet.leadingAnchor constant:20],
        [self.cancelButton.trailingAnchor constraintEqualToAnchor:self.customActionSheet.trailingAnchor constant:-20],
        [self.cancelButton.bottomAnchor constraintEqualToAnchor:self.customActionSheet.safeAreaLayoutGuide.bottomAnchor constant:-10],
        [self.cancelButton.heightAnchor constraintEqualToConstant:50],
    ]];
    
    [self.actionSheetTableView reloadData];
    
    // 动画显示
    [UIView animateWithDuration:0.25 animations:^{
        self.customActionSheet.alpha = 1.0;
    }];
}

- (void)hideCustomLanguageActionSheet {
    if (!self.customActionSheet.superview) {
        return;
    }
    [UIView animateWithDuration:0.25 animations:^{
        self.customActionSheet.alpha = 0;
    } completion:^(BOOL finished) {
        [self.customActionSheet removeFromSuperview];
        self.customActionSheet = nil;
        self.actionSheetContainer = nil;
        self.actionSheetTableView = nil;
        self.cancelButton = nil;
    }];
}

#pragma mark - UITableViewDataSource / UITableViewDelegate

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
    if (tableView == self.actionSheetTableView) {
        return self.languageDisplayArray.count;
    }
    return 0;
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    static NSString *cellId = @"RCCallAISummaryLanguageCell";
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:cellId];
    if (!cell) {
        // 和 RCCallASRConfigController 的 ActionSheetCell 保持一致：Value1 + accessoryView 自定义勾选图标
        cell = [[UITableViewCell alloc] initWithStyle:UITableViewCellStyleValue1 reuseIdentifier:cellId];
        cell.selectionStyle = UITableViewCellSelectionStyleDefault;
    }
    
    cell.backgroundColor = [self adaptiveSecondaryBackgroundColor];
    cell.accessoryView = nil;
    cell.textLabel.textColor = [self adaptiveTextColor];
    cell.textLabel.font = [UIFont systemFontOfSize:16];
    cell.separatorInset = UIEdgeInsetsMake(0, 20, 0, 20);
    cell.preservesSuperviewLayoutMargins = NO;
    cell.layoutMargins = UIEdgeInsetsMake(0, 20, 0, 20);
    
    NSString *language = self.languageDisplayArray[indexPath.row];
    cell.textLabel.text = language;
    
    if ([self.selectedLanguage isEqualToString:language]) {
        UIImageView *checkImageView = [[UIImageView alloc] initWithImage:[RCCallKitUtility imageFromVoIPBundle:@"voip/checkmark.png"]];
        checkImageView.contentMode = UIViewContentModeScaleAspectFit;
        cell.accessoryView = checkImageView;
    }
    return cell;
}

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath {
    if (tableView != self.actionSheetTableView) {
        return;
    }
    [tableView deselectRowAtIndexPath:indexPath animated:YES];
    
    NSString *language = self.languageDisplayArray[indexPath.row];
    if (language.length == 0) {
        return;
    }
    self.selectedLanguage = language;
    [self.languageButton setTitle:language forState:UIControlStateNormal];
    [self hideCustomLanguageActionSheet];
    [self fetchSummarizationContent];
}

- (void)updateStartSummaryImage {
    NSString *imageName = self.isSummaryStarted ? @"voip/switch_on.png" : @"voip/switch_off.png";
    [self.startSummaryButton setImage:[RCCallKitUtility imageFromVoIPBundle:imageName] forState:UIControlStateNormal];
    self.startSummaryButton.imageView.transform = [RCCallKitUtility isArabic] ? CGAffineTransformMakeScale(-1, 1) : CGAffineTransformMakeScale(1, 1);
}

- (void)handleSummarizationStatusChange:(NSNotification *)notification {
    if (self.displayStartSummaryButton) {
        BOOL started = [notification.userInfo[@"started"] boolValue];
        NSString *taskId = notification.userInfo[@"taskId"];
        
        dispatch_async(dispatch_get_main_queue(), ^{
            self.isSummaryStarted = started;
            if (started && taskId.length > 0) {
                self.taskId = taskId;
            }
            [self updateStartSummaryImage];
        });
    }
}

- (void)showErrorAlert:(NSString *)message {
    [RCAlertView showAlertController:nil
                             message:message
                        actionTitles:nil
                         cancelTitle:RCCallKitLocalizedString(@"OK")
                        confirmTitle:nil
                      preferredStyle:UIAlertControllerStyleAlert
                        actionsBlock:nil
                         cancelBlock:nil
                        confirmBlock:nil
                    inViewController:self];
}

- (void)startSummaryButtonClicked {
    __weak typeof(self) weakSelf = self;
    if (!self.isSummaryStarted) {
        if (self.isASRStarted) {
            [self doStartSummarization];
        } else {
            [[RCCallClient sharedRCCallClient] startASR:^(BOOL success, NSInteger code) {
                __strong typeof(weakSelf) strongSelf = weakSelf;
                if (!strongSelf) return;
                
                if (success) {
                    strongSelf.waitingForASRStart = YES;
                } else {
                    [strongSelf showErrorAlert:RCCallKitLocalizedString(@"start_summray_failed_retry_later")];
                }
            }];
        }
    } else {
        [[RCCallClient sharedRCCallClient] stopSummarization:^(BOOL isSuccess, RCRTCCode code) {
            __strong typeof(weakSelf) strongSelf = weakSelf;
            if (!strongSelf) return;
            
            if (isSuccess) {
                strongSelf.isSummaryStarted = NO;
                [strongSelf updateStartSummaryImage];
            } else {
                strongSelf.isSummaryStarted = YES;
                [strongSelf updateStartSummaryImage];
            }
        }];
    }
}

- (void)handleASRStatusChange:(NSNotification *)notification {
    if (self.displayStartSummaryButton) {
        BOOL started = [notification.userInfo[@"started"] boolValue];
        self.isASRStarted = started;
        
        if (started && self.waitingForASRStart) {
            self.waitingForASRStart = NO;
            [self doStartSummarization];
        }
    }
}

- (void)doStartSummarization {
    __weak typeof(self) weakSelf = self;
    [[RCCallClient sharedRCCallClient] startSummarization:^(BOOL isSuccess, RCRTCCode code, NSString * _Nullable taskId) {
        __strong typeof(weakSelf) strongSelf = weakSelf;
        if (!strongSelf) return;
        
        if (isSuccess) {
            strongSelf.taskId = taskId;
            strongSelf.isSummaryStarted = YES;
            [strongSelf updateStartSummaryImage];
            [strongSelf fetchSummarizationContent];
        } else {
            strongSelf.isSummaryStarted = NO;
            [strongSelf updateStartSummaryImage];
            [strongSelf showErrorAlert:RCCallKitLocalizedString(@"start_summray_failed_retry_later")];
        }
    }];
}

#pragma mark - Fetch Content

- (void)fetchSummarizationContent {
    if (!self.callId.length || !self.taskId.length) {
        return;
    }
    
    NSInteger requestId = ++self.currentRequestId;
    self.accumulatedContent = [NSMutableString string];
    [self stopTypingEffect];
    
    // 配置参数
    RCRTCGenerateSummarizationConfig *config = [[RCRTCGenerateSummarizationConfig alloc] init];
    config.destLang = [self languageCodeForSelectedLanguage];
    config.enableSummarization = YES;
    config.enableSummarizationDetails = YES;
    config.enableChapterSummary = YES;
    config.enableTodoList = YES;
    config.enableHashtag = YES;
    config.format = RCRTCSummarizationFormatMarkDown;
    
    __weak typeof(self) weakSelf = self;
    [[RCCallClient sharedRCCallClient] generateSummarization:self.callId
                                                      taskId:self.taskId
                                                   startTime:0
                                                     endTime:0
                                                      config:config
                                                contentBlock:^(NSString * _Nonnull content) {
        __strong typeof(weakSelf) strongSelf = weakSelf;
        if (!strongSelf || requestId != strongSelf.currentRequestId) {
            return;
        }
        
        [strongSelf.accumulatedContent appendString:content];
        if (strongSelf.accumulatedContent.length) {
            NSString *fullText = [strongSelf.accumulatedContent copy];
            if (strongSelf.contentUpdateCallback) {
                strongSelf.contentUpdateCallback(fullText);
            }
        }
        if (!strongSelf.typingTimer || !strongSelf.typingTimer.isValid) {
            [strongSelf startTypingEffect];
        }
    } completion:^(BOOL isSuccess, RCRTCCode code) {
        __strong typeof(weakSelf) strongSelf = weakSelf;
        if (!strongSelf || requestId != strongSelf.currentRequestId) {
            return;
        }
        
        if (isSuccess) {
            [strongSelf stopTypingEffect];
            if (strongSelf.accumulatedContent) {
                NSString *fullText = [strongSelf.accumulatedContent copy];
                [strongSelf updateWebViewContent:fullText];
            }
        } else {
            [strongSelf showErrorAlert:RCCallKitLocalizedString(@"request_failed_retry_later")];
        }
    }];
}

#pragma mark - HTML Structure

- (void)loadInitialHTMLStructure {
    BOOL isDark = [self isDarkMode];
    NSString *bgColor = isDark ? @"#1c1c1e" : @"#ffffff";
    NSString *textColor = isDark ? @"#ffffff" : @"#333333";
    NSString *secondaryTextColor = isDark ? @"#8e8e93" : @"#666666";
    NSString *borderColor = isDark ? @"#38383a" : @"#f0f0f0";
    NSString *codeBackgroundColor = isDark ? @"#2c2c2e" : @"#f5f5f5";
    NSString *blockquoteColor = isDark ? @"#0a84ff" : @"#007aff";
    NSString *htmlDir = [self isRTLForSelectedLanguage] ? @"rtl" : @"ltr";
    
    NSString *initialHTML = [NSString stringWithFormat:
        @"<!DOCTYPE html>"
        @"<html dir=\"%@\">"
        @"<head>"
        @"<meta charset=\"UTF-8\">"
        @"<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, maximum-scale=1.0, user-scalable=no\">"
        @"<style>"
        @"* { box-sizing: border-box; -webkit-tap-highlight-color: transparent; }"
        // RTL：选阿语时整体从右到左（列表缩进也需要反向）
        @"html[dir=\"rtl\"] body { direction: rtl; text-align: right; }"
        @"html[dir=\"rtl\"] ul, html[dir=\"rtl\"] ol { padding-right: 20px; padding-left: 0; }"
        @"body {"
        @"    font-family: -apple-system, BlinkMacSystemFont, 'Segoe UI', Roboto, 'Helvetica Neue', Arial, sans-serif;"
        @"    margin: 0;"
        @"    padding: 16px;"
        @"    line-height: 1.7;"
        @"    color: %@;"
        @"    background-color: %@;"
        @"    font-size: 15px;"
        @"}"
        @"h1 { font-size: 20px; color: %@; border-bottom: 1px solid %@; padding-bottom: 10px; margin: 0 0 14px 0; font-weight: 600; }"
        @"h2 { font-size: 17px; color: %@; margin: 20px 0 10px 0; font-weight: 600; }"
        @"h3 { font-size: 15px; color: %@; margin: 16px 0 8px 0; font-weight: 600; }"
        @"p { margin: 8px 0; color: %@; }"
        @"code { background-color: %@; padding: 2px 6px; border-radius: 4px; font-family: 'SF Mono', Monaco, Menlo, monospace; font-size: 0.9em; }"
        @"pre { background-color: %@; padding: 12px; border-radius: 8px; overflow-x: auto; margin: 12px 0; }"
        @"pre code { background-color: transparent; padding: 0; }"
        @"blockquote { margin: 12px 0; padding: 8px 16px; background-color: %@; border-radius: 8px; }"
        @"ul, ol { padding-left: 20px; margin: 10px 0; }"
        @"li { margin: 4px 0; color: %@; }"
        @"a { color: %@; text-decoration: none; }"
        @"strong { font-weight: 600; }"
        @".content { max-width: 100%%; word-wrap: break-word; }"
        @"</style>"
        @"</head>"
        @"<body>"
        @"<div class=\"content\"></div>"
        @"</body>"
        @"</html>",
        htmlDir,
        textColor, bgColor,
        textColor, borderColor,
        textColor,
        textColor,
        secondaryTextColor,
        codeBackgroundColor,
        codeBackgroundColor,
        codeBackgroundColor,
        textColor,
        blockquoteColor
    ];
    
    [self.webView loadHTMLString:initialHTML baseURL:nil];
}

#pragma mark - WKNavigationDelegate

- (void)webView:(WKWebView *)webView didFinishNavigation:(WKNavigation *)navigation {
    if (self.accumulatedContent.length > 0) {
        [self updateWebViewContent:self.accumulatedContent];
    } else if (self.autoGenSummary && self.taskId.length > 0 && self.callId.length > 0) {
        [self fetchSummarizationContent];
    }
}

#pragma mark - Typing Effect

- (void)startTypingEffect {
    [self stopTypingEffect];
    self.currentIndex = 0;
    self.typingRequestId = self.currentRequestId;
    self.typingTimer = [NSTimer scheduledTimerWithTimeInterval:0.05
                                                        target:self
                                                      selector:@selector(typingStep)
                                                      userInfo:nil
                                                       repeats:YES];
}

- (void)stopTypingEffect {
    if (self.typingTimer) {
        [self.typingTimer invalidate];
        self.typingTimer = nil;
    }
    self.currentIndex = 0;
    self.isUpdatingContent = NO;
}

- (void)typingStep {
    if (self.typingRequestId != self.currentRequestId) {
        [self stopTypingEffect];
        return;
    }
    
    if (self.isUpdatingContent) {
        return;
    }
    
    if (!self.accumulatedContent || self.accumulatedContent.length == 0) {
        return;
    }
    
    NSString *sourceText = [self.accumulatedContent copy];
    NSInteger sourceLength = sourceText.length;
    
    if (self.currentIndex >= sourceLength) {
        return;
    }
    
    NSInteger stepSize = 15;
    NSInteger remainingLength = sourceLength - self.currentIndex;
    
    if (remainingLength < stepSize) {
        return;
    }
    
    NSInteger endIndex = self.currentIndex + stepSize;
    NSString *fullTextToDisplay = [sourceText substringToIndex:endIndex];
    self.currentIndex = endIndex;
    [self updateWebViewContent:fullTextToDisplay];
}

#pragma mark - Content Update

- (void)updateWebViewContent:(NSString *)markdownText {
    if (!markdownText || markdownText.length == 0) {
        self.isUpdatingContent = NO;
        return;
    }
    
    self.isUpdatingContent = YES;
    
    @try {
        NSString *htmlContent = [self htmlFromMarkdown:markdownText];
        
        if (htmlContent && htmlContent.length > 0) {
            // 设置方向 + 更新内容 + 滚动到底部
            NSString *dir = [self isRTLForSelectedLanguage] ? @"rtl" : @"ltr";
            NSString *updateScript = [NSString stringWithFormat:
                @"document.documentElement.setAttribute('dir','%@');"
                @"document.querySelector('.content').innerHTML = %@;"
                @"window.scrollTo(0, document.body.scrollHeight);",
                dir,
                [self escapeJavaScriptString:htmlContent]
            ];
            
            __weak typeof(self) weakSelf = self;
            [self.webView evaluateJavaScript:updateScript completionHandler:^(id result, NSError *error) {
                __strong typeof(weakSelf) strongSelf = weakSelf;
                strongSelf.isUpdatingContent = NO;
            }];
        } else {
            self.isUpdatingContent = NO;
        }
    } @catch (NSException *exception) {
        NSLog(@"更新内容异常: %@", exception.reason);
        self.isUpdatingContent = NO;
    }
}

#pragma mark - Markdown to HTML

- (NSString *)htmlFromMarkdown:(NSString *)markdownText {
    if (!markdownText || markdownText.length == 0) {
        return @"";
    }
    
    const char *cString = [markdownText UTF8String];
    if (!cString) {
        return @"";
    }
    
    size_t length = strlen(cString);
    char *htmlCString = cmark_markdown_to_html(cString, length, CMARK_OPT_DEFAULT);
    
    if (!htmlCString) {
        return @"";
    }
    
    NSString *html = [NSString stringWithUTF8String:htmlCString];
    free(htmlCString);
    
    return html ?: @"";
}

- (NSString *)escapeJavaScriptString:(NSString *)string {
    NSString *escaped = [string stringByReplacingOccurrencesOfString:@"\\" withString:@"\\\\"];
    escaped = [escaped stringByReplacingOccurrencesOfString:@"\"" withString:@"\\\""];
    escaped = [escaped stringByReplacingOccurrencesOfString:@"\n" withString:@"\\n"];
    escaped = [escaped stringByReplacingOccurrencesOfString:@"\r" withString:@"\\r"];
    escaped = [escaped stringByReplacingOccurrencesOfString:@"\t" withString:@"\\t"];
    escaped = [escaped stringByReplacingOccurrencesOfString:@"'" withString:@"\\'"];
    return [NSString stringWithFormat:@"\"%@\"", escaped];
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

- (BOOL)isDarkMode {
    if (@available(iOS 13.0, *)) {
        return self.traitCollection.userInterfaceStyle == UIUserInterfaceStyleDark;
    }
    return NO;
}

- (UIStatusBarStyle)preferredStatusBarStyle {
    if (@available(iOS 13.0, *)) {
        if ([self isDarkMode]) {
            return UIStatusBarStyleDefault;
        }
    }
    return UIStatusBarStyleLightContent;
}

- (void)updateNavigationBarForCurrentTheme {
    if (@available(iOS 13.0, *)) {
        UINavigationBarAppearance *appearance = [UINavigationBarAppearance new];
        [appearance configureWithOpaqueBackground];
        appearance.backgroundColor = [self adaptiveBackgroundColor];
        appearance.titleTextAttributes = @{
            NSFontAttributeName: [UIFont boldSystemFontOfSize:17],
            NSForegroundColorAttributeName: [self adaptiveTextColor]
        };
        self.navigationController.navigationBar.scrollEdgeAppearance = appearance;
        self.navigationController.navigationBar.standardAppearance = appearance;
    } else {
        [self.navigationController.navigationBar setTitleTextAttributes:@{
            NSFontAttributeName: [UIFont boldSystemFontOfSize:17],
            NSForegroundColorAttributeName: [self adaptiveTextColor]
        }];
        self.navigationController.navigationBar.barTintColor = [self adaptiveBackgroundColor];
    }
}

#pragma mark - Theme Change

- (void)traitCollectionDidChange:(UITraitCollection *)previousTraitCollection {
    [super traitCollectionDidChange:previousTraitCollection];
    
    if (@available(iOS 13.0, *)) {
        if ([self.traitCollection hasDifferentColorAppearanceComparedToTraitCollection:previousTraitCollection]) {
            [self updateUIForCurrentTheme];
        }
    }
}

- (void)updateUIForCurrentTheme {
    self.view.backgroundColor = [self adaptiveBackgroundColor];
    
    if (self.contentLabel) {
        self.contentLabel.textColor = [self adaptiveSecondaryTextColor];
    }
    if (self.languageButton) {
        [self.languageButton setTitleColor:[self adaptiveTextColor] forState:UIControlStateNormal];
    }
    if (self.contentContainer) {
        self.contentContainer.backgroundColor = [self adaptiveSecondaryBackgroundColor];
    }
    if (self.actionSheetContainer) {
        self.actionSheetContainer.backgroundColor = [self adaptiveSecondaryBackgroundColor];
    }
    if (self.actionSheetTableView) {
        self.actionSheetTableView.backgroundColor = [self adaptiveSecondaryBackgroundColor];
        [self.actionSheetTableView reloadData];
    }
    if (self.cancelButton) {
        self.cancelButton.backgroundColor = [self adaptiveSecondaryBackgroundColor];
    }
    
    [self updateNavigationBarForCurrentTheme];
    [self loadInitialHTMLStructure];
    [self setNeedsStatusBarAppearanceUpdate];
}

@end
