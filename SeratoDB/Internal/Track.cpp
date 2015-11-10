//
//  Copyright (c) 2015 Next Audio Labs, LLC. All rights reserved.
//
//  Permission is hereby granted, free of charge, to any person obtaining a copy of
//  this software and associated documentation files (the "Software"), to deal in the
//  Software without restriction, including without limitation the rights to use, copy,
//  modify, merge, publish, distribute, sublicense, and/or sell copies of the Software,
//  and to permit persons to whom the Software is furnished to do so, subject to the
//  following conditions:
//
//  The above copyright notice and this permission notice shall be included in all
//  copies or substantial portions of the Software.
//
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
//  INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
//  PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
//  HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
//  OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
//  SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
//

#include "Internal/Track.hpp"
#include "TrackFiles/TrackFileFactory.hpp"
#include "Tags/ObjectTag.hpp"
#include "Tags/TextTag.hpp"
#include "Tags/BooleanTag.hpp"
#include "Tags/PathTag.hpp"
#include "Tags/UInteger32Tag.hpp"
#include "Tags/DatabaseV2Tags.hpp"

// -- Generated internal implementation ommitted because this class does not use the default contructor.

using namespace NxA;
using namespace NxA::Serato::Internal;

#pragma mark Constants

static String::Pointer emptyString = String::string();

#pragma mark Constructors & Destructors

Track::Track(Serato::ObjectTag& tag, const String& rootFolderPath) :
             trackTag(tag.pointer()),
             rootFolder(rootFolderPath.pointer()),
             needsToUpdateDatabaseFile(false)
{
}

#pragma mark Instance Methods

const String& Track::stringForSubTagForIdentifier(uinteger32 identifier) const
{
    auto& trackObjectTag = *this->trackTag;
    if (trackObjectTag.hasSubTagForIdentifier(identifier)) {
        auto& textTag = dynamic_cast<const Serato::TextTag&>(trackObjectTag.subTagForIdentifier(identifier));
        return textTag.value();
    }

    return emptyString;
}

const String& Track::pathForSubTagForIdentifier(uinteger32 identifier) const
{
    auto& trackObjectTag = *this->trackTag;
    if (trackObjectTag.hasSubTagForIdentifier(identifier)) {
        auto& pathTag = dynamic_cast<const Serato::PathTag&>(trackObjectTag.subTagForIdentifier(identifier));
        return pathTag.value();
    }

    return emptyString;
}

uinteger32 Track::uint32ForSubTagForIdentifier(uinteger32 identifier) const
{
    auto& trackObjectTag = *this->trackTag;
    if (trackObjectTag.hasSubTagForIdentifier(identifier)) {
        auto& uintTag = dynamic_cast<const Serato::UInteger32Tag&>(trackObjectTag.subTagForIdentifier(identifier));
        return uintTag.value();
    }

    return 0;
}

void Track::setStringForSubTagForIdentifier(const String& value, uinteger32 identifier)
{
    auto& trackObjectTag = *this->trackTag;
    if (!trackObjectTag.hasSubTagForIdentifier(identifier)) {
        auto textTag = Serato::TextTag::tagWithIdentifierAndValue(identifier, value);
        trackObjectTag.setSubTag(*textTag);
    }
    else {
        auto& textTag = dynamic_cast<Serato::TextTag&>(trackObjectTag.subTagForIdentifier(identifier));
        textTag.setValue(value);
    }

    this->needsToUpdateDatabaseFile = true;
}

void Track::setPathForSubTagForIdentifier(const String& value, uinteger32 identifier)
{
    auto& trackObjectTag = dynamic_cast<Serato::ObjectTag&>(*this->trackTag);
    if (!trackObjectTag.hasSubTagForIdentifier(identifier)) {
        auto pathTag = Serato::PathTag::tagWithIdentifierAndValue(identifier, value);
        trackObjectTag.setSubTag(*pathTag);
    }
    else {
        auto& pathTag = dynamic_cast<Serato::PathTag&>(trackObjectTag.subTagForIdentifier(identifier));
        pathTag.setValue(value);
    }

    this->needsToUpdateDatabaseFile = true;
}

void Track::setUInt32ForSubTagForIdentifier(uinteger32 value, uinteger32 identifier)
{
    auto& trackObjectTag = *this->trackTag;
    if (!trackObjectTag.hasSubTagForIdentifier(identifier)) {
        auto uinteger32Tag = Serato::UInteger32Tag::tagWithIdentifierAndValue(identifier, value);
        trackObjectTag.setSubTag(*uinteger32Tag);
    }
    else {
        auto& uinteger32Tag = dynamic_cast<Serato::UInteger32Tag&>(trackObjectTag.subTagForIdentifier(identifier));
        uinteger32Tag.setValue(value);
    }

    this->needsToUpdateDatabaseFile = true;
}

void Track::setBooleanForSubTagForIdentifier(boolean value, uinteger32 identifier)
{
    auto& trackObjectTag = *this->trackTag;
    if (!trackObjectTag.hasSubTagForIdentifier(identifier)) {
        auto booleanTag = Serato::BooleanTag::tagWithIdentifierAndValue(identifier, value);
        trackObjectTag.setSubTag(*booleanTag);
    }
    else {
        auto& booleanTag = dynamic_cast<Serato::BooleanTag&>(trackObjectTag.subTagForIdentifier(identifier));
        booleanTag.setValue(value);
    }

    this->needsToUpdateDatabaseFile = true;
}

String::Pointer Track::trackFilePath(void) const
{
    auto& pathFromRootFolder = this->pathForSubTagForIdentifier(trackFilePathTagIdentifier);
    return File::joinPaths(this->rootFolder, pathFromRootFolder);
}
