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

#import "Track Collection/NxAArtist.h"
#import "Track Collection/Tags/Track Properties/NxATrackCredit.h"
#import "Track Collection/Tags/Properties/Internal/NxAStringProperty.h"

#pragma mark Private Interface

@interface NxATrackCredit ()

#pragma mark Properties

/*! Artist behind this credit. */
@property (strong, nonatomic) NxAArtist *p_artist;

@end
