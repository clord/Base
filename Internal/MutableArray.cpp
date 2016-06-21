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

#include "Base/Internal/MutableArray.hpp"
#include "Base/String.hpp"

using namespace NxA;

#pragma mark Utility Methods
    
template <class T> String descriptionOfObjectsInArrayAtAddress(const MutableArrayInternal<T>& array)
{
    auto result = String::stringWithFormat("Array at %08p with %ld elements:", &array, array.length());
    for (count index = 0; index < array.length(); ++index) {
        auto& item = array[index];
        result->append(String::stringWithFormat("\n  %ld: %s", index, item.description()->asUTF8()));
    }

    return result;
}
