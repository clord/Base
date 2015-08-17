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

#include "SeratoDB/TrackEntry.hpp"
#include "SeratoDB/Crate.hpp"
#include "Tags/ObjectTag.hpp"
#include "Tags/PathTag.hpp"
#include "Tags/CrateV1Tags.hpp"
#include "Base/Test.hpp"

using namespace testing;
using namespace NxA;
using namespace NxA::Serato;

NXA_CONTAINS_TEST_SUITE_NAMED(SeratoDB_TrackEntry_Tests);

TEST(SeratoDB_TrackEntry, EntryWithTagOnVolume_EntryWithInitialValues_ReturnsAValidEntry)
{
    // -- Given.
    auto tags = Tag::Array::array();
    tags->append(PathTag::tagWithIdentifierAndValue(trackEntryPathTagIdentifier, String::stringWith("Users/didier/Music/Gigs/02 Money On My Mind (MK Remix).m4a")));
    auto tag = ObjectTag::tagWithIdentifierAndValue(trackEntryTagIdentifier, tags);
    auto volumePath = String::stringWith("");

    // -- When.
    auto entry = TrackEntry::entryWithTagOnVolume(tag, volumePath);

    // -- Then.
    ASSERT_STREQ("/Users/didier/Music/Gigs/02 Money On My Mind (MK Remix).m4a", entry->trackFilePath()->toUTF8());
}

TEST(SeratoDB_TrackEntry, EntryWithTrackFileAtOnVolume_EntryWithInitialValues_ReturnsAValidEntry)
{
    // -- Given.
    auto filePath = String::stringWith("Users/didier/Music/Gigs/02 Money On My Mind (MK Remix).m4a");
    auto volumePath = String::stringWith("");

    // -- When.
    auto entry = TrackEntry::entryWithTrackFileAtOnVolume(filePath, volumePath);

    // -- Then.
    ASSERT_STREQ("/Users/didier/Music/Gigs/02 Money On My Mind (MK Remix).m4a", entry->trackFilePath()->toUTF8());
}

TEST(SeratoDB_TrackEntry, HasParentCrate_EntryWithAParentCrate_ReturnsTrue)
{
    // -- Given.
    auto crate = Crate::crateWithNameInFolderOnVolume(String::stringWith("MyFolder%%MyCrate1"),
                                                      String::stringWith(""), String::stringWith(""));
    auto entry = TrackEntry::entryWithTrackFileAtOnVolume(String::stringWith("Users/didier/Music/Gigs/02 Money On My Mind (MK Remix).m4a"), String::stringWith(""));
    crate->addTrackEntry(entry);

    // -- When.
    // -- Then.
    ASSERT_TRUE(entry->hasParentCrate());
}

TEST(SeratoDB_TrackEntry, HasParentCrate_EntryWithNoParentCrate_ReturnsFalse)
{
    // -- Given.
    auto entry = TrackEntry::entryWithTrackFileAtOnVolume(String::stringWith("Users/didier/Music/Gigs/02 Money On My Mind (MK Remix).m4a"), String::stringWith(""));

    // -- When.
    // -- Then.
    ASSERT_FALSE(entry->hasParentCrate());
}

TEST(SeratoDB_TrackEntry, HasParentCrate_EntryWithParentCrateRemoved_ReturnsFalse)
{
    // -- Given.
    auto crate = Crate::crateWithNameInFolderOnVolume(String::stringWith("MyFolder%%MyCrate1"),
                                                      String::stringWith(""), String::stringWith(""));
    auto entry = TrackEntry::entryWithTrackFileAtOnVolume(String::stringWith("Users/didier/Music/Gigs/02 Money On My Mind (MK Remix).m4a"), String::stringWith(""));
    crate->addTrackEntry(entry);
    crate->removeTrackEntry(entry);

    // -- When.
    // -- Then.
    ASSERT_FALSE(entry->hasParentCrate());
}

