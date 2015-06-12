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

#include <SeratoDb/Tags/Tag.hpp>
#include <SeratoDB/Utility.hpp>

namespace NxA { namespace Serato {
    #pragma mark Class Declaration
    class BlobTag : public Tag
    {
    private:
        #pragma mark Private Instance Variables
        CharVectorPtr p_value;

    public:
        #pragma mark Constructors
        explicit BlobTag(const void* tagAddress);
        explicit BlobTag(uint32_t identifier, ConstCharVectorPtr value) :
                         Tag(identifier),
                         p_value(std::make_unique<CharVector>(*value)) { }

        #pragma mark Instance Methods
        const CharVector& value(void) const;
        CharVector& value(void);

        void addTo(CharVector& destination) const;
    };
} }
