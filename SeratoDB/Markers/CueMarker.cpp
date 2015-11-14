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

#include "Markers/CueMarker.hpp"
#include "Markers/Internal/CueMarker.hpp"

NXA_GENERATED_IMPLEMENTATION_IN_NAMESPACE_FOR_CLASS_WITH_PARENT(NxA::Serato, CueMarker, Object);

namespace NxA { namespace Serato {
    #pragma mark Structures
    typedef struct {
        byte tag[4];
        byte size[4];
    } SeratoCueTagHeaderStruct;

    typedef struct {
        byte tag[4];
        byte size[4];
        byte index[2];
        byte position[4];
        byte color[4];
        byte loop_enabled;
        byte loop_locked;
        byte label[0];
    } SeratoCueTagStruct;
} }

using namespace NxA;
using namespace NxA::Serato;

#pragma mark Factory Methods

CueMarker::Pointer CueMarker::markerWithMemoryAt(const byte* id3TagStart)
{
    auto tagStruct = reinterpret_cast<const SeratoCueTagStruct*>(id3TagStart);

    NXA_ASSERT_TRUE(*String::stringWith(reinterpret_cast<const character*>(tagStruct->tag)) == "CUE");

    return CueMarker::markerWithLabelPositionIndexAndColor(String::stringWith(reinterpret_cast<const character*>(tagStruct->label)),
                                                           Platform::bigEndianUInteger32ValueAt(tagStruct->position),
                                                           Platform::bigEndianUInteger16ValueAt(tagStruct->index),
                                                           tagStruct->color[1],
                                                           tagStruct->color[2],
                                                           tagStruct->color[3]);
}

CueMarker::Pointer CueMarker::markerWithLabelPositionIndexAndColor(const String& label,
                                                                   uinteger32 positionInMilliseconds,
                                                                   uinteger16 index,
                                                                   byte colorRedComponent,
                                                                   byte colorGreenComponent,
                                                                   byte colorBlueComponent)
{
    auto newMarker = CueMarker::makeShared();
    newMarker->internal->positionInMilliseconds = positionInMilliseconds;
    newMarker->internal->index = index;
    newMarker->internal->label = label.pointer();
    newMarker->internal->colorRedComponent = colorRedComponent;
    newMarker->internal->colorGreenComponent = colorGreenComponent;
    newMarker->internal->colorBlueComponent = colorBlueComponent;

    return newMarker;
}

CueMarker::Pointer CueMarker::markerWith(const CueMarker&other)
{
    return CueMarker::markerWithLabelPositionIndexAndColor(other.label(),
                                                           other.positionInMilliseconds(),
                                                           other.index(),
                                                           other.colorRedComponent(),
                                                           other.colorGreenComponent(),
                                                           other.colorBlueComponent());
}

#pragma mark Operators

bool CueMarker::operator==(const CueMarker& other) const
{
    if (this == &other) {
        return true;
    }

    return (this->label() == other.label()) &&
           (this->positionInMilliseconds() == other.positionInMilliseconds()) &&
           (this->index() == other.index() &&
           (this->colorRedComponent() == other.colorRedComponent()) &&
           (this->colorGreenComponent() == other.colorGreenComponent()) &&
           (this->colorBlueComponent() == other.colorBlueComponent()));
}

#pragma mark Instance Methods

uinteger32 CueMarker::positionInMilliseconds(void) const
{
    return internal->positionInMilliseconds;
}

uinteger16 CueMarker::index(void) const
{
    return internal->index;
}

const String& CueMarker::label(void) const
{
    return internal->label;
}

byte CueMarker::colorRedComponent(void) const
{
    return internal->colorRedComponent;
}

byte CueMarker::colorGreenComponent(void) const
{
    return internal->colorGreenComponent;
}

byte CueMarker::colorBlueComponent(void) const
{
    return internal->colorBlueComponent;
}

void CueMarker::addId3TagTo(Blob& data) const
{
    SeratoCueTagStruct header;

    memcpy(header.tag, "CUE", 4);
    count size = sizeof(SeratoCueTagStruct) + this->label().length() + 1 - sizeof(SeratoCueTagHeaderStruct);
    Platform::writeBigEndianUInteger32ValueAt(static_cast<uinteger32>(size), header.size);
    Platform::writeBigEndianUInteger16ValueAt(this->index(), header.index);
    Platform::writeBigEndianUInteger32ValueAt(this->positionInMilliseconds(), header.position);
    header.color[0] = 0;
    header.color[1] = this->colorRedComponent();
    header.color[2] = this->colorGreenComponent();
    header.color[3] = this->colorBlueComponent();
    header.loop_enabled = 0;
    header.loop_locked = 0;

    auto headerData = Blob::blobWithMemoryAndSize(reinterpret_cast<const byte*>(&header), sizeof(SeratoCueTagStruct));
    data.append(headerData);
    data.appendWithStringTermination(this->label().toUTF8());
}

#pragma mark Overriden Object Instance Methods

NxA::String::Pointer CueMarker::description(void)
{
    return NxA::String::stringWithFormat("Cue Marker at %fms with index %d label '%s' and color 0x%02x 0x%02x 0x%02x.",
                                         this->positionInMilliseconds(),
                                         this->index(),
                                         this->label().toUTF8(),
                                         this->colorRedComponent(),
                                         this->colorGreenComponent(),
                                         this->colorBlueComponent());
}
