//
// Created by Mykhailo Kuvshynov on 02.05.20.
//

#include "CCalendar.hpp"

bool                                              CCalendar::EventAdd                  ()
{
    std::cout << "=================> Event Editor <=================\n";
    std::string name = ScanEventName();
	std::pair<CDate,CTime> dt = CScanner::ScanDateAndTime();
    int type = CScanner::ScanType();

	auto event = EventCreator(name, dt.first, dt.second, type);
	auto checker_array = CheckTime(dt.first, dt.second);
	for (const auto & checker : checker_array)
	{
		if (!checker->Overlap() && !event->Overlap())
		{
			std::cout << "- Event you want to add overlaps with another event. ("
				      << checker->e_name << ").\n Would you like to:\n"
					     "1. Move " <<  checker->e_name << '\n'
		              << "2. Cancel adding event\n"
				         "Type corresponding number.\n";
			switch(CScanner::ScanNumber(0, 1))
			{
				case 0: return false;
				case 1: if (!EventMove(checker->e_name)) return false;
			}
		}
	}
    std::cout << "- Would you like to add more parameters?\n";
    if (CScanner::ScanYorN()) event->Advanced();
	while (!CheckOverlap(event))
	{
		std::cout << "ERROR: One of repeats overlaps another event\n"
			         "- Do you want to add repeat again?\n";
		auto remover = event->e_dates.begin();
		remover++;
		event->e_dates.erase(remover, event->e_dates.end());
		if (CScanner::ScanYorN()) event->Repeat();
	}

    EventInsert(event);
    std::cout << "Your event " + name + " was successfully added :)\n"
				 "==================================================\n";
    return true;
}

bool 											  CCalendar::CheckOverlap		       (std::shared_ptr<CEvent> & event)
{
	for (auto it = event->e_dates.begin(); it != event->e_dates.end(); it++)
	{
		auto overlaped_array = CheckTime(*it, event->GetTime());
		for (const auto & overlaped : overlaped_array)
			if (!overlaped->Overlap() and !event->Overlap())
				return false;
	}
	return true;
}

std::shared_ptr<CEvent>							  CCalendar::EventCreator		       (const std::string & name,
																				        CDate               date,
																				        const CTime &       time,
																				        int                 type)
{
    switch (type)
    {
        case 1: return CMovableEvent 	(name, date, time).Clone();
        case 2: return CMustDoEvent	 	(name, date, time).Clone();
        case 3: return COptionalEvent	(name, date, time).Clone();
        case 4: return CAlarm		 	(name, date, time).Clone();
        case 5: return CReminder	 	(name, date, time).Clone();
		default: return nullptr;
    }
}

std::vector<std::shared_ptr<CEvent>>::iterator 	  CCalendar::EventInsert			   (const std::shared_ptr<CEvent> & new_event)
{
	auto it_date = std::lower_bound(c_bydates.begin(), c_bydates.end(), new_event,
									[](const std::shared_ptr<CEvent> & a, const std::shared_ptr<CEvent> & b)
									{
										if (a->GetInitDate() == b->GetInitDate())
											return a->GetTime() < b->GetTime();
									  	return a->GetInitDate() < b->GetInitDate();
									});

	auto it_name = std::lower_bound(c_byname.begin(), c_byname.end(), new_event,
									[](const std::shared_ptr<CEvent> & a, const std::shared_ptr<CEvent> & b)
									{ return a->e_name < b->e_name; });

	it_date = c_bydates.insert(it_date, new_event);
	return c_byname.insert(it_name, *it_date);
}

bool                                              CCalendar::EventInfo                 (const std::string & name)
{
	std::string nname;
	if (c_byname.empty()) { std::cout << "You dont have any events, type 'event add' to add one.\n"; return true; }
	if (EventGet(name) == c_byname.end())
	{
	  auto found = FindName(name);
	  if (found.empty())
	  	 return false;
	  else
	  {
		std::cout << "Event with that name does not exist, did you mean?\n";
		int i = 1;
		for (const auto & event_name : found)
			std::cout << i << ". " << *event_name << '\n';
		std::cout << "---------------------------------\n"
			         "Type corresponding number to choose or '0' to cancel\n";
		i = CScanner::ScanNumber(0, (int)found.size());
		if (!i) return true;
		nname = *found[i-1];
	  }
	}
	else nname = name;

    auto event = CCalendar::EventGet(nname);
    if (event == c_byname.end())
      return false;

    event->get()->GetInfo();
    return true;
}

