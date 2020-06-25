//
// Created by Mykhailo Kuvshynov on 24.05.20.
//

#pragma once
#include "CEvent.hpp"
#include "CParticipant.hpp"

/**
 * Abstract class (subclass of CEvent)
 * In addition to CEvent has participants, location and description
 * */
class CSharedEvent : public CEvent
{
protected:
    /** Vector of pointers to instances of class CParticipant from CStorage ("static" class) */
    std::vector<std::shared_ptr<CParticipant>> s_participants;

    /** Pointer to location from CStorage ("static" class)*/
    std::shared_ptr<std::string>               s_location;
    std::string                                s_description;
public:
    CSharedEvent (std::string name, CDate date, const CTime& time, bool overlap, bool move)
    : CEvent (std::move(name), date, time, overlap, move)
    {}

    bool                            LocationCheck    (const std::string & location) const override
    { if (!s_location) return false; return *s_location == location; }

    bool                            LoadAdvanced     (const std::vector<std::string> &)   override;
    bool                            ImportAdvanced   (const std::vector<std::string> &)   override;
    bool                            Repeat           ()                                   override;
    bool                            Advanced         ()                                   override;
    void                            GetInfo          ()                             const override;

    /** Saves event in special format */
    std::string                     SaveShared       ()                             const;

    /** Exports event in special format */
    std::string 					ExportShared     ()								const;

    /**
     * If CStorage::st_participants isn't empty offers user to add participants from there
     * otherwise or if he declines scan info and add new participants to event and storage
     * @returns false if user didn't add a single participant
     * */
    bool                            ScanParticipants ();

    /**
     * If CStorage::st_locations isn't empty offers user to add location from there
     * otherwise or if he declines scan and add new location to event and storage
     * @returns false if user cancels adding location
     * */
    bool                            ScanLocation     ();

    /**
     * Scans description from user
     * @returns false if description hasn't been added
     * */
    bool                            ScanDescription  ();

    /**
     * Checks if participant is already taking part in this event
     * @return bool if given participant is taking part in this event and false otherwise
     */
    bool                            CheckParticipant (const std::shared_ptr<CParticipant> &);
};