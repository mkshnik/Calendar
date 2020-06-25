//
// Created by mkshnik on 27.05.20.
//

#pragma once
#include <iostream>
#include "CTime.hpp"
#include "CDate.hpp"
#include "CStorage.hpp"
#include "ETimeWrapper.hpp"

class CScanner
{
public:
	/**
	 * Scans time from user,
	 * controls format and if time is valid
	 * @returns scanned time
	 * */
    static CTime                            ScanTime            ();

    /**
     * Scans date from user
     * controls format and if date is valid
     * @returns scanned date
     */
    static CDate                            ScanDate            ();

    /**
     * Scans date and time by calling ScanTime and ScanDate until user inputs time in dates that are in the future
     * @returns pair of scanned date and time
     */
    static std::pair<CDate,CTime>           ScanDateAndTime     ();

    /**
     * Scans name from user, checks it's syntax and length
     * @return scanned name
     */
    static std::string                      ScanName            ();

    /**
     * Scans type of CSharedEvent instance
     * @return scanned type
     */
    static int                              ScanType            ();

    /** Scans yes or no from user */
    static bool                             ScanYorN            ();

	/**
     * Scans info from user, checks it's syntax and length
     * @return scanned info
     */
    static std::string                      ScanInfo            ();

    /**
     * Scans number from range [min, max]
     * @return scanned number
     */
    static int                              ScanNumber          (int min, int max);

	/**
 	 * Scans info from user, checks it's syntax and length.
 	 * ALso checks if location with that name is already in CStorage::st_location,
 	 * in positive case returns pointer to location in it
 	 */
    static std::shared_ptr<std::string>     ScanLocation        ();

    /**
     * Checks syntax of given string,
     * optional parameter is 'allowed' which represents allowed symbols besides english letters
     * @return
     */
    static bool                             CheckSyntax         (const std::string &, const std::string & = "");
};

