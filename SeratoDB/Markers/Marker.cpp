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

#include "Markers/Marker.hpp"
#include "Markers/Internal/InternalMarker.hpp"

NXA_GENERATED_IMPLEMENTATION_IN_NAMESPACE_FOR_CLASS_WITH_PARENT(NxA::Serato, Marker, Object);

using namespace NxA;
using namespace NxA::Serato;

#pragma mark Class Methods

bool Marker::isValidV1RawMarker(const byte* tagStart)
{
    auto tagStruct = reinterpret_cast<const InternalMarker::SeratoRawTagV1Struct*>(tagStart);
    return (Platform::bigEndianUInteger32ValueAt(tagStruct->position) != 0xffffffff);
}

bool Marker::isValidV1EncodedMarker(const byte* tagStart)
{
    auto encodedStruct = reinterpret_cast<const InternalMarker::SeratoEncodedTagV1Struct*>(tagStart);

    InternalMarker::SeratoRawTagV1Struct rawStruct;
    InternalMarker::rawV1TagFromEncodedV1TagStruct(rawStruct, *encodedStruct);

    return (Platform::bigEndianUInteger32ValueAt(rawStruct.position) != 0xffffffff);
}

integer32 Marker::sizeOfV1RawMarker(void)
{
    return sizeof(InternalMarker::SeratoRawTagV1Struct);
}

integer32 Marker::sizeOfV1EncodedMarker(void)
{
    return sizeof(InternalMarker::SeratoEncodedTagV1Struct);
}

