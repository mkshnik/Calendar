//
// Created by Mykhailo Kuvshynov on 17.06.2020.
//

#include "CShowCalendar.hpp"

void CShowCalendar::Month () const
{
	CDate current = ETimeWrapper::CurrentDate();
	CDate start_date(1, current.d_month, current.d_year);
	std::cout << "=======================================\n";
	for (; start_date.IsValid(); start_date.d_day++)
	{
		int space_counter = 4;
		std::string date;
		if (start_date.d_day < 10) date += ' ';
		date += std::to_string(start_date.d_day);
		if (start_date == current) { date += '@'; space_counter--; }
		if (!CheckDate(start_date).empty()) { date += '*'; space_counter--; }
		std::cout << date;
		for (int i = 0; i < space_counter; i++) std::cout << ' ';
		if (!(start_date.d_day % 7)) std::cout << '\n';
	}
	std::cout << "\n=======================================\n";
}

void CShowCalendar::Week  () const
{
	if (show_events->empty())
	{ std::cout << "You dont have any events, type 'event add' to add.\n"; return; }
	std::vector<std::vector<std::shared_ptr<CEvent>>> week;
	auto start_date = ETimeWrapper::CurrentDate();
	auto end_date   = ETimeWrapper::CurrentDate();
	auto time       = ETimeWrapper::CurrentTime();
	ETimeWrapper::AddDays(start_date, time, -ETimeWrapper::GetWeekday() + 1);
	ETimeWrapper::AddDays(end_date, time, 7 - ETimeWrapper::GetWeekday());
	size_t max_size = 0;
	for (; start_date <= end_date; ETimeWrapper::AddDays(start_date, time, 1))
	{
		week.push_back(CheckDate(start_date));
		if (week[week.size()-1].size() > max_size) max_size = week[week.size()-1].size();
	}
	if (week.empty()) { std::cout << "- You don't have any events in the upcoming week.\n"; return; }

	std::cout << "-------------------------------------------------------------------------------------\n"
	             "|    Mon    |    Tue    |    Wed    |    Thu    |    Fri    |    Sat    |    Sun    |\n"
			     "|";
				 for (ETimeWrapper::AddDays(start_date, time, -7);
				      start_date <= end_date;
				      ETimeWrapper::AddDays(start_date, time, 1))
				 {
				 	std::cout << "   " << start_date.d_day << '.';
				 	if (start_date.d_month < 10) std::cout << 0;
				 	std::cout << start_date.d_month << "   |";
				 }
	std::cout << "\n|-----------|-----------|-----------|-----------|-----------|-----------|-----------|\n";
	for (size_t i = 0; i < max_size; i++)
	{
		std::cout << '|';
		for (int day = 0; day < 7; day++)
		{
			if (week[day].size() < i)
			{ std::cout << "           |"; continue; }
			if (week[day].size() < i+1)
			{ std::cout << "           |"; continue; }
			if (week[day][i]->e_name.size() > 11)
				std::cout << week[day][i]->e_name.substr(0, 9) << "..|";
			else
			{
				std::cout << week[day][i]->e_name;
				for (int c = week[day][i]->e_name.size(); c < 11; c++)
					std::cout << ' ';
				std::cout << '|';
			}
		}
		std::cout << '\n';
	}
	std::cout << "-------------------------------------------------------------------------------------\n";
}

void CShowCalendar::Day   (const CDate & date) const
{
	if (show_events->empty())
	{ std::cout << "You dont have any events, type 'event add' to add.\n"; return; }
	auto found = CheckDate(date);
	if (found.empty())
	{ std::cout << "There are no events/reminders/alarms on the chosen date\n"; return; }

	std::cout << "=====> " + date.ExportDate() + " <=====\n";
	for (const auto & event : found)
	{
		if (event->e_name.size() > 16)
			std::cout << event->e_name.substr(0, 13) << "...";
		else
		{
			std::cout << event->e_name;
			for (int i = event->e_name.size(); i < 16; i++)
				std::cout << ' ';
		}
		std::cout << " | " << event->GetTime() << '\n';
	}
	std::cout << "========================\n";
}

std::vector<std::shared_ptr<CEvent>> CShowCalendar::CheckDate (const CDate & date) const
{
	std::vector<std::shared_ptr<CEvent>> found;
	copy_if(show_events->begin(), show_events->end(), std::inserter(found, found.end()),
	                  [&date](const auto & event)
	                  {
						  return event->GetInitDate() == date
						  or find(event->e_dates.begin(), event->e_dates.end(),
						  		date) != event->e_dates.end();
	                  });
	return found;
}

