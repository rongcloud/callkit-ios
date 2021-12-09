//
//  RCCallSelectMemberViewController.m
//  RongCallKit
//
//  Created by RongCloud on 16/3/12.
//  Copyright © 2016年 RongCloud. All rights reserved.
//

#import "RCCallSelectMemberViewController.h"
#import "RCCall.h"
#import "RCCallBaseViewController.h"
#import "RCCallKitUtility.h"
#import "RCCallSelectingMemberCell.h"
#import "RCCallToolBar.h"
#import "RCUserInfoCacheManager.h"
#import "RongCallKitAdaptiveHeader.h"

#define FakeNavigationBarHeight 64

typedef void (^CompleteBlock)(NSArray *addUserIdList);

@interface RCCallSelectMemberViewController () <UISearchBarDelegate,
                                                UISearchControllerDelegate,
                                                UISearchResultsUpdating>

@property (nonatomic, strong) NSMutableArray *selectUserIds;
@property (nonatomic, strong) CompleteBlock successBlock;
@property (nonatomic, strong) RCCallToolBar *toolBar;
@property (nonatomic, strong) UISearchBar *searchBar;
@property (nonatomic, strong) UISearchController *searchController;
@property (nonatomic, strong) UITableViewController *resultController;
@property (nonatomic, strong) NSString *searchText;
@property (nonatomic, strong) NSMutableArray *resultUserIdList;

@end

@implementation RCCallSelectMemberViewController
- (instancetype)initWithConversationType:(RCConversationType)conversationType
                                targetId:(NSString *)targetId
                               mediaType:(RCCallMediaType)mediaType
                                   exist:(NSArray *)existUserIdList
                                 success:(void (^)(NSArray *addUserIdList))successBlock {
    self = [super init];
    if (self) {
        self.conversationType = conversationType;
        self.targetId = targetId;
        self.mediaType = mediaType;
        __weak typeof(self) weakSelf = self;
        if (conversationType == ConversationType_GROUP) {
            if ([RCIM sharedRCIM].groupMemberDataSource &&
                [[RCIM sharedRCIM].groupMemberDataSource respondsToSelector:@selector(getAllMembersOfGroup:result:)]) {
                [[RCIM sharedRCIM].groupMemberDataSource getAllMembersOfGroup:self.targetId
                                                                       result:^(NSArray *userIdList) {
                                                                           weakSelf.listingUserIdList = userIdList;
                                                                           RCLogI(@"get the members success");
                                                                       }];
            }
        } else {
            self.listingUserIdList = [NSMutableArray arrayWithArray:existUserIdList];
        }
        self.existUserIdList = existUserIdList;
        self.selectUserIds = [[NSMutableArray alloc] init];
        self.successBlock = successBlock;

        [[NSNotificationCenter defaultCenter] addObserver:self
                                                 selector:@selector(onUserInfoUpdate:)
                                                     name:RCKitDispatchUserInfoUpdateNotification
                                                   object:nil];
    }
    return self;
}

- (void)setListingUserIdList:(NSArray *)listingUserIdList {
    _listingUserIdList = listingUserIdList;

    _resultUserIdList = [NSMutableArray arrayWithArray:listingUserIdList];
    __weak typeof(self) weakSelf = self;
    dispatch_async(dispatch_get_main_queue(), ^{
        [weakSelf.tableView reloadData];
    });
}

