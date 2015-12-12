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

#include "Markers/Marker.hpp"

#include <Base/Base.hpp>
#include <Base/Internal/Object.hpp>

namespace NxA { namespace Serato { namespace Internal {
    struct Marker : public NxA::Internal::Object {
        NXA_GENERATED_INTERNAL_DECLARATIONS_FOR(NxA::Serato, Marker);
        
        enum MarkerType
        {
            eCueMarker = 1,
            eLoopMarker = 3,
            eEmptyMarker = 0,
        };
        
        static void addRawMarkerV1TagWithFieldsTo(MarkerType type, integer32 position, integer32 loopPos, integer32 loopIterations,
                                                  byte red, byte green, byte blue, Blob& data);
        
        static void addEncodedMarkerV1TagWithFieldsTo(MarkerType type, integer32 position, integer32 loopPos, integer32 loopIterations,
                                                      byte red, byte green, byte blue, Blob& data);
    };
} } }
