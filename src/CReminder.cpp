//
// Created by Mykhailo on 05/06/2020.
//

#include "CReminder.hpp"

std::string                            CReminder::PrintType   () const
{
    return "  Reminder ";
}

void CReminder::GetInfo         () const
{
	std::cout << "========> Reminder <========\n"
	          << "# | "     <<  e_name          << " | \n"
	          << "# Time: " <<  e_time          <<    '\n'
	          << "# Date: " << *e_dates.begin() <<    '\n'
	          << "============================\n";
}

std::string 						   CReminder::SaveEvent() const
{
	std::string export__;
	export__ += "5;" + e_name + ';' + e_time.ExportTime()
		+  ';' +  e_dates.begin()->ExportDate() + ';';
	export__ += "N;";
	return export__;
}
