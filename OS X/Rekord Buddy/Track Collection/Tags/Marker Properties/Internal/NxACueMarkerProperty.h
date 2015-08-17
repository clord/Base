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

#import "Track Collection/Tags/Marker Properties/NxACueMarkerProperty.h"
#import "Track Collection/Tags/Marker Properties/Internal/NxAMarkerProperty.h"

#pragma mark Private Interface

@interface NxACueMarkerProperty ()

#pragma mark Properties

/*! Name of this marker. */
@property (strong, nonatomic) NSString *p_name;

/*! Hot cue number. */
@property (strong, nonatomic) NSNumber *p_hotCue;

@end
