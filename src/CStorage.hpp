//
// Created by Mykhailo Kuvshynov on 01/06/2020.
//

#pragma once
#include <vector>
#include <string>
#include <memory>
#include <iostream>
#include <algorithm>
#include <fstream>
#include "CParticipant.hpp"
#include "CSaverLoader.hpp"

/** Class represents storage that stores all ever added locations and participants */
class CStorage
{
public:
	/** Stores all participants that have ever been added to any event */
    static std::vector<std::shared_ptr<CParticipant>>   st_participants;

    /** Stores all locations that have ever been added to any event */
    static std::vector<std::shared_ptr<std::string>>    st_locations;
    CStorage () = default;
    ~CStorage () = default;

	/** Prints names of all stored participants */
    static void                                                 ListParticipantsNames    ();

    /** Prints all stored locations */
    static void                                                 ListLocations            ();

	/**
	 * Checks if given location is in storage
	 * @returns iterator to found location or to the end of st_location if it has not been found
	 * */
    static std::vector<std::shared_ptr<std::string>>::iterator  CheckLocation            (const std::string & location);

	/**
	 * Checks if given participant is in storage
	 * @returns iterator to found participant or to the end of st_participants if it has not been found
	 * */
    static std::vector<std::shared_ptr<CParticipant>>::iterator CheckParticipant         (const std::string & name);

    /** Saves storage to save file (savedata.txt) */
    static void 											    SaveStorage			     ();

    /** Loads storage from save file (savedata.txt) */
    static void 											    LoadStorage			     ();
};



