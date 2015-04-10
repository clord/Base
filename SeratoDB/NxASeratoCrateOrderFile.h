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

#ifndef __SeratoDB__NxASeratoCrateOrderFile__
#define __SeratoDB__NxASeratoCrateOrderFile__

#include <SeratoDB/NxASeratoDBUtility.h>
#include <SeratoDB/NxASeratoCrate.h>

namespace NxA {
    #pragma mark Forward declarations
    class SeratoCrateOrderFile;

    #pragma mark Containers
    typedef std::unique_ptr<const SeratoCrateOrderFile> SeratoCrateOrderFilePtr;

    #pragma mark Class Declaration
    class SeratoCrateOrderFile
    {
    private:
        #pragma mark Private Instance Variables
        ConstStringPtr p_crateOrderFilePath;

        SeratoCratePtr p_rootCrate;

        StringVectorPtr p_unknownCrates;

        #pragma mark Private Instance Methods
        SeratoCrateVectorPtr p_childrenCratesOfCrateNamedUsingNameList(const std::string& name,
                                                                       StringVector::iterator& it,
                                                                       const StringVector::iterator& end,
                                                                       const char* seratoFolderPath,
                                                                       const char* rootFolderPath);

    public:
        #pragma mark Constructors
        explicit SeratoCrateOrderFile(const char* seratoFolderPath, const char* rootFolderPath);

        #pragma mark Instance Methods
        const SeratoCrate* rootCrate(void) const;

        void saveIfModified(void) const;
    };
}

#endif /* defined(__SeratoDB__NxASeratoCrateOrderFile__) */
