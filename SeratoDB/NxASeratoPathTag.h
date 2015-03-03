//
//  NxASeratoPathTag.h
//  SeratoDB
//
//  Created by Didier Malenfant on 2/27/15.
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

#ifndef __SeratoDB__NxASeratoPathTag__
#define __SeratoDB__NxASeratoPathTag__

#include <SeratoDB/NxASeratoTag.h>
#include <SeratoDB/NxASeratoDbUtility.h>

#include <string>

namespace NxA {
    #pragma mark Class Declaration
    class SeratoPathTag : public SeratoTag
    {
    private:
        #pragma mark Private Instance Variables
        ConstStringPtr p_value;

    public:
        #pragma mark Constructors
        explicit SeratoPathTag(const void* tagAddress);
        explicit SeratoPathTag(const uint32_t& identifier, const char* value) :
                               SeratoTag(identifier),
                               p_value(std::make_unique<std::string>(value)) { }

        #pragma mark Instance Methods
        const uint32_t& identifier(void) const;
        const std::string& value(void) const;
        std::string& value(void);

        void addTo(CharVector& destination) const;
    };
}

#endif /* defined(__SeratoDB__NxASeratoPathTag__) */