- (void)viewDidLoad {
    [super viewDidLoad];

    self.definesPresentationContext = YES;
    self.tableView.backgroundColor = [UIColor whiteColor];
    self.tableView.contentInset = UIEdgeInsetsMake(0, 0, 49.0, 0);
    self.tableView.tintColor = [UIColor colorWithRed:58 / 255.0 green:145 / 255.0 blue:243 / 255.0 alpha:1 / 1.0];
    self.tableView.tableFooterView = [[UIView alloc] init];
    self.tableView.backgroundColor = dynamic_color(0xf0f0f6, 0x000000);
    self.tableView.separatorColor = dynamic_color(0xE3E5E6, 0x272727);
    NSInteger versionChecker = [RCCallKitUtility compareVersion:[UIDevice currentDevice].systemVersion toVersion:@"15.0"];
    if (versionChecker >= 0) {
#ifdef __IPHONE_15_0
        self.tableView.sectionHeaderTopPadding = 0;
#endif
    }

    
    __weak RCCallSelectMemberViewController *weakVC = self;
    _toolBar = [[RCCallToolBar alloc]
        initWithFrame:CGRectMake(0, UIScreen.mainScreen.bounds.size.height - 49.0 - RCCallExtraSpace,
                                 self.view.frame.size.width, 49.0 + RCCallExtraSpace)
            withBlock:^{
                [weakVC done];
            }];

    _toolBar.numberLabel.text =
        [NSString stringWithFormat:@"%@ %zi %@", RCCallKitLocalizedString(@"bottom_result_view_choosed_person_prefix"),
                                   self.selectUserIds.count + 1,
                                   RCCallKitLocalizedString(@"bottom_result_view_choosed_person_subfix")];
    _toolBar.numberLabel.textColor = [UIColor colorWithRed:168 / 255.0
                                                     green:168 / 255.0
                                                      blue:168 / 255.0
                                                     alpha:1 / 1.0];

    [self.navigationController.view addSubview:_toolBar];
    [self.navigationController.view bringSubviewToFront:_toolBar];
    _toolBar.confirmButton.enabled = NO;

    UIView *backgroundView = [[UIView alloc] init];
    self.tableView.backgroundView = backgroundView;
    self.searchController = [[UISearchController alloc] initWithSearchResultsController:self.resultController];
    self.searchController.searchResultsUpdater = self;
    self.searchController.delegate = self;
    self.searchController.dimsBackgroundDuringPresentation = YES;

    NSInteger checker = [RCCallKitUtility compareVersion:[UIDevice currentDevice].systemVersion toVersion:@"9.1"];
    if (checker >= 0) {
        self.searchController.obscuresBackgroundDuringPresentation = YES;
    }
    self.searchController.hidesNavigationBarDuringPresentation = NO;

    self.searchController.searchBar.tintColor = [UIColor colorWithRed:22.0 / 255
                                                                green:161.0 / 255
                                                                 blue:1.0 / 255
                                                                alpha:1];
    self.searchController.searchBar.frame = CGRectMake(0, 0, self.searchController.searchBar.frame.size.width, 44);
    self.searchController.searchBar.delegate = self;
    [self.searchController.searchBar sizeToFit];
    self.searchController.searchBar.placeholder = RCCallKitLocalizedString(@"VoIPCall_search_placeholder");

    NSInteger checker_iOS13 = [RCCallKitUtility compareVersion:[UIDevice currentDevice].systemVersion
                                                     toVersion:@"13.0"];
    if (checker_iOS13 >= 0) {
#ifdef __IPHONE_13_0
        self.searchController.searchBar.searchTextField.backgroundColor =
            [RCKitUtility generateDynamicColor:hex_rgb(0xffffff)
                                     darkColor:[hex_rgb(0x1c1c1e) colorWithAlphaComponent:0.6]];
#endif
    }

    //设置顶部搜索栏的背景色
    self.searchController.searchBar.barTintColor = dynamic_color(0xf0f0f6, 0x000000);

    self.tableView.tableHeaderView = self.searchController.searchBar;
    self.tableView.tableFooterView = [[UIView alloc] initWithFrame:CGRectZero];

    [self.navigationItem setTitle:RCCallKitLocalizedString(@"VoIPCallSelectMember")];

    UIBarButtonItem *leftBarButtonItem = [[UIBarButtonItem alloc] initWithTitle:RCCallKitLocalizedString(@"Cancel")
                                                                          style:UIBarButtonItemStylePlain
                                                                         target:self
                                                                         action:@selector(cancel:)];
    self.navigationItem.leftBarButtonItem = leftBarButtonItem;
}

