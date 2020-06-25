//
// Created by Mykhailo on 01/06/2020.
//

#include "CStorage.hpp"

std::vector<std::shared_ptr<std::string>>            CStorage::st_locations          {};
std::vector<std::shared_ptr<CParticipant>>           CStorage::st_participants       {};

void                                                 CStorage::ListParticipantsNames ()
{
    std::cout << "-----------------------------------\n";
    for (size_t i = 1; i <= st_participants.size(); i++)
        std::cout << i << ". " << st_participants[i-1].get()->p_fullname << '\n';
    std::cout << "-----------------------------------\n";

}


void                                                 CStorage::ListLocations         ()
{
    std::cout << "-----------------------------------\n";
    for (size_t i = 1; i <= st_locations.size(); i++)
        std::cout << i << ". " << *st_locations[i-1] << '\n';
    std::cout << "-----------------------------------\n";
}

std::vector<std::shared_ptr<std::string>>::iterator  CStorage::CheckLocation         (const std::string & location)
{
    return std::find_if(st_locations.begin(), st_locations.end(),
                        [&location] (const auto & lc)
                        { return * lc == location; });
}

std::vector<std::shared_ptr<CParticipant>>::iterator CStorage::CheckParticipant      (const std::string &name)
{
    return std::find_if(st_participants.begin(), st_participants.end(),
                        [&name] (const auto & participant)
                        { return participant->p_fullname == name; } );
}

void                                                 CStorage::SaveStorage	         ()
{
	std::string to_save;
	for (const auto & location : st_locations)
	{
		to_save += *location;
		to_save += ';';
	}
	CSaverLoader::SaveStr(to_save);
	to_save.clear();
	for (const auto & participant : st_participants)
	{
		to_save += participant->p_fullname;
		to_save += ':';
		to_save += participant->p_info;
		to_save += ';';
	}
	CSaverLoader::SaveStr(to_save);
}

void 										         CStorage::LoadStorage			 ()
{
	for (const auto & location : CSaverLoader::LoadLocations())
		st_locations.push_back(std::make_shared<std::string>(location));
	for (const auto & participant : CSaverLoader::LoadParticipants())
		st_participants.push_back(std::make_shared<CParticipant>(
			CParticipant(participant.first, participant.second)));
}