std::vector<std::shared_ptr<CEvent>>::iterator    CCalendar::EventGet                  (const std::string & name)
{
     return std::find_if(c_byname.begin(), c_byname.end(),
                              [&name](const auto & event)
                               { return event->e_name == name; });
}

bool                                              CCalendar::List                      () const
{
    if (c_byname.empty())
    {
        std::cout << "You don't have any scheduled events. Type 'event add' to add new event or type 'help'.\n";
        return false;
    }
    std::cout << "--------------------------------------------------------------------------------------\n"
                 "|          Name:          | Time: |   Date:    |    Type:    |        Repeat:        |\n"
                 "--------------------------------------------------------------------------------------\n";
    for (const auto & event : c_bydates)
    {
        std::cout << "| ";
        if (event->e_name.size() > 24)
            std::cout << event->e_name.substr(0, 20) << "...";
        else
        {
            std::cout << event->e_name;
            for (int i = event->e_name.size(); i < 23; i++)
                std::cout << ' ';
        }
        std::cout << " | " << event->GetTime()
				  << " | " << event->GetInitDate()
				  << " | " << event->PrintType()
				  << " | ";

        int spaces = (21 - (int)event->PrintRepeat().length())/2;
		for (int i = 0; i < spaces; i++)
			std::cout << ' ';
		std::cout << event->PrintRepeat();
		for (int i = 0; i < spaces; i++)
			std::cout << ' ';
		if ((21 - event->PrintRepeat().length()) % 2) std::cout << ' ';
		std::cout << " |\n";
    }
    std::cout << "--------------------------------------------------------------------------------------\n";
    return true;
}

std::vector<std::shared_ptr<std::string>>         CCalendar::FindLocation              (const std::string & location)
{
	std::vector<std::shared_ptr<std::string>> found;
	for (const auto & loc_ : CStorage::st_locations)
		if (std::search(loc_->begin(), loc_->end(), location.begin(), location.end()) != loc_->end())
			found.push_back(loc_);

	return found;
}

std::vector<std::shared_ptr<std::string>>         CCalendar::FindName                  (const std::string & name)
{
	std::vector<std::shared_ptr<std::string>> found;
	for (const auto & ev_ : c_byname)
	if (std::search(ev_->e_name.begin(), ev_->e_name.end(), name.begin(), name.end()) != ev_->e_name.end())
		found.push_back(std::make_shared<std::string>(ev_->e_name));
	return found;
}

bool                                              CCalendar::EventLocation             (const std::string & location)
{
	std::string lc = location;
    if (location.empty()) { std::cout << "ERROR: Location name could not be empty :(\n"; return false; }
    if (std::find_if(CStorage::st_locations.begin(), CStorage::st_locations.end(),
    		   [&location] (const auto & lc)
    		          {return *lc == location; }) == CStorage::st_locations.end())
    {
	    auto found = FindLocation(location);
	    if (found.empty()) { std::cout << "- Event with that location does not exist :(\n"; return false; }
	    std::cout << "- Did you mean?\n";
	    int i = 1;
	    for (const auto & loc : found)
	    { std::cout << i << ". " << *loc << '\n'; i++; }
	    std::cout << "---------------------------------\n"
                     "Type corresponding number to choose or '0' to cancel\n";
		int num = CScanner::ScanNumber(0, (int)found.size());
		if (!num) return false;
		lc = *found[num - 1];
    }
    std::cout << "- Found events: \n";
    for (const auto & event : c_bydates)
    	if (event->LocationCheck(lc))
    	    std::cout << "* " << event->e_name << '\n';
    std::cout << "---------------------------------\n";
	return true;
}

void                                              CCalendar::ReminderAdd               (const std::string & name)
{
    if (EventGet(name) != c_byname.end())
    { std::cout << "ERROR: Event/Alarm/Reminder with that name is already exist, choose another one.\n"; return; }
	std::cout << "===============> Reminder Editor <===============\n"
	             "- When would you like to be reminded about it?\n";
    std::pair<CDate,CTime> dt = CScanner::ScanDateAndTime();
    EventInsert(EventCreator(name, dt.first, dt.second, 5));
	std::cout << "Your reminder was successfully added\n"
			  << "=================================================\n";
}