- (void)viewWillAppear:(BOOL)animated {
    [super viewWillAppear:animated];
    self.toolBar.frame = CGRectMake(0, UIScreen.mainScreen.bounds.size.height - 49.0 - RCCallExtraSpace,
                                    self.view.frame.size.width, 49.0 + RCCallExtraSpace);
    NSInteger versionChecker = [RCCallKitUtility compareVersion:[UIDevice currentDevice].systemVersion toVersion:@"15.0"];
    if (versionChecker >= 0) {
#ifdef __IPHONE_15_0
        UINavigationBarAppearance *appearance = [UINavigationBarAppearance new];
        [appearance configureWithOpaqueBackground];
        self.navigationController.navigationBar.scrollEdgeAppearance = appearance;
        self.navigationController.navigationBar.standardAppearance = appearance;
#endif
    }
}

- (UIStatusBarStyle)preferredStatusBarStyle {
    UIViewController *rootVC = [self.navigationController presentingViewController];
    if ([rootVC isKindOfClass:[RCCallBaseViewController class]]) {
        return UIStatusBarStyleLightContent;
    } else {
        return UIStatusBarStyleDefault;
    }
}

- (void)cancel:(id)sender {
    UIViewController *rootVC = [self.navigationController presentingViewController];
    if ([rootVC isKindOfClass:[RCCallBaseViewController class]]) {
        [self.navigationController dismissViewControllerAnimated:YES completion:nil];
    } else {
        [[RCCall sharedRCCall] dismissCallViewController:self.navigationController];
    }
}

- (void)done {
    UIViewController *rootVC = [self.navigationController presentingViewController];
    if ([rootVC isKindOfClass:[RCCallBaseViewController class]]) {
        [self.navigationController dismissViewControllerAnimated:YES completion:nil];
    } else {
        [[RCCall sharedRCCall] dismissCallViewController:self.navigationController];
    }

    if (self.successBlock && (self.selectUserIds.count > 0)) {
        self.successBlock(self.selectUserIds);
    }
}

- (UIImage *)imageFromColor:(UIColor *)color size:(CGSize)size {
    CGRect rect = CGRectMake(0.0f, 0.0f, size.width, size.height);
    UIGraphicsBeginImageContext(size);                         //创建图片
    CGContextRef context = UIGraphicsGetCurrentContext();      //创建图片上下文
    CGContextSetFillColorWithColor(context, [color CGColor]);  //设置当前填充颜色的图形上下文
    CGContextFillRect(context, rect);                          //填充颜色

    UIImage *theImage = UIGraphicsGetImageFromCurrentImageContext();
    UIGraphicsEndImageContext();
    return theImage;
}

- (void)loadErrorAlert:(NSString *)title {
    [RCAlertView showAlertController:title message:nil cancelTitle:RCCallKitLocalizedString(@"OK")  inViewController:self];
}

#pragma mark - UITableViewDataSource
- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
    return self.resultUserIdList.count;
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    static NSString *reusableID = @"RongVoIPSelectMembersCellId";
    static NSString *reusableSearchID = @"RongVoIPSelectMembersCellsId";
    NSString *resuseID = tableView == self.tableView ? reusableID : reusableSearchID;
    RCCallSelectingMemberCell *cell = [self.tableView dequeueReusableCellWithIdentifier:resuseID];

    if (self.resultUserIdList.count != self.listingUserIdList.count) {
        cell = [self.tableView dequeueReusableCellWithIdentifier:reusableSearchID];
    }
    if (!cell) {
        cell = [[RCCallSelectingMemberCell alloc] initWithStyle:UITableViewCellStyleDefault reuseIdentifier:reusableID];
    }
    cell.tintColor = [UIColor colorWithRed:58 / 255.0 green:145 / 255.0 blue:243 / 255.0 alpha:1 / 1.0];

    NSString *userId = self.resultUserIdList[indexPath.row];
    if ([self.existUserIdList containsObject:userId]) {
        [cell.selectedImageView setImage:[RCCallKitUtility imageFromVoIPBundle:@"voip/deselect.png"]];
    } else if ([self.selectUserIds containsObject:userId]) {
        [cell.selectedImageView setImage:[RCCallKitUtility imageFromVoIPBundle:@"voip/selected.png"]];
    } else {
        [cell.selectedImageView setImage:[RCCallKitUtility imageFromVoIPBundle:@"voip/unselected.png"]];
    }
    RCUserInfo *userInfo;
    if (self.conversationType == ConversationType_GROUP) {
        userInfo = [[RCUserInfoCacheManager sharedManager] getUserInfo:userId inGroupId:self.targetId];
    } else {
        userInfo = [[RCUserInfoCacheManager sharedManager] getUserInfo:userId];
    }
    if (userInfo) {
        [cell.headerImageView setImageURL:[NSURL URLWithString:userInfo.portraitUri]];
        [cell.nameLabel setText:userInfo.name];
    } else {
        [cell.headerImageView setPlaceholderImage:[RCCallKitUtility getDefaultPortraitImage]];
        [cell.nameLabel setText:userId];
    }

    return cell;
}

