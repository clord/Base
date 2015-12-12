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

#include "TrackFiles/Internal/WAVTrackFile.hpp"

#include <wavfile.h>

// -- Generated internal implementation ommitted because this class does not use the default contructor.

using namespace NxA;
using namespace NxA::Serato::Internal;

#pragma mark Constructors & Destructors

WAVTrackFile::WAVTrackFile(const String& path) : ID3TrackFile(path) { }

#pragma mark Instance methods

void WAVTrackFile::parseAudioProperties(const TagLib::RIFF::WAV::Properties& properties)
{
    this->TrackFile::parseAudioProperties(properties);

    this->bitDepthInBits = properties.sampleWidth();
}

#pragma mark Overridden TrackFile Instance Methods

void WAVTrackFile::loadAndParseFile(void)
{
    TagLib::RIFF::WAV::File file(this->filePath->toUTF8(),
                                 true,
                                 TagLib::AudioProperties::ReadStyle::Fast);
    if (!file.isValid()) {
        throw TrackFileError::exceptionWith("Error loading track file '%s'.", this->filePath->toUTF8());
    }

    auto tag = file.tag();
    if (!tag) {
        throw TrackFileError::exceptionWith("Error reading tags from track file '%s'.", this->filePath->toUTF8());
    }
    this->parseTag(*tag);

    auto audioProperties = file.audioProperties();
    if (!audioProperties) {
        throw TrackFileError::exceptionWith("Error reading audio properties from track file '%s'.", this->filePath->toUTF8());
    }
    this->parseAudioProperties(*audioProperties);

    if (!this->markersWereIgnored) {
        this->ID3TrackFile::parseMarkersInTagToTrackFile(*tag, *this);
    }
}

void WAVTrackFile::updateAndSaveFile(void) const
{
    TagLib::RIFF::WAV::File file(this->filePath->toUTF8(),
                                 true,
                                 TagLib::AudioProperties::ReadStyle::Fast);
    if (!file.isValid()) {
        throw TrackFileError::exceptionWith("Error loading track file '%s'.", this->filePath->toUTF8());
    }

    auto tag = file.tag();
    if (!tag) {
        throw TrackFileError::exceptionWith("Error reading tags from track file '%s'.", this->filePath->toUTF8());
    }

    if (this->metadataWasModified) {
        this->updateTag(*tag);
    }

    if (this->markersWereModified) {
        NXA_ASSERT_FALSE(this->markersWereIgnored);

        this->updateMarkersInTagFromTrackFile(*tag, *this);
    }

    // -- This is misleading. It doesn't actually save anything to disk.
    // -- Instead, real saving takes place in the file's desctructor. #ugh
    file.save();
}
