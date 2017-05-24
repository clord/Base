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
#include <Base/String.hpp>
#include <Base/MutableSet.hpp>
#include <Base/Internal/MutableSetInternal.hpp>

#include <algorithm>
#include <vector>
#include <mutex>
#include <memory>

namespace NxA {

// -- Class

template <class T>
class Set : std::shared_ptr<MutableSetInternal<T>>
{
    using Internal = MutableSetInternal<T>;

    friend class MutableSet<T>;

public:
    // -- Constructors/Destructors
    Set() : std::shared_ptr<Internal>{ std::make_shared<Internal>() } { }
    Set(const Set<T>& other) : std::shared_ptr<Internal>{ other } { }
    Set(std::initializer_list<T> other) : std::shared_ptr<Internal>{ std::make_shared<Internal>(other) } { }
    Set(Set&& other) = default;
    Set(const MutableSet<T>& other) : std::shared_ptr<Internal>{std::make_shared<Internal>(*other)} { }
    Set(MutableSet<T>&& other) : std::shared_ptr<Internal>{ std::move(other) } { }
    ~Set() = default;

    // -- Class Methods
    static const character* staticClassName()
    {
        static std::unique_ptr<character[]> buffer;
        if (buffer) {
            // This is the fast lock-free path for the common case (unique_ptr engaged)
            return buffer.get();
        }

        static std::mutex m;
        std::lock_guard<std::mutex> guard(m);

        // now under guard, this is the slow-and-safe path. We have to re-check get() in case we lost a race to the lock.
        if (!buffer) {
            const character* format = "Set<%s>";
            const character* valueTypeName = TypeName<T>::get();
            count needed = snprintf(nullptr, 0, format, valueTypeName) + 1;
            buffer = std::make_unique<character[]>(needed);
            snprintf(buffer.get(), needed, format, valueTypeName);
        }

        return buffer.get();
    }

    // -- Iterators
    using const_iterator = typename Internal::const_iterator;
    using iterator = const_iterator;

    // -- Operators
    Set& operator=(const Set& other)
    {
        this->std::shared_ptr<Internal>::operator=(other);
        return *this;
    }
    Set& operator=(const MutableSet<T>& other)
    {
        this->std::shared_ptr<Internal>::operator=(std::make_shared<Internal>(*other));
        return *this;
    }

    bool operator==(const Set& other) const
    {
        auto internal = this->get();
        auto otherInternal = other.get();

        if (internal == otherInternal) {
            return true;
        }

        return *internal == *otherInternal;
    }

    bool operator!=(const Set& other) const
    {
        return !this->operator==(other);
    }

    bool operator==(const MutableSet<T>& other) const
    {
        auto internal = this->get();
        auto otherInternal = other.get();

        if (internal == otherInternal) {
            return true;
        }

        return *internal == *otherInternal;
    }

    bool operator!=(const MutableSet<T>& other) const
    {
        return !this->operator==(other);
    }

    // -- Instance Methods
    virtual const character* className() const final
    {
        return Set::staticClassName();
    }

    boolean classNameIs(const character* className) const
    {
        return !::strcmp(Set::staticClassName(), className);
    }

    const_iterator begin() const noexcept
    {
        return this->get()->begin();
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

    count length() const
    {
        return this->get()->length();
    }

    const T& anyObject() const
    {
        return this->get()->anyObject();
    }

    boolean contains(const T& object) const
    {
        return this->get()->contains(object);
    }

    const_iterator find(const T& object) const
    {
        return this->get()->find(object);
    }

    String description(const DescriberState& state) const
    {
        return this->get()->description(state);
    }
};
    
}
