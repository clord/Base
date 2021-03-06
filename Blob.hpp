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

#define NXA_OBJECT_CLASS                    Blob
#define NXA_OBJECT_INTERNAL_CLASS           MutableBlobInternal
#define NXA_OBJECT_HAS_A_CUSTOM_CLASS_NAME

#include <Base/ObjectForwardDeclarations.ipp>
    
class MutableBlob;
class String;
class DescriberState;

class Blob : protected NXA_OBJECT
{
    #include <Base/ObjectDeclaration.ipp>

    friend MutableBlob;

public:
    // -- Constructors/Destructors
    Blob();
    Blob(const MutableBlob&);
    Blob(MutableBlob&&);

    // -- Factory Methods
    static Blob blobWithMemoryAndSize(const byte*, count);
    static Blob blobWithBase64String(const String&);
    static Blob blobWithStringWithTerminator(const String&);
    static Blob blobWithStringWithoutTerminator(const String&);

    // -- Class Methods
    static Blob hashFor(const byte*, count);
    static String base64StringFor(const byte*, count);

    // -- Operators
    const byte& operator[](count) const;

    // -- Instance Methods
    const character* className() const
    {
        return Blob::staticClassNameConst;
    }

    boolean isEmpty() const
    {
        return (this->size() == 0);
    }

    count size() const;

    const byte* data() const;

    Blob hash();
    String base64String() const;
};

}
