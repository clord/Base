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

#include "Tags/BooleanTag.hpp"
#include "Base/Test.hpp"

using namespace testing;
using namespace NxA;
using namespace NxA::Serato;

NXA_CONTAINS_TEST_SUITE_NAMED(SeratoDB_BooleanTag_Tests);

TEST(SeratoDB_BooleanTag, TagWithIdentifierAndTrueValue_TagCreated_TagHasCorrectValue)
{
    // -- Given.
    // -- When.
    auto tag = BooleanTag::tagWithIdentifierAndValue('btst', true);

    // -- Then.
    ASSERT_EQ('btst', tag->identifier());
    ASSERT_EQ(true, tag->value());
}

TEST(SeratoDB_BooleanTag, TagWithIdentifierAndFalseValue_TagCreated_TagHasCorrectValue)
{
    // -- Given.
    // -- When.
    auto tag = BooleanTag::tagWithIdentifierAndValue('btst', false);

    // -- Then.
    ASSERT_EQ('btst', tag->identifier());
    ASSERT_EQ(false, tag->value());
}

TEST(SeratoDB_BooleanTag, TagWithIdentifierAndValue_IncorrectIdentifier_ThrowsException)
{
    // -- Given.
    // -- When.
    // -- Then.
    ASSERT_THROW(BooleanTag::tagWithIdentifierAndValue('stst', true), NxA::Exception);
}

TEST(SeratoDB_BooleanTag, TagWithMemoryAt_TagCreated_TagHasCorrectValue)
{
    // -- Given.
    constexpr byte data[] = { 0x62, 0x74, 0x73, 0x74, 0x00, 0x00, 0x00, 0x01, 0x01 };

    // -- When.
    auto tag = BooleanTag::tagWithMemoryAt(data);

    // -- Then.
    ASSERT_EQ('btst', tag->identifier());
    ASSERT_EQ(true, tag->value());
}

TEST(SeratoDB_BooleanTag, TagWithMemoryAt_IncorrectIdentifier_ThrowsException)
{
    // -- Given.
    constexpr byte data[] = { 0x64, 0x74, 0x73, 0x74, 0x00, 0x00, 0x00, 0x01, 0x01 };

    // -- When.
    ASSERT_THROW(BooleanTag::tagWithMemoryAt(data), NxA::Exception);
}

TEST(SeratoDB_BooleanTag, TagWithMemoryAt_TagCreatedFromDataWithIncorrectSize_ThrowsException)
{
    // -- Given.
    constexpr byte data[] = { 0x62, 0x74, 0x73, 0x74, 0x00, 0x00, 0x00, 0x04, 0x01, 0x01, 0x01, 0x01 };

    // -- When.
    // -- Then.
    ASSERT_THROW(BooleanTag::tagWithMemoryAt(data), NxA::Exception);
}

TEST(SeratoDB_BooleanTag, OperatorEqual_TwoEqualTags_ReturnsTrue)
{
    // -- Given.
    auto tag = BooleanTag::tagWithIdentifierAndValue('btst', true);
    auto otherTag = BooleanTag::tagWithIdentifierAndValue('btst', true);

    // -- When.
    // -- Then.
    ASSERT_TRUE(*tag == *otherTag);
}

TEST(SeratoDB_BooleanTag, OperatorEqual_TwoEqualTagsSameObject_ReturnsTrue)
{
    // -- Given.
    auto tag = BooleanTag::tagWithIdentifierAndValue('btst', true);

    // -- When.
    // -- Then.
    ASSERT_TRUE(*tag == *tag);
}

TEST(SeratoDB_BooleanTag, OperatorEqual_TwoUnEqualTags_Returnsfalse)
{
    // -- Given.
    auto tag = BooleanTag::tagWithIdentifierAndValue('btst', true);
    auto otherTag = BooleanTag::tagWithIdentifierAndValue('btst', false);

    // -- When.
    // -- Then.
    ASSERT_FALSE(*tag == *otherTag);
}

TEST(SeratoDB_BooleanTag, SetValue_TagWithAValue_SetsTheValueCorrectly)
{
    // -- Given.
    auto tag = BooleanTag::tagWithIdentifierAndValue('btst', true);

    // -- When.
    tag->setValue(false);

    // -- Then.
    ASSERT_EQ('btst', tag->identifier());
    ASSERT_EQ(false, tag->value());
}

TEST(SeratoDB_BooleanTag, AddTo_TagWithTrueValue_WritesCorrectData)
{
    // -- Given.
    auto tag = BooleanTag::tagWithIdentifierAndValue('btst', true);
    auto destination = Blob::blob();

    // -- When.
    tag->addTo(destination);

    // -- Then.
    auto data = destination->data();
    constexpr byte expectedData[] = { 0x62, 0x74, 0x73, 0x74, 0x00, 0x00, 0x00, 0x01, 0x01 };
    ASSERT_EQ(sizeof(expectedData), destination->size());
    ASSERT_EQ(0, ::memcmp(expectedData, data, sizeof(expectedData)));
}

TEST(SeratoDB_BooleanTag, AddTo_TagWithFaleValue_WritesCorrectData)
{
    // -- Given.
    auto tag = BooleanTag::tagWithIdentifierAndValue('btst', false);
    auto destination = Blob::blob();

    // -- When.
    tag->addTo(destination);

    // -- Then.
    auto data = destination->data();
    constexpr byte expectedData[] = { 0x62, 0x74, 0x73, 0x74, 0x00, 0x00, 0x00, 0x01, 0x00 };
    ASSERT_EQ(sizeof(expectedData), destination->size());
    ASSERT_EQ(0, ::memcmp(expectedData, data, sizeof(expectedData)));
}
