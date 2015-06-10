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

#include "SeratoDB/ObjectTag.hpp"
#include "SeratoDB/TagFactory.hpp"

using namespace NxA::Serato;
using namespace std;

#pragma mark Constructors

ObjectTag::ObjectTag(const void* tagAddress) : Tag(tagAddress)
{
    size_t dataSizeInBytes = Tag::p_dataSizeInBytesForTagAt(tagAddress);
    const void* dataAddress = Tag::p_dataForTagAt(tagAddress);

    TagVectorPtr subTags = TagFactory::parseTagsAt(dataAddress, dataSizeInBytes);
    for (TagPtr& subTag : *(subTags)) {
        this->p_subTagForIdentifier[subTag->identifier()] = move(subTag);
    }
}

ObjectTag::ObjectTag(const uint32_t& identifier, TagVectorPtr content) : Tag(identifier)
{
    for (TagPtr& subTag : *(content)) {
        this->p_subTagForIdentifier[subTag->identifier()] = move(subTag);
    }
}

#pragma mark Instance Methods

bool ObjectTag::hasSubTagForIdentifier(const uint32_t& identifier) const
{
    SeratoIdentifierToTagMap::const_iterator it = this->p_subTagForIdentifier.find(identifier);
    return it != this->p_subTagForIdentifier.end();
}

const Tag& ObjectTag::subTagForIdentifier(const uint32_t& identifier) const
{
    SeratoIdentifierToTagMap::const_iterator it = this->p_subTagForIdentifier.find(identifier);
    return *(it->second);
}

Tag& ObjectTag::subTagForIdentifier(const uint32_t& identifier)
{
    return const_cast<Tag&>(static_cast<const ObjectTag&>(*this).subTagForIdentifier(identifier));
}

void ObjectTag::addSubTag(ConstTagPtr tag)
{
    this->p_subTagForIdentifier[tag->identifier()] = move(tag);
}

void ObjectTag::addTo(CharVector& destination) const
{
    CharVector subTagsRepresentation;
    for (auto& identifierAndTag : this->p_subTagForIdentifier) {
        identifierAndTag.second->addTo(subTagsRepresentation);
    }

    size_t memoryNeededForHeaderInBytes = Tag::p_memoryNeededWithDataOfSize(0);
    CharVectorPtr headerRepresentation = make_unique<CharVector>(memoryNeededForHeaderInBytes, 0);
    void* tagAddress = headerRepresentation->data();
    Tag::p_setIdentifierForTagAt(this->identifier(), tagAddress);
    Tag::p_setDataSizeForTagAt(subTagsRepresentation.size(), tagAddress);

    destination.insert(destination.end(), headerRepresentation->begin(), headerRepresentation->end());
    destination.insert(destination.end(), subTagsRepresentation.begin(), subTagsRepresentation.end());
}
