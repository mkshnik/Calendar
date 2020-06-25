//
// Created by Mykhailo Kuvshynov on 02/06/2020.
//

#include "CSharedEvent.hpp"

void CSharedEvent::GetInfo () const
{
    std::cout << "========>" << PrintType() << "Event  <========\n"
              << "# Name: " << e_name << '\n'
              << "# Time: " << e_time << '\n'
              << "# Date: " << *e_dates.begin() << '\n';
    if (s_location)
        std::cout << "# Location: " << *s_location << '\n';
    if (!s_description.empty())
    {
        std::cout << "# Description: ";
        std::string line;
        bool firstline = true;
        for (auto i = s_description.begin(); i != s_description.end(); i++)
        {
            line += *i;
            if ((line.length() >= 30 && *i == ' ') || next(i) == s_description.end()) {
                if (firstline) {
                    std::cout << line << '\n';
                    firstline = false;
                }
                else std::cout << "               " << line << '\n';
                line.clear();
            }
        }
    }
    if (!s_participants.empty())
    {
        std::cout << "# Participants:\n";
        for (const auto & participant : s_participants)
            std::cout << *participant << '\n';
    }
    if (e_dates.size() > 1)
    {
        std::cout << "# Repeat on:\n";
        for (auto date = e_dates.begin(); date != e_dates.end(); date++)
            if (date != e_dates.begin())
        		std::cout << "  @ " << *date << '\n';
    }
    std::cout << "============================\n";
}

bool                            CSharedEvent::ScanParticipants ()
{
    std::string another_one = "- Would you like to add another participant?\n";
    do {
        if (!CStorage::st_participants.empty())
        {
            std::cout << "- Would you like to add participant from previously added?\n";
            if (CScanner::ScanYorN())
            {
                CStorage::ListParticipantsNames();
                std::cout << "Type corresponding number or '0' to add another participant\n";
                int x = CScanner::ScanNumber(0, CStorage::st_participants.size());
                if (x != 0)
                {
                    auto tl = CStorage::st_participants[x-1];
                    if (s_participants.end() == std::find(s_participants.begin(), s_participants.end(), tl))
                    { s_participants.push_back(tl); std::cout << another_one; continue; }
                    else { std::cout << "- This participant is already taking part in this event :)\n"
                                     << another_one; continue; }
                }
            }
        }

        std::cout << "- You can add participants to your event by writing their names and information.\n";
        std::string name = CScanner::ScanName();
        auto tp = CStorage::CheckParticipant(name);
        if (tp != CStorage::st_participants.end())
        {
            std::cout << "- You have previously added participant with that name, you have following options: \n"
                         "1. Use already created participant's information\n"
                         "2. Update already created participant\n"
                         "3. Add different participant or stop adding participants\n";
            int num = CScanner::ScanNumber(1, 3);
            if (num == 2) tp->get()->p_info = CScanner::ScanInfo();
            else if (num == 3) { std::cout << "- Would you like to add different participant?\n"; continue; }
            if (CheckParticipant(*tp)) s_participants.push_back(*tp);
            else { std::cout << "- This participant is already taking part in this event :)\n"
                             << another_one; continue; }
        }
        else
        {
            std::string info = CScanner::ScanInfo();
            std::shared_ptr<CParticipant> tl = std::make_shared<CParticipant>(CParticipant(name, info));
            if (CheckParticipant(tl)) { s_participants.push_back(tl); CStorage::st_participants.push_back(tl); }
            else { std::cout << "- This participant is already taking part in this event :)\n"
                             << another_one; continue; }
        }
        std::cout << "- Would you like to add another participant?\n";
    } while (CScanner::ScanYorN());
	return true;
}

bool           CSharedEvent::CheckParticipant (const std::shared_ptr<CParticipant> & participant)
{
    return s_participants.end() == std::find(s_participants.begin(), s_participants.end(), participant);
}

