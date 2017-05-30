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
#include "Base/Internal/MutableBlobInternal.hpp"
#include "Base/String.hpp"
#include "Base/Assert.hpp"
#include "Base/Describe.hpp"

using namespace NxA;

#define NXA_OBJECT_CLASS                    MutableBlob
#define NXA_OBJECT_HAS_A_CUSTOM_CLASS_NAME

#include <Base/ObjectDefinition.ipp>

// -- Factory Methods

MutableBlob MutableBlob::blobWithCapacity(count size)
{
    return { Internal::blobWithCapacity(size) };
}

MutableBlob MutableBlob::blobWithMemoryAndSize(const byte* other, count size)
{
    return { Internal::blobWithMemoryAndSize(other, size) };
}

MutableBlob MutableBlob::blobWithBase64String(const String& string)
{
    return { Internal::blobWithBase64String(string) };
}

MutableBlob MutableBlob::blobWithStringWithTerminator(const String& string)
{
    return { Internal::blobWithStringWithTerminator(string) };
}

MutableBlob MutableBlob::blobWithStringWithoutTerminator(const String& string)
{
    return { Internal::blobWithStringWithoutTerminator(string) };
}

// -- Constructors/Destructors

MutableBlob::MutableBlob() : std::shared_ptr<Internal>{ std::make_shared<Internal>() } { }
MutableBlob::MutableBlob(const Blob& other) : std::shared_ptr<Internal>{ std::make_shared<Internal>(*other)} { }

// -- Operators

byte& MutableBlob::operator[](count index)
{
    return nxa_internal->operator[](index);
}

const byte& MutableBlob::operator[](count  index) const
{
    return nxa_internal->operator[](index);
}

bool MutableBlob::operator==(const Blob& other) const
{
    return nxa_internal->operator==(*NXA_INTERNAL_OBJECT_FOR(other));
}

// -- Instance Methods

count MutableBlob::size() const
{
    return nxa_internal->size();
}

byte* MutableBlob::data()
{
    return nxa_internal->data();
}

const byte* MutableBlob::data() const
{
    return nxa_internal->data();
}

Blob MutableBlob::hash()
{
    return { nxa_internal->hash() };
}

String MutableBlob::base64String() const
{
    return nxa_internal->base64String();
}

void MutableBlob::fillWithZeros()
{
    return nxa_internal->fillWithZeros();
}

void MutableBlob::append(const Blob& other)
{
    return nxa_internal->append(*NXA_INTERNAL_OBJECT_FOR(other));
}

void MutableBlob::appendMemoryWithSize(const byte* data, count size)
{
    nxa_internal->appendMemoryWithSize(data, size);
}

void MutableBlob::appendWithStringTermination(const character* other)
{
    return nxa_internal->appendWithStringTermination(other);
}

void MutableBlob::appendWithoutStringTermination(const character* other)
{
    return nxa_internal->appendWithoutStringTermination(other);
}

void MutableBlob::append(const character other)
{
    return nxa_internal->append(other);
}

void MutableBlob::removeAll()
{
    nxa_internal->removeAll();
}

void MutableBlob::padToAlignment(count alignment)
{
    nxa_internal->padToAlignment(alignment);
}

String MutableBlob::description(const DescriberState& state) const
{
    return nxa_internal->description();
}
