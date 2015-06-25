//
//  Copyright (c) 2015 Next Audio Labs, LLC. All rights reserved.
//
//  This file contains confidential and proprietary information of Serato
//  Inc. LLP ("Serato"). No use is permitted without express written
//  permission of Serato. If you are not a party to a Confidentiality/
//  Non-Disclosure Agreement with Serato, please immediately delete this
//  file as well as all copies in your possession. For further information,
//  please refer to the modified MIT license provided with this library,
//  or email licensing@serato.com.
//

#pragma once

#include <Base/Base.hpp>

namespace NxA { namespace Serato {
    NXA_GENERATED_FORWARD_DECLARATIONS_FOR(TrackEntry);

    class Tag;

    class TrackEntry : public NxA::Object {
        NXA_GENERATED_DECLARATIONS_FOR(NxA::Serato, TrackEntry);

    public:
        #pragma mark Factory Methods
        static TrackEntry::Pointer entryWithTagOnVolume(NxA::ConstPointer<Tag> const& tag,
                                                        String::ConstPointer const& volumePath);
        static TrackEntry::Pointer entryWithTrackFileAtOnVolume(String::ConstPointer const& path,
                                                                String::ConstPointer const& volumePath);

        #pragma mark Instance Methods
        String::ConstPointer trackFilePath(void) const;

        NxA::ConstPointer<Tag> const& tagForEntry(void) const;

        void destroy(void);
    };
} }