TEST(SeratoDB_TrackEntry, ParentCrate_EntryWithAParentCrate_ReturnsParentCrate)
{
    // -- Given.
    auto crate = Crate::crateWithNameInFolderOnVolume(String::stringWith("MyFolder%%MyCrate1"),
                                                      String::stringWith(""), String::stringWith(""));
    auto entry = TrackEntry::entryWithTrackFileAtOnVolume(String::stringWith("Users/didier/Music/Gigs/02 Money On My Mind (MK Remix).m4a"), String::stringWith(""));
    crate->addTrackEntry(entry);

    // -- When.
    // -- Then.
    ASSERT_EQ(&(*crate), &entry->parentCrate());
}

TEST(SeratoDB_TrackEntry, ParentCrate_EntryWithoutAParentCrate_ThrowsException)
{
    // -- Given.
    auto entry = TrackEntry::entryWithTrackFileAtOnVolume(String::stringWith("Test/MyFile.mp4"), String::stringWith(""));

    // -- When.
    // -- Then.
    ASSERT_THROW(entry->parentCrate(), NxA::Exception);
}

TEST(SeratoDB_TrackEntry, SetParentCrate_AParentCrate_SetsTheParentCrate)
{
    // -- Given.
    auto crate = Crate::crateWithNameInFolderOnVolume(String::stringWith("MyFolder%%MyCrate1"),
                                                      String::stringWith(""), String::stringWith(""));
    auto entry = TrackEntry::entryWithTrackFileAtOnVolume(String::stringWith("Users/didier/Music/Gigs/02 Money On My Mind (MK Remix).m4a"), String::stringWith(""));

    // -- When.
    entry->setParentCrate(crate);

    // -- Then.
    ASSERT_TRUE(entry->hasParentCrate());
    ASSERT_EQ(&(*crate), &entry->parentCrate());
}

TEST(SeratoDB_TrackEntry, RemoveFromParentCrate_AnEntryWithAParentCrate_RemovesTheParentCrate)
{
    // -- Given.
    auto crate = Crate::crateWithNameInFolderOnVolume(String::stringWith("MyFolder%%MyCrate1"),
                                                      String::stringWith(""), String::stringWith(""));
    auto entry = TrackEntry::entryWithTrackFileAtOnVolume(String::stringWith("Users/didier/Music/Gigs/02 Money On My Mind (MK Remix).m4a"), String::stringWith(""));
    crate->addTrackEntry(entry);

    // -- When.
    entry->removeFromParentCrate();

    // -- Then.
    ASSERT_FALSE(entry->hasParentCrate());
    ASSERT_EQ(0, crate->trackEntries().length());
}

TEST(SeratoDB_TrackEntry, RemoveFromParentCrate_AnEntryWithoutAParentCrate_ThrowsException)
{
    // -- Given.
    auto entry = TrackEntry::entryWithTrackFileAtOnVolume(String::stringWith("Users/didier/Music/Gigs/02 Money On My Mind (MK Remix).m4a"), String::stringWith(""));

    // -- When.
    // -- Then.
    ASSERT_THROW(entry->removeFromParentCrate(), NxA::Exception);
}

TEST(SeratoDB_TrackEntry, TagForEntry_AnEntryWithValues_ReturnsTheCorrectTag)
{
    // -- Given.
    auto filePath = String::stringWith("Users/didier/Music/Gigs/02 Money On My Mind (MK Remix).m4a");
    auto volumePath = String::stringWith("");
    auto entry = TrackEntry::entryWithTrackFileAtOnVolume(filePath, volumePath);

    // -- When.
    auto& tag = entry->tagForEntry();

    // -- Then.
    auto& objectTag = dynamic_cast<const ObjectTag&>(tag);
    ASSERT_EQ(trackEntryTagIdentifier, objectTag.identifier());
    ASSERT_EQ(1, objectTag.numberOfSubTags());
    auto& pathTag = dynamic_cast<const PathTag&>(objectTag.subTagForIdentifier(trackEntryPathTagIdentifier));
    ASSERT_EQ(trackEntryPathTagIdentifier, pathTag.identifier());
    ASSERT_STREQ(filePath->toUTF8(), pathTag.value().toUTF8());
}
