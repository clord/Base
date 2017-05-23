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
#include "Base/MutableString.hpp"
#include "Base/Internal/MutableString.hpp"
#include "Base/String.hpp"
#include "Base/Array.hpp"
#include "Base/Assert.hpp"

using namespace NxA;

uinteger32 MutableStringInternal::hash() const
{
    return String::hashFor(this->asUTF8());
}

const character* MutableStringInternal::stringArgumentAsCharacter(std::string& cppstring)
{
    return cppstring.c_str();
}

const character* MutableStringInternal::stringArgumentAsCharacter(String& nxastring)
{
    return nxastring.asUTF8();
}

const character* MutableStringInternal::stringArgumentAsCharacter(MutableString& nxastring)
{
    return nxastring.asUTF8();
}

const character* MutableStringInternal::stringArgumentAsCharacter(MutableStringInternal& nxastring)
{
    return nxastring.asUTF8();
}

const character* MutableStringInternal::stringArgumentAsCharacter(const std::string& cppstring)
{
    return cppstring.c_str();
}

const character* MutableStringInternal::stringArgumentAsCharacter(const String& nxastring)
{
    return nxastring.asUTF8();
}

const character* MutableStringInternal::stringArgumentAsCharacter(const MutableString& nxastring)
{
    return nxastring.asUTF8();
}

const character* MutableStringInternal::stringArgumentAsCharacter(const MutableStringInternal& nxastring)
{
    return nxastring.asUTF8();
}

NxA::boolean MutableStringInternal::hasNonPrintableCharacters() const
{
    const character* input = this->asUTF8();
    for (count index = 0; index < this->length(); ++index) {
        byte value = input[index];
        if (((value <= 0x1f) && (value != 0x09) && (value != 0x0a) && (value != 0x0d)) || (value == 0x7f)) {
            return true;
        }
    }

    return false;
}

count MutableStringInternal::indexOfFirstOccurenceOf(const String& other) const
{
    return this->indexOfFirstOccurenceOf(other.asUTF8());
}

count MutableStringInternal::indexOfFirstOccurenceOf(const character* other) const
{
    NXA_ASSERT_NOT_NULL(other);

    size_t pos = this->find(other);
    if (pos == std::string::npos) {
        return this->length();
    }

    return pos;
}

count MutableStringInternal::indexOfLastOccurenceOf(const String& other) const
{
    return this->indexOfLastOccurenceOf(other.asUTF8());
}

count MutableStringInternal::indexOfLastOccurenceOf(const character* other) const
{
    NXA_ASSERT_NOT_NULL(other);

    size_t pos = this->rfind(other);
    if (pos == std::string::npos) {
        return this->length();
    }

    return pos;
}

void MutableStringInternal::replaceOccurenceOfStringWith(const character* occurence, const character* replacement)
{
    NXA_ASSERT_NOT_NULL(occurence);
    NXA_ASSERT_NOT_NULL(replacement);

    boost::replace_all(*static_cast<std::string*>(this), occurence, replacement);
}

std::shared_ptr<MutableStringInternal> MutableStringInternal::stringWithRepeatedCharacter(count number, character specificCharacter)
{
    std::string asCStr(number, specificCharacter);
    return std::make_shared<MutableStringInternal>(std::move(asCStr));
}

std::shared_ptr<MutableStringInternal> MutableStringInternal::stringWithUTF16AtAndSize(const byte* data, count size)
{
    if (size < 2) {
        return std::make_shared<MutableStringInternal>();
    }

    Blob local;

    if (Platform::endianOrder == Platform::LitleEndian) {
        local = Platform::convertEndiannessOfUInteger16From(Blob::blobWithMemoryAndSize(data, size));
        data = local.data();
    }

    count length = size / 2;
    auto characters = reinterpret_cast<const integer16*>(data);

    std::wstring_convert<std::codecvt_utf8_utf16<char16_t>, char16_t> convert;
    return std::make_shared<MutableStringInternal>(
        convert.to_bytes(reinterpret_cast<const char16_t*>(characters), reinterpret_cast<const char16_t*>(characters + length)));
}


std::shared_ptr<MutableStringInternal> MutableStringInternal::stringWithUTF16(const wchar_t* other, count num)
{
	// TODO: Ideally not byte, but wchar_t
	return MutableStringInternal::stringWithUTF16AtAndSize(reinterpret_cast<const byte*>(other), num);
}

std::shared_ptr<MutableStringInternal> MutableStringInternal::stringWithUTF16(const Blob& other)
{
    return MutableStringInternal::stringWithUTF16AtAndSize(other.data(), other.size());
}

// -- Operators

bool MutableStringInternal::operator==(const character* other) const
{
    return this->std::string::compare(other) == 0;
}
bool MutableStringInternal::operator==(const MutableStringInternal& other) const
{
    return this->std::string::compare(other) == 0;
}

// -- Instance Methods
count MutableStringInternal::length() const
{
    return this->size();
}

integer32 MutableStringInternal::compare(const char* other) const
{
    return this->std::string::compare(other);
}

integer32 MutableStringInternal::compare(const MutableStringInternal& other) const
{
    return this->std::string::compare(static_cast<const std::string&>(other));
}

integer MutableStringInternal::integerValue() const
{
    return ::atoi(this->c_str());
}

decimal3 MutableStringInternal::decimalValue() const
{
    return decimal3(*this);
}

const std::string& MutableStringInternal::asStdString() const
{
    return *this;
}

const character* MutableStringInternal::asUTF8() const
{
    return this->c_str();
}

