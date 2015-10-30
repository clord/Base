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

#include "TrackFiles/AIFFTrackFile.hpp"
#include "TrackFiles/Internal/AIFFTrackFile.hpp"

#include <aifffile.h>

NXA_GENERATED_IMPLEMENTATION_IN_NAMESPACE_FOR_CLASS_WITH_PARENT(NxA::Serato, AIFFTrackFile, ID3TrackFile);

using namespace NxA;
using namespace NxA::Serato;

#pragma mark Factory Methods

AIFFTrackFile::Pointer AIFFTrackFile::fileWithFileAt(const String& path, TrackFile::Flags flags)
{
    auto file = Internal::TagLibFilePointer(std::make_shared<TagLib::RIFF::AIFF::File>(path.toUTF8()));
    if (!file->isValid()) {
        throw TrackFileError::exceptionWith("Error loading track file '%s'.", path.toUTF8());
    }

    auto aiffFile = dynamic_cast<TagLib::RIFF::AIFF::File*>(&(*file));

    auto internalObject = Internal::AIFFTrackFile::Pointer(std::make_shared<Internal::AIFFTrackFile>(path, file));
    auto newFile = AIFFTrackFile::makeSharedWithInternal(NxA::Internal::Object::Pointer::dynamicCastFrom(internalObject));
    newFile->internal->tag = newFile->internal->id3v2Tag = aiffFile->tag();
    if (!newFile->internal->tag) {
        throw TrackFileError::exceptionWith("Error reading tags from track file '%s'.", path.toUTF8());
    }

    if (flags & TrackFile::Flags::IgnoreMarkers) {
        newFile->internal->markersWereIgnored = true;
    }
    else {
        newFile->internal->readMarkers();
    }

    return newFile;
}

#pragma mark Instance Methods

boolean AIFFTrackFile::hasBitDepth(void) const
{
    return true;
}

uinteger32 AIFFTrackFile::bitDepthInBits(void) const
{
    auto audioProperties = dynamic_cast<const TagLib::RIFF::AIFF::Properties*>(internal->file->audioProperties());
    NXA_ASSERT_NOT_NULL(audioProperties);

    return audioProperties->sampleWidth();
}
