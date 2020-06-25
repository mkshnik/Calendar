//
// Created by Mykhailo Kuvshynov on 02.05.20.
//

#include "CApplication.hpp"

CApplication &                        CApplication::Run            ()
{
	Load();
    std::cout << "'Terminal calendar' by Mykhailo Kuvshynov (kuvshmyk@fit.cvut.cz) was successfully started :)\n"
                 "_|Welcome|_\n"
                 "Type 'help' and press 'Enter' for information about functionality.\n";
    a_show_events.Month();
    while (true)
    {
        try {
            if (!ExecuteCommand(GetCommand())) break;
        } catch (...) { Exit(); }
    }
    return *this;
}

std::vector<std::string>             CApplication::GetCommand     ()
{
    std::vector<std::string> command;
    command.resize(5);
    std::cout << ">> ";
    char16_t x;
    for (int i = 0; ;)
    {
        x = std::getchar();
        if      (command[0].empty()  && x == '\n') { std::cout << ">> "; continue; }
        else if (command[i].empty()  && (x == ' ' || x == '\t')) continue;
        else if (!command[i].empty() && (x == ' ' || x == '\t'))
        { i++; if(i > 4) command.resize(command.size() + 10); continue; }
        else if (x == '\n') break;
        else if (x == '\'')
        {
            command[i] += x;
            do {
                x = std::getchar();
                if (x == '\n')
                {
                    command.clear();
                    return command;
                }
                command[i] += x;
            } while(x != '\'');
            if (command.empty()) { i = 0; std::cout << ">> ";}
            else i++;
            continue;
        }
        command[i] += x;
    }
    return command;
}

bool                                 CApplication::ExecuteCommand (const std::vector<std::string> & command)
{
    std::string wrong_msg     = "Wrong parameter or syntax. Type 'help' to see all possible parameters.\n",
                not_found_msg = "Chosen event/alarm/reminder does not exist :(\n";

    switch (StrToCommand(command[0]))
    {
        case Commands::event:
            switch (StrToEventParam(command[1]))
            {
                case EventParams::add:
                    if (command[2].empty())
                        a_calendar.EventAdd();
                    else std::cout << wrong_msg;
                    break;
                case EventParams::list:
                    if (command[2].empty())
                        a_calendar.List();
                    else std::cout << wrong_msg;
                    break;
                default: std::cout << wrong_msg;
            }
            break;
    	case Commands::date:
			switch (StrToDateParams(command[1]))
			{
				case DateParams::now:
				    if (command[2].empty())
                        try {
                            a_show_events.Day(ETimeWrapper::CurrentDate());
                        } catch (...) { std::cout << wrong_msg; }
				    else std::cout << wrong_msg;
					break;
				case DateParams::info:
					if (command[3].empty() and CheckTextSyntax(command[2]))
						try {
							a_show_events.Day(
								ETimeWrapper::StrToDate(
									QuotedStrToStr(command[2])));
						} catch (...) { std::cout << wrong_msg; }
					else std::cout << wrong_msg;
					break;
				case DateParams::week:
					if (command[2].empty())
						a_show_events.Week();
					else std::cout << wrong_msg;
					break;
				case DateParams::month:
					if (command[2].empty())
					{ a_show_events.Month(); break; }
                default: std::cout << wrong_msg;
			}
			break;
		case Commands::remove:
			if (command[2].empty() && CheckTextSyntax(command[1])) {
				if (!a_calendar.EventRemove(QuotedStrToStr(command[1])))
					std::cout << not_found_msg;
			} else std::cout << wrong_msg;
			break;
		case Commands::edit:
			if (command[2].empty() && CheckTextSyntax(command[1]))
				if (a_calendar.EventEdit(QuotedStrToStr(command[1])))
					break;
			std::cout << wrong_msg;
			break;
        case Commands::move:
            if (command[2].empty() && CheckTextSyntax(command[1]))
                a_calendar.EventMove(QuotedStrToStr(command[1]));
            else std::cout << wrong_msg;
            break;
		case Commands::import:
			if (command[2].empty() && CheckTextSyntax(command[1])) {
				if (!a_calendar.EventImport(QuotedStrToStr(command[1])))
					std::cout << "File " + command[1] + " was not found.\n";
			} else std::cout << wrong_msg;
			break;
		case Commands::export_:
			if (command[3].empty() && CheckTextSyntax(command[1]) && CheckTextSyntax(command[2])) {
				if (!a_calendar.EventExport(QuotedStrToStr(command[1]), QuotedStrToStr(command[2])))
					std::cout << not_found_msg;
			} else std::cout << wrong_msg;
			break;
        case Commands::info:
            if (command[2].empty() && CheckTextSyntax(command[1])) {
                if (!a_calendar.EventInfo(QuotedStrToStr(command[1])))
                    std::cout << not_found_msg;
            } else std::cout << wrong_msg;
            break;
        case Commands::alarm:
            if (command[2].empty() && CheckTextSyntax(command[1])) {
                try { a_calendar.AlarmAdd(QuotedStrToTime(command[1])); }
                catch (...) { std::cout << wrong_msg; }
            } else std::cout << wrong_msg;
                break;
        case Commands::reminder:
            if (command[2].empty() && CheckTextSyntax(command[1]))
                a_calendar.ReminderAdd(QuotedStrToStr(command[1]));
            else std::cout << wrong_msg;
            break;
    	case Commands::location:
		    if (command[2].empty() && CheckTextSyntax(command[1]))
			    a_calendar.EventLocation(QuotedStrToStr(command[1]));
		    else std::cout << wrong_msg;
		    	break;
    	case Commands::save:
    		if (command[1].empty())
    			Save();
    		else std::cout << wrong_msg;
    		break;
        case Commands::exit:
            if (command[1].empty())
            { Exit(); break; }
            else std::cout << wrong_msg;
            break;
	    case Commands::help:
	    	if (command[1].empty())
	    		Help();
        default:
            std::cout << wrong_msg;
    }
    return true;
}

