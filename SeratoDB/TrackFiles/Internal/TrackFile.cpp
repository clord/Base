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

#include "TrackFiles/Internal/TrackFile.hpp"

namespace NxA { namespace Serato { namespace Internal {
    #pragma mark Structures
    typedef struct {
        unsigned char majorVersion;
        unsigned char minorVersion;
        unsigned char data[0];
    } MarkerHeaderStruct;
} } }

using namespace NxA;
using namespace NxA::Serato::Internal;

#pragma mark Constructors & Destructors

TrackFile::TrackFile(const String& path, const TagLibFilePointer& newFile) :
                     trackFilePath(path.pointer()),
                     file(newFile),
                     markersWereIgnored(false),
                     markersWereModified(false),
                     metadataWasModified(false),
                     cueMarkers(Serato::CueMarker::Array::array()),
                     loopMarkers(Serato::LoopMarker::Array::array()),
                     gridMarkers(Serato::GridMarker::Array::array()),
                     otherTags(Blob::Array::array()) { }

#pragma mark Class Methods

const byte* TrackFile::nextTagPositionAfterTagNamed(const String& tagName, const byte* currentTagPosition)
{
    auto parserPosition = currentTagPosition;
    parserPosition += tagName.length() + 1;

    auto tagSize = Platform::bigEndianUInteger32ValueAt(parserPosition);
    parserPosition += 4 + tagSize;

    return parserPosition;
}

Blob::Pointer TrackFile::markerV2TagDataFrom(const byte* tagStart)
{
    auto tagName = String::stringWith(reinterpret_cast<const char*>(tagStart));
    count sizeOfNameField = tagName->length() + 1;
    constexpr count sizeOfSizeField = 4;

    auto sizePosition = tagStart + sizeOfNameField;
    count tagSize = Platform::bigEndianUInteger32ValueAt(sizePosition) + sizeOfNameField + sizeOfSizeField;

    return Blob::blobWithMemoryAndSize(tagStart, tagSize);
}

#pragma mark Instance Methods

const byte* TrackFile::readMarkerAtAndAdvanceToNextTag(const byte* tagStart)
{
    NXA_ASSERT_FALSE(this->markersWereIgnored);

    auto tagName = String::stringWith(reinterpret_cast<const character*>(tagStart));

    try {
        if (*tagName == "CUE") {
            this->cueMarkers->append(Serato::CueMarker::markerWithMemoryAt(tagStart));
        }
        else if (*tagName == "LOOP") {
            this->loopMarkers->append(Serato::LoopMarker::markerWithMemoryAt(tagStart));
        }
        else {
            this->otherTags->append(markerV2TagDataFrom(tagStart));
        }
    }
    catch (LoopMarkerError exception) {
        // TODO: This should be a logging call instead.
        printf("%s\n", exception.what());
    }

    return nextTagPositionAfterTagNamed(tagName, tagStart);
}

void TrackFile::readMarkersV2FromBase64String(const byte* markerV2Data, count totalSize)
{
    NXA_ASSERT_FALSE(this->markersWereIgnored);

    if (!totalSize) {
        return;
    }

    auto decodedData = Blob::blobWithBase64String(String::stringWith(reinterpret_cast<const character*>(markerV2Data),
                                                                     totalSize));

    auto markerStruct = reinterpret_cast<MarkerHeaderStruct*>(decodedData->data());
    if ((markerStruct->majorVersion != 1) || (markerStruct->minorVersion != 1)) {
        return;
    }

    auto markerDataEnd = (const byte*)markerStruct + decodedData->size();
    auto tagStart = (const byte*)markerStruct->data;

    while (*tagStart && (tagStart < markerDataEnd)) {
        tagStart = this->readMarkerAtAndAdvanceToNextTag(tagStart);
    }
}

void TrackFile::readGridMarkersFrom(const byte* gridMarkerData)
{
    NXA_ASSERT_FALSE(this->markersWereIgnored);

    this->gridMarkers = Serato::GridMarker::markersWithMemoryAt(gridMarkerData);
}

String::Pointer TrackFile::base64StringFromMarkersV2(void)
{
    NXA_ASSERT_FALSE(this->markersWereIgnored);

    if (!this->cueMarkers->length() && !this->loopMarkers->length() && !this->otherTags->length()) {
        return String::string();
    }

    auto decodedData = Blob::blob();

    MarkerHeaderStruct markersHeader;
    markersHeader.majorVersion = 1;
    markersHeader.minorVersion = 1;

    auto headerData = Blob::blobWithMemoryAndSize(reinterpret_cast<byte*>(&markersHeader), sizeof(MarkerHeaderStruct));
    decodedData->append(headerData);

    for (auto& marker : *this->cueMarkers) {
        marker->addId3TagTo(decodedData);
    }

    for (auto& marker : *this->loopMarkers) {
        marker->addId3TagTo(decodedData);
    }

    for (auto& tagData : *this->otherTags) {
        decodedData->append(tagData);
    }

    // -- This marks the end of tags.
    decodedData->append('\0');

    auto encodedData = Blob::base64StringFor(decodedData->data(), decodedData->size());
    return encodedData;
}

Blob::Pointer TrackFile::gridMarkerDataFromGridMarkersAndFixGridMarkersToMatchData(void)
{
    NXA_ASSERT_FALSE(this->markersWereIgnored);

    auto data = Blob::blob();
    if (!this->gridMarkers->length()) {
        return data;
    }

    Serato::GridMarker::addMarkersTo(this->gridMarkers, data);

    // -- Serato doesn't support very flexible grid markers, the ones we end up writing
    // -- might not be exactly the ones we wanted to write so we read them back to
    // -- make sure our internal ones match what was written.
    this->gridMarkers = Serato::GridMarker::markersWithMemoryAt(data->data());

    return data;
}
