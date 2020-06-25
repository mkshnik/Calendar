//
// Created by Mykhailo Kuvshynov (kuvshmyk@fit.cvut.cz) on 05.05.20.
//

#pragma once
#include <sstream>
#include <iostream>
#include <string>
#include <memory>
#include <utility>
#include <vector>
#include <map>
#include "CTime.hpp"
#include "CDate.hpp"
#include "ECalendarTypes.hpp"
#include "ECommands.hpp"
#include "CScanner.hpp"
#include "CStorage.hpp"

/** Abstract class which provides a template for any type of events in the calendar */
class CEvent
{
protected:
	/**
	 * @param type type of repeat
	 * @param date date until repeat will be set
	 * Sets repeat of given type until given date
	 * */
	void							  		 SetRepeat 	     (int type, CDate date);
public:
	std::string                       		 e_name;
	CTime                                    e_time;

	/** First element is event's initial date and rest are repeats. */
	std::set<CDate>                          e_dates;

	/** Type of event's repeat */
	RepeatType					             e_repeat;

	/** True if event can have overlapped events and false if not */
	bool 								     e_overlap;

	/** True if event can be moved and false if not */
	bool 									 e_move;

    explicit CEvent (std::string name, const CDate & date, const CTime & time, bool overlap, bool move)
    : e_name(std::move(name)),
      e_time(time),
      e_overlap(overlap),
      e_move(move)
    {
      e_dates.insert(date);
      e_repeat = RepeatType::NoRepeat;
    }

	virtual ~CEvent() = default;
	CEvent (const CEvent & event) = default;
	CEvent & operator = (const CEvent & event) = default;


	bool 									  Overlap		  ()					  const 		  { return e_overlap; }
    CDate                                     GetInitDate     () 					  const           { return *e_dates.begin(); }

    /** @returns reference to e_time attribute */
    CTime &                                   GetTime         () 					                  { return e_time; }

    /** @returns shared pointer to a clone of itself */
    virtual std::shared_ptr<CEvent>           Clone           () 					  const           = 0;

    /** @returns event in unique saving format */
    virtual std::string 					  SaveEvent       ()   					  const           = 0;

	/** @returns event in unique export format */
	virtual	std::string 				      ExportEvent     ()					  const           = 0;

	/** Prints an information about event */
	virtual void                              GetInfo         () 					  const           = 0;

	/** Prints type of event (only used in displaying purposes) */
	virtual std::string                       PrintType       () 					  const           = 0;

	/** Prints type of repeat */
	std::string 							  PrintRepeat     ()					  const           { return RepeatToStr(e_repeat); }

	/**
	 * Opens repeat editing menu
	 * @return True if repeat was successfully set and false in any other case
	 * */
	virtual bool 							  Repeat          ();

	/**
	 * Opens edit menu
	 * @returns false if event can't be edited and true in any other case
	 * */
	virtual bool                              Edit            () 	     			     	          { return false; }

	/**
	 * Opens advanced settings
	 * @returns true if Advanced settings were set successfully
	 * */
	virtual bool                              Advanced        () 					     	          { return false; }

	/**
	 * @param location
	 * Checks if given location equals to the one event has
	 * @returns false if event doesn't have location or given location isn't equal to it
	 * */
	virtual bool                              LocationCheck   (const std::string &)   const           { return false; }

	/**
	 * Loads advanced settings of the event
	 * @returns true if advanced settings were loaded successfully
	 * */
	virtual bool                              LoadAdvanced    (const std::vector<std::string> & info) { return false; }

	/**
	 * Imports advanced settings of the event
	 * @returns true if advanced settings were imported successfully
	 * */
	virtual bool                              ImportAdvanced  (const std::vector<std::string> & info) { return false; }
};
