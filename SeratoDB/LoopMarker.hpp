//
//  Copyright (c) 2015 Next Audio Labs, LLC. All rights reserved.
//
//  This file contains confidential and proprietary information of Serato
//  Inc. LLP ("Serato"). No use is permitted without express written
//  permission of Serato. If you are not a party to a Confidentiality/
//  Non-Disclosure Agreement with Serato, please immediately delete this
//  file as well as all copies in your possession. For further information,
//  please refer to the modified MIT license provided with this library,
//  or email licensing@serato.com.
//

#pragma once

#include <SeratoDB/DbUtility.hpp>

#include <vector>

namespace NxA { namespace Serato {
    #pragma mark Forward declarations
    class LoopMarker;

    #pragma mark Containers
    typedef std::unique_ptr<const LoopMarker> LoopMarkerPtr;
    typedef std::vector<LoopMarkerPtr> LoopMarkerVector;
    typedef std::unique_ptr<LoopMarkerVector> LoopMarkerVectorPtr;

    #pragma mark Class Declaration
    class LoopMarker
    {
    private:
        #pragma mark Private Instance Variable
        uint32_t p_startPositionInMilliSeconds;
        uint32_t p_endPositionInMilliSeconds;

        uint32_t p_index;

        std::string p_label;

    public:
        #pragma mark Constructors
        explicit LoopMarker(const char* id3TagStart);
        explicit LoopMarker(const std::string& label,
                            uint32_t startPositionInMilliseconds,
                            uint32_t endPositionInMilliseconds,
                            uint16_t index) :
                    p_startPositionInMilliSeconds(startPositionInMilliseconds),
                    p_endPositionInMilliSeconds(endPositionInMilliseconds),
                    p_index(index),
                    p_label(label) { }

        #pragma mark Instance Methods
        uint32_t startPositionInMilliseconds(void) const;
        uint32_t endPositionInMilliseconds(void) const;
        uint16_t index(void) const;
        const std::string& label(void) const;

        void addId3TagTo(CharVector& data) const;
    };
} }
