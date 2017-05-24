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
#include <Base/WeakReference.hpp>

namespace NxA {

#define NXA_OBJECT_CLASS                    MutableBlob
#define NXA_OBJECT_HAS_A_CUSTOM_CLASS_NAME

#include <Base/ObjectForwardDeclarations.ipp>

// -- Forward Declarations
class String;
class Blob;
class DescriberState;

// -- Public Interface
class MutableBlob : protected NXA_OBJECT
{
    #include <Base/ObjectDeclaration.ipp>

    friend Blob;

public:
    // -- Constructors/Destructors
    MutableBlob();
    MutableBlob(const Blob&);

    // -- Factory Methods
    static MutableBlob blobWithCapacity(count);
    static MutableBlob blobWithMemoryAndSize(const byte*, count);
    static MutableBlob blobWithBase64String(const String&);
    static MutableBlob blobWithStringWithTerminator(const String&);
    static MutableBlob blobWithStringWithoutTerminator(const String&);

    // -- Operators
    const byte& operator[](count) const;
    byte& operator[](count);
    bool operator==(const Blob& other) const;
    inline bool operator!=(const Blob& other) const
    {
        return !this->operator==(other);
    }

    // -- Instance Methods
    const character* className() const
    {
        return MutableBlob::staticClassNameConst;
    }
    
    count size() const;

    const byte* data() const;
    byte* data();

    void fillWithZeros();

    Blob hash();
    String base64String() const;

    void append(const Blob&);
    void appendMemoryWithSize(const byte*, count);
    void appendWithStringTermination(const character*);
    void appendWithoutStringTermination(const character*);
    void append(const character);

    void removeAll();

    void padToAlignment(count);
};
    
}
