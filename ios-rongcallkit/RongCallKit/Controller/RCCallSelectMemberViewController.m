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
#import <RongIMKit/RongIMKit.h>

#define FakeNavigationBarHeight 64

typedef void (^CompleteBlock)(NSArray *addUserIdList);

@interface RCCallSelectMemberViewController () <UITableViewDataSource, UITableViewDelegate>

@property(nonatomic, strong) NSMutableArray *selectUserIds;
@property(nonatomic, strong) CompleteBlock successBlock;
@property(nonatomic, strong) UITableView *tableView;
@property(nonatomic, strong) UIBarButtonItem *rightBarButtonItem;
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

    __weak typeof(self) weakSelf = self;
    dispatch_async(dispatch_get_main_queue(), ^{
        [weakSelf.tableView reloadData];
    });
}

- (void)viewDidLoad {
    [super viewDidLoad];

    self.view.backgroundColor = RongVoIPUIColorFromRGB(0x262e42);

    self.tableView = [[UITableView alloc] init];
    self.tableView.frame = CGRectMake(0, 64, self.view.frame.size.width, self.view.frame.size.height - 64);
    self.tableView.dataSource = self;
    self.tableView.delegate = self;
    self.tableView.backgroundColor = [UIColor clearColor];
    [self.view addSubview:self.tableView];
    self.tableView.tableFooterView = [[UIView alloc] init];

    UINavigationBar *navigationBar =
        [[UINavigationBar alloc] initWithFrame:CGRectMake(0, 0, self.view.frame.size.width, 64)];
    navigationBar.backgroundColor = [UIColor clearColor];
    [navigationBar setTintColor:[UIColor whiteColor]];
    [navigationBar setBarTintColor:RongVoIPUIColorFromRGB(0x262e42)];

    [self.view addSubview:navigationBar];

    UINavigationItem *navigationBarTitle = [[UINavigationItem alloc]
        initWithTitle:NSLocalizedStringFromTable(@"VoIPCallSelectMember", @"RongCloudKit", nil)];
    [navigationBar pushNavigationItem:navigationBarTitle animated:YES];

    UIBarButtonItem *leftBarButtonItem =
        [[UIBarButtonItem alloc] initWithTitle:NSLocalizedStringFromTable(@"Cancel", @"RongCloudKit", nil)
                                         style:UIBarButtonItemStylePlain
                                        target:self
                                        action:@selector(cancel:)];
    navigationBarTitle.leftBarButtonItem = leftBarButtonItem;

    self.rightBarButtonItem =
        [[UIBarButtonItem alloc] initWithTitle:NSLocalizedStringFromTable(@"OK", @"RongCloudKit", nil)
                                         style:UIBarButtonItemStylePlain
                                        target:self
                                        action:@selector(done:)];
    navigationBarTitle.rightBarButtonItem = self.rightBarButtonItem;
    [navigationBar setItems:[NSArray arrayWithObject:navigationBarTitle]];

    [self updateRightButton];
}

- (void)cancel:(id)sender {
    [[RCCall sharedRCCall] dismissCallViewController:self];
}

- (void)done:(id)sender {
    if ((self.selectUserIds.count + self.existUserIdList.count > [RCCall sharedRCCall].maxMultiAudioCallUserNumber) &&
        self.mediaType == RCCallMediaAudio) {
        [self loadErrorAlert:[NSString stringWithFormat:NSLocalizedStringFromTable(@"VoIPAudioCallMaxNumSelectMember",
                                                                                   @"RongCloudKit", nil),
                                                        [RCCall sharedRCCall].maxMultiAudioCallUserNumber]];
    } else if ((self.selectUserIds.count + self.existUserIdList.count >
                [RCCall sharedRCCall].maxMultiVideoCallUserNumber) &&
               self.mediaType == RCCallMediaVideo) {
        [self loadErrorAlert:[NSString stringWithFormat:NSLocalizedStringFromTable(@"VoIPVideoCallMaxNumSelectMember",
                                                                                   @"RongCloudKit", nil),
                                                        [RCCall sharedRCCall].maxMultiVideoCallUserNumber]];
    } else {
        [[RCCall sharedRCCall] dismissCallViewController:self];
        if (self.successBlock) {
            self.successBlock(self.selectUserIds);
        }
    }
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

// UITableViewDataSource
- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
    return self.listingUserIdList.count;
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    static NSString *reusableID = @"RongVoIPSelectMembersCellId";
    RCCallSelectingMemberCell *cell = [tableView dequeueReusableCellWithIdentifier:reusableID];
    if (!cell) {
        cell = [[RCCallSelectingMemberCell alloc] initWithStyle:UITableViewCellStyleDefault reuseIdentifier:reusableID];
    }

    NSString *userId = self.listingUserIdList[indexPath.row];
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
    return 70;
}

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath {
    NSString *userId = self.listingUserIdList[indexPath.row];
    if (![self.existUserIdList containsObject:userId]) {
        if ([self.selectUserIds containsObject:userId]) {
            [self.selectUserIds removeObject:userId];
        } else if (userId) {
            [self.selectUserIds addObject:userId];
        }
        [self updateRightButton];
    }

    [UIView performWithoutAnimation:^{
        [self.tableView reloadRowsAtIndexPaths:@[indexPath] withRowAnimation:UITableViewRowAnimationNone];
        
    }];
    
    /*
    NSInteger selectedBlinkNormalUserCount = 0;
    for (RCCallUserProfile *userProfile in self.callSession.userProfileList) {
        if (userProfile.blinkUserType == 1)
            selectedBlinkNormalUserCount++;
    }
    
    if (self.mediaType == RCCallMediaVideo && [self.selectUserIds count] + selectedBlinkNormalUserCount == 6)
    {
        UIAlertAction *okAlert = [UIAlertAction actionWithTitle:@"确定" style:(UIAlertActionStyleDefault) handler:^(UIAlertAction * _Nonnull action) {}];
        UIAlertController *memberAlertController = [UIAlertController alertControllerWithTitle:@"" message:@"为了保证会议流畅, 后续用户只能以观众模式加入, 是否继续?" preferredStyle:UIAlertControllerStyleAlert];
        [memberAlertController addAction:okAlert];
        [self presentViewController:memberAlertController animated:YES completion:^{}];
    }
    */
}

- (void)updateRightButton {
    [self.rightBarButtonItem setEnabled:self.selectUserIds.count > 0];
}

#pragma mark - UserInfo Update
- (void)onUserInfoUpdate:(NSNotification *)notification {
    NSDictionary *userInfoDic = notification.object;
    NSString *updateUserId = userInfoDic[@"userId"];

    for (NSString *userId in self.listingUserIdList) {
        if ([updateUserId isEqualToString:userId]) {
            __weak typeof(self) weakSelf = self;
            dispatch_async(dispatch_get_main_queue(), ^{
                NSIndexPath *index =
                    [NSIndexPath indexPathForRow:[weakSelf.listingUserIdList indexOfObject:userId] inSection:0];

                [weakSelf.tableView reloadRowsAtIndexPaths:@[ index ]
                                          withRowAnimation:UITableViewRowAnimationAutomatic];
            });
            return;
        }
    }
}

- (void)dealloc {
    [[NSNotificationCenter defaultCenter] removeObserver:self];
}

@end
