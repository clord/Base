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

// -- Strongly based on the std::experimental::optional type, modified to fit NxA style

#include <Base/Types.hpp>
#include <Base/Assert.hpp>
#include <functional>
#include <stdexcept>
#include <initializer_list>
#include <type_traits>
#include <new>

namespace NxA {

struct BadOptionalAccess : public std::logic_error
{
    inline BadOptionalAccess(const BadOptionalAccess&) noexcept = default;
    inline BadOptionalAccess& operator=(const BadOptionalAccess&) noexcept = default;
    inline explicit BadOptionalAccess(const std::string& arg) : logic_error(arg)
    {
    }
    inline explicit BadOptionalAccess(const char* arg) : logic_error(arg)
    {
    }
};

struct InPlaceT
{
};

constexpr InPlaceT inPlace{};

struct NothingT
{
    explicit constexpr NothingT(int) noexcept
    {
    }
};

constexpr NothingT nothing{0};

template <typename ValueT, bool = std::is_trivially_destructible<ValueT>::value>
class Storage
{
protected:
    using ValueType = ValueT;

    union
    {
        char nothingState;
        ValueType engagedValue;
    };

    bool engaged = false;

    inline ~Storage()
    {
        if (engaged) {
            engagedValue.~ValueType();
        }
    }

    inline constexpr Storage() noexcept : nothingState{}
    {
    }

    inline Storage(const Storage& xParm) : engaged{xParm.engaged}
    {
        if (engaged) {
            ::new (std::addressof(engagedValue)) ValueType(xParm.engagedValue);
        }
    }

    inline Storage(Storage&& xParm) noexcept(std::is_nothrow_move_constructible<ValueType>::value) : engaged{xParm.engaged}
    {
        if (engaged) {
            ::new (std::addressof(engagedValue)) ValueType(std::move(xParm.engagedValue));
        }
    }

    inline constexpr Storage(const ValueType& withValue) : engagedValue{withValue}, engaged{true}
    {
    }
    inline constexpr Storage(ValueType&& withValue) : engagedValue{std::move(withValue)}, engaged{true}
    {
    }

    template <typename... Arguments>
    inline constexpr explicit Storage(InPlaceT, Arguments&&... arguments) : engagedValue{std::forward<Arguments>(arguments)...}, engaged{true}
    {
    }
};

template <typename ValueT>
class Storage<ValueT, true>
{
protected:
    using ValueType = ValueT;

    union
    {
        char nothingState;
        ValueType engagedValue;
    };

    bool engaged = false;
    inline constexpr Storage() noexcept : nothingState{'\0'}
    {
    }

    inline Storage(const Storage& xParm) : engaged{xParm.engaged}
    {
        if (engaged) {
            ::new (std::addressof(engagedValue)) ValueType(xParm.engagedValue);
        }
    }

    inline Storage(Storage&& xParm) noexcept(std::is_nothrow_move_constructible<ValueType>::value) : engaged{xParm.engaged}
    {
        if (engaged) {
            ::new (std::addressof(engagedValue)) ValueType(std::move(xParm.engagedValue));
        }
    }

    inline constexpr Storage(const ValueType& withValue) : engagedValue{withValue}, engaged{true}
    {
    }
    inline constexpr Storage(ValueType&& withValue) : engagedValue{std::move(withValue)}, engaged{true}
    {
    }
    template <typename... Arguments>
    inline constexpr explicit Storage(InPlaceT, Arguments&&... arguments) : engagedValue{std::forward<Arguments>(arguments)...}, engaged{true}
    {
    }
};

template <typename ValueT>
struct Optional : private Storage<ValueT>
{
    using ValueType = ValueT;

    static_assert(!std::is_reference<ValueType>::value, "Instantiation of Optional with a reference type is ill-formed");
    static_assert(!std::is_same<typename std::remove_cv<ValueType>::type, InPlaceT>::value,
                  "Instantiation of Optional with InPlaceT type is ill-formed");
    static_assert(!std::is_same<typename std::remove_cv<ValueType>::type, NothingT>::value,
                  "Instantiation of Optional with NothingT type is ill-formed");
    static_assert(std::is_object<ValueType>::value, "Instantiation of Optional with a non-object type is undefined behavior");
    static_assert(std::is_nothrow_destructible<ValueType>::value,
                  "Instantiation of Optional with an object type that is not noexcept destructible is undefined behavior");

    constexpr Optional() noexcept = default;
    inline constexpr Optional(const Optional&) = default;
    constexpr Optional(Optional&&) = default;
    ~Optional() {}

    inline constexpr Optional(NothingT) noexcept
    {
    }

    inline constexpr Optional(const ValueType& withValue) : Storage<ValueT>{withValue}
    {
    }

    inline constexpr Optional(ValueType&& withValue) : Storage<ValueT>{std::move(withValue)}
    {
    }

