//
//  Copyright (c) 2015 Next Audio Labs, LLC. All rights reserved.
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

#include "Base/String.hpp"
#include "Base/Blob.hpp"
#include "Base/Platform.hpp"
#include "Base/Internal/String.hpp"

#include <cstdio>
#include <codecvt>
#include <locale>
#include <sstream>

NXA_GENERATED_IMPLEMENTATION_IN_NAMESPACE_FOR_CLASS_WITH_PARENT(NxA, String, Object);

using namespace NxA;

#pragma mark Factory Methods

String::Pointer String::string(void)
{
    auto newString = String::makeShared();
    newString->internal->value = "";

    return newString;
}

String::Pointer String::stringWith(const character* other)
{
    auto newString = String::makeShared();
    newString->internal->value = other;

    return newString;
}

String::Pointer String::stringWith(const String& other)
{
    auto newString = String::makeShared();
    newString->internal->value = other.internal->value;

    return newString;
}

String::Pointer String::stringWithFormat(const character* format, ...)
{
    constexpr count formatStringBufferSize = 256;
    char buffer[formatStringBufferSize];

    va_list args;
    va_start(args, format);
    vsnprintf(buffer, formatStringBufferSize, format, args);
    va_end(args);

    auto newString = String::makeShared();
    newString->internal->value = buffer;

    return newString;
}

String::Pointer String::stringWithUTF16(const Blob& other)
{
    auto source = other.pointer();

    if (Platform::endianOrder == Platform::LitleEndian) {
        source = Platform::convertEndiannessOfUInteger16From(other);
    }

    const integer16* characters = reinterpret_cast<const integer16*>(source->data());
    count length = source->size() / 2;

    auto newString = String::makeShared();

    std::wstring_convert<std::codecvt_utf8_utf16<char16_t>,char16_t> convert;
    newString->internal->value = convert.to_bytes(reinterpret_cast<const char16_t*>(characters), reinterpret_cast<const char16_t*>(characters + length));

    return newString;
}

#pragma mark Operators

String::operator const character*() const
{
    return internal->value.c_str();
}

String::operator const character*()
{
    return internal->value.c_str();
}

boolean String::isEqualTo(const String& other) const
{
    return internal->value == other.internal->value;
}

boolean String::isEqualTo(const character* other) const
{
    return internal->value == other;
}

#pragma mark mark Instance Methods

count String::length(void) const
{
    return internal->value.size();
}

String::Pointer String::description(void) const
{
    return String::stringWith(*this);
}

const character* String::toUTF8(void) const
{
    return internal->value.c_str();
}

Blob::Pointer String::toUTF16(void) const
{
    std::wstring_convert<std::codecvt_utf8_utf16<char16_t>,char16_t> convert;
    std::u16string u16 = convert.from_bytes(internal->value.c_str());

    auto newBlob = Blob::blobWithMemoryAndSize(reinterpret_cast<const byte*>(reinterpret_cast<const integer16*>(u16.c_str())),
                                               u16.length() * 2);
    if (Platform::endianOrder == Platform::LitleEndian) {
        newBlob = Platform::convertEndiannessOfUInteger16From(newBlob);
    }

    return newBlob;
}

void String::append(const String& other)
{
    internal->value.append(other);
}

void String::append(const character* other)
{
    internal->value.append(other);
}

String::Array::Pointer String::splitBySeperator(char seperator) const
{
    auto results = String::Array::array();
    std::stringstream stream(this->toUTF8());
    std::string line;

    while(getline(stream, line, seperator)) {
        results->append(String::stringWith(line.c_str()));
    }

    return results;
}

String::Pointer String::subString(count start, count end) const
{
    NXA_ASSERT_TRUE(start <= end);

    if ((end == -1) || (end > this->length())) {
        end = this->length();
    }

    if (start >= this->length()) {
        return String::string();
    }

    auto newString = String::makeShared();
    newString->internal->value = internal->value.substr(start, end - start);
    
    return newString;
}

boolean String::hasPrefix(const String& prefix) const
{
    return this->hasPrefix(prefix.operator const char *());
}

boolean String::hasPostfix(const String& postfix) const
{
    size_t pos = internal->value.rfind(postfix);
    if (pos == std::string::npos) {
        return false;
    }

    return pos == (this->length() - postfix.length());
}

boolean String::hasPrefix(const character* prefix) const
{
    return internal->value.find(prefix) == 0;
}

boolean String::hasPostfix(const character* postfix) const
{
    size_t pos = internal->value.rfind(postfix);
    if (pos == std::string::npos) {
        return false;
    }

    count length = strlen(postfix);
    return pos == (this->length() - length);
}

count String::indexOfFirstOccurenceOf(const String& other) const
{
    return this->indexOfFirstOccurenceOf(other.operator const character *());
}

count String::indexOfLastOccurenceOf(const String& other) const
{
    return this->indexOfLastOccurenceOf(other.operator const character *());
}

count String::indexOfFirstOccurenceOf(const char* other) const
{
    size_t pos = internal->value.find(other);
    if (pos == std::string::npos) {
        return this->length();
    }

    return pos;
}

count String::indexOfLastOccurenceOf(const char*  other) const
{
    size_t pos = internal->value.rfind(other);
    if (pos == std::string::npos) {
        return this->length();
    }

    return pos;
}
