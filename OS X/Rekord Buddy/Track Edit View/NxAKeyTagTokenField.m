//
//  Copyright (c) 2013-2015 Next Audio Labs, LLC. All rights reserved.
//
//  This file contains confidential and proprietary information of Next
//  Audio Labs, LLC ("Next"). No use is permitted without express written
//  permission of Next. If you are not a party to a Confidentiality/
//  Non-Disclosure Agreement with Next, please immediately delete this
//  file as well as all copies in your possession. For further information,
//  please email info@nextaudiolabs.com.
//

#import "Track Collection/Tags/Track Properties/NxATrackKey.h"
#import "Track Edit View/Internal/NxATagTokenField.h"
#import "NxAKeyTagTokenField.h"

#pragma mark Implementation

@implementation NxAKeyTagTokenField

#pragma mark NSNibAwaking Protocol

- (void)awakeFromNib
{
    [super awakeFromNib];

    self.p_itemsClass = [NxATrackKey class];
}

@end
