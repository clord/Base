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

#pragma once

#include <Base/Base.hpp>

#pragma mark Constants

namespace NxA { namespace Serato {
    // -- Known database Tag identifiers.
    constexpr uinteger32 databaseVersionTagIdentifier                   = 'vrsn';
    constexpr uinteger32 trackObjectTagIdentifier                       = 'otrk';
    constexpr uinteger32 trackFilePathTagIdentifier                     = 'pfil';
    constexpr uinteger32 databaseDirectoryPathTagIdentifier             = 'pdir';
    constexpr uinteger32 databaseVideoFilePathTagIdentifier             = 'pvid';
    constexpr uinteger32 databaseFileTypeTagIdentifier                  = 'ttyp';
    constexpr uinteger32 trackTitleTagIdentifier                        = 'tsng';
    constexpr uinteger32 trackArtistTagIdentifier                       = 'tart';
    constexpr uinteger32 trackAlbumTagIdentifier                        = 'talb';
    constexpr uinteger32 trackGenreTagIdentifier                        = 'tgen';
    constexpr uinteger32 trackLengthTagIdentifier                       = 'tlen';
    constexpr uinteger32 trackSizeStringTagIdentifier                   = 'tsiz';
    constexpr uinteger32 trackBitrateTagIdentifier                      = 'tbit';
    constexpr uinteger32 trackSampleRateTagIdentifier                   = 'tsmp';
    constexpr uinteger32 trackBpmTagIdentifier                          = 'tbpm';
    constexpr uinteger32 trackCommentsTagIdentifier                     = 'tcom';
    constexpr uinteger32 trackGroupingTagIdentifier                     = 'tgrp';
    constexpr uinteger32 trackRemixerTagIdentifier                      = 'trmx';
    constexpr uinteger32 trackLabelTagIdentifier                        = 'tlbl';
    constexpr uinteger32 trackComposerTagIdentifier                     = 'tcmp';
    constexpr uinteger32 trackYearTagIdentifier                         = 'ttyr';
    constexpr uinteger32 trackCrateNameTagIdentifier                    = 'tcrt';
    constexpr uinteger32 trackDateAddedStringTagIdentifier              = 'tadd';
    constexpr uinteger32 trackIsCorruptedMessageTagIdentifier           = 'tcor';
    constexpr uinteger32 trackVideoEffectsTagIdentifier                 = 'tvfx';
    constexpr uinteger32 trackKeyTagIdentifier                          = 'tkey';
    constexpr uinteger32 trackItunesIdentifierTagIdentifier             = 'tiid';
    constexpr uinteger32 trackNumberTagIdentifier                       = 'utkn';
    constexpr uinteger32 trackDiscNumberTagIdentifier                   = 'udsc';
    constexpr uinteger32 trackLabelColorTagIdentifier                   = 'ulbl';
    constexpr uinteger32 trackDateModifiedTagIdentifier                 = 'utme';
    constexpr uinteger32 trackDateAddedTagIdentifier                    = 'uadd';
    constexpr uinteger32 trackSizeTagIdentifier                         = 'ufsb';
    constexpr uinteger32 trackLastAnalyzedVersionTagIdentifier          = 'sbav';
    constexpr uinteger32 trackMetadataWasReadTagIdentifier              = 'bhrt';
    constexpr uinteger32 trackIsMissingTagIdentifier                    = 'bmis';
    constexpr uinteger32 trackWasRecentlyPlayedTagIdentifier            = 'bply';
    constexpr uinteger32 trackLoopingTagIdentifier                      = 'blop';
    constexpr uinteger32 trackIsFromItunesTagIdentifier                 = 'bitu';
    constexpr uinteger32 trackIsReadOnlyTagIdentifier                   = 'biro';
    constexpr uinteger32 trackWasAnalyzedTagIdentifier                  = 'bovc';
    constexpr uinteger32 trackIsCorruptedTagIdentifier                  = 'bcrt';
    constexpr uinteger32 trackIsWhiteLabelTagIdentifier                 = 'bwlb';
    constexpr uinteger32 trackIsAccessControlledWhiteLabelTagIdentifier = 'bwll';
    constexpr uinteger32 trackIsUnsuportedTagIdentifier                 = 'buns';
    constexpr uinteger32 trackBeatGridIsLockedTagIdentifier             = 'bbgl';
} }
