//
//  NxASeratoDbUtility.h
//  SeratoDB
//
//  Created by Didier Malenfant on 2/4/15.
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

#ifndef __SeratoDB__NxASeratoDbUtility__
#define __SeratoDB__NxASeratoDbUtility__

#include <string>
#include <vector>

namespace NxA {
    #pragma mark Containers
    typedef std::unique_ptr<const std::string> StringPtr;
    typedef std::vector<StringPtr> StringVector;
    typedef std::unique_ptr<StringVector> StringVectorPtr;
    typedef std::vector<char> CharVector;
    typedef std::unique_ptr<CharVector> CharVectorPtr;
    typedef std::unique_ptr<const CharVector> ConstCharVectorPtr;

    #pragma mark Utility Functions
    StringPtr convertUTF16ToStdString(const char16_t* characters, int numberOfCharacters);
    void writeStringAsUTF16At(const char* characters, void* destination);

    StringVectorPtr splitStringIntoOneStringForEachLine(const std::string& text);

    uint32_t bigEndianUInt32ValueAt(const void* ptr);
    uint16_t bigEndianUInt16ValueAt(const void* ptr);
    void writeBigEndianUInt32ValueAt(uint32_t value, void* ptr);
    void writeBigEndianUInt16ValueAt(uint16_t value, void* ptr);

    bool containsAValidSeratoFolder(const char* folderPath);

    StringPtr seratoFolderPathForFolder(const char* folderPath);
    StringPtr databaseFilePathForSeratoFolder(const char* seratoFolderPath);
    StringPtr crateOrderFilePathForSeratoFolder(const char* seratoFolderPath);
    StringPtr crateFilePathForCrateNameInSeratoFolder(const char* crateName, const char* seratoFolderPath);

    StringPtr joinPaths(const char* firstPath, const char* secondPath);
    StringPtr removePrefixFromPath(const char* prefixPath, const char* fullPath);

    bool fileExistsAt(const char* filePath);
    size_t sizeOfFileAt(const char* filePath);
    time_t modificationDateInSecondsSince1970ForFile(const char* filePath);

    CharVectorPtr readFileAt(const char* filePath);
    void writeToFile(const char* filePath, const CharVector& content);
}

#endif /* defined(__SeratoDB__NxASeratoDbUtility__) */
