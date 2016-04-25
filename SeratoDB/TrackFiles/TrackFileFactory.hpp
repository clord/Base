//
//  Copyright (c) 2015-2016 Next Audio Labs, LLC. All rights reserved.
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

#pragma once

#include <SeratoDb/TrackFiles/TrackFile.hpp>

#include <Base/Base.hpp>

NXA_ENTER_NAMESPACE(NxA);
NXA_ENTER_NAMESPACE(Serato);

class TrackFileFactory : public Uncopyable {
public:
    #pragma mark Constants
    enum AudioFileType {
        Unknown,
        AIFF,
        MP3,
        WAV,
        OGG,
        MP4,
        FLAC,
        WMA,
    };

    #pragma mark Constructors & Destructors
    TrackFileFactory() = delete;

    #pragma mark Class Methods
    static AudioFileType audioFileTypeForPath(const character *trackFilePath);
    static AudioFileType audioFileTypeForPath(const String& trackFilePath);

    static NxA::Serato::TrackFile::Pointer trackFileForPath(const String& trackFilePath, TrackFile::Flags flags = TrackFile::Flags::NoFlag);
};

NXA_EXIT_NAMESPACE;
NXA_EXIT_NAMESPACE;
