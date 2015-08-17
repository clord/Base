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

#import "NxACueMarkerProperty+NxAWaveformViewController.h"
#import "NxAWaveformViewController.h"
#import "Track Collection/Tags/Marker Properties/Internal/NxALoopMarkerProperty.h"

#pragma mark Implementation

@implementation NxALoopMarkerProperty (NxAWaveformViewController)

- (void)addToWaveformViewController:(NxAWaveformViewController *)controller
{
    [controller addLoopMarkerAt:self.p_pos.doubleValue
                lengthInSeconds:self.p_length.doubleValue
                   hotCueNumber:self.p_hotCue.integerValue];
}

@end