    template <typename... Arguments, class = typename std::enable_if<std::is_constructible<ValueType, Arguments...>::value>::type>
    inline constexpr explicit Optional(InPlaceT, Arguments&&... arguments) : Storage<ValueT>{inPlace, std::forward<Arguments>(arguments)...}
    {
    }

    template <typename OtherValue, class... Arguments,
              class = typename std::enable_if<std::is_constructible<ValueType, std::initializer_list<OtherValue>&, Arguments...>::value>::type>
    inline constexpr explicit Optional(InPlaceT, std::initializer_list<OtherValue> initList, Arguments&&... arguments)
        : Storage<ValueT>{inPlace, initList, std::forward<Arguments>(arguments)...}
    {
    }

    inline Optional& operator=(NothingT) noexcept
    {
        if (this->engaged) {
            this->engagedValue.~ValueType();
            this->engaged = false;
        }
        return *this;
    }

    inline Optional& operator=(const Optional& withOptional)
    {
        if (this->engaged == withOptional.engaged) {
            if (this->engaged) {
                this->engagedValue = withOptional.engagedValue;
            }
        }
        else {
            if (this->engaged) {
                this->engagedValue.~ValueType();
            }
            else {
                ::new (std::addressof(this->engagedValue)) ValueType(withOptional.engagedValue);
            }
            this->engaged = withOptional.engaged;
        }
        return *this;
    }

    inline Optional& operator=(Optional&& withOptional) noexcept(
        std::is_nothrow_move_assignable<ValueType>::value&& std::is_nothrow_move_constructible<ValueType>::value)
    {
        if (this->engaged == withOptional.engaged) {
            if (this->engaged) {
                this->engagedValue = std::move(withOptional.engagedValue);
            }
        }
        else {
            if (this->engaged) {
                this->engagedValue.~ValueType();
            }
            else {
                ::new (std::addressof(this->engagedValue)) ValueType(std::move(withOptional.engagedValue));
            }
            this->engaged = withOptional.engaged;
        }
        return *this;
    }

    template <typename OtherValue,
              class = typename std::enable_if<std::is_same<typename std::remove_reference<OtherValue>::type, ValueType>::value &&
                                              std::is_constructible<ValueType, OtherValue>::value &&
                                              std::is_assignable<ValueType&, OtherValue>::value>::type>
    inline Optional& operator=(OtherValue&& withValue)
    {
        if (this->engaged) {
            this->engagedValue = std::forward<OtherValue>(withValue);
        }
        else {
            ::new (std::addressof(this->engagedValue)) ValueType(std::forward<OtherValue>(withValue));
            this->engaged = true;
        }
        return *this;
    }

    template <typename... Arguments, class = typename std::enable_if<std::is_constructible<ValueType, Arguments...>::value>::type>
    inline void emplace(Arguments&&... arguments)
    {
        *this = nothing;
        ::new (std::addressof(this->engagedValue)) ValueType(std::forward<Arguments>(arguments)...);
        this->engaged = true;
    }

    template <typename OtherValue, class... Arguments,
              class = typename std::enable_if<std::is_constructible<ValueType, std::initializer_list<OtherValue>&, Arguments...>::value>::type>
    inline void emplace(std::initializer_list<OtherValue> initList, Arguments&&... arguments)
    {
        *this = nothing;
        ::new (std::addressof(this->engagedValue)) ValueType(initList, std::forward<Arguments>(arguments)...);
        this->engaged = true;
    }

    inline void
    swap(Optional& withOptional) noexcept(std::is_nothrow_move_constructible<ValueType>::value&& std::__is_nothrow_swappable<ValueType>::value)
    {
        if (this->engaged == withOptional.engaged) {
            if (this->engaged) {
                std::swap(this->engagedValue, withOptional.engagedValue);
            }
        }
        else {
            if (this->engaged) {
                ::new (std::addressof(withOptional.engagedValue)) ValueType(std::move(this->engagedValue));
                this->engagedValue.~ValueType();
            }
            else {
                ::new (std::addressof(this->engagedValue)) ValueType(std::move(withOptional.engagedValue));
                withOptional.engagedValue.~ValueType();
            }

            std::swap(this->engaged, withOptional.engaged);
        }
    }

    inline constexpr ValueType const* operator->() const
    {
        NXA_ASSERT_TRUE(this->engaged);
        return internalOperatorArrow(std::__has_operator_addressof<ValueType>{});
    }

    inline ValueType* operator->()
    {
        NXA_ASSERT_TRUE(this->engaged);
        return std::addressof(this->engagedValue);
    }

    inline constexpr const ValueType& operator*() const
    {
        NXA_ASSERT_TRUE(this->engaged);
        return this->engagedValue;
    }

    inline ValueType& operator*()
    {
        NXA_ASSERT_TRUE(this->engaged);
        return this->engagedValue;
    }

    inline constexpr explicit operator bool() const noexcept
    {
        return this->engaged;
    }

