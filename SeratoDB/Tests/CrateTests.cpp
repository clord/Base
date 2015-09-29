//
//  Copyright (c) 2015 Next Audio Labs, LLC. All rights reserved.
//
//  This file contains confidential and proprietary information of Next
//  Audio Labs, LLC ("Next"). No use is permitted without express written
//  permission of Next. If you are not a party to a Confidentiality/
//  Non-Disclosure Agreement with Next, please immediately delete this
//  file as well as all copies in your possession. For further information,
//  please email info@nextaudiolabs.com.
//

#include "SeratoDB/Crate.hpp"
#include "Base/Test.hpp"

using NxA::String;

using namespace testing;
using namespace NxA::Serato;

NXA_CONTAINS_TEST_SUITE_NAMED(SeratoDB_Crate_Tests);

TEST(SeratoDB_Crate, CrateWithNameInFolderOnVolume_CrateInitialValues_ReturnsAValidCrate)
{
    // -- Given.
    auto crateName = String::stringWith("MyFolder%%MyCrate");
    auto folderPath = String::stringWith("");
    auto volumePath = String::stringWith("");

    // -- When.
    auto crate = Crate::crateWithNameInFolderOnVolume(crateName, folderPath, volumePath);

    // -- Then.
    ASSERT_STREQ("MyCrate", crate->crateName().toUTF8());
    ASSERT_STREQ("MyFolder%%MyCrate", crate->crateFullName().toUTF8());
}

// -- TDOO: Add test for addFullCrateNameWithPrefixAndRecurseToChildren()

TEST(SeratoDB_Crate, AddCrate_AddingTwoCratesToACrate_AddsTheTwoCratesCorrectly)
{
    // -- Given.
    auto crate1 = Crate::crateWithNameInFolderOnVolume(String::stringWith("MyFolder%%MyCrate1"),
                                                       String::stringWith(""), String::stringWith(""));
    auto crate2 = Crate::crateWithNameInFolderOnVolume(String::stringWith("MyFolder%%MyCrate2"),
                                                       String::stringWith(""), String::stringWith(""));
    auto crate3 = Crate::crateWithNameInFolderOnVolume(String::stringWith("MyFolder%%MyCrate3"),
                                                       String::stringWith(""), String::stringWith(""));

    // -- When.
    crate1->addCrate(crate2);
    crate1->addCrate(crate3);

    // -- Then.
    auto& crates = crate1->crates();
    auto& tracks = crate1->trackEntries();
    ASSERT_EQ(0, tracks.length());
    ASSERT_EQ(2, crates.length());
    ASSERT_EQ(&(*crate2), &crates[0]);
    ASSERT_EQ(&(*crate3), &crates[1]);
    ASSERT_TRUE(crate2->hasParentCrate());
    ASSERT_TRUE(crate3->hasParentCrate());
}

TEST(SeratoDB_Crate, AddCrate_AddingACrateWhichAlreadyHasAParent_ThrowsAnException)
{
    // -- Given.
    auto crate1 = Crate::crateWithNameInFolderOnVolume(String::stringWith("MyFolder%%MyCrate1"),
                                                       String::stringWith(""), String::stringWith(""));
    auto crate2 = Crate::crateWithNameInFolderOnVolume(String::stringWith("MyFolder%%MyCrate2"),
                                                       String::stringWith(""), String::stringWith(""));
    auto crate3 = Crate::crateWithNameInFolderOnVolume(String::stringWith("MyFolder%%MyCrate3"),
                                                       String::stringWith(""), String::stringWith(""));
    crate2->addCrate(crate3);

    // -- When.
    // -- Then.
    ASSERT_THROW(crate1->addCrate(crate3), NxA::Exception);
}

