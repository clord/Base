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
#include <Base/Assert.hpp>
#include <Base/Internal/MutableArrayInternal.hpp>

#include <initializer_list>
#include <algorithm>
#include <vector>
#include <mutex>
#include <memory>
#include <type_traits>
#include <utility>

namespace NxA {

// -- Class

template <class T, template <typename, typename...> class Implementation, typename... Rest>
class MutableArray : protected std::shared_ptr<Implementation<T, Rest...>>
{
    using Internal = Implementation<T, Rest...>;

    template <typename V, template <typename, typename...> class I, typename... R>
    friend class MutableArray;

    template <typename V, template <typename, typename...> class I, typename... R>
    friend class Array;

    friend Implementation<T, Rest...>;

public:
    // -- Constructors/Destructors
    MutableArray() : std::shared_ptr<Internal>{ std::make_shared<Internal>() } { }
    MutableArray(const std::shared_ptr<Internal>& other) : std::shared_ptr<Internal>{ other } { }
    MutableArray(const MutableArray& other) : std::shared_ptr<Internal>{ std::make_shared<Internal>(*other) } { }
    MutableArray(MutableArray& other) : std::shared_ptr<Internal>{ std::make_shared<Internal>(*other) } { }
    MutableArray(std::initializer_list<T> other) : std::shared_ptr<Internal>{ std::make_shared<Internal>(other) } { }
    MutableArray(MutableArray<T, Implementation, Rest...>&& other) :std::shared_ptr<Internal>{ std::move(other) } { }
    template <template <typename, typename...> class I, typename... R>
    MutableArray(const MutableArray<T, I, R...>& other) : std::shared_ptr<Internal>{ std::make_shared<Internal>(std::vector<T>{other->begin(), other->end()}) } { }
    template <template <typename, typename...> class I, typename... R>
    MutableArray(const Array<T, I, R...>& other) : std::shared_ptr<Internal>{ std::make_shared<Internal>(std::vector<T>{other->begin(), other->end()}) } { }
    ~MutableArray() { }

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
            count needed = snprintf(nullptr, 0, format, valueTypeName) + 1;
            buffer = std::make_unique<character[]>(needed);
            snprintf(buffer.get(), needed, format, valueTypeName);
        }

        return buffer.get();
    }
    
    // -- Iterators
    using iterator = typename Internal::iterator;
    using const_iterator = typename Internal::const_iterator;

    // -- Operators
    MutableArray& operator=(MutableArray&& other)
    {
        this->std::shared_ptr<Internal>::operator=(std::make_shared<Internal>(*other));
        return *this;
    }
    MutableArray& operator=(const MutableArray& other)
    {
        this->std::shared_ptr<Internal>::operator=(std::make_shared<Internal>(*other));
        return *this;
    }

    bool operator==(const MutableArray& other) const
    {
        auto internal = this->get();
        auto otherInternal = other.get();

        if (internal == otherInternal) {
            return true;
        }

        return *internal == *otherInternal;
    }

    bool operator!=(const MutableArray& other) const
    {
        return !this->operator==(other);
    }

    template <template <typename, typename...> class I>
    bool operator==(const Array<T, I>& other) const
    {
        auto internal = this->get();
        auto otherInternal = other.get();

        if (internal == otherInternal) {
            return true;
        }

        return *internal == *otherInternal;
    }

    template <template <typename, typename...> class I>
    bool operator!=(const Array<T, I>& other) const
    {
        return !this->operator==(other);
    }

    const T& operator[](count index) const
    {
        return this->get()->operator[](index);
    }

    T& operator[](count index)
    {
        return this->get()->operator[](index);
    }

    // -- Instance Methods
    virtual const character* className() const final
    {
        return MutableArray::staticClassName();
    }

    boolean classNameIs(const character* className) const
    {
        return !::strcmp(MutableArray::staticClassName(), className);
    }

    iterator begin() noexcept
    {
        return this->get()->begin();
    }

    const_iterator begin() const noexcept
    {
        return this->get()->begin();
    }

    iterator end() noexcept
    {
        return this->get()->end();
    }

    const_iterator end() const noexcept
    {
        return this->get()->end();
    }

    const_iterator cbegin() const noexcept
    {
        return this->get()->cbegin();
    }

    const_iterator cend() const noexcept
    {
        return this->get()->cend();
    }

    void reserve(count amount)
    {
        return this->get()->reserve(amount);
    }

    void append(T object)
    {
        return this->get()->append(object);
    }

    template<class... ConstructorArguments>
    void emplaceAppend(ConstructorArguments &&... arguments)
    {
        this->get()->emplaceAppend(std::forward<ConstructorArguments>(arguments)...);
    }

    void append(const MutableArray<T>& objects)
    {
        auto internal = this->get();
        for (auto& object : objects) {
            internal->append(object);
        }
    }

    template <template <typename, typename...> class I>
    void append(Array<T, I> objects)
    {
        auto internal = this->get();
        for (auto& object : objects) {
            internal->append(object);
        }
    }

    void insertAt(T object, const_iterator position)
    {
        this->get()->insertAt(object, position);
    }

    void remove(const T& object)
    {
        this->get()->remove(object);
    }

    void removeAll()
    {
        this->get()->removeAll();
    }

    count length() const
    {
        return this->get()->length();
    }

    const T& firstObject() const
    {
        return this->get()->firstObject();
    }

    T& firstObject()
    {
        return this->get()->firstObject();
    }

    const T& lastObject() const
    {
        return this->get()->lastObject();
    }

    T& lastObject()
    {
        return this->get()->lastObject();
    }

    boolean contains(const T& object) const
    {
        return this->get()->contains(object);
    }

    iterator find(const T& object)
    {
        return this->get()->find(object);
    }

    const_iterator find(const T& object) const
    {
        return this->get()->find(object);
    }

    void removeObjectAt(const_iterator objectPosition)
    {
        this->get()->removeObjectAt(objectPosition);
    }

    void sort()
    {
        this->get()->sort();
    }

    void rearrange(Array<T> movingTs, size_t to)
    {
        this->get()->rearrange(movingTs, to);
    }

};
    
}
