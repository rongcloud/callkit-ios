//
//  RCBaseCellViewModel.h
//  Pods-RCUserProfile_Example
//
//  Created by RobinCui on 2024/8/15.
//

#import <Foundation/Foundation.h>
#import "RCCellViewModelProtocol.h"

extern NSInteger const RCUserManagementCellHeight;

NS_ASSUME_NONNULL_BEGIN

@interface RCBaseCellViewModel : NSObject<RCCellViewModelProtocol>
@property (nonatomic, assign) BOOL hideSeparatorLine;
@end

NS_ASSUME_NONNULL_END
