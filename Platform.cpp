//
//  Copyright (c) 2015-2017 Next Audio Labs, LLC. All rights reserved.
//
//  Permission is hereby granted, free of charge, to any person obtaining a copy of
//  this software and associated documentation files (the "Software"), to deal in the
//  Software without restriction, including without limitation the rights to use, copy,
//  modify, merge, publish, distribute, sublicense, and/or sell copies of the Software,
//  and to permit persons to whom the Software is furnished to do so, subject to the
//  following conditions:
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

#include "Base/MutableBlob.hpp"
#include "Base/Blob.hpp"
#include "Base/Platform.hpp"

#include <utility>

using namespace NxA;

// -- Class Methods

float Platform::bigEndianFloatValueAt(const byte* pointer)
{
    const auto* charsPtr = reinterpret_cast<const character*>(pointer);
    uint32_t bigEndianVersion =
        ((charsPtr[0] << 24) & 0xff000000) | ((charsPtr[1] << 16) & 0xff0000) | ((charsPtr[2] << 8) & 0xff00) | (charsPtr[3] & 0xff);
    return *reinterpret_cast<float*>(&bigEndianVersion);
}

uinteger32 Platform::bigEndianUInteger32ValueAt(const byte* pointer)
{
    const auto* charsPtr = reinterpret_cast<const character*>(pointer);
    return ((charsPtr[0] << 24) & 0xff000000) | ((charsPtr[1] << 16) & 0xff0000) | ((charsPtr[2] << 8) & 0xff00) | (charsPtr[3] & 0xff);
}

uinteger16 Platform::bigEndianUInteger16ValueAt(const byte* pointer)
{
    const auto* charsPtr = reinterpret_cast<const character*>(pointer);
    return ((charsPtr[0] << 8) & 0xff00) | (charsPtr[1] & 0xff);
}

void Platform::writeBigEndianFloatValueAt(float value, byte* pointer)
{
    auto* charsPtr = reinterpret_cast<character*>(pointer);
    const auto* valuePtr = reinterpret_cast<const character*>(&value);
    charsPtr[0] = valuePtr[3];
    charsPtr[1] = valuePtr[2];
    charsPtr[2] = valuePtr[1];
    charsPtr[3] = valuePtr[0];
}

void Platform::writeBigEndianUInteger32ValueAt(uinteger32 value, byte* pointer)
{
    auto* charsPtr = reinterpret_cast<character*>(pointer);
    charsPtr[0] = (value >> 24) & 0xff;
    charsPtr[1] = (value >> 16) & 0xff;
    charsPtr[2] = (value >> 8) & 0xff;
    charsPtr[3] = value & 0xff;
}

void Platform::writeBigEndianUInteger16ValueAt(uinteger16 value, byte* pointer)
{
    auto* charsPtr = reinterpret_cast<character*>(pointer);
    charsPtr[0] = (value >> 8) & 0xff;
    charsPtr[1] = value & 0xff;
}

Blob Platform::convertEndiannessOfUInteger16From(const Blob& other)
{
    MutableBlob copy(other);
    if (!copy.size()) {
        return {std::move(copy)};
    }

    auto numberOfSwaps = copy.size() / 2;

    integer index = 0;
    byte* data = copy.data();
    for (integer count = 0; count < numberOfSwaps; ++count, index += 2) {
        std::swap(data[index], data[index + 1]);
    }

    return {std::move(copy)};
}
