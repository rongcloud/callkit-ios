//
//  RCActionSheetView.h
//  RongIMKit
//
//  Created by liyan on 2019/8/22.
//  Copyright © 2019 RongCloud. All rights reserved.
//

#import <UIKit/UIKit.h>


@interface RCActionSheetView : UIView <UITableViewDelegate, UITableViewDataSource>

+ (void)showActionSheetView:(NSString *)title
                  cellArray:(NSArray *)cellArray
                cancelTitle:(NSString *)cancelTitle
              selectedBlock:(void (^)(NSInteger index))selectedBlock
                cancelBlock:(void (^)(void))cancelBlock;
@end

