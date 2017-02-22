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
#include <Base/GeneratedObjectCode.hpp>
#include <Base/Internal/MutableArray.hpp>

#include <initializer_list>
#include <algorithm>
#include <vector>
#include <mutex>
#include <memory>
#include <type_traits>
#include <utility>

namespace NxA {

// -- Class

template <class T, template <typename> class Implementation>
class MutableArray
{
    NXA_GENERATED_INTERNAL_OBJECT_FORWARD_DECLARATION_USING(Implementation<T>);

    std::shared_ptr<Internal> internal;

    template <typename V, template <typename> class I>
    friend class MutableArray;

    template <typename V, template <typename> class I>
    friend class Array;

    friend Implementation<T>;

public:
    // -- Constructors/Destructors

    MutableArray() : internal{std::make_shared<Internal>()} { }

    MutableArray(const MutableArray& other) : internal{std::make_shared<Internal>(*other.internal)} { }

    MutableArray(MutableArray& other) : internal{std::make_shared<Internal>(*other.internal)} { }

    MutableArray(std::initializer_list<T> other) : internal{std::make_shared<Internal>(other)} { }

    MutableArray(MutableArray&&) = default;

    template <template <typename> class I>
    MutableArray(const Array<T, I>& other) : internal{std::make_shared<Internal>(*other.internal)} { }

    ~MutableArray() = default;

    // -- Class Methods

    static const character* staticClassName()
    {
        static std::unique_ptr<character[]> buffer;
        if (buffer) {
            // -- This is the fast lock-free path for the common case (unique_ptr engaged)
            return buffer.get();
        }

        static std::mutex m;
        std::lock_guard<std::mutex> guard(m);

        if (!buffer.get()) {
            const character* format = "MutableArray<%s>";
            const character* valueTypeName = TypeName<T>::get();
            count needed = snprintf(NULL, 0, format, valueTypeName) + 1;
            buffer = std::make_unique<character[]>(needed);
            snprintf(buffer.get(), needed, format, valueTypeName);
        }

        return buffer.get();
    }

    static uinteger32 staticClassHash()
    {
        return static_cast<uinteger32>(std::hash<std::string>{}(std::string{MutableArray::staticClassName()}));
    }

    // -- Iterators

    using iterator = typename Internal::iterator;
    using const_iterator = typename Internal::const_iterator;

    // -- Operators

    MutableArray& operator=(MutableArray&&) = default;

    MutableArray& operator=(const MutableArray& other)
    {
        internal = std::make_shared<Internal>(*other.internal);
        return *this;
    }

    bool operator==(const MutableArray& other) const
    {
        if (internal == other.internal) {
            return true;
        }

        return *internal == *(other.internal);
    }

    bool operator!=(const MutableArray& other) const
    {
        return !this->operator==(other);
    }

    template <template <typename> class I>
    bool operator==(const Array<T, I>& other) const
    {
        if (internal == other.internal) {
            return true;
        }

        return *internal == *(other.internal);
    }

    template <template <typename> class I>
    bool operator!=(const Array<T, I>& other) const
    {
        return !this->operator==(other);
    }

    const T& operator[](count index) const
    {
        return internal->operator[](index);
    }

    T& operator[](count index)
    {
        return internal->operator[](index);
    }

    // -- Instance Methods

    uinteger32 classHash() const
    {
        return MutableArray::staticClassHash();
    }

    const character* className() const
    {
        return MutableArray::staticClassName();
    }

    boolean classNameIs(const character* className) const
    {
        return !::strcmp(MutableArray::staticClassName(), className);
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

    void reserve(count amount)
    {
        return internal->reserve(amount);
    }

    void append(T object)
    {
        return internal->append(object);
    }

    template <class... ConstructorArguments>
    void emplaceAppend(ConstructorArguments&&... arguments)
    {
        internal->emplaceAppend(std::forward<ConstructorArguments>(arguments)...);
    }

    void append(MutableArray<T>& objects)
    {
        for (auto& object : objects) {
            internal->append(object);
        }
    }

    void append(const MutableArray<T>& objects)
    {
        for (auto& object : objects) {
            internal->append(object);
        }
    }

    template <template <typename> class I>
    void append(const Array<T, I>& objects)
    {
        for (auto& object : objects) {
            internal->append(object);
        }
    }

    template <template <typename> class I>
    void append(Array<T, I>& objects)
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

    const T& firstObject() const
    {
        return internal->firstObject();
    }

    T& firstObject()
    {
        return internal->firstObject();
    }

    const T& lastObject() const
    {
        return internal->lastObject();
    }

    T& lastObject()
    {
        return internal->lastObject();
    }

    boolean contains(const T& object) const
    {
        return internal->contains(object);
    }

    iterator find(const T& object)
    {
        return internal->find(object);
    }

    const_iterator find(const T& object) const
    {
        return internal->find(object);
    }

    void removeObjectAt(const_iterator objectPosition)
    {
        internal->removeObjectAt(objectPosition);
    }

    void sort()
    {
        internal->sort();
    }
};
}