bool                                              CCalendar::AlarmAdd                  (const CTime &       time)
{
    std::cout << "=================> Alarm Editor <=================\n"
                 "- Would you like to name your alarm?\n";
    std::string name;
    if (CScanner::ScanYorN())
        name = ScanEventName();
    else
    {
        name = "Alarm";
            for (int i = 1; ; i++)
            {
                if (EventGet(name) == c_byname.end()) break;
                if (name[name.size()-1] != 'm') name.pop_back();
                name += std::to_string(i);
            }
    }
    std::cout << "- Would you like to specify date? (otherwise it will be set for tomorrow)\n";
    CDate date(0,0,0);
    if (CScanner::ScanYorN())
        date = CScanner::ScanDate();
    else date = ETimeWrapper::TomorrowDate();
    if (ETimeWrapper::Check_Time(time, date) != ETimeWrapper::Future)
	{ std::cout << "ERROR: Alarm could not be set for past time.\n"; return false; }
    std::cout << "- Would you like to add repeat?\n";
    auto alarm = EventCreator(name, date, time, 4);
    if (CScanner::ScanYorN())
        alarm->Advanced();

    EventInsert(alarm);
    std::cout << "Your alarm was successfully added :)\n"
                 "==================================================\n";
    return true;
}

bool                                              CCalendar::EventEdit                 (const std::string & name)
{
    auto it = EventGet(name);
    if (it == c_byname.end()) return false;
    it->get()->GetInfo();
    if (!it->get()->Edit())
        std::cout << it->get()->e_name << " can't be edited.\n";
    return true;
}

bool                                              CCalendar::EventImport               (const std::string & path)
{
	int type, hour, min, day, month, year;
	try {
		for (const auto & event : CSaverLoader::ImportEvents(path))
		{
			if (event.size() < 4)
			{ std::cout << "ERROR: Invalid parameters/Wrong syntax\n"; continue; }

			if (EventGet(event[1]) != c_byname.end())
			{ std::cout << "ERROR: You already have event/alarm/reminder with name " + event[1] + '\n'; continue; }

			type = std::stoi(event[0]);
			sscanf(event[2].c_str(), "%d:%d", &hour, &min);
			sscanf(event[3].c_str(), "%d.%d.%d", &day, &month, &year);
			auto date = CDate(day, month, year);
			auto time = CTime(hour, min);

			if (type < 0 or type > 5 or !date.IsValid() or !time.IsValid())
			{ std::cout << "ERROR: Invalid parameters/Wrong syntax\n"; continue; }

			auto ev = EventCreator(event[1], date, time, type);
			auto checker_array = CheckTime(date, time);
			bool occp = false;
			for (const auto & checker : checker_array)
				if (!checker->Overlap() && !ev->Overlap())
				{
					std::cout << "ERROR: This date and time is already occupied by another event "
				                 "(" + checker->e_name + ")\n";
					occp = true;
					break;
				}
			if (occp) continue;
			EventInsert(ev);
			if (event[4] == "A") ev->ImportAdvanced(event);
			if (ev->e_repeat != RepeatType::NoRepeat)
				if (!CheckOverlap(ev)) {
						std::cout << "ERROR: This date and time is already occupied by another event\n";
						continue;
					}
			std::cout << "Event " + event[1] + " was added.\n";
		}
	} catch (...) { return false; }

	return true;
}

bool                                              CCalendar::EventExport               (const std::string & event,
																						const std::string & path_)
{
	auto it = EventGet(event);
	if (it == c_byname.end()) return false;
	CSaverLoader::ExportTo(path_, it->get()->ExportEvent());
	std::cout << it->get()->e_name + " was exported.\n";
	return true;
}

