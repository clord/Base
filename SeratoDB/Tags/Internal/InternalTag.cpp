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

#include "SeratoDB/Tags/Internal/InternalTag.hpp"

using namespace NxA;
using namespace NxA::Serato;

#pragma mark Constructors & Destructors

InternalTag::InternalTag() :
    identifier(0)
{
}

#pragma mark Class Methods

void InternalTag::setIdentifierForTagAt(uinteger32 identifier, byte* tagAddress)
{
    TagStruct* tagStructPtr = reinterpret_cast<TagStruct*>(tagAddress);
    Platform::writeBigEndianUInteger32ValueAt(identifier, tagStructPtr->identifier);
}

void InternalTag::setDataSizeForTagAt(count dataSize, byte* tagAddress)
{
    TagStruct* tagStructPtr = reinterpret_cast<TagStruct*>(tagAddress);
    Platform::writeBigEndianUInteger32ValueAt((uint32_t)dataSize, tagStructPtr->length);
}

count InternalTag::memoryNeededForTagHeader(void)
{
    return sizeof(TagStruct);
}

const byte* InternalTag::dataForTagAt(const byte* tagAddress)
{
    const TagStruct* tagStructPtr = reinterpret_cast<const TagStruct*>(tagAddress);
    return tagStructPtr->data;
}

byte* InternalTag::dataForTagAt(byte* tagAddress)
{
    return const_cast<byte*>(InternalTag::dataForTagAt(const_cast<const byte*>(tagAddress)));
}
