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

#include "SeratoDB/CrateOrderFile.hpp"
#include "SeratoDB/Internal/CrateOrderFile.hpp"
#include "SeratoDB/Crate.hpp"

NXA_GENERATED_IMPLEMENTATION_IN_NAMESPACE_FOR_CLASS_WITH_PARENT(NxA::Serato, CrateOrderFile, Object);

using namespace NxA;
using namespace NxA::Serato;

#pragma mark Factory Methods

CrateOrderFile::Pointer CrateOrderFile::fileWithSeratoFolderInRootFolder(const String& seratoFolderPath,
                                                                         const String& rootFolderPath)
{
    auto rootCrate = Crate::crateWithNameInFolderOnVolume(String::string(), String::string(), String::string());
    auto crateOrderFilePath = CrateOrderFile::pathForFileInSeratoFolder(seratoFolderPath);
    auto internalObject = Internal::CrateOrderFile::Pointer(std::make_shared<Internal::CrateOrderFile>(crateOrderFilePath, rootCrate));
    auto newCrateOrderFile = CrateOrderFile::makeSharedWithInternal(NxA::Internal::Object::Pointer::dynamicCastFrom(internalObject));

    if (!File::fileExistsAt(crateOrderFilePath)) {
        return newCrateOrderFile;
    }

    auto subCratesDirectory = Crate::subCratesDirectoryPathInSeratoFolder(seratoFolderPath);
    auto subCratesFound = Internal::CrateOrderFile::cratesInSubCratesDirectory(subCratesDirectory);
    auto cratesInOrder = Internal::CrateOrderFile::readCratesNamesInCrateOrderFile(newCrateOrderFile->internal->crateOrderFilePath);

    Internal::CrateOrderFile::addCratesNamesAtTheStartOfUnlessAlreadyThere(*cratesInOrder, *subCratesFound);

    auto it = cratesInOrder->begin();
    auto crates = newCrateOrderFile->internal->childrenCratesOfCrateNamedUsingNameList(String::string(),
                                                                                       it,
                                                                                       cratesInOrder->end(),
                                                                                       seratoFolderPath,
                                                                                       rootFolderPath);
    for (auto& crate : *crates) {
        newCrateOrderFile->internal->rootCrate->addCrate(crate);
    }

    newCrateOrderFile->internal->rootCrate->resetModificationFlags();

    return newCrateOrderFile;
}

#pragma mark Class Methods

String::Pointer CrateOrderFile::pathForFileInSeratoFolder(const String& seratoFolderPath)
{
    auto joinedPath = File::joinPaths(seratoFolderPath, String::stringWith("neworder.pref"));
    return joinedPath;
}

#pragma mark Instance Methods

Crate& CrateOrderFile::rootCrate(void)
{
    return internal->rootCrate;
}

timestamp CrateOrderFile::modificationDateInSecondsSince1970(void) const
{
    return File::modificationDateInSecondsSince1970ForFile(internal->crateOrderFilePath);
}

void CrateOrderFile::saveIfModified(void) const
{
    internal->rootCrate->saveIfModifiedAndRecurseToChildren();

    if (!internal->rootCrate->childrenCratesWereModified()) {
        return;
    }

    auto result = String::string();
    result->append("[begin record]\n");
    internal->rootCrate->addFullCrateNameWithPrefixAndRecurseToChildren(result, "[crate]");
    for (auto& crateName : *internal->unknownCratesNames) {
        result->append("[crate]");
        result->append(crateName);
        result->append("\n");
    }
    result->append("[end record]\n");

    File::writeBlobToFileAt(result->toUTF16(), internal->crateOrderFilePath);
}