TEST(SeratoDB_Crate, RemoveCrate_ACrateWithTwoCrates_RemovesCrateCorrectly)
{
    // -- Given.
    auto crate1 = Crate::crateWithNameInFolderOnVolume(String::stringWith("MyFolder%%MyCrate1"),
                                                       String::stringWith(""), String::stringWith(""));
    auto crate2 = Crate::crateWithNameInFolderOnVolume(String::stringWith("MyFolder%%MyCrate2"),
                                                       String::stringWith(""), String::stringWith(""));
    auto crate3 = Crate::crateWithNameInFolderOnVolume(String::stringWith("MyFolder%%MyCrate3"),
                                                       String::stringWith(""), String::stringWith(""));
    crate1->addCrate(crate2);
    crate1->addCrate(crate3);

    // -- When.
    crate1->removeCrate(crate2);

    // -- Then.
    auto& crates = crate1->crates();
    auto& tracks = crate1->trackEntries();
    ASSERT_EQ(0, tracks.length());
    ASSERT_EQ(1, crates.length());
    ASSERT_EQ(&(*crate3), &crates[0]);
    ASSERT_FALSE(crate2->hasParentCrate());
    ASSERT_TRUE(crate3->hasParentCrate());
}

TEST(SeratoDB_Crate, AddTrackEntry_ACrateAndTwoTrackEntries_AddsEntryCorrectly)
{
    // -- Given.
    auto crate = Crate::crateWithNameInFolderOnVolume(String::stringWith("MyFolder%%MyCrate1"),
                                                      String::stringWith(""), String::stringWith(""));
    auto entry1 = TrackEntry::entryWithTrackFileAtOnVolume(String::stringWith("Test/MyFile.mp4"), String::stringWith(""));
    auto entry2 = TrackEntry::entryWithTrackFileAtOnVolume(String::stringWith("Test/MyFile2.mp4"), String::stringWith(""));

    // -- When.
    crate->addTrackEntry(entry1);
    crate->addTrackEntry(entry2);

    // -- Then.
    auto& crates = crate->crates();
    auto& tracks = crate->trackEntries();
    ASSERT_EQ(0, crates.length());
    ASSERT_EQ(2, tracks.length());
    ASSERT_EQ(&(*entry1), &tracks[0]);
    ASSERT_EQ(&(*entry2), &tracks[1]);
    ASSERT_TRUE(entry1->hasParentCrate());
    ASSERT_TRUE(entry2->hasParentCrate());
}

TEST(SeratoDB_Crate, AddTrackEntry_ACrateAndATrackEntryAlreadyInAnotherCrate_ThrowsException)
{
    // -- Given.
    auto crate1 = Crate::crateWithNameInFolderOnVolume(String::stringWith("MyFolder%%MyCrate1"),
                                                       String::stringWith(""), String::stringWith(""));
    auto crate2 = Crate::crateWithNameInFolderOnVolume(String::stringWith("MyFolder%%MyCrate2"),
                                                       String::stringWith(""), String::stringWith(""));
    auto entry = TrackEntry::entryWithTrackFileAtOnVolume(String::stringWith("Test/MyFile.mp4"), String::stringWith(""));
    crate2->addTrackEntry(entry);

    // -- When.
    // -- Then.
    ASSERT_THROW(crate1->addTrackEntry(entry), NxA::Exception);
}

TEST(SeratoDB_Crate, RemoveTrackEntry_ACrateAndATwoTrackEntried_AddsEntryCorrectly)
{
    // -- Given.
    auto crate = Crate::crateWithNameInFolderOnVolume(String::stringWith("MyFolder%%MyCrate1"),
                                                      String::stringWith(""), String::stringWith(""));
    auto entry1 = TrackEntry::entryWithTrackFileAtOnVolume(String::stringWith("Test/MyFile.mp4"), String::stringWith(""));
    auto entry2 = TrackEntry::entryWithTrackFileAtOnVolume(String::stringWith("Test/MyFile2.mp4"), String::stringWith(""));
    crate->addTrackEntry(entry1);
    crate->addTrackEntry(entry2);

    // -- When.
    crate->removeTrackEntry(entry1);

    // -- Then.
    auto& crates = crate->crates();
    auto& tracks = crate->trackEntries();
    ASSERT_EQ(0, crates.length());
    ASSERT_EQ(1, tracks.length());
    ASSERT_EQ(&(*entry2), &tracks[0]);
    ASSERT_FALSE(entry1->hasParentCrate());
    ASSERT_TRUE(entry2->hasParentCrate());
}

