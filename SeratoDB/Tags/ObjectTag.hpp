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

#include <Base/Base.hpp>

namespace NxA { namespace Serato {
    NXA_GENERATED_FORWARD_DECLARATIONS_FOR(ObjectTag);

    class ObjectTag : public Tag {
        NXA_GENERATED_DECLARATIONS_FOR(NxA::Serato, ObjectTag);
        
    public:
        #pragma mark Factory Methods
        static ObjectTag::Pointer tagWithMemoryAt(const byte* tagAddress);
        static ObjectTag::Pointer tagWithIdentifierAndValue(uinteger32 identifier, Tag::Array::Pointer const& content);

        #pragma mark Instance Methods
        bool hasSubTagForIdentifier(uinteger32 identifier) const;

        Tag::ConstPointer const& subTagForIdentifier(uinteger32 identifier) const;
        Tag::Pointer const& subTagForIdentifier(uinteger32 identifier);

        void addSubTag(Tag::Pointer const& tag);

        void addTo(Blob::Pointer const& destination) const;
    };
} }
