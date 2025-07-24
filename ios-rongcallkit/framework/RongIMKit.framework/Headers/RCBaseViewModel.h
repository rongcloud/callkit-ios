//
//  RCBaseViewModel.h
//  Pods-RCUserProfile_Example
//
//  Created by RobinCui on 2024/8/15.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
NS_ASSUME_NONNULL_BEGIN

@interface RCBaseViewModel : NSObject
@property (nonatomic, weak) id delegate;
- (void)loadingWithTip:(NSString *)tip;
- (void)stopLoading;
@end

NS_ASSUME_NONNULL_END
