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

#include <boost/scope_exit.hpp>
#include <stdexcept>

// -- Macros

#define NXA_EXCEPTION_NAMED_WITH_PARENT(exception_name, parent_class_name) \
        class exception_name : public parent_class_name { \
        public: \
            explicit exception_name(const character* reason) : parent_class_name(reason) { } \
            explicit exception_name(const Exception& other) : parent_class_name(other.what()) { } \
            virtual ~exception_name() = default; \
            static exception_name exceptionWith(const character* format, ...) \
            { \
                constexpr size_t formatStringBufferSize = 256; \
                character buffer[formatStringBufferSize]; \
                va_list args; \
                va_start(args, format); \
                vsnprintf(buffer, formatStringBufferSize, format, args); \
                va_end(args); \
                return exception_name(buffer); \
            } \
        };

#define NXA_SCOPE_EXIT \
        _Pragma("clang diagnostic push") \
        _Pragma("clang diagnostic ignored \"-Wshadow\"") \
        BOOST_SCOPE_EXIT

#define NXA_SCOPE_EXIT_END \
        BOOST_SCOPE_EXIT_END \
        _Pragma("clang diagnostic pop") \

// -- Public Interface

namespace NxA {

class Exception : public std::runtime_error
{
public:
    // -- Constructors & Destructors
    Exception() = delete;
    explicit Exception(const character* reason) : std::runtime_error(reason) { }
    ~Exception() override = default;
};

class FatalException : public std::logic_error
{
public:
    // -- Constructors & Destructors
    FatalException() = delete;
    explicit FatalException(const character* reason) : std::logic_error(reason) { }
    ~FatalException() override = default;
};
    
}
