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

#include <SeratoDb/TrackFiles/ID3TrackFile.hpp>

#include <Base/Base.hpp>

namespace NxA { namespace Serato {
    NXA_GENERATED_FORWARD_DECLARATIONS_FOR_CLASS(AIFFTrackFile);

    class AIFFTrackFile : public ID3TrackFile {
        NXA_GENERATED_OPERATOR_EQUAL_DECLARATION_IN_NAMESPACE_FOR_CLASS(NxA::Serato, AIFFTrackFile);
        NXA_GENERATED_DECLARATIONS_IN_NAMESPACE_FOR_CLASS(NxA::Serato, AIFFTrackFile);

    public:
        #pragma mark Factory Methods
        static AIFFTrackFile::Pointer fileWithFileAt(const String& path);

        #pragma mark Instance Methods
        virtual uinteger32 lengthInMilliseconds(void) const;
        virtual boolean hasBitDepth(void) const;
        virtual uinteger32 bitDepthInBits(void) const;
    };
} }