Blob MutableStringInternal::asUTF16() const
{
    std::wstring_convert<std::codecvt_utf8_utf16<char16_t>, char16_t> convert;
    std::u16string u16 = convert.from_bytes(this->c_str());

    auto newBlob = Blob::blobWithMemoryAndSize(reinterpret_cast<const byte*>(reinterpret_cast<const integer16*>(u16.c_str())), u16.length() * 2);
    if (Platform::endianOrder == Platform::LitleEndian) {
        newBlob = Platform::convertEndiannessOfUInteger16From(newBlob);
    }

    return newBlob;
}

void MutableStringInternal::append(const MutableStringInternal& other)
{
    this->std::string::append(other);
}

void MutableStringInternal::append(const character* other)
{
    this->std::string::append(other);
}

void MutableStringInternal::append(const character other)
{
    this->std::string::operator+=(other);
}

std::shared_ptr<MutableStringInternal> MutableStringInternal::stringByAppending(const MutableStringInternal& other) const
{
    return {std::make_shared<MutableStringInternal>(*this + other)};
}

std::vector<String> MutableStringInternal::splitBySeparator(character separator) const
{
    std::vector<String> results;
    std::stringstream stream(this->asUTF8());
    std::string line;

    while (getline(stream, line, separator)) {
        results.emplace_back(line);
    }

    return results;
}

std::shared_ptr<MutableStringInternal> MutableStringInternal::utfSeek(count skip) const
{
    NXA_ASSERT_TRUE(skip >= 0);

    if (skip > this->length()) {
        return {std::make_shared<MutableStringInternal>()};
    }

    auto rawPointer = this->c_str();
    auto startPointer = utf8seek(rawPointer, this->length(), rawPointer, skip, SEEK_SET);

    return {std::make_shared<MutableStringInternal>(startPointer)};
}

std::shared_ptr<MutableStringInternal> MutableStringInternal::subString(count start, count end) const
{
    NXA_ASSERT_TRUE(start <= end);

    if ((end == -1) || (end > this->length())) {
        end = this->length();
    }

    if (start >= this->length()) {
        return {std::make_shared<MutableStringInternal>()};
    }

    return {std::make_shared<MutableStringInternal>(this->substr(start, end - start))};
}

std::shared_ptr<MutableStringInternal> MutableStringInternal::lowerCaseString() const
{
    auto inputLength = this->length();
    if (!inputLength) {
        return {std::make_shared<MutableStringInternal>()};
    }

    auto input = this->c_str();

	count convertedSize;
	integer32 errors;
	size_t i;

	if ((convertedSize = utf8tolower(input, inputLength, NULL, 0, UTF8_LOCALE_DEFAULT, &errors)) == 0 || errors != UTF8_ERR_NONE) {
		return { std::make_shared<MutableStringInternal>() };
	}

	auto converted = static_cast<char*>(alloca(convertedSize + 1));

	if (utf8tolower(input, inputLength, converted, convertedSize, UTF8_LOCALE_DEFAULT, &errors) == 0 || errors != UTF8_ERR_NONE) {
		return { std::make_shared<MutableStringInternal>() };
	}

	converted[convertedSize] = 0;
	
	return { std::make_shared<MutableStringInternal>(converted, convertedSize) };
}

std::shared_ptr<MutableStringInternal> MutableStringInternal::upperCaseString() const
{
	auto inputLength = this->length();
	if (!inputLength) {
		return { std::make_shared<MutableStringInternal>() };
	}

	auto input = this->c_str();

	count convertedSize;
	integer32 errors;
	size_t i;

	if ((convertedSize = utf8toupper(input, inputLength, NULL, 0, UTF8_LOCALE_DEFAULT, &errors)) == 0 || errors != UTF8_ERR_NONE) {
		return { std::make_shared<MutableStringInternal>() };
	}

	auto converted = static_cast<char*>(alloca(convertedSize + 1));

	if (utf8toupper(input, inputLength, converted, convertedSize, UTF8_LOCALE_DEFAULT, &errors) == 0 || errors != UTF8_ERR_NONE) {
		return { std::make_shared<MutableStringInternal>() };
	}

	converted[convertedSize] = 0;

	return { std::make_shared<MutableStringInternal>(converted, convertedSize) };
}

NxA::boolean MutableStringInternal::hasPrefix(const MutableStringInternal& prefix) const
{
    return this->find(prefix) == 0;
}

NxA::boolean MutableStringInternal::hasPrefix(const character* prefix) const
{
    NXA_ASSERT_NOT_NULL(prefix);

    return this->find(prefix) == 0;
}

NxA::boolean MutableStringInternal::hasPostfix(const MutableStringInternal& postfix) const
{
    size_t pos = this->find(postfix);
    if (pos == std::string::npos) {
        return false;
    }

    return pos == (this->length() - postfix.length());
}

NxA::boolean MutableStringInternal::hasPostfix(const character* postfix) const
{
    NXA_ASSERT_NOT_NULL(postfix);

    size_t pos = this->rfind(postfix);
    if (pos == std::string::npos) {
        return false;
    }

    count length = strlen(postfix);
    return pos == (this->length() - length);
}

NxA::boolean MutableStringInternal::contains(const MutableStringInternal& other) const
{
    return this->find(other) != std::string::npos;
}

NxA::boolean MutableStringInternal::contains(const character* other) const
{
    return this->find(other) != std::string::npos;
}

std::shared_ptr<MutableStringInternal> MutableStringInternal::stringByFilteringNonPrintableCharactersIn(const String& other)
{
    std::string filtered;
    filtered.reserve(other.length());

    const character* input = other.asUTF8();

    for (count index = 0; index < other.length(); ++index) {
        byte value = input[index];
        if (((value <= 0x1f) && (value != 0x09) && (value != 0x0a) && (value != 0x0d)) || (value == 0x7f)) {
            continue;
        }

        filtered += value;
    }

    return {std::make_shared<MutableStringInternal>(std::move(filtered))};
}
