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

#import "NxACrateListViewItem.h"

#pragma mark Public Interface

@interface NxACrateListViewTagClassItem :  NxACrateListViewItem

#pragma mark Factory Methods

+ (instancetype)itemWithTagClass:(Class)itemsClass
                     displayedAs:(NSString *)title
                    usingContext:(NSManagedObjectContext *)context;

#pragma mark Properties

@property (strong, nonatomic) NSString *tagNameFilter;

@end
