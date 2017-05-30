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

#if !defined(NXA_OBJECT_INTERNAL_BASE_CLASS)
    #define NXA_CAT_SUB_MACRO(A, B) A ## B
    #define NXA_CAT(A, B) NXA_CAT_SUB_MACRO(A, B)
    #define NXA_OBJECT_INTERNAL_BASE_CLASS NXA_CAT(NXA_OBJECT_BASE_CLASS, Internal)
    #undef NXA_CAT_SUB_MACRO
    #undef NXA_CAT
#endif

// -- Constructors & Destructors
#ifdef NXA_INTERNAL_OBJECT_SHOULD_NEVER_BE_COPIED
    #ifdef NXA_OBJECT_BASE_CLASS
        NXA_OBJECT_CLASS::NXA_OBJECT_CLASS(const NXA_OBJECT_CLASS& other) : NXA_OBJECT_BASE_CLASS{ other } { }
    #else
        NXA_OBJECT_CLASS::NXA_OBJECT_CLASS(const NXA_OBJECT_CLASS& other) : std::shared_ptr<Internal>{ other } { }
    #endif
#else
    #ifdef NXA_OBJECT_BASE_CLASS
        NXA_OBJECT_CLASS::NXA_OBJECT_CLASS(const NXA_OBJECT_CLASS& other) : NXA_OBJECT_BASE_CLASS{ std::make_shared<NXA_OBJECT_INTERNAL_BASE_CLASS>(*other) } { }
    #else
        NXA_OBJECT_CLASS::NXA_OBJECT_CLASS(const NXA_OBJECT_CLASS& other) : std::shared_ptr<Internal>{ std::make_shared<Internal>(*other) } { }
    #endif
#endif

NXA_OBJECT_CLASS::NXA_OBJECT_CLASS(NXA_OBJECT_CLASS&&) = default;
NXA_OBJECT_CLASS::NXA_OBJECT_CLASS(NXA_OBJECT_CLASS&) = default;
#ifdef NXA_OBJECT_BASE_CLASS
    NXA_OBJECT_CLASS::NXA_OBJECT_CLASS(std::shared_ptr<Internal>&& other) : NXA_OBJECT_BASE_CLASS{ std::move(other) } { }
#else
    NXA_OBJECT_CLASS::NXA_OBJECT_CLASS(std::shared_ptr<Internal>&& other) : std::shared_ptr<Internal>{ std::move(other) } { }
#endif
NXA_OBJECT_CLASS::~NXA_OBJECT_CLASS() = default;

// -- Operators
NXA_OBJECT_CLASS& NXA_OBJECT_CLASS::operator=(NXA_OBJECT_CLASS&&) = default;
NXA_OBJECT_CLASS& NXA_OBJECT_CLASS::operator=(const NXA_OBJECT_CLASS&) = default;
boolean NXA_OBJECT_CLASS::operator==(const NXA_OBJECT_CLASS& other) const
{
    if (this->get() == other.get()) {
        return true;
    }

    return *(this->get()) == *(other.get());
}

// -- Instance Methods
#if !defined(NXA_OBJECT_HAS_A_CUSTOM_CLASS_NAME)
    const character* NXA_OBJECT_CLASS::className() const
    {
        return nxa_internal->className();
    }
#endif
bool NXA_OBJECT_CLASS::classNameIs(const character* className) const
{
    return !::strcmp(nxa_internal->className(), className);
}

String NXA_OBJECT_CLASS::description() const
{
    DescriberState state;
    return this->description(state);
}

#undef NXA_OBJECT_CLASS
#undef NXA_OBJECT_BASE_CLASS
#undef NXA_OBJECT_INTERNAL_BASE_CLASS
#undef NXA_INTERNAL_OBJECT_SHOULD_NEVER_BE_COPIED
#undef NXA_OBJECT_HAS_A_CUSTOM_CLASS_NAME
