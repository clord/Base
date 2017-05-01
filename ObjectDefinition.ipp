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

// -- Constructors & Destructors

#ifdef NXA_INTERNAL_OBJECT_IS_VIRTUAL
    #ifdef NXA_INTERNAL_OBJECT_IS_DERIVED_FROM_CLASS
        NXA_OBJECT_CLASS::NXA_OBJECT_CLASS(const NXA_OBJECT_CLASS& other) : NXA_INTERNAL_OBJECT_IS_DERIVED_FROM_CLASS{ std::make_shared<Internal>(static_cast<NXA_OBJECT_CLASS::Internal&>(*other.internal)) } { }
    #else
        NXA_OBJECT_CLASS::NXA_OBJECT_CLASS(const NXA_OBJECT_CLASS& other) : internal{ other.internal->baseInternalSharedPointer() } { }
    #endif
#elif defined(NXA_OBJECT_IS_IMMUTABLE)
    NXA_OBJECT_CLASS::NXA_OBJECT_CLASS(const NXA_OBJECT_CLASS&) = default;
#endif

NXA_OBJECT_CLASS::NXA_OBJECT_CLASS(NXA_OBJECT_CLASS&&) = default;
NXA_OBJECT_CLASS::NXA_OBJECT_CLASS(NXA_OBJECT_CLASS&) = default;
#ifdef NXA_INTERNAL_OBJECT_IS_DERIVED_FROM_CLASS
    NXA_OBJECT_CLASS::NXA_OBJECT_CLASS(std::shared_ptr<Internal>&& other) : NXA_INTERNAL_OBJECT_IS_DERIVED_FROM_CLASS{ std::move(other) } { }
#else
    NXA_OBJECT_CLASS::NXA_OBJECT_CLASS(std::shared_ptr<Internal>&& other) : internal{ std::move(other) } { }
#endif
NXA_OBJECT_CLASS::~NXA_OBJECT_CLASS() = default;

// -- Operators

NXA_OBJECT_CLASS& NXA_OBJECT_CLASS::operator=(NXA_OBJECT_CLASS&&) = default;
NXA_OBJECT_CLASS& NXA_OBJECT_CLASS::operator=(const NXA_OBJECT_CLASS&) = default;
boolean NXA_OBJECT_CLASS::operator==(const NXA_OBJECT_CLASS& other) const
{
    if (internal == other.internal) {
        return true;
    }

    return *internal == *(other.internal);
}

// -- Instance Methods

const character* NXA_OBJECT_CLASS::className() const
{
    return internal->className();
}
bool NXA_OBJECT_CLASS::classNameIs(const character* className) const
{
    return !::strcmp(internal->className(), className);
}

String NXA_OBJECT_CLASS::description() const
{
    DescriberState state;
    return this->description(state);
}

#undef NXA_OBJECT_CLASS
#undef NXA_OBJECT_IS_IMMUTABLE
#undef NXA_INTERNAL_OBJECT_IS_VIRTUAL
#undef NXA_INTERNAL_OBJECT_IS_DERIVED_FROM_CLASS
