//
// Created by mkshnik on 01.06.20.
//

#include "CParticipant.hpp"

std::ostream& operator << (std::ostream& out, const CParticipant& participant)
{
    out << "   | * Name: " << participant.p_fullname << '\n';
    std::string line;
    bool firstline = true;
    if (!participant.p_info.empty())
    {
        std::cout << "   | * Info: ";
        for (auto i = participant.p_info.begin(); i != participant.p_info.end(); i++)
        {
            line += *i;
            if ((line.length() >= 30 && *i == ' ') || std::next(i) == participant.p_info.end())
            {
                if (firstline)
                {
                    out << line << '\n';
                    firstline = false;
                }
                else out << "   |         " << line << '\n';
                line.clear();
            }
        }
    }
    out << "   ======";
    return out;
}
