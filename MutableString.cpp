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

#include <Base/Types.hpp>
#include <Base/Describe.hpp>
#include <Base/MutableString.hpp>
#include <Base/String.hpp>
#include <Base/Internal/MutableStringInternal.hpp>
#include <Base/Exception.hpp>
#include <Base/Platform.hpp>
#include <Base/Assert.hpp>
#include <Base/Array.hpp>

using namespace NxA;

#define NXA_OBJECT_CLASS                    MutableString
#define NXA_OBJECT_HAS_A_CUSTOM_CLASS_NAME

#include <Base/ObjectDefinition.ipp>

// -- Constructors/Destructors

MutableString::MutableString() : std::shared_ptr<Internal>{ std::make_shared<Internal>() } { }
MutableString::MutableString(const String& other) : std::shared_ptr<Internal>{ std::make_shared<Internal>(other.asStdString()) } { }
MutableString::MutableString(const std::string& other) : std::shared_ptr<Internal>{ std::make_shared<Internal>(other) } { }
MutableString::MutableString(std::string&& other) : std::shared_ptr<Internal>{ std::make_shared<Internal>(std::move(other)) } { }
MutableString::MutableString(const character* other, size_t size) : std::shared_ptr<Internal>{ std::make_shared<Internal>(other, size) } { }

// -- Factory Methods

MutableString MutableString::stringWithUTF16(const Blob& other)
{
    return { Internal::stringWithUTF16(other) };
}

MutableString MutableString::stringWithRepeatedCharacter(count number, character specificChar)
{
    return { Internal::stringWithRepeatedCharacter(number, specificChar) };
}

template <template <typename> class Implementation>
MutableString MutableString::stringByJoiningArrayWithString(const Array<String, Implementation>& array, String join)
{
    return { Internal::stringByJoiningArrayWithString(array, *NXA_INTERNAL_OBJECT_FOR(join)) };
}

// -- Operators

bool MutableString::operator==(const String& other) const
{
    return nxa_internal->operator==(*NXA_INTERNAL_OBJECT_FOR(other));
}

bool MutableString::operator==(const character* other) const
{
    return nxa_internal->operator==(other);
}

// -- Instance Methods

String MutableString::description(const DescriberState& state) const
{
    return String(*nxa_internal);
}

count MutableString::length() const
{
    return nxa_internal->length();
}

uinteger32 MutableString::hash() const
{
    return nxa_internal->hash();
}

integer MutableString::integerValue() const
{
    return nxa_internal->integerValue();
}

decimal3 MutableString::decimalValue() const
{
    return nxa_internal->decimalValue();
}

const std::string& MutableString::asStdString() const
{
    return nxa_internal->asStdString();
}

const character* MutableString::asUTF8() const
{
    return nxa_internal->asUTF8();
}

Blob MutableString::asUTF16() const
{
    return nxa_internal->asUTF16();
}

void MutableString::append(const String& other)
{
    nxa_internal->append(*NXA_INTERNAL_OBJECT_FOR(other));
}

void MutableString::append(const character* other)
{
    nxa_internal->append(other);
}

void MutableString::append(character other)
{
    nxa_internal->append(other);
}

Array<String> MutableString::splitBySeparator(character separator) const
{
    return nxa_internal->splitBySeparator(separator);
}

MutableString MutableString::utfSeek(count skip) const
{
    return { nxa_internal->utfSeek(skip) };
}

MutableString MutableString::subString(count start, count end) const
{
    return { nxa_internal->subString(start, end) };
}

MutableString MutableString::lowerCaseString() const
{
    return { nxa_internal->lowerCaseString() };
}

MutableString MutableString::upperCaseString() const
{
    return { nxa_internal->upperCaseString() };
}

boolean MutableString::hasPrefix(const String& prefix) const
{
    return nxa_internal->hasPrefix(*NXA_INTERNAL_OBJECT_FOR(prefix));
}

boolean MutableString::hasPrefix(const character* prefix) const
{
    return nxa_internal->hasPrefix(prefix);
}

boolean MutableString::hasPostfix(const String& postfix) const
{
    return nxa_internal->hasPostfix(*NXA_INTERNAL_OBJECT_FOR(postfix));
}

boolean MutableString::hasPostfix(const character* postfix) const
{
    return nxa_internal->hasPostfix(postfix);
}

boolean MutableString::contains(const String& other) const
{
    return nxa_internal->contains(*NXA_INTERNAL_OBJECT_FOR(other));
}

boolean MutableString::contains(const character* other) const
{
    return nxa_internal->contains(other);
}

boolean MutableString::hasNonPrintableCharacters() const
{
    return nxa_internal->hasNonPrintableCharacters();
}

count MutableString::indexOfFirstOccurenceOf(const String& other) const
{
    return nxa_internal->indexOfFirstOccurenceOf(other);
}

count MutableString::indexOfFirstOccurenceOf(const character* other) const
{
    return nxa_internal->indexOfFirstOccurenceOf(other);
}

count MutableString::indexOfLastOccurenceOf(const String& other) const
{
    return nxa_internal->indexOfLastOccurenceOf(other);
}

count MutableString::indexOfLastOccurenceOf(const character* other) const
{
    return nxa_internal->indexOfLastOccurenceOf(other);
}

void MutableString::replaceOccurenceOfStringWith(const character* occurence, const character* replacement)
{
    return nxa_internal->replaceOccurenceOfStringWith(occurence, replacement);
}
