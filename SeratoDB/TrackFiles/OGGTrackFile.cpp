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

#include "TrackFiles/OGGTrackFile.hpp"
#include "TrackFiles/Internal/OGGTrackFile.hpp"

#include <vorbisfile.h>

NXA_GENERATED_IMPLEMENTATION_IN_NAMESPACE_FOR_CLASS_WITH_PARENT(NxA::Serato, OGGTrackFile, TrackFile);

using namespace NxA;
using namespace NxA::Serato;

#pragma mark Factory Methods

OGGTrackFile::Pointer OGGTrackFile::fileWithFileAt(const String& path, TrackFile::Flags flags)
{
    auto file = Internal::TagLibFilePointer(std::make_shared<TagLib::Vorbis::File>(path.toUTF8()));
    if (!file->isValid()) {
        throw TrackFileError::exceptionWith("Error loading track file '%s'.", path.toUTF8());
    }

    auto oggFile = dynamic_cast<TagLib::Vorbis::File*>(&(*file));

    auto internalObject = Internal::OGGTrackFile::Pointer(std::make_shared<Internal::OGGTrackFile>(path, file));
    auto newFile = OGGTrackFile::makeSharedWithInternal(NxA::Internal::Object::Pointer::dynamicCastFrom(internalObject));
    newFile->internal->tag = newFile->internal->oggComment = oggFile->tag();
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

String::Pointer OGGTrackFile::releaseDate(void) const
{
    return Internal::OGGTrackFile::releaseDateInComment(internal->oggComment);
}

boolean OGGTrackFile::hasKey(void) const
{
    return false;
}

String::Pointer OGGTrackFile::key(void) const
{
    return String::string();
}

String::Pointer OGGTrackFile::composer(void) const
{
    return internal->stringValueForFieldNamed(Internal::oggComposerFieldName);
}

String::Pointer OGGTrackFile::grouping(void) const
{
    return internal->stringValueForFieldNamed(Internal::oggGroupingFieldName);
}

String::Pointer OGGTrackFile::bpm(void) const
{
    return internal->stringValueForFieldNamed(Internal::oggBpmFieldName);
}

boolean OGGTrackFile::hasRecordLabel(void) const
{
    return true;
}

String::Pointer OGGTrackFile::recordLabel(void) const
{
    return internal->stringValueForFieldNamed(Internal::oggRecordLabelFieldName);
}

boolean OGGTrackFile::hasRemixer(void) const
{
    return true;
}

String::Pointer OGGTrackFile::remixer(void) const
{
    return internal->stringValueForFieldNamed(Internal::oggRemixerFieldName);
}

boolean OGGTrackFile::hasRating(void) const
{
    return false;
}

integer OGGTrackFile::rating(void) const
{
    return 0;
}

Blob::Pointer OGGTrackFile::artwork(void) const
{
    // -- TODO: To be implemented.
    return Blob::blob();
}

void OGGTrackFile::setReleaseDate(const String& date)
{
    Internal::OGGTrackFile::setReleaseDateInComment(date, internal->oggComment);
    internal->metadataWasModified = true;
}

void OGGTrackFile::setKey(const String& key)
{
    // -- This is not supported by OGG files.
}

void OGGTrackFile::setComposer(const String& composer)
{
    internal->setStringValueForFieldNamed(composer, Internal::oggComposerFieldName);
    internal->metadataWasModified = true;
}

void OGGTrackFile::setGrouping(const String& grouping)
{
    internal->setStringValueForFieldNamed(grouping, Internal::oggGroupingFieldName);
    internal->metadataWasModified = true;
}

void OGGTrackFile::setBpm(const String& bpm)
{
    internal->setStringValueForFieldNamed(bpm, Internal::oggBpmFieldName);
    internal->metadataWasModified = true;
}

void OGGTrackFile::setRecordLabel(const String& recordLabel)
{
    internal->setStringValueForFieldNamed(recordLabel, Internal::oggRecordLabelFieldName);
    internal->metadataWasModified = true;
}

void OGGTrackFile::setRemixer(const String& remixer)
{
    internal->setStringValueForFieldNamed(remixer, Internal::oggRemixerFieldName);
    internal->metadataWasModified = true;
}

void OGGTrackFile::setRating(integer rating)
{
    // -- TODO: To be implemented.
}

void OGGTrackFile::setArtwork(const Blob& artwork)
{
    // -- TODO: To be implemented.
}
