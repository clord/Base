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

#include <SeratoDb/TrackFiles/TrackFile.hpp>

#include <Base/Base.hpp>

namespace NxA { namespace Serato {
    NXA_GENERATED_FORWARD_DECLARATIONS_FOR_CLASS(MP4TrackFile);

    class MP4TrackFile : public TrackFile {
        NXA_GENERATED_OPERATOR_EQUAL_DECLARATION_IN_NAMESPACE_FOR_CLASS(NxA::Serato, MP4TrackFile);
        NXA_GENERATED_DECLARATIONS_IN_NAMESPACE_FOR_CLASS(NxA::Serato, MP4TrackFile);

    public:
        #pragma mark Factory Methods
        static MP4TrackFile::Pointer fileWithFileAt(const String& path);

        #pragma mark Instance Methods
        virtual boolean hasKey(void) const;
        virtual String::Pointer key(void) const;
        virtual String::Pointer grouping(void) const;

        virtual boolean hasRecordLabel(void) const;
        virtual String::Pointer recordLabel(void) const;
        virtual boolean hasRemixer(void) const;
        virtual String::Pointer remixer(void) const;
        virtual String::Pointer yearReleased(void) const;

        virtual Blob::Pointer artwork(void) const;

        virtual void setKey(const String& key);
        virtual void setGrouping(const String& grouping);
        virtual void setRecordLabel(const String& recordLabel);
        virtual void setRemixer(const String& emixer);
        virtual void setYearReleased(const String& year);

        virtual void setArtwork(const Blob& artwork);
    };
} }
