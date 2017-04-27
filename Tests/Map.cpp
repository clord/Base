//
//  Copyright (c) 2015-2017 Next Audio Labs, LLC. All rights reserved.
//
//  Permission is hereby granted, free of charge, to any person obtaining a copy of
//  this software and associated documentation files (the "Software"), to deal in the
//  Software without restriction, including without limitation the rights to use, copy,
//  modify, merge, publish, distribute, sublicense, and/or sell copies of the Software,
//  and to permit persons to whom the Software is furnished to do so, subject to the
//  following conditions:
//
//  The above copyright notice and this permission notice shall be included in all
//  copies or substantial portions of the Software.
//
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
//  INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
//  PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
//  HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
//  OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
//  SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
//

#include "Base/Map.hpp"
#include "Base/Test.hpp"
#include "Base/Array.hpp"

using namespace testing;
using namespace NxA;

NXA_CONTAINS_TEST_SUITE_NAMED(Base_Map_Tests);

using TestMapUInteger32ToString = MutableMap<uinteger32, String>;
using TestMapUInteger32ToUInteger32 = MutableMap<uinteger32, uinteger32>;

static String testString("Test String");
static String otherString("Other String");

TEST(Base_Map, ClassName_MapOfUInteger32AndUInteger32_ClassNameIsReturnedCorrectly)
{
    // -- Given.
    Map<uinteger32, uinteger32> test;

    // -- When.
    auto name = test.className();

    // -- Then.
    ASSERT_STREQ("Map<uinteger32, uinteger32>", name);
}

TEST(Base_Map, ClassName_MapOfUInteger32AndMapOfBytesAndArrayOfStrings_ClassNameIsReturnedCorrectly)
{
    // -- Given.
    Map<uinteger32, Map<byte, Array<String>>> test;

    // -- When.
    auto name = test.className();

    // -- Then.
    ASSERT_STREQ("Map<uinteger32, Map<byte, Array<String>>>", name);
}

TEST(Base_Map, ClassName_TwoMapsOfUInteger32AndMapOfBytesAndArrayOfStrings_ClassNameIsActuallyTheSamePointer)
{
    // -- Given.
    Map<uinteger32, Map<byte, Array<String>>> test;
    Map<uinteger32, Map<byte, Array<String>>> other;

    // -- When.
    auto name = test.className();
    auto otherName = other.className();

    // -- Then.
    ASSERT_EQ(otherName, name);
}

TEST(Base_Map, SetValueForKey_IntegerValue_SetsCorrectValue)
{
    // -- Given.
    static const uinteger32 integerValue = 72;
    TestMapUInteger32ToUInteger32 test;

    // -- When.
    test.setValueForKey(integerValue, 0);

    // -- Then.
    ASSERT_EQ(integerValue, test.valueForKey(0));
}

TEST(Base_Map, SetValueForKey_ValueFromAPointer_SetsCorrectValue)
{
    // -- Given.
    static const character* otherTestString = "testString";
    TestMapUInteger32ToString test;

    // -- When.
    test.setValueForKey(String{ otherTestString }, 0);

    // -- Then.
    ASSERT_STREQ(otherTestString, test.valueForKey(0).asUTF8());
}

TEST(Base_Map, SetValueForKey_ValueFromAReference_SetsCorrectValue)
{
    // -- Given.
    TestMapUInteger32ToString test;

    // -- When.
    test.setValueForKey(testString, 0);

    // -- Then.
    ASSERT_STREQ(testString.asUTF8(), test.valueForKey(0).asUTF8());
}

TEST(Base_Map, SetValueForKey_ValueFromAPointerOverAnExistingValue_SetsCorrectValue)
{
    // -- Given.
    static const character* otherTestString = "testString";
    TestMapUInteger32ToString test;
    test.setValueForKey(String{ "Initial String" }, 44);

    // -- When.
    test.setValueForKey(String{ otherTestString }, 44);

    // -- Then.
    ASSERT_STREQ(otherTestString, test.valueForKey(44).asUTF8());
}

TEST(Base_Map, SetValueForKey_ValueFromAReferenceOverAnExistingValue_SetsCorrectValue)
{
    // -- Given.
    TestMapUInteger32ToString test;
    test.setValueForKey(testString, 44);

    // -- When.
    test.setValueForKey(otherString, 44);

    // -- Then.
    ASSERT_STREQ(otherString.asUTF8(), test.valueForKey(44).asUTF8());
}