    inline constexpr ValueType const& value() const
    {
        if (!this->engaged) {
            throw BadOptionalAccess("Optional<T>::value: not engaged");
        }
        return this->engagedValue;
    }

    inline ValueType& value()
    {
        if (!this->engaged) {
            throw BadOptionalAccess("Optional<T>::value: not engaged");
        }
        return this->engagedValue;
    }

    template <typename OtherValue>
    inline constexpr ValueType valueOr(OtherValue&& withValue) const &
    {
        static_assert(std::is_copy_constructible<ValueType>::value, "Optional<T>::valueOr: T must be copy constructible");
        static_assert(std::is_convertible<OtherValue, ValueType>::value, "Optional<T>::valueOr: OtherType must be convertible to T");
        return this->engaged ? this->engagedValue : static_cast<ValueType>(std::forward<OtherValue>(withValue));
    }

    template <typename OtherValue>
    inline ValueType valueOr(OtherValue&& withValue) &&
    {
        static_assert(std::is_move_constructible<ValueType>::value, "Optional<T>::valueOr: T must be move constructible");
        static_assert(std::is_convertible<OtherValue, ValueType>::value, "Optional<T>::valueOr: OtherType must be convertible to T");
        return this->engaged ? std::move(this->engagedValue) : static_cast<ValueType>(std::forward<OtherValue>(withValue));
    }

private:
    inline ValueType const* internalOperatorArrow(std::true_type) const
    {
        return std::addressof(this->engagedValue);
    }

    inline constexpr ValueType const* internalOperatorArrow(std::false_type) const
    {
        return &this->engagedValue;
    }
};

template <typename ValueT>
inline constexpr bool operator==(const Optional<ValueT>& xParm, const Optional<ValueT>& yParm)
{
    if (static_cast<bool>(xParm) != static_cast<bool>(yParm)) {
        return false;
    }

    if (!static_cast<bool>(xParm)) {
        return true;
    }

    return *xParm == *yParm;
}

template <typename ValueT>
inline constexpr bool operator<(const Optional<ValueT>& xParm, const Optional<ValueT>& yParm)
{
    if (!static_cast<bool>(yParm)) {
        return false;
    }

    if (!static_cast<bool>(xParm)) {
        return true;
    }

    return std::less<ValueT>{}(*xParm, *yParm);
}

template <typename ValueT>
inline constexpr bool operator==(const Optional<ValueT>& xParm, NothingT) noexcept
{
    return !static_cast<bool>(xParm);
}

template <typename ValueT>
inline constexpr bool operator==(NothingT, const Optional<ValueT>& xParm) noexcept
{
    return !static_cast<bool>(xParm);
}

template <typename ValueT>
inline constexpr bool operator<(const Optional<ValueT>&, NothingT) noexcept
{
    return false;
}

template <typename ValueT>
inline constexpr bool operator<(NothingT, const Optional<ValueT>& xParm) noexcept
{
    return static_cast<bool>(xParm);
}

template <typename ValueT>
inline constexpr bool operator==(const Optional<ValueT>& xParm, const ValueT& withValue)
{
    return static_cast<bool>(xParm) ? *xParm == withValue : false;
}

template <typename ValueT>
inline constexpr bool operator==(const ValueT& withValue, const Optional<ValueT>& xParm)
{
    return static_cast<bool>(xParm) ? *xParm == withValue : false;
}

template <typename ValueT>
inline constexpr bool operator<(const Optional<ValueT>& xParm, const ValueT& withValue)
{
    return static_cast<bool>(xParm) ? std::less<ValueT>{}(*xParm, withValue) : true;
}

template <typename ValueT>
inline constexpr bool operator<(const ValueT& withValue, const Optional<ValueT>& xParm)
{
    return static_cast<bool>(xParm) ? std::less<ValueT>{}(withValue, *xParm) : false;
}

template <typename ValueT>
inline void swap(Optional<ValueT>& xParm, Optional<ValueT>& yParm) noexcept(noexcept(xParm.swap(yParm)))
{
    xParm.swap(yParm);
}

template <typename ValueT>
inline constexpr Optional<typename std::decay<ValueT>::type> makeOptional(ValueT&& withValue)
{
    return Optional<typename std::decay<ValueT>::type>(std::forward<ValueT>(withValue));
}

template <typename T, typename Function>
auto maybe(const NxA::Optional<T>& arg, Function&& f) -> Optional<typename std::result_of<Function(const T&)>::type>
{
    if (!arg) {
        return nothing;
    }
    return {f(*arg)};
}

template <typename T>
struct TypeName<Optional<T>>
{
    static const character* get()
    {
        return TypeName<T>::get();
    }
};
}
namespace std {
template <typename ValueT>
struct hash<NxA::Optional<ValueT>>
{
    inline size_t operator()(const NxA::Optional<ValueT>& withOptional) const
    {
        return static_cast<bool>(withOptional) ? hash<ValueT>()(*withOptional) : 0;
    }
};
}
