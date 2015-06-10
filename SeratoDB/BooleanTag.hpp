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

#include <SeratoDB/Tag.hpp>
#include <SeratoDB/DbUtility.hpp>

namespace NxA {
    namespace Serato {
    #pragma mark Class Declaration
    class BooleanTag : public Tag
    {
    private:
        #pragma mark Private Instance Variables
        bool p_value;

    public:
        #pragma mark Constructors
        explicit BooleanTag(const void* tagAddress);
        explicit BooleanTag(const uint32_t& identifier, const bool& value) :
                            Tag(identifier), p_value(value) { }

        #pragma mark Instance Methods
        const uint32_t& identifier(void) const;
        const bool& value(void) const;
        bool& value(void);

        void addTo(CharVector& destination) const;
    };
}
}