TEST(Base_Map, SetValueForKeyCausedAnInsertion_IntegerValue_SetsCorrectValue)
{
    // -- Given.
    static const uinteger32 integerValue = 72;
    TestMapUInteger32ToUInteger32 test;

    // -- When.
    auto existed = !test.setValueForKeyCausedAnInsertion(integerValue, 0);

    // -- Then.
    ASSERT_FALSE(existed);
    ASSERT_EQ(integerValue, test.valueForKey(0));
}

TEST(Base_Map, SetValueForKeyCausedAnInsertion_ValueFromAPointer_SetsCorrectValue)
{
    // -- Given.
    static const character* otherTestString = "testString";
    TestMapUInteger32ToString test;

    // -- When.
    auto existed = !test.setValueForKeyCausedAnInsertion(String{ otherTestString }, 0);

    // -- Then.
    ASSERT_FALSE(existed);
    ASSERT_STREQ(otherTestString, test.valueForKey(0).asUTF8());
}

TEST(Base_Map, SetValueForKeyCausedAnInsertion_ValueFromAReference_SetsCorrectValue)
{
    // -- Given.
    TestMapUInteger32ToString test;

    // -- When.
    auto existed = !test.setValueForKeyCausedAnInsertion(testString, 0);

    // -- Then.
    ASSERT_FALSE(existed);
    ASSERT_STREQ(testString.asUTF8(), test.valueForKey(0).asUTF8());
}

TEST(Base_Map, SetValueForKeyCausedAnInsertion_ValueFromAPointerOverAnExistingValue_SetsCorrectValue)
{
    // -- Given.
    static const character* otherTestString = "testString";
    TestMapUInteger32ToString test;
    test.setValueForKey(String{ "Initial String" }, 44);

    // -- When.
    auto existed = !test.setValueForKeyCausedAnInsertion(String{ otherTestString }, 44);

    // -- Then.
    ASSERT_TRUE(existed);
    ASSERT_STREQ(otherTestString, test.valueForKey(44).asUTF8());
}

TEST(Base_Map, SetValueForKeyCausedAnInsertion_ValueFromAReferenceOverAnExistingValue_SetsCorrectValue)
{
    // -- Given.
    TestMapUInteger32ToString test;
    test.setValueForKey(testString, 44);

    // -- When.
    auto existed = !test.setValueForKeyCausedAnInsertion(otherString, 44);

    // -- Then.
    ASSERT_TRUE(existed);
    ASSERT_STREQ(otherString.asUTF8(), test.valueForKey(44).asUTF8());
}

TEST(Base_Map, ValueForKey_IntegerValue_SetsCorrectValue)
{
    // -- Given.
    static const uinteger32 integerValue = 72;
    TestMapUInteger32ToUInteger32 test;

    // -- When.
    test.valueForKey(0) = integerValue;

    // -- Then.
    ASSERT_EQ(integerValue, test.valueForKey(0));
}

TEST(Base_Map, ValueForKey_ValueFromAPointer_SetsCorrectValue)
{
    // -- Given.
    static const character* otherTestString = "testString";
    TestMapUInteger32ToString test;

    // -- When.
    test.valueForKey(0) = String(otherTestString);

    // -- Then.
    ASSERT_STREQ(otherTestString, test.valueForKey(0).asUTF8());
}

TEST(Base_Map, ValueForKey_ValueFromAReference_SetsCorrectValue)
{
    // -- Given.
    TestMapUInteger32ToString test;

    // -- When.
    test.valueForKey(0) = testString;

    // -- Then.
    ASSERT_STREQ(testString.asUTF8(), test.valueForKey(0).asUTF8());
}

TEST(Base_Map, ValueForKey_ValueFromAPointerOverAnExistingValue_SetsCorrectValue)
{
    // -- Given.
    static const character* otherTestString = "testString";
    TestMapUInteger32ToString test;
    test.setValueForKey(String{ "Initial String" }, 44);

    // -- When.
    test.valueForKey(44) = String(otherTestString);

    // -- Then.
    ASSERT_STREQ(otherTestString, test.valueForKey(44).asUTF8());
}

TEST(Base_Map, ValueForKey_ValueFromAReferenceOverAnExistingValue_SetsCorrectValue)
{
    // -- Given.
    TestMapUInteger32ToString test;
    test.setValueForKey(testString, 44);

    // -- When.
    test.valueForKey(44) = otherString;

    // -- Then.
    ASSERT_STREQ(otherString.asUTF8(), test.valueForKey(44).asUTF8());
}