- (CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath {
    return 55.0;
}

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath {
    NSString *userId = self.resultUserIdList[indexPath.row];
    if (![self.existUserIdList containsObject:userId]) {
        if ([self.selectUserIds containsObject:userId]) {
            [self.selectUserIds removeObject:userId];
        } else if (userId) {
            [self.selectUserIds addObject:userId];
        }
    }

    if ((self.selectUserIds.count + self.existUserIdList.count > [RCCall sharedRCCall].maxMultiAudioCallUserNumber) &&
        self.mediaType == RCCallMediaAudio) {
        [self loadErrorAlert:[NSString stringWithFormat:RCCallKitLocalizedString(@"VoIPAudioCallMaxNumSelectMember"),
                                                        [RCCall sharedRCCall].maxMultiAudioCallUserNumber]];
        [self.selectUserIds removeObject:userId];
    } else if ((self.selectUserIds.count + self.existUserIdList.count >
                [RCCall sharedRCCall].maxMultiVideoCallUserNumber) &&
               self.mediaType == RCCallMediaVideo) {
        [self loadErrorAlert:[NSString stringWithFormat:RCCallKitLocalizedString(@"VoIPVideoCallMaxNumSelectMember"),
                                                        [RCCall sharedRCCall].maxMultiVideoCallUserNumber]];
        [self.selectUserIds removeObject:userId];
    }

    if (!_searchController.isActive) {
        [UIView performWithoutAnimation:^{
            [self.tableView reloadRowsAtIndexPaths:@[ indexPath ] withRowAnimation:UITableViewRowAnimationNone];
        }];
    } else {
        RCCallSelectingMemberCell *cell = (RCCallSelectingMemberCell *)[tableView cellForRowAtIndexPath:indexPath];
        NSString *userId = self.resultUserIdList[indexPath.row];
        if ([self.existUserIdList containsObject:userId]) {
            [cell.selectedImageView setImage:[RCCallKitUtility imageFromVoIPBundle:@"voip/deselect.png"]];
        } else if ([self.selectUserIds containsObject:userId]) {
            [cell.selectedImageView setImage:[RCCallKitUtility imageFromVoIPBundle:@"voip/selected.png"]];
        } else {
            [cell.selectedImageView setImage:[RCCallKitUtility imageFromVoIPBundle:@"voip/unselected.png"]];
        }

        [tableView deselectRowAtIndexPath:indexPath animated:NO];
    }

    _toolBar.numberLabel.text =
        [NSString stringWithFormat:@"%@ %zi %@", RCCallKitLocalizedString(@"bottom_result_view_choosed_person_prefix"),
                                   self.selectUserIds.count + 1,
                                   RCCallKitLocalizedString(@"bottom_result_view_choosed_person_subfix")];

    if (self.selectUserIds.count > 0) {
        _toolBar.numberLabel.textColor = dynamic_color(0x3A91F3, 0x007acc);
        _toolBar.confirmButton.enabled = YES;
    } else {
        _toolBar.numberLabel.textColor = dynamic_color(0xA8A8A8, 0x666666);
        _toolBar.confirmButton.enabled = NO;
    }
}

#pragma mark - UISearchControllerDelegate
- (void)willPresentSearchController:(UISearchController *)searchController {
    self.tabBarController.tabBar.hidden = YES;
    self.edgesForExtendedLayout = UIRectEdgeBottom;
}

- (void)didPresentSearchController:(UISearchController *)searchController {
}

- (void)willDismissSearchController:(UISearchController *)searchController {
    self.tabBarController.tabBar.hidden = NO;
    self.edgesForExtendedLayout = UIRectEdgeBottom;
    __weak typeof(self) weakSelf = self;
    dispatch_async(dispatch_get_main_queue(), ^{
        [weakSelf.tableView reloadData];
    });
}

- (void)didDismissSearchController:(UISearchController *)searchController {
}

- (void)presentSearchController:(UISearchController *)searchController {
}

#pragma mark - UISearchResultsUpdating
- (void)updateSearchResultsForSearchController:(UISearchController *)searchController {
    self.searchText = searchController.searchBar.text;
    [self searchTexts];
}

#pragma mark - UserInfo Update
- (void)onUserInfoUpdate:(NSNotification *)notification {
    NSDictionary *userInfoDic = notification.object;
    NSString *updateUserId = userInfoDic[@"userId"];

    for (NSString *userId in self.resultUserIdList) {
        if ([updateUserId isEqualToString:userId]) {
            __weak typeof(self) weakSelf = self;
            dispatch_async(dispatch_get_main_queue(), ^{
                NSIndexPath *index = [NSIndexPath indexPathForRow:[weakSelf.resultUserIdList indexOfObject:userId]
                                                        inSection:0];
                UITableViewCell *cell = [weakSelf.tableView cellForRowAtIndexPath:index];
                if (cell) {
                    [weakSelf.tableView reloadRowsAtIndexPaths:@[ index ]
                                              withRowAnimation:UITableViewRowAnimationAutomatic];
                }
            });
            return;
        }
    }
}

#pragma mark - UISearchBarDelegate
- (void)searchBar:(UISearchBar *)searchBar textDidChange:(NSString *)searchText {
    self.searchText = searchText;
    [self searchTexts];
}

- (void)searchBarCancelButtonClicked:(UISearchBar *)searchBar {
    self.searchText = @"";
    [self searchTexts];
}

#pragma mark - Getter
- (UITableViewController *)resultController {
    if (!_resultController) {
        _resultController = [[UITableViewController alloc] initWithStyle:UITableViewStyleGrouped];
        _resultController.tableView.dataSource = self;
        _resultController.tableView.delegate = self;
        _resultController.editing = NO;
        _resultController.automaticallyAdjustsScrollViewInsets = NO;
        _resultController.tableView.separatorInset = UIEdgeInsetsMake(0, 12, 0, 0);
        _resultController.tableView.contentInset = UIEdgeInsetsMake(20, 0, 49, 0);
        _resultController.tableView.allowsSelection = YES;
#if __IPHONE_OS_VERSION_MAX_ALLOWED > __IPHONE_10_3
        NSInteger checker = [RCCallKitUtility compareVersion:[UIDevice currentDevice].systemVersion toVersion:@"11.0"];
        if (checker >= 0) {
            _resultController.tableView.contentInsetAdjustmentBehavior = UIScrollViewContentInsetAdjustmentNever;
        }
#endif
    }
    return _resultController;
}

#pragma mark - Private
- (void)searchTexts {
    if ([self.searchText isEqualToString:@""]) {
        self.resultUserIdList = [NSMutableArray arrayWithArray:self.listingUserIdList];
    } else {
        self.resultUserIdList = [NSMutableArray array];
        for (NSString *userId in self.listingUserIdList) {
            RCUserInfo *userInfo;
            if (self.conversationType == ConversationType_GROUP) {
                userInfo = [[RCUserInfoCacheManager sharedManager] getUserInfo:userId inGroupId:self.targetId];
            } else {
                userInfo = [[RCUserInfoCacheManager sharedManager] getUserInfo:userId];
            }
            if ([userInfo.name containsString:_searchText]) {
                [self.resultUserIdList addObject:userId];
            }
        }
    }
    [self.resultController.tableView reloadData];
}

- (void)dealloc {
    [[NSNotificationCenter defaultCenter] removeObserver:self];
}

@end
