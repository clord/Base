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

#pragma once

#include "Base/Test.hpp"

// -- This forces the linker to link the object files where these tests
// -- are defined. Otherwise they would get stripped out.
NXA_USING_TEST_SUITE_NAMED(SeratoDB_Tag_Tests);
NXA_USING_TEST_SUITE_NAMED(SeratoDB_BlobTag_Tests);
NXA_USING_TEST_SUITE_NAMED(SeratoDB_BooleanTag_Tests);
NXA_USING_TEST_SUITE_NAMED(SeratoDB_ObjectTag_Tests);
NXA_USING_TEST_SUITE_NAMED(SeratoDB_PathTag_Tests);
NXA_USING_TEST_SUITE_NAMED(SeratoDB_TextTag_Tests);
NXA_USING_TEST_SUITE_NAMED(SeratoDB_UInteger16Tag_Tests);
NXA_USING_TEST_SUITE_NAMED(SeratoDB_UInteger32Tag_Tests);
NXA_USING_TEST_SUITE_NAMED(SeratoDB_VersionTag_Tests);

NXA_USE_TEST_SUITES_FOR_MODULE(SeratoDB_Tags) {
    SeratoDB_Tag_Tests,
    SeratoDB_BlobTag_Tests,
    SeratoDB_BooleanTag_Tests,
    SeratoDB_ObjectTag_Tests,
    SeratoDB_PathTag_Tests,
    SeratoDB_TextTag_Tests,
    SeratoDB_UInteger16Tag_Tests,
    SeratoDB_UInteger32Tag_Tests,
    SeratoDB_VersionTag_Tests
};
