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
class Array
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

    Array() : internal{std::make_shared<Internal>()} { }

    Array(const Array& other) : internal{std::make_shared<Internal>(*other.internal)} { }

    Array(Array&& other) : internal{std::move(other.internal)} { }

    Array(std::initializer_list<T> other) : internal{std::make_shared<Internal>(other)} { }

    template <template <typename> class I>
    Array(const MutableArray<T, I>& other) : internal{std::make_shared<Internal>(*other.internal)} { }

    template <template <typename> class I>
    Array(const Array<T, I>& other) : internal{std::make_shared<Internal>(*other.internal)} { }

    Array(MutableArray<T, Implementation>&& other) : internal{std::move(other.internal)} { }

    Array(std::vector<T>&& other) : internal{std::make_shared<Internal>(std::move(other))} { }

    template <typename V, template <typename> class I, typename = std::enable_if_t<std::is_convertible<V, T>::value>>
    Array(const Array<V, I>& other) : internal{std::make_shared<Internal>(*other.internal)} { }

    ~Array() { }

    // -- Class Methods

    static const character* staticClassName() {
        static std::unique_ptr<character[]> buffer;
        if (buffer) {
            // -- This is the fast lock-free path for the common case (unique_ptr engaged)
            return buffer.get();
        }

        static std::mutex m;
        std::lock_guard<std::mutex> guard(m);

        // -- now under guard, this is the slow-and-safe path. We have to re-check in case we lost a race to the lock.
        if (!buffer) {
            const character* format = "Array<%s>";
            const character* valueTypeName = TypeName<T>::get();
            count needed = snprintf(NULL, 0, format, valueTypeName) + 1;
            buffer = std::make_unique<character[]>(needed);
            snprintf(buffer.get(), needed, format, valueTypeName);
        }

        return buffer.get();
    }

    static uinteger32 staticClassHash() {
        return static_cast<uinteger32>(std::hash<std::string> {}(std::string{Array::staticClassName()}));
    }

    // -- Iterators

    using iterator = typename Internal::iterator;
    using const_iterator = typename Internal::const_iterator;

    // -- Operators

    Array& operator=(Array&& other) {
        internal = std::move(other.internal);
        return *this;
    }

    Array& operator=(const Array& other) {
        internal = std::make_shared<Internal>(*other.internal);
        return *this;
    }

    template <template <typename> class I>
    Array& operator=(const MutableArray<T, I>& other) {
        internal = std::make_shared<Internal>(*other.internal);
        return *this;
    }

    bool operator==(const Array& other) const {
        if (internal == other.internal) {
            return true;
        }

        return *internal == *(other.internal);
    }

    bool operator!=(const Array& other) const {
        return !this->operator==(other);
    }

    template <template <typename> class I>
    bool operator==(const MutableArray<T, I>& other) const {
        if (internal == other.internal) {
            return true;
        }

        return *internal == *(other.internal);
    }

    template <template <typename> class I>
    bool operator!=(const MutableArray<T, I>& other) const {
        return !this->operator==(other);
    }

    const T& operator[](count index) const {
        return internal->operator[](index);
    }

    T& operator[](count index) {
        return internal->operator[](index);
    }

    // -- Instance Methods

    uinteger32 classHash() const {
        return Array::staticClassHash();
    }

    const character* className() const {
        return Array::staticClassName();
    }

    const Implementation<T>& implementation() const {
        return *(internal.get());
    }

    boolean classNameIs(const character* className) const {
        return !::strcmp(Array::staticClassName(), className);
    }

    iterator begin() noexcept {
        return internal->begin();
    }

    iterator end() noexcept {
        return internal->end();
    }

    const_iterator begin() const noexcept {
        return internal->cbegin();
    }

    const_iterator end() const noexcept {
        return internal->cend();
    }

    const_iterator cbegin() const noexcept {
        return internal->cbegin();
    }

    const_iterator cend() const noexcept {
        return internal->cend();
    }

    count length() const {
        return internal->length();
    }

    const T& firstObject() const {
        return internal->firstObject();
    }

    T& firstObject() {
        return internal->firstObject();
    }

    const T& lastObject() const {
        return internal->lastObject();
    }

    T& lastObject() {
        return internal->lastObject();
    }

    boolean contains(const T& object) const {
        return internal->contains(object);
    }

    iterator find(const T& object) {
        return internal->find(object);
    }

    const_iterator find(const T& object) const {
        return internal->find(object);
    }

};
}
