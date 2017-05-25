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

#pragma once

#include <Base/Types.hpp>
#include <Base/Internal/MutableStringInternal.hpp>

namespace NxA {

#define NXA_OBJECT_CLASS                            String
#define NXA_OBJECT_INTERNAL_CLASS                   MutableStringInternal
#define NXA_OBJECT_HAS_A_CUSTOM_CLASS_NAME

#include <Base/ObjectForwardDeclarations.ipp>

// -- Forward Declarations
class MutableString;
class Blob;

// -- Public Interface
class String : protected NXA_OBJECT
{
    #include <Base/ObjectDeclaration.ipp>

    friend MutableString;
    friend bool operator<(const String&, const String&);

public:
    // -- Constants
    enum class UTF8Flag {
        NeedsNormalizing,
        IsNormalized,
    };

    // -- Constructors/Destructors
    String();
    String(const character*, count);
    String(MutableString&&);
    String(const MutableString&);
    explicit String(const std::string&);
    explicit String(const std::string&&);

    // -- Provide a statically-sized character constant, which saves the runtime from computing the length.
    template <count size>
    String(const character (&chars)[size]) : String{chars, size - 1} { }

    // -- Factory Methods
    template <typename... FormatArguments>
    static String stringWithFormat(String format, FormatArguments&&... formatArguments)
    {
        return String{Internal::stringWithFormat(256, format.asUTF8(), Internal::stringArgumentAsCharacter(formatArguments)...)};
    }

    static String stringWithFormat(String format)
    {
        return format;
    }

    static String stringWithUTF8(const character* other, UTF8Flag normalize = UTF8Flag::IsNormalized);
    static String stringWithMemoryAndLength(const character* other, count length)
    {
        return { other, length };
    }

    static String stringWithRepeatedCharacter(count, character);

    static String stringWithUTF16AtAndSize(const byte*, count);

    static String stringWithUTF16(const Blob&);

    static String stringByFilteringNonPrintableCharactersIn(const String&);

    template <typename ArrayType>
    static String stringByJoiningArrayWithString(const ArrayType& array, String join)
    {
        return { Internal::stringByJoiningArrayWithString(array, *NXA_INTERNAL_OBJECT_FOR(join)) };
    }

    // -- Class Methods
    static uinteger32 hashFor(const character*);
    static count lengthOf(const character* str);

    // -- Operators
    bool operator==(const character*) const;
    inline bool operator!=(const character* other) const
    {
        return !this->operator==(other);
    }
    bool operator==(const MutableString& other) const;
    inline bool operator!=(const MutableString& other) const
    {
        return !this->operator==(other);
    }

    // -- Instance Methods
    const character* className() const
    {
        return String::staticClassNameConst;
    }
    
    count length() const;
    boolean isEmpty() const
    {
        return this->length() == 0;
    }
    uinteger32 hash() const;
    integer32 compare(const String& other) const;
    integer32 compare(const char* other) const;
    integer integerValue() const;
    decimal3 decimalValue() const;

    const std::string& asStdString() const;
    const character* asUTF8() const;
    Blob asUTF16() const;

    String stringByAppending(const String&) const;

    Array<String> splitBySeparator(char) const;
    String subString(count, count = -1) const;
    String utfSeek(count) const;
    String lowerCaseString() const;
    String upperCaseString() const;

    boolean hasPrefix(const String&) const;
    boolean hasPrefix(const character*) const;
    boolean hasPostfix(const String&) const;
    boolean hasPostfix(const character*) const;
    boolean contains(const String&) const;
    boolean contains(const character*) const;
    boolean hasNonPrintableCharacters() const;

    count indexOfFirstOccurenceOf(const String&) const;
    count indexOfLastOccurenceOf(const String&) const;
    count indexOfFirstOccurenceOf(const character*) const;
    count indexOfLastOccurenceOf(const character*) const;

    template <typename Char, typename CharTraits>
    friend inline ::std::basic_ostream<Char, CharTraits>& operator<<(::std::basic_ostream<Char, CharTraits>& os, const String& self)
    {
        return (os << self.asStdString());
    }
};

// -- Operators
bool operator<(const String&, const String&);
String operator"" _String(const character* str, count length);
    
}