TEST(SeratoDB_Crate, HasParentCrate_ACrateWithAParent_ReturnsTrue)
{
    // -- Given.
    auto crate1 = Crate::crateWithNameInFolderOnVolume(String::stringWith("MyFolder%%MyCrate1"),
                                                       String::stringWith(""), String::stringWith(""));
    auto crate2 = Crate::crateWithNameInFolderOnVolume(String::stringWith("MyFolder%%MyCrate2"),
                                                       String::stringWith(""), String::stringWith(""));
    crate1->addCrate(crate2);

    // -- When.
    // -- Then.
    ASSERT_TRUE(crate2->hasParentCrate());
}

TEST(SeratoDB_Crate, HasParentCrate_ACrateWithNoParent_ReturnsFalse)
{
    // -- Given.
    auto crate1 = Crate::crateWithNameInFolderOnVolume(String::stringWith("MyFolder%%MyCrate1"),
                                                       String::stringWith(""), String::stringWith(""));
    auto crate2 = Crate::crateWithNameInFolderOnVolume(String::stringWith("MyFolder%%MyCrate2"),
                                                       String::stringWith(""), String::stringWith(""));

    // -- When.
    // -- Then.
    ASSERT_FALSE(crate2->hasParentCrate());
}

TEST(SeratoDB_Crate, HasParentCrate_ACrateWithNoParentBecauseItWasRemoved_ReturnsFalse)
{
    // -- Given.
    auto crate1 = Crate::crateWithNameInFolderOnVolume(String::stringWith("MyFolder%%MyCrate1"),
                                                       String::stringWith(""), String::stringWith(""));
    auto crate2 = Crate::crateWithNameInFolderOnVolume(String::stringWith("MyFolder%%MyCrate2"),
                                                       String::stringWith(""), String::stringWith(""));
    crate1->addCrate(crate2);
    crate1->removeCrate(crate2);

    // -- When.
    // -- Then.
    ASSERT_FALSE(crate2->hasParentCrate());
}

TEST(SeratoDB_Crate, ParentCrate_ACrateWithAParent_ReturnsTheCorrectCrate)
{
    // -- Given.
    auto crate1 = Crate::crateWithNameInFolderOnVolume(String::stringWith("MyFolder%%MyCrate1"),
                                                       String::stringWith(""), String::stringWith(""));
    auto crate2 = Crate::crateWithNameInFolderOnVolume(String::stringWith("MyFolder%%MyCrate2"),
                                                       String::stringWith(""), String::stringWith(""));
    crate1->addCrate(crate2);

    // -- When.
    // -- Then.
    ASSERT_EQ(&(*crate1), &crate2->parentCrate());
}

TEST(SeratoDB_Crate, ParentCrate_ACrateWithoutAParent_ThrowsException)
{
    // -- Given.
    auto crate2 = Crate::crateWithNameInFolderOnVolume(String::stringWith("MyFolder%%MyCrate2"),
                                                       String::stringWith(""), String::stringWith(""));

    // -- When.
    // -- Then.
    ASSERT_THROW(crate2->parentCrate(), NxA::Exception);
}

TEST(SeratoDB_Crate, RemoveFromParentCrate_ACrateWithAParent_RemovesTheCrateFromItsParent)
{
    // -- Given.
    auto crate1 = Crate::crateWithNameInFolderOnVolume(String::stringWith("MyFolder%%MyCrate1"),
                                                       String::stringWith(""), String::stringWith(""));
    auto crate2 = Crate::crateWithNameInFolderOnVolume(String::stringWith("MyFolder%%MyCrate2"),
                                                       String::stringWith(""), String::stringWith(""));
    crate1->addCrate(crate2);

    // -- When.
    crate2->removeFromParentCrate();

    // -- Then.
    ASSERT_EQ(0, crate1->crates().length());
    ASSERT_FALSE(crate2->hasParentCrate());
}

TEST(SeratoDB_Crate, RemoveFromParentCrate_ACrateWithoutParent_ThrowsException)
{
    // -- Given.
    auto crate2 = Crate::crateWithNameInFolderOnVolume(String::stringWith("MyFolder%%MyCrate2"),
                                                       String::stringWith(""), String::stringWith(""));

    // -- When.
    // -- Then.
    ASSERT_THROW(crate2->removeFromParentCrate(), NxA::Exception);
}

