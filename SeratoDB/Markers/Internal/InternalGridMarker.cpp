//
//  Copyright (c) 2015-2016 Next Audio Labs, LLC. All rights reserved.
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

#include "Markers/Internal/InternalGridMarker.hpp"

using namespace NxA::Serato;

#pragma mark Constructors & Destructors

InternalGridMarker::InternalGridMarker() :
    positionInSeconds(0.0f),
    beatsPerMinute("0.0")
{
}

#pragma mark Class Methods

NxA::count InternalGridMarker::actualNumberOfBeatsIfSupported(const decimal3& numberOfBeats)
{
    integer64 integerPart = numberOfBeats.getUnbiased();
    integer64 decimalPart = integerPart % 1000;

    if (decimalPart > 995) {
        integerPart += 10;
    }
    else if (decimalPart >= 5) {
        return 0;
    }

    integerPart /= 1000;

    // -- Serato grid marker need to be on a first downbeat.
    if (integerPart % 4) {
        return 0;
    }
    else {
        return integerPart;
    }
}
