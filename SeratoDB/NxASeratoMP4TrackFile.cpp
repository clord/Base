//
//  NxASeratoMP4TrackFile.cpp
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

#include "SeratoDB/NxASeratoMP4TrackFile.h"
#include "SeratoDB/NxASeratoBase64.h"

#include <taglib/mp4tag.h>

using namespace NxA;
using namespace TagLib;
using namespace std;

#pragma mark Constants

static const string emptyString("");

#pragma mark Structures

typedef struct {
    unsigned char mimeType[25];
    unsigned char filename[1];
    unsigned char description[16];
    unsigned char majorVersion;
    unsigned char minorVersion;
    unsigned char data[0];
} SeratoMP4MarkerHeaderStruct;

#pragma mark Constructors

SeratoMP4TrackFile::SeratoMP4TrackFile(const char* trackFilePath) : SeratoTrackFile(trackFilePath)
{
    TaglibFilePtr file = make_unique<MP4::File>(trackFilePath);
    if (!file->isValid()) {
        this->p_file = TaglibFilePtr();
        this->p_itemListMap = NULL;
        this->p_audioProperties = NULL;
        this->p_parsedFileTag = NULL;
        return;
    }

    MP4::Tag* tag = (MP4::Tag*)file->tag();
    this->p_parsedFileTag = tag;
    this->p_itemListMap = &(tag->itemListMap());
    this->p_audioProperties = file->audioProperties();
    this->p_properties = file->properties();
    this->p_file = move(file);

    this->p_readMarkersV2();
}

#pragma mark Instance Methods

void SeratoMP4TrackFile::p_readMarkersV2(void)
{
    if (!this->p_itemListMap) {
        return;
    }

    MP4::Item item = (*this->p_itemListMap)["----:com.serato.dj:markersv2"];
    if (!item.isValid()) {
        return;
    }

    const String markersEncodedData = item.toStringList().toString();
    uint32_t encodedDataSize = markersEncodedData.size();
    if (!encodedDataSize) {
        return;
    }

    CharVectorPtr decodedData = SeratoBase64::decodeBlock((const char*)markersEncodedData.data(String::UTF8).data(),
                                                                      encodedDataSize);

    const SeratoMP4MarkerHeaderStruct* headerStruct = (const SeratoMP4MarkerHeaderStruct*)decodedData->data();
    this->p_readMarkersV2FromBase64Data((const char*)headerStruct->data, decodedData->size() - sizeof(SeratoMP4MarkerHeaderStruct));
}

void SeratoMP4TrackFile::p_writeMarkersV2(void)
{
    CharVector decodedData;

    SeratoMP4MarkerHeaderStruct header;
    memcpy(header.mimeType, "application/octet-stream", 25);
    header.filename[0] = 0;
    memcpy(header.description, "Serato Markers2", 16);
    header.majorVersion = 1;
    header.minorVersion = 1;

    CharVector headerData((char*)&header, (char*)&header.data);
    decodedData.insert(decodedData.end(), headerData.begin(), headerData.end());

    CharVectorPtr base64Data(this->p_base64DataFromMarkersV2());
    decodedData.insert(decodedData.end(), base64Data->begin(), base64Data->end());

    CharVectorPtr encodedData = SeratoBase64::encodeBlock(decodedData.data(), decodedData.size());
    encodedData->push_back('\0');

    StringList newList;
    newList.append(String(encodedData->data()));

    MP4::Item newItem(newList);
    (*this->p_itemListMap)["----:com.serato.dj:markersv2"] = newItem;
}

bool SeratoMP4TrackFile::hasKey(void) const
{
    return true;
}

string SeratoMP4TrackFile::key(void) const
{
    MP4::Item item = (*this->p_itemListMap)["----:com.apple.iTunes:initialkey"];
    if (item.isValid()) {
        String text = item.toStringList().front();
        if (text != String::null) {
            return text.to8Bit();
        }
    }

    return emptyString;
}

string SeratoMP4TrackFile::grouping(void) const
{
    String text = this->p_properties["GROUPING"].toString();
    if (text != String::null) {
        return text.to8Bit();
    }

    return emptyString;
}

bool SeratoMP4TrackFile::hasRecordLabel(void) const
{
    return false;
}

string SeratoMP4TrackFile::recordLabel(void) const
{
    return emptyString;
}

bool SeratoMP4TrackFile::hasRemixer(void) const
{
    return false;
}

string SeratoMP4TrackFile::remixer(void) const
{
    return emptyString;
}

string SeratoMP4TrackFile::yearReleased(void) const
{
    String text = this->p_properties["DATE"].toString();
    if (text != String::null) {
        return text.to8Bit();
    }

    return emptyString;
}

CharVectorPtr SeratoMP4TrackFile::artwork(void) const
{
    CharVectorPtr result;

    MP4::Item item = (*this->p_itemListMap)["covr"];
    if (item.isValid()) {
        MP4::CoverArtList coverArtList = item.toCoverArtList();
        MP4::CoverArt coverArt = coverArtList.front();
        ByteVector coverArtData(coverArt.data());
        size_t size = coverArtData.size();
        if (size) {
            char* data = coverArtData.data();
            result = make_unique<CharVector>(data, data + size);
        }
    }

    return move(result);
}

void SeratoMP4TrackFile::setKey(const char* key)
{
    StringList newList;
    newList.append(String(key));
    MP4::Item newItem(newList);
    (*this->p_itemListMap)["----:com.apple.iTunes:initialkey"] = newItem;
}

void SeratoMP4TrackFile::setGrouping(const char* grouping)
{
    this->p_properties["GROUPING"] = String(grouping);
}

void SeratoMP4TrackFile::setRecordLabel(const char* recordLabel)
{
    // -- This is not supported by MP4 files.
}

void SeratoMP4TrackFile::setRemixer(const char* remixer)
{
    // -- This is not supported by MP4 files.
}

void SeratoMP4TrackFile::setYearReleased(const char* year)
{
    this->p_properties["DATE"] = String(year);
}

void SeratoMP4TrackFile::setArtwork(CharVectorPtr artwork)
{
    ByteVector data(artwork->data(), artwork->size());
    MP4::CoverArt newCoverArt(MP4::CoverArt::Unknown, data);
    MP4::CoverArtList newCoverArtList;
    newCoverArtList.append(newCoverArt);

    MP4::Item newItem(newCoverArtList);
    (*this->p_itemListMap)["covr"] = newItem;
}
