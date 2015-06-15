//
//  Copyright (c) 2015 Next Audio Labs, LLC. All rights reserved.
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

#include <memory>
#include <cassert>

namespace NxA {
    template <class T> class WeakPointer;

    template <class T> class Pointer {
        friend class WeakPointer<T>;

    public:
        #pragma mark Constructors & Destructors
        Pointer() = delete;
        Pointer(std::shared_ptr<T> const &other) : pointer(other) { }
        Pointer(Pointer<T> const &other) : pointer(other.pointer) { }
        template <class From> Pointer(Pointer<From> const &other) :
                pointer(std::dynamic_pointer_cast<T>(other.toStdSharedPointer()))
        {
            assert(this->pointer.get() != nullptr);
        }

        #pragma mark Operators
        T* operator->()
        {
            return this->pointer.get();
        }
        const T* operator->() const
        {
            return this->pointer.get();
        }

        #pragma mark Instance Methods
        std::shared_ptr<T> const& toStdSharedPointer(void) const
        {
            return this->pointer;
        }

    private:
        #pragma mark Instance Variables
        std::shared_ptr<T> pointer;
    };
}

