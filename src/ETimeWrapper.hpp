//
// Created by mkshnik on 05.05.20.
//

#pragma once
#include <chrono>
#include <ctime>
#include <iomanip>
#include "CDate.hpp"
#include "CTime.hpp"

/** @namespace represents wrapper around <chrono> library */
namespace ETimeWrapper
{
	using days = std::chrono::duration<int,std::ratio<86400>>;
    enum        		   	TimeType         { Past, Present, Future };

    /**
     * Checks if given time and date are past/present or future
     * @returns type of time
     */
	TimeType    		   	Check_Time       (CTime, CDate);

	/** Returns instance of class CDate that represents tomorrow */
    CDate       		   	TomorrowDate     ();

	/** Returns instance of class CDate that represents current date */
	CDate       		   	CurrentDate      ();

	/** Return instance of class CTime that represents current time */
    CTime       		   	CurrentTime      ();

	/**
	 * Converts instance of CDate and optionally CTime to time_t
	 * @param date to be converted
	 * @param time to be converted
	 * @returns time_t converted from date and time
	 */
    time_t      		   	DateTo_Time_t    (const CDate & date, const CTime & time = CTime(0, 0));

    /**
     * Converts time_t to instance of CDate
     * @param time to be converted
     * @returns date converted from time
     */
    CDate       		   	Time_t_ToDate    (const std::time_t & time);

    /**
     * Adds given number of days to diven date
     * @param date to add days to
     * @param time just here for gun
     * @param days amount of days to be added
     */
    void 				   	AddDays        	 (CDate & date, const CTime & time, int days);

    /** Converts string to instance of class CDate */
    CDate   			   	StrToDate	   	 (const std::string &);

    /** Get number of current day of a week */
    int                     GetWeekday       ();
}

