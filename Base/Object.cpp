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

#include "Base/Object.hpp"
#include "Base/String.hpp"
#include "Base/Internal/InternalObject.hpp"

using namespace NxA;

#pragma mark Constructors

Object::Object(NxA::Pointer<InternalObject> initial_internal) :
    internalImplementation(initial_internal),
    internal(&(*initial_internal))
{
}

#pragma mark Static Methods

Pointer<InternalObject> Object::makeInternal(void)
{
    return NxA::Pointer<InternalObject>::dynamicCastFrom(InternalObject::makeShared());
}

uinteger32 Object::staticClassHash(void)
{
    static uinteger32 hash = String::hashFor(Object::staticClassName());
    return hash;
}

#pragma mark Instance Methods

String::Pointer Object::description(void) const
{
    return String::stringWithFormat("<%s at 0x%08lx>", this->className(), this);
}
