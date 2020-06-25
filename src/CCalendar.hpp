//
// Created by Mykhailo Kuvshynov (kuvshmyk@fit.cvut.cz) on 05.05.20.
//

#pragma once
#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <set>
#include <map>
#include <algorithm>
#include <cctype>
#include <functional>
#include "CEvent.hpp"
#include "CAlarm.hpp"
#include "CReminder.hpp"
#include "CMovableEvent.hpp"
#include "CMustDoEvent.hpp"
#include "COptionalEvent.hpp"
#include "ETimeWrapper.hpp"
#include "CScanner.hpp"

/** Class represents a calendar with events, alarms and reminders */
class CCalendar
{
protected:
	/** Stores pointers to instances of abstract class CEvent sorted by name. */
    std::vector<std::shared_ptr<CEvent>>              c_bydates;

    /** Stores pointers to instances of abstract class CEvent sorted by date. */
    std::vector<std::shared_ptr<CEvent>>              c_byname;
public:

    CCalendar () : c_bydates{}, c_byname{} {}

    ~CCalendar() = default;

	CCalendar (const CCalendar & calendar);
    CCalendar & operator = (const CCalendar &);

    /** @returns reference to c_bydates */
	std::vector<std::shared_ptr<CEvent>> &            GetEvents                 () { return c_bydates; }

	/** Opens event editor for creating a new event */
	bool                                              EventAdd                  ();

	/**
	 * @param event's name
	 * Moves event to another time/date. If it overlaps with another event
	 * asks user if he wants to change chosen time/date or move other event.
	 */
	bool                                              EventMove                 (const std::string &);

	/**
	 * @param event's name
	 * Removes event from a calendar
	 * */
	bool                                              EventRemove               (const std::string &);

	/**
	 * @returns iterator to pointer of CEvent found by it's name in c_byname.
	 * Or if it wasn't found iterator to last element
	 * */
	std::vector<std::shared_ptr<CEvent>>::iterator    EventGet                  (const std::string &);

	/**
	 * @param event's name
	 * @returns information about event
	 */
	bool                                              EventInfo                 (const std::string &);

	/**
	 * @param event's name
	 * @returs fasle if no event happening on searched location and true in any other case
	 */
	bool                                              EventLocation             (const std::string &);

	/**
	 * Creates new event (subclass of CEvent) by given parameters
	 * @param name
	 * @param date
	 * @param time
	 * @param type
	 * @return Pointer to newly created event
	 */
	static std::shared_ptr<CEvent>				      EventCreator				(const std::string & name,
																				 CDate               date,
																				 const CTime &       time,
																				 int                 type);

	/** Saves all events to savedata.txt */
	void 									  		  SaveEvents 				() const;

	/** Loads all events from savedata.txt */
	CCalendar & 									  LoadEvents    			();
	bool                                              EventImport               (const std::string &);

	/**
	 * @param event's name
	 * @param file's name
	 * @return
	 */
	bool                                              EventExport               (const std::string &,
																				 const std::string &);

	/**
	 * Displays a list of all events
	 * @returns false if there are no events and true in other cases
	 * */
	bool                                              List                      () const;

	/**
	 * Take event's name as an input until given name is unique among whole calendar
	 * @return scanned name
	 */
	std::string                                       ScanEventName             ();

	/**
	 * Creates new reminder and adds it to calendar
	 * @param name for new reminder
	 */
	void                                              ReminderAdd               (const std::string & name);

	/**
	 * Creates new alarm and adds iut to calendar
	 * @return true if alarm was successfully added or false if user tries to set alarm for a past time
	 */
	bool                                              AlarmAdd                  (const CTime&);

	/**
	 * Opens edit menu for chosen event
	 * @param name of event to be edited
	 * @return false if event with that name does not exist
	 */
	bool                                              EventEdit                 (const std::string &);

	/**
	 * @param date
	 * @param time
	 * @returns vector of events which time matches "time" parameter and date could be found in repeats or initial date
	 */
	std::vector<std::shared_ptr<CEvent>>              CheckTime                 (const CDate & date, const CTime& time);
private:
	/**
	 * Inserts given event to both c_byname and c_byydates vectors
	 * @param event pointer to an event to be inserted
	 * @return iterator to the inserted event in c_byname
	 */
	std::vector<std::shared_ptr<CEvent>>::iterator    EventInsert				(const std::shared_ptr<CEvent> & event);

	/**
	 * Looks for matches among location of given location (also searches as substring)
	 * @param location to be searched
	 * @returns vector of events that are happening on searched location
	 * */
	std::vector<std::shared_ptr<std::string>>         FindLocation              (const std::string &);

	/**
	 * Checks if event has any overlaps with events that aren't allowing overlapping
	 * @return
	 */
	bool                                              CheckOverlap              (std::shared_ptr<CEvent> &);

	/**
	 * @param particle to be searched
	 * Search given name as substring
	 * @returns vector of events that are matches
	 * */
    std::vector<std::shared_ptr<std::string>> 		  FindName                  (const std::string &);
};
