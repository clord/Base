//  OCHamcrest by Jon Reid, http://qualitycoding.org/about/
//  Copyright 2014 hamcrest.org. See LICENSE.txt

    // System under test
#define HC_SHORTHAND
#import <OCHamcrest/HCIsTrueFalse.h>

    // Test support
#import "AbstractMatcherTest.h"


@interface IsTrueTest : AbstractMatcherTest
@end

@implementation IsTrueTest

- (void)testCopesWithNilsAndUnknownTypes
{
    id matcher = isTrue();

    assertNilSafe(matcher);
    assertUnknownTypeSafe(matcher);
}

- (void)testNonZero_ShouldMatch
{
    assertMatches(@"boolean YES", isTrue(), @YES);
    assertMatches(@"non-zero", isTrue(), @123);
}

- (void)testZero_ShouldNotMatch
{
    assertDoesNotMatch(@"boolean NO", isTrue(), @NO);
    assertDoesNotMatch(@"zero is false", isTrue(), @0);
}

- (void)testNonNumber_ShouldNotMatch
{
    assertDoesNotMatch(@"non-number", isTrue(), [[NSObject alloc] init]);
}

- (void)testHasAReadableDescription
{
    assertDescription(@"true (non-zero)", isTrue());
}

- (void)testDescribesMismatchOfDifferentNumber
{
    assertMismatchDescription(@"was <0>", isTrue(), @0);
}

- (void)testDescribesMismatchOfNonNumber
{
    assertMismatchDescriptionPrefix(@"was <NSObject:", isTrue(), [[NSObject alloc] init]);
}

@end

#pragma mark -

@interface IsFalseTest : AbstractMatcherTest
@end

@implementation IsFalseTest

- (void)testCopesWithNilsAndUnknownTypes
{
    id matcher = isFalse();

    assertNilSafe(matcher);
    assertUnknownTypeSafe(matcher);
}

- (void)testZero_ShouldMatch
{
    assertMatches(@"boolean NO", isFalse(), @NO);
    assertMatches(@"zero is false", isFalse(), @0);
}

- (void)testNonZero_ShouldNotMatch
{
    assertDoesNotMatch(@"boolean YES", isFalse(), @YES);
    assertDoesNotMatch(@"non-zero is true", isFalse(), @123);
}

- (void)testHasAReadableDescription
{
    assertDescription(@"false (zero)", isFalse());
}

- (void)testDescribesMismatchOfDifferentNumber
{
    assertMismatchDescription(@"was <123>", isFalse(), @123);
}

- (void)testDescribesMismatchOfNonNumber
{
    assertMismatchDescriptionPrefix(@"was <NSObject:", isFalse(), [[NSObject alloc] init]);
}

@end
