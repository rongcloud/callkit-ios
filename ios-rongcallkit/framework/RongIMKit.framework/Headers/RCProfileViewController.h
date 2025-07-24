//
//  RCUUserProfileViewController.h
//  RongUserProfile
//
//  Created by zgh on 2024/8/19.
//

#import "RCBaseViewController.h"
#import "RCProfileViewModel.h"
NS_ASSUME_NONNULL_BEGIN

/// 资料页 VC
/// - Since: 5.12.0
@interface RCProfileViewController : RCBaseViewController

/// 实例化 RCProfileViewController
///
/// - Parameters viewModel: viewModel
- (instancetype)initWithViewModel:(RCProfileViewModel *)viewModel;

@end

NS_ASSUME_NONNULL_END
