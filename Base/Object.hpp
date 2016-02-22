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

#include "Base/Uncopyable.hpp"
#include "Base/GeneratedObjectCode.hpp"

NXA_ENTER_NAMESPACE(NxA);

NXA_GENERATED_FORWARD_DECLARATIONS_FOR_CLASS(Object);

class String;

class Object : private Uncopyable, public NXA_ENABLE_OBJECT_SHARED_FROM_THIS(Object) {
    NXA_GENERATED_OBJECT_DECLARATIONS_FOR(NxA, Object);

public:
    #pragma mark Class Methods
    static const character* staticClassName(void)
    {
        return "NxA::Object";
    }
    static uinteger32 staticClassHash(void);

    #pragma mark Operators
    virtual bool operator==(const NxA::Object& other) const
    {
        NXA_ALOG("Undefined operator==() for class '%s'.", this->className());
        return false;
    }
    virtual bool operator!=(const NxA::Object& other) const
    {
        return !this->operator==(other);
    }

    #pragma mark Instance Methods
    virtual const character* className(void) const
    {
        return Object::staticClassName();
    }

    virtual NxA::Pointer<NxA::String> description(void) const;
};

NXA_EXIT_NAMESPACE;
