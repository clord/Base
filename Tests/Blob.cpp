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

#include "Base/Blob.hpp"
#include "Base/MutableBlob.hpp"
#include "Base/String.hpp"
#include "Base/Test.hpp"

using namespace testing;
using namespace NxA;

static const byte testData[] = {
    0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17,
    0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F, 0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29, 0x2A, 0x2B, 0x2C, 0x2D, 0x2E, 0x2F,
    0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x3A, 0x3B, 0x3C, 0x3D, 0x3E, 0x3F, 0x40, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47,
    0x48, 0x49, 0x4A, 0x4B, 0x4C, 0x4D, 0x4E, 0x4F, 0x50, 0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 0x57, 0x58, 0x59, 0x5A, 0x5B, 0x5C, 0x5D, 0x5E, 0x5F,
    0x60, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68, 0x69, 0x6A, 0x6B, 0x6C, 0x6D, 0x6E, 0x6F, 0x70, 0x71, 0x72, 0x73, 0x74, 0x75, 0x76, 0x77,
    0x78, 0x79, 0x7A, 0x7B, 0x7C, 0x7D, 0x7E, 0x7F, 0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8A, 0x8B, 0x8C, 0x8D, 0x8E, 0x8F,
    0x90, 0x91, 0x92, 0x93, 0x94, 0x95, 0x96, 0x97, 0x98, 0x99, 0x9A, 0x9B, 0x9C, 0x9D, 0x9E, 0x9F, 0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6, 0xA7,
    0xA8, 0xA9, 0xAA, 0xAB, 0xAC, 0xAD, 0xAE, 0xAF, 0xB0, 0xB1, 0xB2, 0xB3, 0xB4, 0xB5, 0xB6, 0xB7, 0xB8, 0xB9, 0xBA, 0xBB, 0xBC, 0xBD, 0xBE, 0xBF,
    0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9, 0xCA, 0xCB, 0xCC, 0xCD, 0xCE, 0xCF, 0xD0, 0xD1, 0xD2, 0xD3, 0xD4, 0xD5, 0xD6, 0xD7,
    0xD8, 0xD9, 0xDA, 0xDB, 0xDC, 0xDD, 0xDE, 0xDF, 0xE0, 0xE1, 0xE2, 0xE3, 0xE4, 0xE5, 0xE6, 0xE7, 0xE8, 0xE9, 0xEA, 0xEB, 0xEC, 0xED, 0xEE, 0xEF,
    0xF0, 0xF1, 0xF2, 0xF3, 0xF4, 0xF5, 0xF6, 0xF7, 0xF8, 0xF9, 0xFA, 0xFB, 0xFC, 0xFD, 0xFE, 0xFF};

static const byte testHash[] = {0xD2, 0x76, 0xE4, 0xEF, 0x00, 0xA8, 0x28, 0xA9, 0xEA, 0x51, 0xB4, 0x83, 0xA4, 0xB6, 0xA8, 0x32};

static const String testBase64String("YXBwbGljYXRpb24vb2N0ZXQtc3RyZWFtAABTZXJhdG8gTWFya2VyczIAAQFBUUZEVDB4UFVn\nQUFBQUFFQVAvLy8wTlZSUUFBQUFBTkFBQUFBQ"
                                     "UFJQU13QUFBQUFBRU5WUlFBQUFBQU5BQUVB\nQXQxbUFNeUkKQUFBQUFFeFBUMUFBQUFBQUZRQUFBQUlpUndBQ01XYi8vLy8vQUNlcTRRQUFB\n"
                                     "RUpRVFV4UFEwc0FBQUFBQVFBQQAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA\nAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"
                                     "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA\nAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA\n"
                                     "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA\nAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"
                                     "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA\nAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA\n"
                                     "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA\nAAAAAAAAAAAAAAAAAAAAAA==\n");

