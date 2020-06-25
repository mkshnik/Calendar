//
// Created by mkshnik on 27.05.20.
//

#include "CScanner.hpp"

bool            CScanner::ScanYorN        ()
{
    std::string ans;
    do {
        std::cout << "[y/n]: ";
        std::getline(std::cin, ans);
        if (std::cin.eof())
            throw std::logic_error("EOF");
    } while (ans.length() != 1 || (ans != "y" && ans != "n"));
    return ans == "y";
}

CTime           CScanner::ScanTime        ()
{
    std::string time;
    std::cout << "-> Time (hh:mm): ";
    char ch = ' '; int h, m, checker;
    while (true)
    {
        std::getline(std::cin, time);
        if (std::cin.eof())
            throw std::logic_error("EOF");
        checker = sscanf(time.c_str(), "%d%c%d", &h, &ch, &m);
        if (checker != 3 || ch != ':' || time.length() != 5)
            std::cout << "ERROR: Wrong time format, try again.\n-> Time (hh:mm): ";
        else break;
    }
    CTime t_time = CTime(h, m);
    if (!t_time.IsValid())
    { std::cout << "ERROR: Your time is not valid.\n"; return ScanTime(); }
    return t_time;
}

std::string     CScanner::ScanName        ()
{
    std::string name;
    while(true)
    {
        std::cout << "-> Name: ";
        std::getline(std::cin, name);
        if (std::cin.eof()) throw std::logic_error("EOF");
        else if (name.length() > 30) std::cout << "ERROR: Name is too long :(\n";
        else if (name.length() < 2)  std::cout << "ERROR: Name is too short :(\n";
        else if (name.length() == 0) std::cout << "ERROR: Name can't be empty :(\n";
        else if (!CheckSyntax(name))
            std::cout << "ERROR: You used forbidden symbols, only english letters [a-z] upper/lower case are allowed.\n";
        else break;
    }
    return name;
}

CDate           CScanner::ScanDate        ()
{
    std::string date;
    char ch = ' ', ch2 = ' ';
    int year, day, month;
    std::cout << "-> Date (dd.mm.yyyy): ";
    while (true)
    {
        std::getline(std::cin, date);
        if (std::cin.eof())
            throw std::logic_error("EOF");
        if (sscanf(date.c_str(), "%d%c%d%c%d", &day, &ch, &month, &ch2, &year) != 5
            || ch != '.' || ch2 != '.' || date.length() != 10                             )
            std::cout << "ERROR: Wrong date format, try again.\n-> Date (dd.mm.yyyy): ";
        else break;
    }
    auto d_date = CDate(day, month, year);
    if (!d_date.IsValid())
	{ std::cout << "ERROR: Your date is not valid.\n"; return ScanDate(); }
    return d_date;
}

int              CScanner::ScanType        ()
{
    std::cout << "- Would you like to choose type of your event? Otherwise your event will be 'Optional'\n";
    if (!ScanYorN()) return 3;

    std::cout << "Choose type of your event by typing corresponding number or '0' for types information\n"
                 "1: Movable | 2: MustDO | 3: Optional\n"
                 ">>> ";
    int number = 0;
    std::string snum;
    while (true)
    {
        std::getline(std::cin, snum);
        if (std::cin.eof())
            throw std::logic_error("EOF");
        if (snum.length() != 1 || sscanf(snum.c_str(), "%d", &number) != 1 || number > 3 || number < 0)
            std::cout << "ERROR: Something wrong, try again :)\n"
                         ">>> ";
        else if (number == 0)
            std::cout << " * Movable: could be moved to another time or location.\n"
                         " * MustDo: cannot be changed or moved after created.\n"
                         " * Optional: could be moved to another time, location and description\n"
                         "             could be changed. Also can be overlapped with other event(s).\n"
                         ">>> ";
        else return number;
    }
}

std::string      CScanner::ScanInfo        ()
{
    std::string info;
    while(true)
    {
        std::cout << "-> Info: ";
        std::getline(std::cin, info);
        if (std::cin.eof())
            throw std::logic_error("EOF");
        else if (info.length() > 200)
            std::cout << "ERROR: Info is too long :(\n";
        else if (!CheckSyntax(info))
            std::cout << "ERROR: You used forbidden symbols, only english letters [a-z] upper/lower case are allowed.\n";
        else break;
    }
    return info;
}

int              CScanner::ScanNumber      (int min, int max)
{
    std::string snum;
    int number;
    std::cout << ">>> ";
    while (true)
    {
        std::getline(std::cin, snum);
        if (std::cin.eof())
            throw std::logic_error("EOF");
        if (snum.length() != 1 || sscanf(snum.c_str(), "%d", &number) != 1 || number > max || number < min)
            std::cout << "ERROR: Something wrong, try again :)\n"
                         ">>> ";
        else break;
    }
    return number;
}

std::shared_ptr<std::string> CScanner::ScanLocation ()
{
    std::string location;
    while(true)
    {
        std::cout << "-> Location: ";
        std::getline(std::cin, location);
        if (std::cin.eof())
            throw std::logic_error("EOF");
        else if (location.length() > 30)
            std::cout << "ERROR: Location is too long :(\n";
        else if (!CheckSyntax(location))
            std::cout << "ERROR: You used forbidden symbols, only english letters [a-z] upper/lower case are allowed.\n";
        else break;
    }
    if (location.empty()) return nullptr;
    auto tl = CStorage::CheckLocation(location);
    if (tl == CStorage::st_locations.end())
    {
        auto loc = std::make_shared<std::string>(location);
        CStorage::st_locations.push_back(loc);
        return loc;
    }
    else return *tl;
}

std::pair<CDate,CTime> CScanner::ScanDateAndTime ()
{
	while (true)
	{
		CTime time = CScanner::ScanTime();
		CDate date = CScanner::ScanDate();
		if (ETimeWrapper::Check_Time(time, date) == ETimeWrapper::Future)
		    return {date, time};
		std::cout << "ERROR: Time and date could not be in the past.\n";
	}
}

bool                             CScanner::CheckSyntax         (const std::string & text, const std::string & allowed)
{
    for (const auto & c : text)
    {
        if ((c < 'A' or c > 'z') and c != ' ')
        {
            if (!allowed.empty())
                for (const auto & f : allowed)
                    if (c == f) continue;
            return false;
        }

    }
    return true;
}
