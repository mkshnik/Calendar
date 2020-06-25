//
// Created by mkshnik on 06.05.20.
//

#pragma once
#include <utility>

#include "CEvent.hpp"
#include "ETimeWrapper.hpp"

/** Abstract class represents a view of the calendar */
class CShowCalendar
{
private:
	/** Pointer to vector of events sorted by dates */
    std::vector<std::shared_ptr<CEvent>> * show_events;
public:
    explicit CShowCalendar (std::vector<std::shared_ptr<CEvent>> * events)
    : show_events(events)
    {}

	~CShowCalendar() { delete show_events; }

    /**
     * Checks if date pf any event matches given date.
     * @returns all matches
     * */
	std::vector<std::shared_ptr<CEvent>> CheckDate (const CDate & date) const;

	/** Shows calendar in 'Monthly' format */
	void Month () const;

	/** Shows calendar in 'Weekly' format */
	void Week  ()  const;

	/** Shows calendar in 'Daily' format */
	void Day   (const CDate & date)  const;

	CShowCalendar();
};
