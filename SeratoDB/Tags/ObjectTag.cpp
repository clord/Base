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

#include "Tags/TagFactory.hpp"

#include "Tags/ObjectTag.hpp"
#include "Tags/Internal/ObjectTag.hpp"

NXA_GENERATED_IMPLEMENTATION_FOR(NxA::Serato, ObjectTag);

using namespace NxA;
using namespace NxA::Serato;

#pragma mark Constructors & Destructors

ObjectTag::ObjectTag(NxA::Internal::Object::Pointer const& initial_internal) :
                     Tag(initial_internal),
                     internal(initial_internal) { }

#pragma mark Factory Methods

ObjectTag::Pointer ObjectTag::tagWithMemoryAt(const byte* tagAddress)
{
    auto dataSize = Internal::Tag::dataSizeForTagAt(tagAddress);
    auto tagData = Internal::Tag::dataForTagAt(tagAddress);
    auto subTags = TagFactory::parseTagsAt(tagData, dataSize);

    return ObjectTag::tagWithIdentifierAndValue(Tag::identifierForTagAt(tagAddress),
                                                subTags);
}

ObjectTag::Pointer ObjectTag::tagWithIdentifierAndValue(uinteger32 identifier, Tag::Array::Pointer const& content)
{
    auto newTag = ObjectTag::makeShared();
    newTag->internal->identifier = identifier;

    for (auto& subTag : *content) {
        newTag->addSubTag(subTag);
    }

    return newTag;
}

#pragma mark Instance Methods

bool ObjectTag::hasSubTagForIdentifier(uinteger32 identifier) const
{
    return internal->subTagForIdentifier->containsValueForKey(identifier);
}

Tag::ConstPointer const& ObjectTag::subTagForIdentifier(uinteger32 identifier) const
{
    return (*internal->subTagForIdentifier)[identifier];
}

Tag::Pointer const& ObjectTag::subTagForIdentifier(uinteger32 identifier)
{
    return (*internal->subTagForIdentifier)[identifier];
}

void ObjectTag::addSubTag(Tag::Pointer const& tag)
{
    (*internal->subTagForIdentifier)[tag->identifier()] = tag;
}

void ObjectTag::addTo(Blob::Pointer const& destination) const
{
    auto subTagsRepresentation = Blob::blob();
    for (auto& identifierAndTag : *(internal->subTagForIdentifier)) {
        identifierAndTag.second->addTo(subTagsRepresentation);
    }

    auto sizeNeededForHeader = Internal::Tag::memoryNeededForTagHeader();
    auto headerRepresentation = Blob::blobWithCapacity(sizeNeededForHeader);
    auto tagAddress = headerRepresentation->data();
    Internal::Tag::setIdentifierForTagAt(this->identifier(), tagAddress);
    Internal::Tag::setDataSizeForTagAt(subTagsRepresentation->size(), tagAddress);

    destination->append(headerRepresentation);
    destination->append(subTagsRepresentation);
}