bool           CSharedEvent::ScanLocation     ()
{
    if (!CStorage::st_locations.empty())
    {
        std::cout << "- Would you like to choose location from previously used?\n";
        if (CScanner::ScanYorN()) {
            CStorage::ListLocations();
            std::cout << "Type corresponding number or '0' to choose another location\n";
            int x = CScanner::ScanNumber(0, CStorage::st_locations.size());
            if (x != 0) { s_location = CStorage::st_locations[x - 1]; return true; }
        }
    }
    std::shared_ptr<std::string> location;
    while (true)
    {
        location = CScanner::ScanLocation();
        if (location) { s_location = location; return true; }
        std::cout << "Location can't be empty, do you want to try adding location again?\n";
        if (!CScanner::ScanYorN()) { return false; }
        else return ScanLocation();
    }
}

bool           CSharedEvent::ScanDescription  ()
{
    std::string description;
    while(true)
    {
        std::cout << "-> Description: ";
        std::getline(std::cin, description);
        if (std::cin.eof())
            throw std::logic_error("EOF");
        else if (description.length() > 200)
            std::cout << "ERROR: Description is too long :("
                         "\nTry again: ";
        else if (description.empty())
        {
            std::cout << "Description could not be empty, would you like to try again?\n";
            if (!CScanner::ScanYorN()) return false;
        }
        else break;
    }
    s_description = description;
    return true;
}

bool CSharedEvent::Advanced            ()
{

    std::cout << "You can add/edit following attributes to your event:\n"
                 "| 1. Location | 2. Participants | 3. Description | 4. Repeat |\n"
                 "Press corresponding number to choose section to add or '0' to save event:\n";
    std::map<std::string,bool> attributes;
    attributes["location"]     = false;
    attributes["participants"] = false;
    attributes["description"]  = false;
    attributes["repeat"]       = false;
    while(true)
    {
        int num = CScanner::ScanNumber(0, 4);
        if (num == 1 && attributes["location"])     continue;
        if (num == 2 && attributes["participants"]) continue;
        if (num == 3 && attributes["description"])  continue;
        if (num == 4 && attributes["repeat"])       continue;
        if (num == 0) break;
        switch (num)
        {
            case 1:
                if (ScanLocation())
                    attributes["location"]     = true;
                break;
            case 2:
                if (ScanParticipants())
                    attributes["participants"] = true;
                break;
            case 3:
                if (ScanDescription())
                    attributes["description"]  = true;
                break;
            case 4:
                if (Repeat())
                	attributes["repeat"]	   = true;
                break;
        }
        if (attributes["location"] && attributes["participants"] && attributes["description"] && attributes["repeat"])
        	break;
        std::cout << "Do you want to add anything else? Press '0' if not or corresponding key to add section.\n| ";
        if (!attributes["location"])      std::cout << "1. Location | ";
        if (!attributes["participants"])  std::cout << "2. Participants | ";
        if (!attributes["description"])   std::cout << "3. Description | ";
        if (!attributes["repeat"])		  std::cout << "4. Repeat | ";
        std::cout << '\n';
    }
    return true;
}

bool                    CSharedEvent::Repeat()
{
    std::cout << "You can set repeat for the following intervals:\n"
                 "1. Every week | 2. Every 14 days | 3. Every month* | 4. Every year*\n"
                 "Press corresponding number to choose, '5' for more info or '0' to cancel:\n";
    int num = 5;
    while (num == 5)
    {
        num = CScanner::ScanNumber(0, 5);
        if (num == 5)
            std::cout << "Every month means repeating event on the same day number each month and flooring \n"
                         "to the last day of month when needed (when there not that many days in that month)\n"
                         "--\n"
                         "Every year: same as with month in case of February 29th \n"
                         "(in non leap years February 28th will be chosen)\n";
    }
    if (!num) return false;
    std::cout << "Repeat until:\n";
    CDate until = CScanner::ScanDate();
    if (until < *e_dates.begin())
    { std::cout << "ERROR: End date can't be earlier initial date"; return false; }
    SetRepeat(num + 1, until);
	std::cout << "Repeat was successfully set :)\n"
			     "==============================\n";
    return true;
}

