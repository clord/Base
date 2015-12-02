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

#include "Markers/Internal/GridMarker.hpp"

using namespace NxA::Serato::Internal;

#pragma mark Constructors & Destructors

GridMarker::GridMarker() : positionInSeconds(0.0f),
                           beatsPerMinute(0.0f) { }

#pragma mark Class Methods

NxA::boolean GridMarker::numberOfBeatsValueSupportedBySerato(decimal numberOfBeats)
{
    uinteger32 integerNumberOfBeats = numberOfBeats;
    if ((numberOfBeats != static_cast<decimal>(integerNumberOfBeats)) ||
        (integerNumberOfBeats % 4)) {
        // -- This grid marker is not on a first downbeat which is not supported by Serato.
        return false;
    }

    return true;
}
