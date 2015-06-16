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

#include "Markers/CueMarker.hpp"

#include <Base/Platform.hpp>

using namespace NxA::Serato;
using namespace std;

#pragma mark Structures

typedef struct {
    unsigned char tag[4];
    unsigned char size[4];
} SeratoCueTagHeaderStruct;

typedef struct {
    unsigned char tag[4];
    unsigned char size[4];
    unsigned char index[2];
    unsigned char position[4];
    unsigned char color[4];
    unsigned char loop_enabled;
    unsigned char loop_locked;
    unsigned char label[0];
} SeratoCueTagStruct;

#pragma mark Constructors

CueMarker::CueMarker(const char* id3TagStart)
{
    const SeratoCueTagStruct* tagStruct = (const SeratoCueTagStruct* )id3TagStart;

    this->p_positionInMilliSeconds = Platform::bigEndianUInt32ValueAt(tagStruct->position);
    this->p_index = Platform::bigEndianUInt16ValueAt(tagStruct->index);
    this->p_label = (char*)tagStruct->label;
}

#pragma mark Instance Methods

uint32_t CueMarker::positionInMilliseconds(void) const
{
    return this->p_positionInMilliSeconds;
}

uint16_t CueMarker::index(void) const
{
    return this->p_index;
}

const string& CueMarker::label(void) const
{
    return this->p_label;
}

void CueMarker::addId3TagTo(CharVector& data) const
{
    SeratoCueTagStruct header;

    memcpy(header.tag, "CUE", 4);
    size_t size = sizeof(SeratoCueTagStruct) + this->p_label.length() + 1 - sizeof(SeratoCueTagHeaderStruct);
    Platform::writeBigEndianUInt32ValueAt((uint32_t)size, &header.size);
    Platform::writeBigEndianUInt16ValueAt(this->p_index, &header.index);
    Platform::writeBigEndianUInt32ValueAt(this->p_positionInMilliSeconds, &header.position);
    Platform::writeBigEndianUInt32ValueAt(0, &header.color);
    header.loop_enabled = 0;
    header.loop_locked = 0;

    CharVector headerData((char*)&header, (char*)&header.label);
    data.insert(data.end(), headerData.begin(), headerData.end());

    data.insert(data.end(), this->p_label.begin(), this->p_label.end());
    data.insert(data.end(), 0);
}
