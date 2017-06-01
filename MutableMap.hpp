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
#include <Base/Internal/MutableMapInternal.hpp>

#include <mutex>

namespace NxA {

template <typename Tkey, typename Tvalue>
class Map;

// -- Class

template <typename Tkey, typename Tvalue>
class MutableMap : protected std::shared_ptr<MutableMapInternal<const Tkey, Tvalue>>
{
    using Internal = MutableMapInternal<const Tkey, Tvalue>;

    friend Map<const Tkey, Tvalue>;

public:
    // -- Constructors/Destructors
    MutableMap() : std::shared_ptr<Internal>{ std::make_shared<MutableMapInternal<const Tkey, Tvalue>>() } { }
    MutableMap(const MutableMap& other) : std::shared_ptr<Internal>{ std::make_shared<Internal>(*other) } { }
    MutableMap(MutableMap& other) : std::shared_ptr<Internal>{ other } { }
    MutableMap(MutableMap&&) = default;
    MutableMap(const Map<Tkey, Tvalue>& other) : std::shared_ptr<Internal>{ std::make_shared<Internal>(*other) } { }
    ~MutableMap() = default;

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
            const character* format = "MutableMap<%s, %s>";
            const character* keyTypeName = TypeName<Tkey>::get();
            const character* valueTypeName = TypeName<Tvalue>::get();
            count needed = snprintf(nullptr, 0, format, keyTypeName, valueTypeName) + 1;
            buffer = std::make_unique<character[]>(needed);
            snprintf(buffer.get(), needed, format, keyTypeName, valueTypeName);
        }

        return buffer.get();
    }

    // -- Iterators
    using iterator = typename MutableMapInternal<const Tkey, Tvalue>::iterator;
    using const_iterator = typename MutableMapInternal<const Tkey, Tvalue>::const_iterator;

    // -- Operators
    MutableMap& operator=(MutableMap&&) = default;
    MutableMap& operator=(const MutableMap& other)
    {
        this->std::shared_ptr<Internal>::operator=(other);
        return *this;
    }

    bool operator==(const MutableMap& other) const
    {
        auto internal = this->get();
        auto otherInternal = other.get();

        if (internal == otherInternal) {
            return true;
        }

        return *internal == *otherInternal;
    }

    bool operator==(const Map<Tkey, Tvalue>& other) const
    {
        auto internal = this->get();
        auto otherInternal = other.get();

        if (internal == otherInternal) {
            return true;
        }

        return *internal == *otherInternal;
    }

    const Tvalue& operator[](const Tkey& key) const
    {
        return this->get()->operator[](key);
    }

    Tvalue& operator[](const Tkey& key)
    {
        return this->get()->operator[](key);
    }

    Tvalue& operator[](Tkey&& key)
    {
        return this->get()->operator[](std::move(key));
    }

    // -- Instance Methods
    virtual const character* className() const final
    {
        return MutableMap::staticClassName();
    }

    boolean classNameIs(const character* className) const
    {
        return !::strcmp(MutableMap::staticClassName(), className);
    }

    iterator begin()
    {
        return this->get()->begin();
    }

    const_iterator begin() const
    {
        return this->get()->begin();
    }

    const_iterator cbegin() const
    {
        return this->get()->cbegin();
    }

    iterator end()
    {
        return this->get()->end();
    }

    const_iterator end() const
    {
        return this->get()->end();
    }
    const_iterator cend() const
    {
        return this->get()->cend();
    }

    count length() const
    {
        return this->get()->length();
    }

    boolean setValueForKeyCausedAnInsertion(const Tvalue& value, const Tkey& key)
    {
        return this->get()->setValueForKeyCausedAnInsertion(value, key);
    }
    void setValueForKey(const Tvalue& value, const Tkey& key)
    {
        this->get()->setValueForKeyCausedAnInsertion(value, key);
    }

    Tvalue& valueForKey(const Tkey& key)
    {
        return this->get()->valueForKey(key);
    }
    const Tvalue& valueForKey(const Tkey& key) const
    {
        return this->get()->operator[](key);
    }
    Tvalue& valueForKey(Tkey&& key)
    {
        return this->get()->valueForKey(std::move(key));
    }

    Optional<Tvalue> maybeValueForKey(const Tkey& key) const
    {
        return this->get()->maybeValueForKey(key);
    }

    boolean removeValueForKeyCausedARemoval(const Tkey& key)
    {
        return this->get()->removeValueForKeyCausedARemoval(key);
    }
    void removeValueForKey(const Tkey& key)
    {
        this->get()->removeValueForKeyCausedARemoval(key);
    }

    void removeValueAt(const_iterator position)
    {
        this->get()->removeValueAt(position);
    }

    void removeAll()
    {
        this->get()->removeAll();
    }
};
    
}
