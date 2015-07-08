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

namespace NxA { namespace Serato {
    NXA_GENERATED_FORWARD_DECLARATIONS_FOR_CLASS(Database);

    class Crate;
    class Track;
    class TrackEntry;

    class Database : public Object {
        NXA_GENERATED_DECLARATIONS_IN_NAMESPACE_FOR_CLASS(NxA::Serato, Database);

    public:
        #pragma mark Factory Methods
        static Database::Pointer databaseWithFileAt(const String& seratoFolderPath);

        #pragma mark Class Methods
        static String::Pointer versionAsStringForDatabaseIn(const String& seratoFolderPath);

        #pragma mark Instance Methods
        timestamp databaseModificationDateInSecondsSince1970(void) const;
        timestamp rootCrateModificationDateInSecondsSince1970(void) const;

        Crate& rootCrate(void) const;
        const NxA::ArrayContainer<Track>& tracks(void) const;
        NxA::Pointer<NxA::ArrayContainer<Track>> removeAndReturnTracks(void);

        void deleteTrackEntry(TrackEntry& trackEntry);
        void deleteCrate(Crate& crate);

        void addTrack(Track& track);
        void deleteTrack(Track& track);

        void saveIfModified(void) const;
    };
} }
