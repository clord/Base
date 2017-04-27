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
#include <Base/String.hpp>
#include <Base/Internal/MutableMap.hpp>
#include <Base/GeneratedObjectCode.hpp>

#include <mutex>

namespace NxA {

template <typename Tkey, typename Tvalue>
class Map;

// -- Class

template <typename Tkey, typename Tvalue>
class MutableMap
{
    NXA_GENERATED_INTERNAL_OBJECT_FORWARD_DECLARATION_USING(MutableMapInternal<const Tkey, Tvalue>);

    std::shared_ptr<MutableMapInternal<const Tkey, Tvalue>> internal;

    friend Map<const Tkey, Tvalue>;

public:
    // -- Constructors/Destructors
    MutableMap() : internal{ std::make_shared<MutableMapInternal<const Tkey, Tvalue>>() } { }
    MutableMap(const MutableMap& other) : internal{ std::make_shared<Internal>(*other.internal) } { }
    MutableMap(MutableMap& other) : internal{other.internal} { }
    MutableMap(MutableMap&&) = default;
    MutableMap(const Map<Tkey, Tvalue>& other) : internal{ std::make_shared<Internal>(*other.internal) } { }
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
    MutableMap& operator=(const MutableMap& other) = default;

    bool operator==(const MutableMap& other) const
    {
        if (internal == other.internal) {
            return true;
        }

        return *internal == *(other.internal);
    }

    bool operator==(const Map<Tkey, Tvalue>& other) const
    {
        if (internal == other.internal) {
            return true;
        }

        return *internal == *(other.internal);
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
        return MutableMap::staticClassName();
    }

    boolean classNameIs(const character* className) const
    {
        return !::strcmp(MutableMap::staticClassName(), className);
    }

    iterator begin()
    {
        return internal->begin();
    }

    const_iterator begin() const
    {
        return internal->begin();
    }

    const_iterator cbegin() const
    {
        return internal->cbegin();
    }

    iterator end()
    {
        return internal->end();
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

    void setValueForKey(Tvalue value, const Tkey& key)
    {
        internal->setValueForKey(value, key);
    }

    Tvalue& valueForKey(const Tkey& key)
    {
        return internal->valueForKey(key);
    }
    const Tvalue& valueForKey(const Tkey& key) const
    {
        return internal->operator[](key);
    }
    Tvalue& valueForKey(Tkey&& key)
    {
        return internal->valueForKey(std::move(key));
    }

    Optional<Tvalue> maybeValueForKey(const Tkey& key) const
    {
        return internal->maybeValueForKey(key);
    }

    boolean containsValueForKey(const Tkey& key) const
    {
        return internal->containsValueForKey(key);
    }

    void removeValueAt(const_iterator position)
    {
        return internal->removeValueAt(position);
    }

    void removeValueForKey(const Tkey& key)
    {
        return internal->removeValueForKey(key);
    }

    void removeAll()
    {
        return internal->removeAll();
    }
};
    
}