static const byte testBinarySourceData[] = {
    0x61, 0x70, 0x70, 0x6C, 0x69, 0x63, 0x61, 0x74, 0x69, 0x6F, 0x6E, 0x2F, 0x6F, 0x63, 0x74, 0x65, 0x74, 0x2D, 0x73, 0x74, 0x72, 0x65, 0x61, 0x6D,
    0x00, 0x00, 0x53, 0x65, 0x72, 0x61, 0x74, 0x6F, 0x20, 0x4D, 0x61, 0x72, 0x6B, 0x65, 0x72, 0x73, 0x32, 0x00, 0x01, 0x01, 0x41, 0x51, 0x46, 0x44,
    0x54, 0x30, 0x78, 0x50, 0x55, 0x67, 0x41, 0x41, 0x41, 0x41, 0x41, 0x45, 0x41, 0x50, 0x2F, 0x2F, 0x2F, 0x30, 0x4E, 0x56, 0x52, 0x51, 0x41, 0x41,
    0x41, 0x41, 0x41, 0x4E, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x49, 0x41, 0x4D, 0x77, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x45, 0x4E, 0x56,
    0x52, 0x51, 0x41, 0x41, 0x41, 0x41, 0x41, 0x4E, 0x41, 0x41, 0x45, 0x41, 0x41, 0x74, 0x31, 0x6D, 0x41, 0x4D, 0x79, 0x49, 0x0A, 0x41, 0x41, 0x41,
    0x41, 0x41, 0x45, 0x78, 0x50, 0x54, 0x31, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x46, 0x51, 0x41, 0x41, 0x41, 0x41, 0x49, 0x69, 0x52, 0x77, 0x41,
    0x43, 0x4D, 0x57, 0x62, 0x2F, 0x2F, 0x2F, 0x2F, 0x2F, 0x41, 0x43, 0x65, 0x71, 0x34, 0x51, 0x41, 0x41, 0x41, 0x45, 0x4A, 0x51, 0x54, 0x55, 0x78,
    0x50, 0x51, 0x30, 0x73, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x51, 0x41, 0x41, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00};

NXA_CONTAINS_TEST_SUITE_NAMED(Base_Blob_Tests);

TEST(Base_Blob, ClassName_ABlob_ClassNameIsReturnedCorrectly)
{
    // -- Given.
    Blob test;

    // -- When.
    auto name = test.className();

    // -- Then.
    ASSERT_STREQ("Blob", name);
}

TEST(Base_Blob, ClassName_TwoBlobs_ClassNameIsActuallyTheSamePointer)
{
    // -- Given.
    Blob test;
    Blob other;

    // -- When.
    auto name = test.className();
    auto otherName = other.className();

    // -- Then.
    ASSERT_EQ(otherName, name);
}

TEST(Base_Blob, Blob_CallConstructor_BlobCreatedCorrectly)
{
    // -- Given.
    // -- When.
    Blob test;

    // -- Then.
    ASSERT_EQ(0, test.size());
}

TEST(Base_Blob, BlobWithCapacity_AGivenSize_BlobCreatedCorrectly)
{
    // -- Given.
    constexpr count testSize = 32;

    // -- When.
    auto test = MutableBlob::blobWithCapacity(testSize);

    // -- Then.
    ASSERT_EQ(testSize, test.size());
    auto data = test.data();
    for (integer i = 0; i < testSize; ++i) {
        ASSERT_EQ(0, data[i]);
    }
}

TEST(Base_Blob, BlobWithMemoryAndSize_SomeDataInMemory_BlobCreatedCorrectly)
{
    // -- Given.
    // -- When.
    auto test = Blob::blobWithMemoryAndSize(testData, sizeof(testData));

    // -- Then.
    ASSERT_EQ(sizeof(testData), test.size());
    ASSERT_EQ(0, ::memcmp(test.data(), testData, sizeof(testData)));
}

TEST(Base_Blob, blobWithBase64String_ABase64String_BlobCreatedCorrectly)
{
    // -- Given.
    // -- When.
    auto test = Blob::blobWithBase64String(testBase64String);

    // -- Then.
    ASSERT_EQ(sizeof(testBinarySourceData), test.size());
    ASSERT_EQ(0, ::memcmp(test.data(), testBinarySourceData, sizeof(testBinarySourceData)));
}

TEST(Base_Blob, BlobWith_BlobCreatedFromAnotherBlob_BlobCreatedCorrectly)
{
    // -- Given.
    auto source = Blob::blobWithMemoryAndSize(testData, sizeof(testData));

    // -- When.
    auto test = Blob(source);

    // -- Then.
    ASSERT_EQ(sizeof(testData), test.size());
    ASSERT_EQ(0, ::memcmp(test.data(), testData, sizeof(testData)));
}

TEST(Base_Blob, base64String_hashFor_ReturnsTheCorrectHash)
{
    // -- Given.
    // -- When.
    auto result = Blob::hashFor(testData, sizeof(testData));

    // -- Then.
    ASSERT_EQ(sizeof(testHash), result.size());
    ASSERT_EQ(0, ::memcmp(result.data(), testHash, sizeof(testHash)));
}

