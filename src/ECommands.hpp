//
// Created by mkshnik on 28.05.20.
//

#pragma once
#include <string>
#include "ECalendarTypes.hpp"
#include "CTime.hpp"

enum class Commands    { event, date, reminder, alarm, show, save, exit, help, location, info, export_, import, edit, remove, move, wrong };
enum class EventParams { add, list, wrong };
enum class DateParams  { now, info, wrong, week, month };

/** Converts string to command */
Commands    StrToCommand    (const std::string & command);

/** Convert string to event parameter */
EventParams StrToEventParam (const std::string & command);

/** Convert string to date parameter */
DateParams  StrToDateParams (const std::string & command);

/**
 * Converts quoted string to a normal one
 * @param quoted string to be converted
 * @returns for example 'text' -> text
 */
std::string QuotedStrToStr  (const std::string & quoted);

/**
 * Converts quoted string to an instance of class CTime
 * @param quoted string to be converted
 * @return instance of CTime after conversion
 */
CTime       QuotedStrToTime (const std::string & quoted);

/**
 * Checks quoted text syntax (if it is surrounded by apostrophes and is not empty
 * @param text to be checked
 * @return true if syntax if right and false if not
 */
bool        CheckTextSyntax (const std::string & text);
