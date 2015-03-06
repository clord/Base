//
//  NxASeratoID3TrackFile.cpp
//  SeratoDB
//
//  Created by Didier Malenfant on 2/12/15.
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

#include <taglib/generalencapsulatedobjectframe.h>

#include "SeratoDB/NxASeratoID3TrackFile.h"
#include "SeratoDB/NxASeratoBase64.h"

#include <taglib/id3v2tag.h>
#include <taglib/attachedpictureframe.h>

using namespace NxA;
using namespace TagLib;
using namespace std;

#pragma mark Constants

static const string emptyString("");

#pragma mark Structures

typedef struct {
    unsigned char dummy;
    unsigned char mimeType[25];
    unsigned char filename;
    unsigned char description[16];
    unsigned char majorVersion;
    unsigned char minorVersion;
} SeratoGeobBodyHeaderStruct;

typedef struct {
    unsigned char majorVersion;
    unsigned char minorVersion;
    unsigned char data[0];
} SeratoGeobObjectStruct;

#pragma mark Utility Functions

static bool p_isAValidGeobFrame(const ID3v2::GeneralEncapsulatedObjectFrame* frame)
{
    String frameID(frame->frameID().data());
    if (frameID != "GEOB") {
        return false;
    }

    String mimeType = frame->mimeType();
    return mimeType == "application/octet-stream";
}

#pragma mark Instance Methods

void SeratoID3TrackFile::p_readMarkersV2(void)
{
    ID3v2::Tag* tag = (ID3v2::Tag*)this->p_parsedFileTag;
    if (!tag) {
        return;
    }

    ID3v2::FrameListMap frameListMap = tag->frameListMap();
    if (!frameListMap.contains("GEOB")) {
        return;
    }

    ID3v2::FrameList geobFrames = frameListMap["GEOB"];
    for (auto& framePtr : geobFrames) {
        const ID3v2::GeneralEncapsulatedObjectFrame* frame = (ID3v2::GeneralEncapsulatedObjectFrame*)framePtr;
        if (!p_isAValidGeobFrame(frame)) {
            continue;
        }

        const String description = frame->description();
        if (description == "Serato Markers2") {
            uint32_t encodedDataSize = frame->size() - sizeof(SeratoGeobBodyHeaderStruct);
            const ByteVector frameObject = frame->object();

            SeratoGeobObjectStruct* objectData = (SeratoGeobObjectStruct*)frameObject.data();
            this->p_readMarkersV2FromBase64Data((char*)objectData->data, encodedDataSize);
        }
    }
}

bool SeratoID3TrackFile::hasKey(void) const
{
    return true;
}

string SeratoID3TrackFile::key(void) const
{
    String text = this->p_properties["INITIALKEY"].toString();
    if (text != String::null) {
        return text.to8Bit();
    }

    return emptyString;
}

string SeratoID3TrackFile::grouping(void) const
{
    String text = this->p_properties["CONTENTGROUP"].toString();
    if (text != String::null) {
        return text.to8Bit();
    }

    return emptyString;
}

bool SeratoID3TrackFile::hasRecordLabel(void) const
{
    return true;
}

string SeratoID3TrackFile::recordLabel(void) const
{
    String text = this->p_properties["LABEL"].toString();
    if (text != String::null) {
        return text.to8Bit();
    }

    return emptyString;
}

bool SeratoID3TrackFile::hasRemixer(void) const
{
    return true;
}

string SeratoID3TrackFile::remixer(void) const
{
    String text = this->p_properties["REMIXER"].toString();
    if (text != String::null) {
        return text.to8Bit();
    }

    return emptyString;
}

string SeratoID3TrackFile::yearReleased(void) const
{
    String text = this->p_properties["DATE"].toString();
    if (text != String::null) {
        return text.to8Bit();
    }

    return emptyString;
}

CharVectorPtr SeratoID3TrackFile::artwork(void) const
{
    CharVectorPtr result;

    ID3v2::Tag* tag = (ID3v2::Tag*)this->p_parsedFileTag;
    if(tag) {
        ID3v2::FrameListMap frameListMap = tag->frameListMap();
        ID3v2::FrameList frameList = frameListMap["APIC"];

        ID3v2::AttachedPictureFrame* artworkFrame = nullptr;

        for(ID3v2::FrameList::ConstIterator it = frameList.begin(); it != frameList.end(); ++it) {
            ID3v2::Frame* frame = *it;

            ID3v2::AttachedPictureFrame* pic = dynamic_cast<ID3v2::AttachedPictureFrame*>(frame);
            if (pic->type() == ID3v2::AttachedPictureFrame::FrontCover) {
                artworkFrame = pic;
                break;
            }
            else if (pic->type() == ID3v2::AttachedPictureFrame::Other) {
                artworkFrame = pic;
            }
        }

        if (artworkFrame) {
            ByteVector picture(artworkFrame->picture());
            size_t size = picture.size();
            if (size) {
                char* data = picture.data();
                result = make_unique<CharVector>(data, data + size);
            }
        }
    }

    return move(result);
}
