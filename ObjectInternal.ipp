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

// -- Instance Methods

#if !defined(NXA_INTERNAL_OBJECT_IS_PURE_VIRTUAL)
    const character* className() const
    #ifdef NXA_BASE_INTERNAL_OBJECT_IS_IN_CLASS
        override
    #endif
    {
        return NXA_OBJECT_CLASS::staticClassNameConst;
    }
#endif

#ifdef NXA_BASE_INTERNAL_OBJECT_IS_IN_CLASS
    virtual std::shared_ptr<NXA_BASE_INTERNAL_OBJECT_IS_IN_CLASS> baseInternalSharedPointer() override
    {
        return std::static_pointer_cast<NXA_BASE_INTERNAL_OBJECT_IS_IN_CLASS>(std::make_shared<Internal>(*this));
    }
#elif defined(NXA_INTERNAL_OBJECT_IS_PURE_VIRTUAL)
    virtual std::shared_ptr<Internal> baseInternalSharedPointer() = 0;
#endif

#undef NXA_OBJECT_CLASS
#undef NXA_BASE_INTERNAL_OBJECT_IS_IN_CLASS
#undef NXA_INTERNAL_OBJECT_IS_PURE_VIRTUAL