// -- TDOO: Add test for crateFilePath()
// -- TDOO: Add test for resetModificationFlags()
// -- TDOO: Add test for childrenCratesWereModified()
// -- TDOO: Add test for childrenCratesWereModified()

TEST(SeratoDB_Crate, RemoveAndReturnTrackEntries_ACrateWithTwoTrackEntries_ReturnsTheTwoEntriesSeperateFromTheirParent)
{
    // -- Given.
    auto crate = Crate::crateWithNameInFolderOnVolume(String::stringWith("MyFolder%%MyCrate1"),
                                                      String::stringWith(""), String::stringWith(""));
    auto entry1 = TrackEntry::entryWithTrackFileAtOnVolume(String::stringWith("Test/MyFile.mp4"), String::stringWith(""));
    auto entry2 = TrackEntry::entryWithTrackFileAtOnVolume(String::stringWith("Test/MyFile2.mp4"), String::stringWith(""));
    crate->addTrackEntry(entry1);
    crate->addTrackEntry(entry2);

    // -- When.
    auto result = crate->removeAndReturnTrackEntries();

    // -- Then.
    ASSERT_EQ(0, crate->crates().length());
    ASSERT_EQ(0, crate->trackEntries().length());
    ASSERT_EQ(2, result->length());
    ASSERT_EQ(&(*entry1), &(*result)[0]);
    ASSERT_EQ(&(*entry2), &(*result)[1]);
    ASSERT_FALSE(entry1->hasParentCrate());
    ASSERT_FALSE(entry2->hasParentCrate());
}

TEST(SeratoDB_Crate, RemoveAndReturnTrackEntries_ACrateWithNoTrackEntries_ReturnsAnEmptyArray)
{
    // -- Given.
    auto crate = Crate::crateWithNameInFolderOnVolume(String::stringWith("MyFolder%%MyCrate1"),
                                                      String::stringWith(""), String::stringWith(""));

    // -- When.
    auto result = crate->removeAndReturnTrackEntries();

    // -- Then.
    ASSERT_EQ(0, crate->crates().length());
    ASSERT_EQ(0, crate->trackEntries().length());
    ASSERT_EQ(0, result->length());
}

TEST(SeratoDB_Crate, RemoveAndReturnChildrenCrates_ACrateWithTwoChildCrates_ReturnsTheTwoCratesSeperateFromTheirParent)
{
    // -- Given.
    auto crate1 = Crate::crateWithNameInFolderOnVolume(String::stringWith("MyFolder%%MyCrate1"),
                                                       String::stringWith(""), String::stringWith(""));
    auto crate2 = Crate::crateWithNameInFolderOnVolume(String::stringWith("MyFolder%%MyCrate2"),
                                                       String::stringWith(""), String::stringWith(""));
    auto crate3 = Crate::crateWithNameInFolderOnVolume(String::stringWith("MyFolder%%MyCrate3"),
                                                       String::stringWith(""), String::stringWith(""));
    crate1->addCrate(crate2);
    crate1->addCrate(crate3);

    // -- When.
    auto result = crate1->removeAndReturnChildrenCrates();

    // -- Then.
    ASSERT_EQ(0, crate1->crates().length());
    ASSERT_EQ(0, crate1->trackEntries().length());
    ASSERT_EQ(2, result->length());
    ASSERT_EQ(&(*crate2), &(*result)[0]);
    ASSERT_EQ(&(*crate3), &(*result)[1]);
    ASSERT_FALSE(crate2->hasParentCrate());
    ASSERT_FALSE(crate3->hasParentCrate());
}

TEST(SeratoDB_Crate, RemoveAndReturnChildrenCrates_ACrateWithNoChildCrates_ReturnsAnEmptyArray)
{
    // -- Given.
    auto crate1 = Crate::crateWithNameInFolderOnVolume(String::stringWith("MyFolder%%MyCrate1"),
                                                       String::stringWith(""), String::stringWith(""));

    // -- When.
    auto result = crate1->removeAndReturnChildrenCrates();

    // -- Then.
    ASSERT_EQ(0, crate1->crates().length());
    ASSERT_EQ(0, crate1->trackEntries().length());
    ASSERT_EQ(0, result->length());
}
