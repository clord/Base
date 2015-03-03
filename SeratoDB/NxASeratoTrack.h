//
//  NxASeratoTrack.h
//  SeratoDB
//
//  Created by Didier Malenfant on 2/3/15.
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

#ifndef __SeratoDB__NxASeratoTrack__
#define __SeratoDB__NxASeratoTrack__

#include <SeratoDB/NxASeratoTag.h>
#include <SeratoDB/NxASeratoTrackFile.h>

#include <string>
#include <vector>

namespace NxA {
    #pragma mark Forward declarations
    class SeratoTrack;

    #pragma mark Containers
    typedef std::unique_ptr<SeratoTrack> SeratoTrackPtr;
    typedef std::vector<SeratoTrackPtr> SeratoTrackVector;

    #pragma mark Class Declaration
    class SeratoTrack
    {
    private:
        #pragma mark Private Instance Variables
        ConstSeratoTagPtr p_trackTag;
        SeratoTrackFilePtr p_trackFile;
        StringPtr p_rootFolder;

        bool p_markersRead;
        SeratoCueMarkerVector p_cueMarkers;
        SeratoLoopMarkerVector p_loopMarkers;

        #pragma mark Private Instance Methods
        inline bool p_containsAValidTrackTag(void) const;

        const std::string& p_stringForSubTagForIdentifier(const uint32_t& identifier) const;
        const std::string& p_pathForSubTagForIdentifier(const uint32_t& identifier) const;
        const uint32_t& p_uint32ForSubTagForIdentifier(const uint32_t& identifier) const;

        void p_setStringForSubTagForIdentifier(const char* value, const uint32_t& identifier);
        void p_setUInt32ForSubTagForIdentifier(const uint32_t& value, const uint32_t& identifier);

        void p_loadTrackFile(void);
        void p_unloadTrackFile(void);
        void p_readMarkersIfNotAlreadyRead(void);

    public:
        #pragma mark Constructors
        explicit SeratoTrack(SeratoTagPtr& trackTag, const char* rootDirectoryPath);

        #pragma mark Instance Methods
        StringPtr trackFilePath(void) const;

        const std::string& title(void) const;
        const std::string& artist(void) const;
        const std::string& album(void) const;
        const std::string& genre(void) const;
        const std::string& comments(void) const;
        const std::string& grouping(void) const;
        const std::string& remixer(void) const;
        const std::string& recordLabel(void) const;
        const std::string& composer(void) const;
        const std::string& key(void) const;
        const std::string& length(void) const;
        const uint32_t& sizeInBytes(void) const;
        const std::string& bitRate(void) const;
        const std::string& sampleRate(void) const;
        const std::string& bpm(void) const;
        const std::string& year(void) const;
        const uint32_t& trackNumber(void) const;
        const uint32_t& discNumber(void) const;
        const uint32_t& dateModifiedInSecondsSinceJanuary1st1970(void) const;
        const uint32_t& dateAddedInSecondsSinceJanuary1st1970(void) const;

        const SeratoCueMarkerVector& cueMarkers(void);
        const SeratoLoopMarkerVector& loopMarkers(void);
    };
}

#endif /* defined(__SeratoDB__NxASeratoTrack__) */