TEST(Base_Map, ValueForKey_MapWithAGivenValue_ReturnsCorrectValue)
{
    // -- Given.
    TestMapUInteger32ToString test;
    test.setValueForKey(testString, 0x2323);
    test.setValueForKey(otherString, 0x2423);

    // -- When.
    // -- Then.
    ASSERT_STREQ(testString.asUTF8(), test.valueForKey(0x2323).asUTF8());
}

TEST(Base_Map, ValueForKey_MapWithAnotherValue_ReturnsCorrectValue)
{
    // -- Given.
    TestMapUInteger32ToString test;
    test.setValueForKey(testString, 0x2323);
    test.setValueForKey(otherString, 0x2423);

    // -- When.
    // -- Then.
    ASSERT_STREQ(otherString.asUTF8(), test.valueForKey(0x2423).asUTF8());
}

TEST(Base_Map, ValueForKey_LookingForAnUnknownKey_CreatesANewEntry)
{
    // -- Given.
    TestMapUInteger32ToString test;
    test.setValueForKey(testString, 0x2323);
    test.setValueForKey(otherString, 0x2423);

    // -- When.
    test.valueForKey(0x23);

    // -- Then.
    ASSERT_TRUE(test.maybeValueForKey(0x23) ? true : false);
    ASSERT_STREQ("", test.valueForKey(0x23).asUTF8());
}

TEST(Base_Map, ValueForKey_ConstMapWithAGivenValue_ReturnsCorrectValue)
{
    // -- Given.
    TestMapUInteger32ToString test;
    test.setValueForKey(testString, 0x2323);
    test.setValueForKey(otherString, 0x2423);
    const TestMapUInteger32ToString& constTest = test;

    // -- When.
    // -- Then.
    ASSERT_STREQ(testString.asUTF8(), constTest.valueForKey(0x2323).asUTF8());
}

TEST(Base_Map, ValueForKey_ConstMapWithAnotherValue_ReturnsCorrectValue)
{
    // -- Given.
    TestMapUInteger32ToString test;
    test.setValueForKey(testString, 0x2323);
    test.setValueForKey(otherString, 0x2423);
    const TestMapUInteger32ToString& constTest = test;

    // -- When.
    // -- Then.
    ASSERT_STREQ(otherString.asUTF8(), constTest.valueForKey(0x2423).asUTF8());
}

TEST(Base_Map, ValueForKey_LookingForAnUnknownKeyInConstMap_ThrowsException)
{
    // -- Given.
    TestMapUInteger32ToString test;
    test.setValueForKey(testString, 0x2323);
    test.setValueForKey(otherString, 0x2423);
    const TestMapUInteger32ToString& constTest = test;

    // -- When.
    // -- Then.
    ASSERT_THROW(constTest.valueForKey(0x23).asUTF8(), std::exception);
}

TEST(Base_Map, OperatorSquareBrackets_MapWithAGivenValue_ReturnsCorrectValue)
{
    // -- Given.
    TestMapUInteger32ToString test;
    test.setValueForKey(testString, 0x2323);
    test.setValueForKey(otherString, 0x2423);

    // -- When.
    // -- Then.
    ASSERT_STREQ(testString.asUTF8(), test[0x2323].asUTF8());
}

TEST(Base_Map, OperatorSquareBrackets_MapWithAnotherValue_ReturnsCorrectValue)
{
    // -- Given.
    TestMapUInteger32ToString test;
    test.setValueForKey(testString, 0x2323);
    test.setValueForKey(otherString, 0x2423);

    // -- When.
    // -- Then.
    ASSERT_STREQ(otherString.asUTF8(), test[0x2423].asUTF8());
}

TEST(Base_Map, OperatorSquareBrackets_LookingForAnUnknownKey_ThrowsException)
{
    // -- Given.
    TestMapUInteger32ToString test;
    test.setValueForKey(testString, 0x2323);
    test.setValueForKey(otherString, 0x2423);

    // -- When.
    // -- Then.
    ASSERT_THROW(test[0x23].asUTF8(), std::exception);
}

TEST(Base_Map, OperatorSquareBrackets_ConstMapWithAGivenValue_ReturnsCorrectValue)
{
    // -- Given.
    TestMapUInteger32ToString test;
    test.setValueForKey(testString, 0x2323);
    test.setValueForKey(otherString, 0x2423);
    const TestMapUInteger32ToString& constTest = test;

    // -- When.
    // -- Then.
    ASSERT_STREQ(testString.asUTF8(), constTest[0x2323].asUTF8());
}

