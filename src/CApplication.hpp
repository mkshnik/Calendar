//
// Created by Mykhailo Kuvshynov (kuvshmyk@fit.cvut.cz) on 05.05.20.
//

#pragma once
#include <iostream>
#include "CCalendar.hpp"
#include "ECommands.hpp"
#include "CShowCalendar.hpp"

/** Class represents whole calendar application which will accept input commands and provide user-calendar interaction */
class CApplication
{
private:
	/**
	 * Stores events and provides all manipulations with them
	 */
    CCalendar     a_calendar;

    /**
     * Provides showing and getting info of dates, current month and week
     */
    CShowCalendar a_show_events { &a_calendar.GetEvents() };
public:
    CApplication () = default;
    ~CApplication () = default;
    CApplication (const CApplication &) = delete;
    CApplication & operator = (const CApplication &) = delete;

    /** Gets user input */
    static std::vector<std::string>      GetCommand     ();

    /** Provides operations with user input */
    bool                                 ExecuteCommand (const std::vector<std::string> &);

    /** Method displays all commands and parameters that are available to user */
    void                                 Help           () const;

    /** Loads all data from savedata.txt folder */
    CApplication &                       Load           ();

    /** Saves all calendar data to savedata.txt */
    CApplication &                       Save           ();

    /** Terminates program */
	void                                 Exit           ();

	/**  Gets and executes commands by calling calendar methods */
    CApplication &                       Run            ();
};
