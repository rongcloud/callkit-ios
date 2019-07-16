//
//  RCCallSelectMemberViewController.m
//  RongCallKit
//
//  Created by 岑裕 on 16/3/12.
//  Copyright © 2016年 RongCloud. All rights reserved.
//

#import "RCCallSelectMemberViewController.h"
#import "RCCall.h"
#import "RCCallKitUtility.h"
#import "RCCallSelectingMemberCell.h"
#import "RCUserInfoCacheManager.h"
#import "RCCallToolBar.h"
#import "RCCallBaseViewController.h"
#import <RongIMKit/RongIMKit.h>

#define FakeNavigationBarHeight 64

typedef void (^CompleteBlock)(NSArray *addUserIdList);

@interface RCCallSelectMemberViewController () < UISearchBarDelegate, UISearchDisplayDelegate, UITableViewDelegate, UITableViewDataSource>

@property(nonatomic, strong) NSMutableArray *selectUserIds;
@property(nonatomic, strong) CompleteBlock successBlock;
@property(nonatomic, strong) RCCallToolBar *toolBar;
@property(nonatomic, strong) UIBarButtonItem *rightBarButtonItem;
@property(nonatomic, strong) UISearchBar *searchBar;
@property(nonatomic, strong) UISearchDisplayController *searchDisplayController;
@property(nonatomic, strong) NSString *searchText;
@property(nonatomic, strong) NSMutableArray *resultUserIdList;

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
        if (conversationType == ConversationType_DISCUSSION) {
            [[RCIMClient sharedRCIMClient] getDiscussion:targetId
                                                 success:^(RCDiscussion *discussion) {
                                                     weakSelf.listingUserIdList = [discussion.memberIdList copy];
                                                 }
                                                   error:^(RCErrorCode status){

                                                   }];

        } else if (conversationType == ConversationType_GROUP) {
            if ([RCIM sharedRCIM].groupMemberDataSource &&
                [[RCIM sharedRCIM].groupMemberDataSource respondsToSelector:@selector(getAllMembersOfGroup:result:)]) {
                [[RCIM sharedRCIM].groupMemberDataSource getAllMembersOfGroup:self.targetId
                                                                       result:^(NSArray *userIdList) {
                                                                           weakSelf.listingUserIdList = userIdList;
                                                                           NSLog(@"get the members success");
                                                                       }];
            }
        }else{
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

- (void)viewWillDisappear:(BOOL)animated
{
    [super viewWillDisappear:animated];
    UIViewController *rootVC = [self.navigationController presentingViewController];

    if ([rootVC isKindOfClass:[RCCallBaseViewController class]]) {
        [[UIApplication sharedApplication] setStatusBarStyle:UIStatusBarStyleLightContent];
    }else{
        [[UIApplication sharedApplication] setStatusBarStyle:UIStatusBarStyleDefault];
    }
}

- (void)viewWillAppear:(BOOL)animated
{
    [super viewWillAppear:animated];
    UIViewController *rootVC = [self.navigationController presentingViewController];
    [[UIApplication sharedApplication] setStatusBarStyle:UIStatusBarStyleDefault];
}

- (void)viewDidLoad {
    [super viewDidLoad];

    self.view.backgroundColor = [UIColor whiteColor];
    
    self.tableView.backgroundColor = [UIColor whiteColor];
    self.tableView.contentInset = UIEdgeInsetsMake(0, 0, 49.0, 0);
    self.tableView.tintColor = [UIColor colorWithRed:58/255.0 green:145/255.0 blue:243/255.0 alpha:1/1.0];
    
    self.searchBar = [[UISearchBar alloc] init];
    self.searchBar.frame = CGRectMake(0, 0, self.view.frame.size.width, 64);
    self.searchBar.delegate = self;
    self.searchBar.backgroundColor = [UIColor whiteColor];
    self.searchBar.barStyle = UISearchBarStyleMinimal;
    [self.searchBar setSearchFieldBackgroundImage:[self imageFromColor:[UIColor whiteColor] size:CGSizeMake(self.searchBar.frame.size.width,36)] forState:(UIControlStateNormal)];
    
    self.searchBar.barTintColor = [UIColor colorWithRed:242/255.0 green:242/255.0 blue:243/255.0 alpha:1/1.0];
    UIView *searchBarTextField = [[_searchBar.subviews.firstObject subviews] firstObject];
    searchBarTextField.backgroundColor = [UIColor colorWithRed:242/255.0 green:242/255.0 blue:243/255.0 alpha:1/1.0];
    searchBarTextField.layer.borderColor = [UIColor colorWithRed:242/255.0 green:242/255.0 blue:243/255.0 alpha:1/1.0].CGColor;
    searchBarTextField.layer.borderWidth = 0.5;
    
    self.tableView.tableFooterView = [[UIView alloc] init];
    self.tableView.tableHeaderView = self.searchBar;
    
    
    __weak RCCallSelectMemberViewController *weakVC = self;
    _toolBar = [[RCCallToolBar alloc] initWithFrame:CGRectMake(0, UIScreen.mainScreen.bounds.size.height - 49.0 - RCCallExtraSpace, self.view.frame.size.width, 49.0 + RCCallExtraSpace) withBlock:^{
        [weakVC done];
    }];
    
    _toolBar.backgroundColor = [UIColor colorWithRed:250/255.0 green:250/255.0 blue:250/255.0 alpha:1/1.0];
    _toolBar.numberLabel.text = [NSString stringWithFormat:@"%@ %zi %@",NSLocalizedStringFromTable(@"bottom_result_view_choosed_person_prefix", @"RongCloudKit", nil),  self.selectUserIds.count, NSLocalizedStringFromTable(@"bottom_result_view_choosed_person_subfix", @"RongCloudKit", nil)];
    _toolBar.numberLabel.textColor = [UIColor colorWithRed:168/255.0 green:168/255.0 blue:168/255.0 alpha:1/1.0];
 
    [self.navigationController.view addSubview:_toolBar];
    [self.navigationController.view bringSubviewToFront:_toolBar];
    _toolBar.confirmButton.enabled = NO;
 
    self.searchDisplayController = [[UISearchDisplayController alloc] initWithSearchBar:self.searchBar contentsController:self];
    _searchDisplayController.searchResultsDelegate = self;
    _searchDisplayController.searchResultsDataSource = self;
    _searchDisplayController.searchResultsTableView.allowsMultipleSelection = YES;
  
    _searchDisplayController.delegate = self;
    _searchDisplayController.searchResultsTableView.tintColor = [UIColor blueColor];
   
    UINavigationBar *navigationBar =
        [[UINavigationBar alloc] initWithFrame:CGRectMake(0, 0, self.view.frame.size.width, 64)];
    navigationBar.backgroundColor = [UIColor whiteColor];

    [self.navigationItem setTitle:NSLocalizedStringFromTable(@"VoIPCallSelectMember", @"RongCloudKit", nil) ];
    
    UIBarButtonItem *leftBarButtonItem =
        [[UIBarButtonItem alloc] initWithTitle:NSLocalizedStringFromTable(@"Cancel", @"RongCloudKit", nil)
                                         style:UIBarButtonItemStylePlain
                                        target:self
                                        action:@selector(cancel:)];
    self.navigationItem.leftBarButtonItem = leftBarButtonItem;

    self.rightBarButtonItem =
        [[UIBarButtonItem alloc] initWithTitle:NSLocalizedStringFromTable(@"OK", @"RongCloudKit", nil)
                                         style:UIBarButtonItemStylePlain
                                        target:self
                                        action:@selector(done:)];
}

- (void)cancel:(id)sender {
    UIViewController *rootVC = [self.navigationController presentingViewController];

    if ([rootVC isKindOfClass:[RCCallBaseViewController class]]) {
        [self.navigationController dismissViewControllerAnimated:YES completion:nil];
        [[UIApplication sharedApplication] setStatusBarStyle:UIStatusBarStyleLightContent];
    }else{
        [[RCCall sharedRCCall] dismissCallViewController:self.navigationController];
    }
}

- (void)done {
    UIViewController *rootVC = [self.navigationController presentingViewController];
    if ([rootVC isKindOfClass:[RCCallBaseViewController class]]) {
        [self.navigationController dismissViewControllerAnimated:YES completion:nil];
    }else{
        [[RCCall sharedRCCall] dismissCallViewController:self.navigationController];
    }
    
    if (self.successBlock && (self.selectUserIds.count > 0)) {
        self.successBlock(self.selectUserIds);
    }
}

- (UIImage*)imageFromColor:(UIColor*)color size:(CGSize)size
{
    CGRect rect=CGRectMake(0.0f, 0.0f, size.width,size.height);
    UIGraphicsBeginImageContext(size);//创建图片
    CGContextRef context = UIGraphicsGetCurrentContext();//创建图片上下文
    CGContextSetFillColorWithColor(context, [color CGColor]);//设置当前填充颜色的图形上下文
    CGContextFillRect(context, rect);//填充颜色
    
    UIImage *theImage = UIGraphicsGetImageFromCurrentImageContext();
    UIGraphicsEndImageContext();
    return theImage;
}

- (void)loadErrorAlert:(NSString *)title {
    UIAlertView *alert =
        [[UIAlertView alloc] initWithTitle:title message:nil delegate:nil cancelButtonTitle:nil otherButtonTitles:nil];
    [NSTimer scheduledTimerWithTimeInterval:1.0f
                                     target:self
                                   selector:@selector(cancelAlert:)
                                   userInfo:alert
                                    repeats:NO];
    [alert show];
}

- (void)cancelAlert:(NSTimer *)scheduledTimer {
    UIAlertView *alert = (UIAlertView *)(scheduledTimer.userInfo);
    [alert dismissWithClickedButtonIndex:0 animated:NO];
}

#pragma mark - UITableViewDataSource
- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
    return self.resultUserIdList.count;
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    static NSString *reusableID = @"RongVoIPSelectMembersCellId";
    static NSString *reusableSearchID = @"RongVoIPSelectMembersCellsId";
    RCCallSelectingMemberCell *cell = [self.tableView dequeueReusableCellWithIdentifier:reusableID];
    
    if (self.resultUserIdList.count != self.listingUserIdList.count) {
        cell = [self.tableView dequeueReusableCellWithIdentifier:reusableSearchID];
    }
    if (!cell) {
        cell = [[RCCallSelectingMemberCell alloc] initWithStyle:UITableViewCellStyleDefault reuseIdentifier:reusableID];
    }
    cell.tintColor =  [UIColor colorWithRed:58/255.0 green:145/255.0 blue:243/255.0 alpha:1/1.0];

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
    }else{
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

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath
{
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
        [self loadErrorAlert:[NSString stringWithFormat:NSLocalizedStringFromTable(@"VoIPAudioCallMaxNumSelectMember",
                                                                                   @"RongCloudKit", nil),
                              [RCCall sharedRCCall].maxMultiAudioCallUserNumber]];
        [self.selectUserIds removeObject:userId];
    } else if ((self.selectUserIds.count + self.existUserIdList.count >
                [RCCall sharedRCCall].maxMultiVideoCallUserNumber) &&
               self.mediaType == RCCallMediaVideo) {
        [self loadErrorAlert:[NSString stringWithFormat:NSLocalizedStringFromTable(@"VoIPVideoCallMaxNumSelectMember",
                                                                                   @"RongCloudKit", nil),
                              [RCCall sharedRCCall].maxMultiVideoCallUserNumber]];
        [self.selectUserIds removeObject:userId];
    }
    
    if (!_searchDisplayController.isActive) {
        [UIView performWithoutAnimation:^{
            [self.tableView reloadRowsAtIndexPaths:@[indexPath] withRowAnimation:UITableViewRowAnimationNone];
            
        }];
    }else
    {
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

    _toolBar.numberLabel.text = [NSString stringWithFormat:@"%@ %zi %@",NSLocalizedStringFromTable(@"bottom_result_view_choosed_person_prefix", @"RongCloudKit", nil),  self.selectUserIds.count, NSLocalizedStringFromTable(@"bottom_result_view_choosed_person_subfix", @"RongCloudKit", nil)];
    
    if (self.selectUserIds.count) {
        _toolBar.numberLabel.textColor = [UIColor colorWithRed:58/255.0 green:145/255.0 blue:243/255.0 alpha:1.0];
        _toolBar.confirmButton.enabled = YES;
    }
    else {
        _toolBar.numberLabel.textColor = [UIColor colorWithRed:168/255.0 green:168/255.0 blue:168/255.0 alpha:1/1.0];
        _toolBar.confirmButton.enabled = NO;
    }
}

#pragma mark - UserInfo Update
- (void)onUserInfoUpdate:(NSNotification *)notification {
    NSDictionary *userInfoDic = notification.object;
    NSString *updateUserId = userInfoDic[@"userId"];

    for (NSString *userId in self.resultUserIdList) {
        if ([updateUserId isEqualToString:userId]) {
            __weak typeof(self) weakSelf = self;
            dispatch_async(dispatch_get_main_queue(), ^{
                NSIndexPath *index =
                    [NSIndexPath indexPathForRow:[weakSelf.resultUserIdList indexOfObject:userId] inSection:0];

                [weakSelf.tableView reloadRowsAtIndexPaths:@[ index ]
                                          withRowAnimation:UITableViewRowAnimationAutomatic];
            });
            return;
        }
    }
}

#pragma mark - UISearchBarDelegate
- (void)searchBar:(UISearchBar *)searchBar textDidChange:(NSString *)searchText
{
    self.searchText = searchText;
    [self searchTexts];
}

- (void)searchBarCancelButtonClicked:(UISearchBar *)searchBar
{
    self.searchText = @"";
    [self searchTexts];
}

- (void)searchTexts
{
    if ([self.searchText isEqualToString:@""]) {
        self.resultUserIdList = [NSMutableArray arrayWithArray:self.listingUserIdList];
    }else
    {
        self.resultUserIdList = [NSMutableArray array];
        for (NSString *userId in self.listingUserIdList) {
            RCUserInfo *userInfo;
            if (self.conversationType == ConversationType_GROUP) {
                userInfo = [[RCUserInfoCacheManager sharedManager] getUserInfo:userId inGroupId:self.targetId];
            }else{
                userInfo = [[RCUserInfoCacheManager sharedManager] getUserInfo:userId];
            }
            if ([userInfo.name containsString:_searchText]) {
                [self.resultUserIdList addObject:userId];
            }
        }
    }
 
    [self.tableView reloadData];
}

#pragma mark - UISearchDisplayDelegate
- (void)searchDisplayController:(UISearchDisplayController *)controller willShowSearchResultsTableView:(UITableView *)tableView
{
    [tableView setContentInset:UIEdgeInsetsMake(self.searchBar.frame.size.height, 0, 0, 0)];
}

- (void)dealloc {
    [[NSNotificationCenter defaultCenter] removeObserver:self];
}

@end