void							     CApplication::Exit           ()
{
	Save();
    std::cout << "Application was ended.\n"
                 "See you soon :)\n";
	exit(0);
}

CApplication &						 CApplication::Load     	  ()
{
	CSaverLoader::OpenForReading();
	CStorage::LoadStorage();
	a_calendar.LoadEvents();
	CSaverLoader::CloseLoader();
	std::cout << "Saved data was successfully loaded.\n";
	return *this;
}

CApplication &						 CApplication::Save     	  ()
{
	CSaverLoader::OpenForWriting();
	CStorage::SaveStorage();
	a_calendar.SaveEvents();
	CSaverLoader::CloseLoader();

	std::cout << "Your data was successfully saved.\n";
	return *this;
}

void                                 CApplication::Help           () const
{
	std::cout << "===============================================================\n"
			     "-> event [add, list] :\n"
				 "          'add'  - opens event editor to create a new event.\n"
	             "          'list' - list of all events/alarms and reminders.\n"
				 "-> date [now, info, week, month] :"
	             "          'now' - shows all events/reminder/alarms that are scheduled for today.\n"
			     "          'info [dd.mm.yyyy]' - shows all events/reminder/alarms that are scheduled for today.\n"
				 "          'week' - shows calendar in weekly format.\n"
	             "          'month' - shows calendar in monthly format.\n"
			     "-> remove <event name> - removes chosen event from the calendar.\n"
				 "-> edit <event name> - opens edit menu of chosen event.\n"
	             "-> move <event name> - opens move menu of chosen event.\n"
			     "-> import <file name> - import event from chosen file. (Calendar/imports/<file name>)\n"
		         "-> export <event name> <file name> - exports event from a file. (Calendar/exports/filename)\n"
		         "-> info <event name> - shows information of chosen event.\n"
		         "-> alarm <time> - sets an alarm for a time in a format 'hh.mm'.\n"
		         "-> reminder <name> - opens reminder settings.\n"
		         "-> location <location> - shows events that are happening at the chosen location (will search for substring in case of no-match).\n"
		         "-> save - will save all events to Calendar/saves/savedata.txt.\n"
		         "-> exit - will save all events and exit application\n";
}