bool                                              CCalendar::EventMove                 (const std::string & name)
{
    auto event = EventGet(name);
    if (event == c_byname.end())
    { std::cout << "You dont have event with that name\n"; return false; }
    else if (!event->get()->e_move or event->get()->e_repeat != RepeatType::NoRepeat)
    { std::cout << "ERROR: " << event->get()->e_name << " can't be moved.\n"; return false; }

	while (true)
	{
		std::cout << "- Would you like to:\n"
					 "1. Choose time and date where you would like to move your event to*\n"
					 "2. Move to nearest available time*\n"
					 "Type corresponding number or '0' to cancel or '3' to get more info\n";
		switch (CScanner::ScanNumber(0, 3))
		{
			case 0: return false;
			case 1:
				while (true)
				{
					CTime time = CScanner::ScanTime();
					CDate date = CScanner::ScanDate();
					auto checker_array = CheckTime(date, time);
					for (const auto & checker : checker_array)
					{
						if (!checker->Overlap() && !event->get()->Overlap())
						{
							std::cout << "ERROR: This date and time is already occupied by another event "
										 "(" + checker->e_name + ")\n"
										  "Would you like to:\n"
				                          "1. Move " + checker->e_name + "\n"
										  "2. Choose another move settings\n"
										  "Press corresponding number or '0' to cancel\n";
							switch (CScanner::ScanNumber(0, 2))
							{
								case 1:
									if (checker->e_move)
		                                    if (EventMove(checker->e_name)) break;
									std::cout << "ERROR: " << checker->e_name << " can't be moved\n"
		                                         "Choose another time and date\n";
									break;
									case 2: break;
									case 0: return false;
							}
						}
					}
					event->get()->GetTime() = time;
					event->get()->e_dates.erase(event->get()->e_dates.begin());
					event->get()->e_dates.insert(date);
                    std::cout << "Event was successfully moved.\n";
					return true;
				}
			case 2: {
				auto move_to_time = event->get()->GetTime();
				auto tmp_date = *event->get()->e_dates.begin();
				for (move_to_time += 30; move_to_time <= CTime(23, 59); move_to_time += 1)
				{
					auto checker_array = CheckTime(tmp_date, move_to_time);
					if (checker_array.empty())
					{
						event->get()->GetTime() = move_to_time;
						std::cout << "Event was successfully moved.\n";
						return true;
					}
					for (const auto & checker : checker_array)
						if (checker->Overlap())
						{
							event->get()->GetTime() = move_to_time;
							std::cout << "Event was successfully moved.\n";
							return true;
						}
				}
                std::cout << "ERROR: " << event->get()->e_name << " can't be moved\n";
				return false;
			}
			case 3:
				std::cout << "1. Events with repeats can't be moved to another date\n"
							 "2. Nearest available time means time within current day\n";
				break;
			default:;
		}
		std::cout << "ERROR: " << event->get()->e_name << " can't be moved\n";

		return false;
	}
	std::cout << event->get()->e_name + " was successfully moved.\n";
}

bool                                              CCalendar::EventRemove               (const std::string & name)
{
	if (c_byname.empty()) { std::cout << "You dont have any events, type 'event add' to add one.\n"; return true; }
  	auto it = EventGet(name);
    if (it == c_byname.end()) return false;
    c_bydates.erase(std::remove_if(c_bydates.begin(), c_bydates.end(),
                                   [&name](const std::shared_ptr<CEvent> & event)
                                   { return event->e_name == name; }), c_bydates.end());
    c_byname.erase(it);
    std::cout << name << " was removed.\n";
    return true;
}

std::string                                       CCalendar::ScanEventName             ()
{
    std::string name;
    while (true)
    {
        name = CScanner::ScanName();
        if (EventGet(name) != c_byname.end())
          	std::cout << "ERROR: Event/Alarm/Reminder with that name is already exist, choose another one.\n";
        else return name;
    }
}

void        									  CCalendar::SaveEvents 			   () const
{
	for (const auto & event : c_bydates)
		CSaverLoader::SaveStr(event->SaveEvent());
}

CCalendar & 									  CCalendar::LoadEvents  			   ()
{
	int type, hour, min, day, month, year;
	for (const auto & event : CSaverLoader::LoadEvents())
	{
		type = std::stoi(event[0]);
		sscanf(event[2].c_str(), "%d:%d", &hour, &min);
		sscanf(event[3].c_str(), "%d.%d.%d", &day, &month, &year);
		auto ev = EventInsert(EventCreator(event[1], CDate(day, month, year), CTime(hour, min), type));
		if (event[4] == "A") ev->get()->LoadAdvanced(event);
	}
	return *this;
}

std::vector<std::shared_ptr<CEvent>>    CCalendar::CheckTime                 (const CDate & date, const CTime & time)
{
	std::vector<std::shared_ptr<CEvent>> found;
	copy_if(c_bydates.begin(), c_bydates.end(), std::inserter(found, found.end()),
	                  [&date](const auto & event)
	                  {
		                  return event->GetInitDate() == date
		                  or find(event->e_dates.begin(), event->e_dates.end(),
		                            date) != event->e_dates.end();
	                  });
	return found;
}

CCalendar::CCalendar (const CCalendar & calendar)
{
	for (auto & bdate : calendar.c_bydates)
		c_bydates.push_back(bdate->Clone());
	for (auto & bname : c_byname)
		c_byname.push_back(bname->Clone());

}

CCalendar & CCalendar::operator = (const CCalendar & calendar)
{
	if (this == &calendar) return *this;
	for (auto & bdate : calendar.c_bydates)
		c_bydates.push_back(bdate->Clone());
	for (auto & bname : c_byname)
		c_byname.push_back(bname->Clone());
	return *this;
}