std::string CSharedEvent::SaveShared() const
{
    std::string export_;
    export_ += e_name + ';' + e_time.ExportTime() + ';' + e_dates.begin()->ExportDate() + ';';
    // Repeat, Participants, Location, Description
    export_ += "A;";
    if (e_dates.size() == 1) export_ += "N;";
    else
    {
        export_ += "A;";
        export_ += PrintRepeat() + ';';
        auto last_date = e_dates.end();
        last_date--;
        export_ += last_date->ExportDate() + ';';
    }
    if (s_participants.empty()) export_ += "N;";
    else
    {
        export_ += "A;";
        for (const auto & participant : s_participants)
        {
            auto it = find(CStorage::st_participants.begin(), CStorage::st_participants.end(), participant);
            export_ += std::to_string(it - CStorage::st_participants.begin());
        }
        export_ += ';';
    }
    if (!s_location) export_ += "N;";
    else
    {
        export_ += "A;";
        auto it = find(CStorage::st_locations.begin(), CStorage::st_locations.end(), s_location);
        export_ += std::to_string(it - CStorage::st_locations.begin()) + ';';
    }
    if (s_description.empty()) export_ += "N;";
    else export_ += "A;" + s_description + ';';

    return export_;
}

bool CSharedEvent::LoadAdvanced   (const std::vector<std::string> & info)
{
	int counter = 0;
	if (info[5] == "A")
	{
		SetRepeat(StrToRepeatNum(info[6]), ETimeWrapper::StrToDate(info[7]));
		counter += 2;
	}
	if (info[6 + counter] == "A")
	{
		for (const auto & num : info[7 + counter])
			s_participants.push_back(CStorage::st_participants[num - '0']);
		counter++;
	}
	if (info[7 + counter] == "A")
	{
		s_location = CStorage::st_locations[std::stoi(info[8 + counter])];
		counter++;
	}
	if (info[8 + counter] == "A") s_description = info[9 + counter];
	return true;
}

bool CSharedEvent::ImportAdvanced   (const std::vector<std::string> & info)
{
	{
		int counter = 0;
		if (info[5] == "A")
		{
			SetRepeat(StrToRepeatNum(info[6]), ETimeWrapper::StrToDate(info[7]));
			counter += 2;
		}
		if (info[6 + counter] == "A")
		{
			std::string name, info_;
			bool add_name = true;
			for (const auto & c : info[7 + counter])
			{

				if (c == ',')
				{
					auto tp = CStorage::CheckParticipant(name);
					if (tp != CStorage::st_participants.end())
						s_participants.push_back(*tp);
					else
					{
						auto pt = std::make_shared<CParticipant>(CParticipant(name, info_));
						CStorage::st_participants.push_back(pt);
						s_participants.push_back(pt);
					}
					name.clear();
					info_.clear();
					add_name = true;
					continue;
				}
				if (c == ':') { add_name = false; continue; }
				if (c == ';') break;
				if (add_name) name += c;
				else info_ += c;
			}
			counter++;
		}
		if (info[7 + counter] == "A")
		{
			auto lc = CStorage::CheckLocation(info[8 + counter]);
			if (lc == CStorage::st_locations.end())
			{
				auto location = std::make_shared<std::string>(info[8 + counter]);
				CStorage::st_locations.push_back(location);
				s_location = location;
			}
			else s_location = *lc;
			counter++;
		}
		if (info[8 + counter] == "A") s_description = info[9 + counter];
		return true;
	}
}

std::string 				CSharedEvent::ExportShared     () const
{
    std::string export_;
    export_ += e_name + ';' + e_time.ExportTime() + ';' + e_dates.begin()->ExportDate() + ';';
    // Repeat, Participants, Location, Description
    export_ += "A;";
    if (e_dates.size() == 1) export_ += "N;";
    else
    {
        export_ += "A;" + PrintRepeat() + ';';
        auto last_date = e_dates.end(); last_date--;
        export_ += last_date->ExportDate() + ';';
    }
    if (s_participants.empty()) export_ += "N;";
    else
    {
        export_ += "A;";
        for (const auto & participant : s_participants)
        {
            auto it = find(CStorage::st_participants.begin(), CStorage::st_participants.end(), participant);
            export_ += it->get()->p_fullname + ':' + it->get()->p_info + ',';
        }
        export_ += ';';
    }

    if (!s_location) export_ += "N;";
    else export_ += "A;" + *s_location + ';';

    if (s_description.empty()) export_ += "N;";
    else export_ += "A;" + s_description + ';';

    return export_;
}


