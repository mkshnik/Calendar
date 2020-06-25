//
// Created by Mykhailo Kuvshynov on 13/06/2020.
//

#include "ECalendarTypes.hpp"

std::string RepeatToStr (RepeatType type)
{
	switch (type)
	{
		case RepeatType::Day: 		return "Daily";
		case RepeatType::Week: 		return "Weekly";
		case RepeatType::TwoWeeks:  return "Every 14 days";
		case RepeatType::Month:  	return "Monthly";
		case RepeatType::Year: 		return "Yearly";
		case RepeatType::NoRepeat:  return "No Repeat";
	}
	return "";
}

int 		StrToRepeatNum (const std::string & repeat)
{
	if (repeat == "Daily") 			return 1;
	if (repeat == "Weekly") 		return 2;
	if (repeat == "Every 14 days") 	return 3;
	if (repeat == "Monthly") 		return 4;
	if (repeat == "Yearly") 		return 5;
	else					 		return 6;

}
