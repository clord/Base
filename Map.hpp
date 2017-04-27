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
#include <Base/MutableString.hpp>
#include <Base/MutableMap.hpp>
#include <Base/Internal/MutableMap.hpp>
#include <Base/GeneratedObjectCode.hpp>

#include <mutex>

namespace NxA {

// -- Class

template <typename Tkey, typename Tvalue>
class Map
{
    NXA_GENERATED_INTERNAL_OBJECT_FORWARD_DECLARATION_USING(MutableMapInternal<const Tkey, Tvalue>);

    std::shared_ptr<MutableMapInternal<const Tkey, Tvalue>> internal;

    friend MutableString;

public:
    // -- Constructors/Destructors
    Map() : internal{std::make_shared<MutableMapInternal<const Tkey, Tvalue>>()} { }
    Map(const Map&) = default;
    Map(Map&&) = default;
    Map(MutableMap<Tkey, Tvalue>&& other) : internal{std::move(other.internal)} { }
    ~Map() = default;

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
            const character* format = "Map<%s, %s>";
            const character* keyTypeName = TypeName<Tkey>::get();
            const character* valueTypeName = TypeName<Tvalue>::get();
            count needed = snprintf(nullptr, 0, format, keyTypeName, valueTypeName) + 1;
            buffer = std::make_unique<character[]>(needed);
            snprintf(buffer.get(), needed, format, keyTypeName, valueTypeName);
        }

        return buffer.get();
    }

    // -- Iterators
    using const_iterator = typename MutableMapInternal<const Tkey, Tvalue>::const_iterator;

    // -- Operators
    Map& operator=(Map&&) = default;
    Map& operator=(const Map& other) = default;
    bool operator==(const Map& other) const
    {
        if (internal == other.internal) {
            return true;
        }

        return *internal == *(other.internal);
    }
    bool operator!=(const Map& other) const
    {
        return !this->operator==(other);
    }
    bool operator==(const MutableMap<Tkey, Tvalue>& other) const
    {
        if (internal == other.internal) {
            return true;
        }

        return *internal == *(other.internal);
    }
    bool operator!=(const MutableMap<Tkey, Tvalue>& other) const
    {
        return !this->operator==(other);
    }
    const Tvalue& operator[](const Tkey& key) const
    {
        return internal->operator[](key);
    }
    Tvalue& operator[](const Tkey& key)
    {
        return internal->operator[](key);
    }
    Tvalue& operator[](Tkey&& key)
    {
        return internal->operator[](std::move(key));
    }

    // -- Instance Methods
    virtual const character* className() const final
    {
        return Map::staticClassName();
    }

    boolean classNameIs(const character* className) const
    {
        return !::strcmp(Map::staticClassName(), className);
    }

    const_iterator begin() const
    {
        return internal->begin();
    }

    const_iterator cbegin() const
    {
        return internal->cbegin();
    }

    const_iterator end() const
    {
        return internal->end();
    }

    const_iterator cend() const
    {
        return internal->cend();
    }

    count length() const
    {
        return internal->length();
    }

    Tvalue& valueForKey(const Tkey& key)
    {
        return internal->operator[](key);
    }
    const Tvalue& valueForKey(const Tkey& key) const
    {
        return internal->operator[](key);
    }
    Tvalue& valueForKey(Tkey&& key)
    {
        return internal->operator[](std::move(key));
    }

    Optional<Tvalue> maybeValueForKey(const Tkey& key) const
    {
        return internal->maybeValueForKey(key);
    }
    
    boolean containsValueForKey(const Tkey& key) const
    {
        return internal->containsValueForKey(key);
    }
};
    
}