TEST(Base_Blob, base64String_base64StringFor_ReturnsTheCorrectBase64String)
{
    // -- Given.
    // -- When.
    auto result = Blob::base64StringFor(testBinarySourceData, sizeof(testBinarySourceData));

    // -- Then.
    ASSERT_EQ(testBase64String.length(), result.length());
    ASSERT_EQ(testBase64String, result);
}

TEST(Base_Blob, OperatorSquareBrackets_BlobWithDataInIt_ReturnsCorrectData)
{
    // -- Given.
    // -- When.
    auto test = Blob::blobWithMemoryAndSize(testData, sizeof(testData));

    // -- Then.
    ASSERT_EQ(sizeof(testData), test.size());
    ASSERT_EQ(0, ::memcmp(test.data(), testData, sizeof(testData)));
}

TEST(Base_Blob, OperatorSquareBrackets_ConstantBlobWithDataInIt_ReturnsCorrectData)
{
    // -- Given.
    // -- When.
    auto const test = Blob::blobWithMemoryAndSize(testData, sizeof(testData));

    // -- Then.
    ASSERT_EQ(sizeof(testData), test.size());
    ASSERT_EQ(0, ::memcmp(test.data(), testData, sizeof(testData)));
}

TEST(Base_Blob, OperatorSquareBrackets_OutOfBoundsAccess_ThrowsAnException)
{
    // -- Given.
    // -- When.
    auto test = Blob::blobWithMemoryAndSize(testData, sizeof(testData));

    // -- Then.
    ASSERT_THROW(test[-2], NxA::AssertionFailed);
    ASSERT_THROW(test[sizeof(testData)], NxA::AssertionFailed);
    ASSERT_THROW(test[sizeof(testData) + 46], NxA::AssertionFailed);
}

TEST(Base_Blob, OperatorSquareBrackets_OutOfBoundsAccessOnConstantBlob_ThrowsAnException)
{
    // -- Given.
    // -- When.
    auto const test = Blob::blobWithMemoryAndSize(testData, sizeof(testData));

    // -- Then.
    ASSERT_THROW(test[-2], NxA::AssertionFailed);
    ASSERT_THROW(test[sizeof(testData)], NxA::AssertionFailed);
    ASSERT_THROW(test[sizeof(testData) + 46], NxA::AssertionFailed);
}

TEST(Base_Blob, Data_BlobIsEmpty_ThrowsAnException)
{
    // -- Given.
    // -- When.
    Blob test;

    // -- Then.
    ASSERT_THROW(test.data(), NxA::AssertionFailed);
}

TEST(Base_Blob, Data_ConstantBlobIsEmpty_ThrowsAnException)
{
    // -- Given.
    // -- When.
    const Blob test;

    // -- Then.
    ASSERT_THROW(test.data(), NxA::AssertionFailed);
}

TEST(Base_Blob, OperatorEqual_TwoEqualBlobs_ReturnsTrue)
{
    // -- Given.
    auto source = Blob::blobWithMemoryAndSize(testData, sizeof(testData));

    // -- When.
    auto test = Blob(source);

    // -- Then.
    ASSERT_TRUE(source == test);
}

TEST(Base_Blob, OperatorEqual_TwoUnequalBlobs_ReturnsFalse)
{
    // -- Given.
    auto source = Blob::blobWithMemoryAndSize(testData, sizeof(testData));

    // -- When.
    Blob test;

    // -- Then.
    ASSERT_FALSE(source == test);
}

TEST(Base_Blob, FillWithZeros_ABlobWithContent_FillsTheBlobWithZeros)
{
    // -- Given.
    auto test = MutableBlob::blobWithMemoryAndSize(testData, sizeof(testData));

    // -- When.
    test.fillWithZeros();

    // -- Then.
    ASSERT_EQ(sizeof(testData), test.size());
    auto data = test.data();
    for (integer i = 0; i < sizeof(testData); ++i) {
        ASSERT_EQ(0, data[i]);
    }
}

TEST(Base_Blob, Hash_ABlobWithContent_ReturnsTheCorrectHashValue)
{
    // -- Given.
    auto test = Blob::blobWithMemoryAndSize(testData, sizeof(testData));

    // -- When.
    auto result = test.hash();

    // -- Then.
    ASSERT_EQ(sizeof(testHash), result.size());
    ASSERT_EQ(0, ::memcmp(result.data(), testHash, sizeof(testHash)));
}

