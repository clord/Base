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
#include <Base/Assert.hpp>
#include <Base/Internal/Object.hpp>
#include <Base/Internal/Array.hpp>

#include <algorithm>
#include <vector>

namespace NxA {

template <class T> class Array;

#pragma mark Class

template <class T> class MutableArray {
    NXA_GENERATED_INTERNAL_OBJECT_FORWARD_DECLARATION_USING(ArrayInternal<T>);

    std::shared_ptr<Internal> internal;

    friend Array<T>;

public:
    #pragma mark Constructors/Destructors
    MutableArray() : internal{ std::make_shared<Internal>() } { }
    MutableArray(const MutableArray& other) : internal{ std::make_shared<Internal>(*other.internal) } { }
    MutableArray(MutableArray&&) = default;
    MutableArray(const Array<T>& other) : internal{ std::make_shared<Internal>(*other.internal) } { }
    ~MutableArray() = default;

    #pragma mark Class Methods
    static const character* staticClassName()
    {
        static std::mutex m;
        static std::unique_ptr<character[]> buffer;

        m.lock();

        if (!buffer.get()) {
            const character* format = "MutableArray<%s>";
            count needed = snprintf(NULL, 0, format, T::staticClassName()) + 1;
            buffer = std::make_unique<character[]>(needed);
            snprintf(buffer.get(), needed, format, T::staticClassName());
        }

        m.unlock();

        return buffer.get();
    }
    static uinteger32 staticClassHash()
    {
        static uinteger32 result = String::hashFor(MutableArray::staticClassName());
        return result;
    }

    #pragma mark Iterators
    using iterator = typename ArrayInternal<T>::iterator;
    using const_iterator = typename ArrayInternal<T>::const_iterator;

    #pragma mark Operators
    MutableArray& operator=(MutableArray&&) = default;
    MutableArray& operator=(const MutableArray& other) = default;
    bool operator==(const MutableArray& other) const
    {
        if (internal == other.internal) {
            return true;
        }

        return *internal == *(other.internal);
    }
    bool operator==(const Array<T>& other) const
    {
        if (internal == other.internal) {
            return true;
        }

        return *internal == *(other.internal);
    }
    T operator[] (count index) const
    {
        return internal->operator[](index);
    }

    #pragma mark Instance Methods
    uinteger32 classHash() const
    {
        return MutableArray::staticClassHash();
    }
    const character* className() const
    {
        return MutableArray::staticClassName();
    }
    iterator begin() noexcept
    {
        return internal->begin();
    }
    const_iterator begin() const noexcept
    {
        return internal->begin();
    }
    iterator end() noexcept
    {
        return internal->end();
    }
    const_iterator end() const noexcept
    {
        return internal->end();
    }
    const_iterator cbegin() const noexcept
    {
        return internal->cbegin();
    }
    const_iterator cend() const noexcept
    {
        return internal->cend();
    }

    void append(T object)
    {
        return internal->append(object);
    }
    void append(const Array<T>& objects)
    {
        for (auto& object : objects) {
            internal->append(object);
        }
    }
    void insertAt(T object, const_iterator position)
    {
        internal->insertAt(object, position);
    }
    void remove(const T& object)
    {
        internal->remove(object);
    }
    void removeAll()
    {
        internal->removeAll();
    }
    count length() const
    {
        return internal->length();
    }

    T firstObject()
    {
        return internal->firstObject();
    }
    T lastObject()
    {
        return internal->lastObject();
    }
    boolean contains(const T& object) const
    {
        return internal->contains(object);
    }
    const_iterator find(const T& object) const
    {
        return internal->find(object);
    }
    void removeObjectAt(const_iterator objectPosition)
    {
        internal->removeObjectAt(objectPosition);
    }

    String description() const
    {
        return internal->description();
    }
};

}
