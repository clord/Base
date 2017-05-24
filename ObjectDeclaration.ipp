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

protected:

// -- Forward declarations
friend WeakReference<NXA_OBJECT_CLASS>;

#ifdef NXA_INTERNAL_OBJECT_CLASS
    private:
        using Internal = NXA_INTERNAL_OBJECT_CLASS;
    protected:
#else
    struct Internal;
#endif

#if !defined(NXA_INTERNAL_OBJECT_IS_DERIVED)
    // -- Protected Instance Variables
    std::shared_ptr<Internal> internal;
#endif

// -- Protected Constructors & Destructors
NXA_OBJECT_CLASS(std::shared_ptr<Internal>&& other);

public:

// -- Constructors & Destructors
#ifdef NXA_INTERNAL_OBJECT_SHOULD_NEVER_BE_COPIED
    NXA_OBJECT_CLASS(const NXA_OBJECT_CLASS&) = delete;
#else
    NXA_OBJECT_CLASS(const NXA_OBJECT_CLASS&);
#endif

NXA_OBJECT_CLASS(NXA_OBJECT_CLASS&&);
NXA_OBJECT_CLASS(NXA_OBJECT_CLASS&);
~NXA_OBJECT_CLASS();

// -- Static Methods
static const character* staticClassName()
{
    return NXA_OBJECT_CLASS::staticClassNameConst;
}

// -- Operators
NXA_OBJECT_CLASS& operator=(NXA_OBJECT_CLASS&&);
NXA_OBJECT_CLASS& operator=(const NXA_OBJECT_CLASS&);
bool operator==(const NXA_OBJECT_CLASS& other) const;
bool operator!=(const NXA_OBJECT_CLASS& other) const
{
    return !this->operator==(other);
}

// -- Instance Methods
const character* className() const;
boolean classNameIs(const character* className) const;

String description(const DescriberState&) const;
String description() const;

// -- Since this is placed at the beginning of the class definition,
// -- we restore the private setting for subsequent content.
private:

// -- Clean up any defines that were used.
#undef NXA_OBJECT_CLASS
#undef NXA_INTERNAL_OBJECT_CLASS
#undef NXA_INTERNAL_OBJECT_SHOULD_NEVER_BE_COPIED
#undef NXA_INTERNAL_OBJECT_IS_DERIVED