TEST(Base_Blob, base64String_ABlobWithBinaryData_ReturnsTheCorrectBase64String)
{
    // -- Given.
    auto test = Blob::blobWithMemoryAndSize(testBinarySourceData, sizeof(testBinarySourceData));

    // -- When.
    auto result = test.base64String();

    // -- Then.
    ASSERT_EQ(testBase64String.length(), result.length());
    ASSERT_EQ(testBase64String, result);
}

TEST(Base_Blob, Append_AnEmptyBlobAndBlobWithContent_AppendTheContentCorrectly)
{
    // -- Given.
    MutableBlob test;
    auto test2 = Blob::blobWithMemoryAndSize(testData, sizeof(testData));

    // -- When.
    test.append(test2);

    // -- Then.
    ASSERT_EQ(sizeof(testData), test.size());
    ASSERT_EQ(0, ::memcmp(test.data(), testData, sizeof(testData)));
}

TEST(Base_Blob, Append_TwoBlobsWithContent_AppendTheContentCorrectly)
{
    // -- Given.
    auto test = MutableBlob::blobWithMemoryAndSize(testData, sizeof(testData));
    auto test2 = Blob::blobWithMemoryAndSize(testData, sizeof(testData));

    // -- When.
    test.append(test2);

    // -- Then.
    ASSERT_EQ(2 * sizeof(testData), test.size());
    ASSERT_EQ(0, ::memcmp(test.data(), testData, sizeof(testData)));
    ASSERT_EQ(0, ::memcmp(test.data() + sizeof(testData), testData, sizeof(testData)));
}

TEST(Base_Blob, Append_ABlobWithContentAndEmptyBlob_AppendTheContentCorrectly)
{
    // -- Given.
    auto test = MutableBlob::blobWithMemoryAndSize(testData, sizeof(testData));
    Blob test2;

    // -- When.
    test.append(test2);

    // -- Then.
    ASSERT_EQ(sizeof(testData), test.size());
    ASSERT_EQ(0, ::memcmp(test.data(), testData, sizeof(testData)));
}

TEST(Base_Blob, Append_TwoEmptyBlobs_LeavesTheBlobEmpty)
{
    // -- Given.
    MutableBlob test;
    Blob test2;

    // -- When.
    test.append(test2);

    // -- Then.
    ASSERT_EQ(0, test.size());
}

TEST(Base_Blob, AppendWithStringTermination_AnEmptyBlobAndAString_AppendTheStringCorrectly)
{
    // -- Given.
    MutableBlob test;

    // -- When.
    test.appendWithStringTermination("Hello");

    // -- Then.
    ASSERT_EQ(6, test.size());
    auto data = test.data();
    ASSERT_EQ('H', data[0]);
    ASSERT_EQ('e', data[1]);
    ASSERT_EQ('l', data[2]);
    ASSERT_EQ('l', data[3]);
    ASSERT_EQ('o', data[4]);
    ASSERT_EQ(0, data[5]);
}

TEST(Base_Blob, AppendWithoutStringTermination_AnEmptyBlobAndAString_AppendTheStringCorrectly)
{
    // -- Given.
    MutableBlob test;

    // -- When.
    test.appendWithoutStringTermination("Hello");

    // -- Then.
    ASSERT_EQ(5, test.size());
    auto data = test.data();
    ASSERT_EQ('H', data[0]);
    ASSERT_EQ('e', data[1]);
    ASSERT_EQ('l', data[2]);
    ASSERT_EQ('l', data[3]);
    ASSERT_EQ('o', data[4]);
}

TEST(Base_Blob, AppendWithStringTermination_AnEmptyBlobAndAnEmptyString_OnlyAppendsAStringTerminatorCharacter)
{
    // -- Given.
    MutableBlob test;

    // -- When.
    test.appendWithStringTermination("");

    // -- Then.
    ASSERT_EQ(1, test.size());
    auto data = test.data();
    ASSERT_EQ(data[0], '\0');
}

TEST(Base_Blob, AppendWithoutStringTermination_AnEmptyBlobAndAnEmptyString_OnlyAppendsAStringTerminatorCharacter)
{
    // -- Given.
    MutableBlob test;

    // -- When.
    test.appendWithoutStringTermination("");

    // -- Then.
    ASSERT_EQ(0, test.size());
}

TEST(Base_Blob, Append_AnEmptyBlobAndACharacter_AppendsTheCharacter)
{
    // -- Given.
    MutableBlob test;

    // -- When.
    test.append('G');

    // -- Then.
    ASSERT_EQ(1, test.size());
    auto data = test.data();
    ASSERT_EQ(data[0], 'G');
}
