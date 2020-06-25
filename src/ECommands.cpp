//
// Created by mkshnik on 30.05.20.
//

#include "ECommands.hpp"


Commands    StrToCommand     (const std::string & command)
{
    if (command == "event")    return Commands::event;
    if (command == "date")     return Commands::date;
    if (command == "reminder") return Commands::reminder;
    if (command == "alarm")    return Commands::alarm;
    if (command == "show")     return Commands::show;
    if (command == "save")     return Commands::save;
    if (command == "info")     return Commands::info;
    if (command == "exit")     return Commands::exit;
	if (command == "remove")   return Commands::remove;
	if (command == "export")   return Commands::export_;
    if (command == "location") return Commands::location;
    if (command == "import")   return Commands::import;
	if (command == "edit")     return Commands::edit;
    if (command == "move")     return Commands::move;
    if (command == "help")     return Commands::help;
    else                       return Commands::wrong;
}

EventParams StrToEventParam (const std::string & command)
{
    if (command == "add")      return EventParams::add;
    if (command == "list")     return EventParams::list;
    else                       return EventParams::wrong;
}

DateParams  StrToDateParams (const std::string & command)
{
    if (command == "now")      return DateParams::now;
    if (command == "info")     return DateParams::info;
    if (command == "week")     return DateParams::week;
    if (command == "month")    return DateParams::month;
    else                       return DateParams::wrong;
}

std::string QuotedStrToStr  (const std::string & quoted)
{
    return quoted.substr(1, quoted.size() - 2);
}

CTime       QuotedStrToTime (const std::string & quoted)
{
    int m = 0, h = 0;
    char colon = ' ';
    if (sscanf(QuotedStrToStr(quoted).c_str(), "%d%c%d", &h, &colon, &m) != 3 || colon != ':' || quoted.length() != 7)
        throw (std::logic_error("Wrong syntax"));
    return CTime(h, m);
}

bool        CheckTextSyntax (const std::string & text)
{
    return text.length() > 2 &&
           text[0] == '\''   &&
           text[text.size()-1] == '\'';
}