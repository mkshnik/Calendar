//
// Created by Mykhailo Kuvshynov on 05.05.20.
//

#include "CAlarm.hpp"

void CAlarm::GetInfo           () const
{
    std::cout << "========> Alarm <========\n"
              << "# Time: " <<  e_time          << '\n'
              << "# Date: " << *e_dates.begin() << '\n';
    if (e_name.substr(0, 5) != "Alarm")
        std::cout << "# Name: " << e_name << '\n';
    if (e_dates.size() > 1)
    {
        std::cout << "# Repeats " << PrintRepeat() << '\n';
        for (auto date = e_dates.begin(); date != e_dates.end(); date++)
            if (date != e_dates.begin())
                std::cout << "  @ " << *date << '\n';
    }
    std::cout << "=========================\n";
}

std::string                       CAlarm::SaveEvent         () const
{
    std::string export_;
    export_ += "4;" + e_name + ';' + e_time.ExportTime()
             + ';'  + e_dates.begin()->ExportDate() + ';';
    if (e_repeat != RepeatType::NoRepeat)
    {
        export_ += "A;";
        auto last_date = e_dates.end();
        last_date--;
        export_ += PrintRepeat() + ';' + last_date->ExportDate() + ';';
    } else export_ += "N;";
    return export_;
}

bool CAlarm::Advanced          ()
{
    std::cout << "You can set repeat for the following intervals:\n"
                 "1. Every day | 2. Every week\n"
                 "Press corresponding number to choose or '0' to cancel:\n";
    int num = CScanner::ScanNumber(0, 2);
    if (!num) return false;
    std::cout << "Repeat until:\n";
    CDate until = CScanner::ScanDate();
    if (until < *e_dates.begin())
    {
        std::cout << "ERROR: End date can't be earlier initial date\n"
                     "- Would you like to add repeat again?\n";
        if (!CScanner::ScanYorN()) return false;
        return Advanced();
    }
	SetRepeat(num, until);
    std::cout << "Repeat was successfully set :)\n"
                 "==============================\n";
    return true;
}

bool CAlarm::LoadAdvanced      (const std::vector<std::string> & info)
{
    int d, m, y, type;
    if (info[5] == "Daily") type = 1;
    else type = 2;
    sscanf(info[6].c_str(), "%d.%d.%d", &d, &m, &y);
    auto date = CDate(d, m, y);
	SetRepeat(type, date);
	return true;
}
