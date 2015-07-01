//
//  Copyright (c) 2015 Next Audio Labs, LLC. All rights reserved.
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

#include "Base/Debugger.hpp"
#include "Base/Exception.hpp"

#ifdef DEBUG
// -- Replacement for printf, but only prints its message in DEBUG builds. Otherwise it compiles down to a NO-OP.
#define NXA_DLOG(...) { printf("%s: ", __PRETTY_FUNCTION__); printf(__VA_ARGS__); }

// -- Prints a message and throws an exception in all builds but also breaks into the debugger in DEBUG builds.
#define NXA_ALOG(...) { printf("%s: ", __PRETTY_FUNCTION__); printf(__VA_ARGS__); printf("\n");NxA::Debugger::launch();throw NxA::Exception(__VA_ARGS__); }

// -- NXA_ALOG_DEBUG does the same thing as ALog in DEBUG builds.
#define NXA_ALOG_DEBUG NXA_ALOG
#else
#define NXA_DLOG(...) do { } while (0)
#define NXA_ALOG(...) { printf("%s: ", __PRETTY_FUNCTION__); printf(__VA_ARGS__);throw NxA::Exception(__VA_ARGS__); }
#define NXA_ALOG_DEBUG(...) { printf("%s: ", __PRETTY_FUNCTION__); printf(__VA_ARGS__); }
#endif

// -- Replacements for assert which use NXA_ALOG().
#define NXA_ASSERT_NOT_NULL(expression) do { if ((expression) == nullptr) { NXA_ALOG("%s is nil.", #expression); } } while(0)
#define NXA_ASSERT_NULL(expression) do { if ((expression) != nullptr) { NXA_ALOG("%s is not nil.", #expression); } } while(0)
#define NXA_ASSERT_TRUE(expression) do { if (!(expression)) { NXA_ALOG("%s is false.", #expression); } } while(0)
#define NXA_ASSERT_FALSE(expression) do { if (expression) { NXA_ALOG("%s is true.", #expression); } } while(0)
#define NXA_ASSERT_EQ(expression1, expression2) do { if ((expression1) != (expression2)) { NXA_ALOG("%s is not equal to %s.", #expression1, #expression2); } } while(0)
#define NXA_ASSERT_NOT_EQ(expression1, expression2) do { if ((expression1) == (expression2)) { NXA_ALOG("%s is equal to %s.", #expression1, #expression2); } } while(0)

// -- Replacements for assert which use NXA_ALOG() and, in non-DEBUG builds, only prints its message.
#define NXA_ASSERT_NOT_NULL_DEBUG(expression) do { if ((expression) == nullptr) { NXA_ALOG_DEBUG("%s is nil.", #expression); } } while(0)
#define NXA_ASSERT_NULL_DEBUG(expression) do { if ((expression) != nullptr) { NXA_ALOG_DEBUG("%s is not nil.", #expression); } } while(0)
#define NXA_ASSERT_TRUE_DEBUG(expression) do { if (!(expression)) { NXA_ALOG_DEBUG("%s is false.", #expression); } } while(0)
#define NXA_ASSERT_FALSE_DEBUG(expression) do { if (expression) { NXA_ALOG_DEBUG("%s is true.", #expression); } } while(0)
#define NXA_ASSERT_EQ_DEBUG(expression1, expression2) do { if ((expression1) != (expression2)) { NXA_ALOG_DEBUG("%s is not equal to %s.", #expression1, #expression2); } } while(0)
#define NXA_ASSERT_NOT_EQ_DEBUG(expression1, expression2) do { if ((expression1) == (expression2)) { NXA_ALOG_DEBUG("%s is equal to %s.", #expression1, #expression2); } } while(0)
