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

#include "SeratoDB/Crate.hpp"
#include "SeratoDB/TrackEntry.hpp"
#include "SeratoDB/Tags/Tag.hpp"

#include <Base/Base.hpp>
#include <Base/Internal/InternalObject.hpp>

NXA_ENTER_NAMESPACE(NxA);
NXA_ENTER_NAMESPACE(Serato);

struct InternalTrackEntry : public InternalObject {
    NXA_GENERATED_DESTRUCTOR_FOR_CLASS(InternalTrackEntry);

    #pragma mark Constructors & Destructors
    InternalTrackEntry(const Tag& tag,
                       const String& newVolumePath);

    #pragma mark Instance Variable
    Crate::WeakPointer parentCrate;

    Tag::PointerToConst trackEntryTag;
    String::PointerToConst volumePath;
};

NXA_EXIT_NAMESPACE;
NXA_EXIT_NAMESPACE;
