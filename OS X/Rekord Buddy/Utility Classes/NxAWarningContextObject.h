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

#pragma mark Protocol

/*! A object used as a context for a group of warning messages */
@protocol NxAWarningContextObject <NSObject>

#pragma mark Properties

@required

/*! Name of the object for warning messages. */
@property (readonly, nonatomic) NSString *objectTypeName;

@end
