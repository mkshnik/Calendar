//
// Created by mkshnik on 04.05.20.
//

#pragma once
#include <string>

enum class RepeatType { Day, Week, TwoWeeks, Month, Year, NoRepeat };

/** Converts RepeatType to string
 * @param type to be converted
 * @return string after convertion
 */
std::string RepeatToStr    (RepeatType 			type);
int 		StrToRepeatNum (const std::string & rep);

enum class EventType  { Movable, MustDO, Optional };
enum class CalendarType { Yearly, Monthly, Weekly };
