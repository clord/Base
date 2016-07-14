//
//  Copyright (c) 2015-2016 Next Audio Labs, LLC. All rights reserved.
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
#include <Base/GeneratedObjectCode.hpp>

#pragma mark Forward Declarations

namespace NxA {

class Blob;
class String;
struct StringInternal;
template <class T> class Array;

#pragma mark Public Interface

class MutableString {
    NXA_GENERATED_INTERNAL_OBJECT_FORWARD_DECLARATION_USING(StringInternal);
    NXA_GENERATED_OBJECT_METHODS_DECLARATIONS_FOR(MutableString);

    friend String;
    
public:
    #pragma mark Constructors/Destructors
    MutableString();
    MutableString(const String&);
    MutableString(const character*, count);
    explicit MutableString(const std::string &);

    // -- Provide a statically-sized character constant, which saves the runtime from computing the length.
    template<count size> explicit MutableString(const character (&chars)[size]) : MutableString{ chars, size - 1 } { }

    #pragma mark Factory Methods
    static MutableString stringWithFormat(const character*, ...);
    static MutableString stringWith(const character* other)
    {
        return { other, strlen(other) };
    }
    static MutableString stringWithUTF16(const Blob&);

    #pragma mark Operators
    bool operator==(const String& other) const;
    bool operator!=(const String& other) const
    {
        return !this->operator==(other);
    }
    bool operator==(const character*) const;
    bool operator!=(const character* other) const
    {
        return !this->operator==(other);
    }

    #pragma mark Instance Methods
    count length() const;
    boolean isEmpty() const
    {
        return this->length() == 0;
    }
    uinteger32 hash() const;
    integer integerValue() const;

    const std::string& asStdString() const;
    const character* asUTF8() const;
    Blob asUTF16() const;

    void append(const String&);
    void append(const character*);

    Array<String> splitBySeparator(char) const;
    MutableString subString(count, count = -1) const;
    MutableString utfSeek(count) const;
    MutableString lowerCaseString() const;
    MutableString upperCaseString() const;

    boolean hasPrefix(const String&) const;
    boolean hasPrefix(const character*) const;
    boolean hasPostfix(const String&) const;
    boolean hasPostfix(const character*) const;
    boolean contains(const String&) const;
    boolean contains(const character*) const;
    boolean hasNonPrintableCharacters() const;

    count indexOfFirstOccurenceOf(const String&) const;
    count indexOfFirstOccurenceOf(const character*) const;
    count indexOfLastOccurenceOf(const String&) const;
    count indexOfLastOccurenceOf(const character*) const;

    void replaceOccurenceOfStringWith(const character*, const character*);
};

}
