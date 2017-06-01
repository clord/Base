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

#include "Base/Blob.hpp"
#include "Base/MutableBlob.hpp"
#include "Base/Internal/MutableBlobInternal.hpp"
#include "Base/String.hpp"
#include "Base/Assert.hpp"
#include "Base/Describe.hpp"

using namespace NxA;

#define NXA_OBJECT_CLASS                            Blob
#define NXA_INTERNAL_OBJECT_SHOULD_NOT_BE_COPIED
#define NXA_OBJECT_HAS_A_CUSTOM_CLASS_NAME

#include <Base/ObjectDefinition.ipp>

// -- Factory Methods

Blob Blob::blobWithMemoryAndSize(const byte* other, count size)
{
    return {Internal::blobWithMemoryAndSize(other, size)};
}

Blob Blob::blobWithBase64String(const String& string)
{
    return {Internal::blobWithBase64String(string)};
}

Blob Blob::blobWithStringWithTerminator(const String& string)
{
    return {Internal::blobWithStringWithTerminator(string)};
}

Blob Blob::blobWithStringWithoutTerminator(const String& string)
{
    return {Internal::blobWithStringWithoutTerminator(string)};
}

// -- Class Methods

Blob Blob::hashFor(const byte* memory, count size)
{
    return {Internal::hashFor(memory, size)};
}

String Blob::base64StringFor(const byte* memory, count size)
{
    return {Internal::base64StringFor(memory, size)};
}

// -- Constructors/Destructors

Blob::Blob() : std::shared_ptr<Internal>{ std::make_shared<Internal>() } { }
Blob::Blob(MutableBlob&& other) : std::shared_ptr<Internal>{ std::move(other) }
{
    // -- If we're moving this other mutable, it can't be referred to by anyone else.
    NXA_ASSERT_TRUE(this->use_count() == 1);
}
Blob::Blob(const MutableBlob& other) : std::shared_ptr<Internal>{ std::make_shared<Internal>(*other) } { }

// -- Operators

const byte& Blob::operator[](count index) const
{
    return nxa_internal->operator[](index);
}

// -- Instance Methods

count Blob::size() const
{
    return nxa_internal->size();
}

const byte* Blob::data() const
{
    return nxa_internal->data();
}

Blob Blob::hash()
{
    return { nxa_internal->hash() };
}

String Blob::base64String() const
{
    return nxa_internal->base64String();
}

String Blob::description(const DescriberState& state) const
{
    return nxa_internal->description();
}