TEST(Base_Map, OperatorSquareBrackets_ConstMapWithAnotherValue_ReturnsCorrectValue)
{
    // -- Given.
    TestMapUInteger32ToString test;
    test.setValueForKey(testString, 0x2323);
    test.setValueForKey(otherString, 0x2423);
    const TestMapUInteger32ToString& constTest = test;

    // -- When.
    // -- Then.
    ASSERT_STREQ(otherString.asUTF8(), constTest[0x2423].asUTF8());
}

TEST(Base_Map, OperatorSquareBrackets_LookingForAnUnknownKeyInConstMap_ThrowsException)
{
    // -- Given.
    TestMapUInteger32ToString test;
    test.setValueForKey(testString, 0x2323);
    test.setValueForKey(otherString, 0x2423);
    const TestMapUInteger32ToString& constTest = test;

    // -- When.
    // -- Then.
    ASSERT_THROW(constTest[0x23].asUTF8(), std::exception);
}

TEST(Base_Map, MaybeValueForKey_UnknownKey_ReturnsFalse)
{
    // -- Given.
    TestMapUInteger32ToString test;
    test.setValueForKey(testString, 0x2323);
    test.setValueForKey(otherString, 0x2423);

    // -- When.
    // -- Then.
    ASSERT_FALSE(test.maybeValueForKey(0x23));
}

TEST(Base_Map, MaybeValueForKey_KnownKey_ReturnsTrue)
{
    // -- Given.
    TestMapUInteger32ToString test;
    test.setValueForKey(testString, 0x2323);
    test.setValueForKey(otherString, 0x2423);

    // -- When.
    // -- Then.
    ASSERT_TRUE(test.maybeValueForKey(0x2323) ? true : false);
}

TEST(Base_Map, RemoveValueForKey_UnknownKey_ReturnsFalse)
{
    // -- Given.
    TestMapUInteger32ToString test;
    test.setValueForKey(testString, 0x2323);
    test.setValueForKey(otherString, 0x2423);

    // -- When.
    test.removeValueForKey(0x23);

    // -- Then.
    ASSERT_EQ(2, test.length());
    ASSERT_TRUE(test.maybeValueForKey(0x2323) ? true : false);
    ASSERT_TRUE(test.maybeValueForKey(0x2423) ? true : false);
}

TEST(Base_Map, RemoveValueForKey_KnownKey_ReturnsTrueAndRemovesTheKey)
{
    // -- Given.
    TestMapUInteger32ToString test;
    test.setValueForKey(testString, 0x2323);
    test.setValueForKey(otherString, 0x2423);

    // -- When.
    test.removeValueForKey(0x2323);

    // -- Then.
    ASSERT_EQ(1, test.length());
    ASSERT_TRUE(test.maybeValueForKey(0x2423) ? true : false);
}

TEST(Base_Map, RemoveValueForKeyCausedARemoval_UnknownKey_ReturnsFalse)
{
    // -- Given.
    TestMapUInteger32ToString test;
    test.setValueForKey(testString, 0x2323);
    test.setValueForKey(otherString, 0x2423);

    // -- When.
    auto existed = test.removeValueForKeyCausedARemoval(0x23);

    // -- Then.
    ASSERT_FALSE(existed);
    ASSERT_EQ(2, test.length());
    ASSERT_TRUE(test.maybeValueForKey(0x2323) ? true : false);
    ASSERT_TRUE(test.maybeValueForKey(0x2423) ? true : false);
}

TEST(Base_Map, RemoveValueForKeyCausedARemoval_KnownKey_ReturnsTrueAndRemovesTheKey)
{
    // -- Given.
    TestMapUInteger32ToString test;
    test.setValueForKey(testString, 0x2323);
    test.setValueForKey(otherString, 0x2423);

    // -- When.
    auto existed = test.removeValueForKeyCausedARemoval(0x2323);

    // -- Then.
    ASSERT_TRUE(existed);
    ASSERT_EQ(1, test.length());
    ASSERT_TRUE(test.maybeValueForKey(0x2423) ? true : false);
}

TEST(Base_Map, Length_MapWithKeys_ReturnsCorrectValue)
{
    // -- Given.
    TestMapUInteger32ToString test;
    test.setValueForKey(testString, 0x2323);
    test.setValueForKey(otherString, 0x2423);

    // -- When.
    // -- Then.
    ASSERT_EQ(2, test.length());
}

TEST(Base_Map, Length_MapWithNoKeys_ReturnsCorrectValue)
{
    // -- Given.
    TestMapUInteger32ToString test;

    // -- When.
    // -- Then.
    ASSERT_EQ(0, test.length());
}
