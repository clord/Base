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

#include "TrackFiles/WAVTrackFile.hpp"
#include "TrackFiles/Internal/ID3TrackFile.hpp"

#include <Base/Base.hpp>

#include <wavproperties.h>

namespace NxA { namespace Serato { namespace Internal {
    struct WAVTrackFile : public ID3TrackFile {
        NXA_GENERATED_DESTRUCTOR_FOR_CLASS(WAVTrackFile);

        #pragma mark Constructor & Destructors
        WAVTrackFile(const String& path);

        #pragma mark Instance Methods
        void parseAudioProperties(const TagLib::RIFF::WAV::Properties& properties);

        #pragma mark Overridden TrackFile Instance Methods
        virtual void loadAndParseFile(void) override;
        virtual void updateAndSaveFile(void) const override;
    };
} } }
